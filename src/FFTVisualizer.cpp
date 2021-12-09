#include <FFTVisualizer.h>


CApp::CApp(uint16_t width, uint16_t height, tsqueue<Audio::sample_block>& stream) :
    m_width(width),
    m_heigth(height),
	m_stream(stream),
    m_window(nullptr),
    m_renderer(nullptr),
	m_font(nullptr),
	m_fontsurface(nullptr),
	m_fonttexture(nullptr),
    m_state(CApp::State::NotInitialized)
{}

CApp::~CApp()
{
	Stop();
}

bool CApp::Initialize()
{
	// Initialize SDL
	auto ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	m_window = SDL_CreateWindow(
		"FFT Spectrum", // Window title
		100,	        // Top left x-coordinate of window
		100,	        // Top left y-coordinate of window
		m_width,        // Width of window
		m_heigth,       // Height of window
		0		        // Flags (0 for no flags set)
	);

	if (!m_window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	
	// Create SDL renderer
	m_renderer = SDL_CreateRenderer(
		m_window,                                           // Window to create renderer for
		-1,		                                            // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!m_renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// render font & surface
	TTF_Init();
	m_font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoOblique.ttf", FONT_SIZE);
	if (!m_font)
	{
		SDL_Log("Failed to load font: %s", SDL_GetError());
		return false;
	}
	m_fontsurface = TTF_RenderText_Solid(m_font, "20 - 50   50 - 150   150 - 250", SDL_Color{255,255,255});
	m_fonttexture = SDL_CreateTextureFromSurface(m_renderer, m_fontsurface);

	// Update State
	m_state = State::ReadyToRun;

	return true;

}

void CApp::Start()
{
	// is in runnable state?
	if (!(m_state == State::ReadyToRun))
	{
		std::cerr << "Failed to start app, incorrect state!\n";
		return;
	}
	m_state = State::Running;

	// main loop
	while (m_state == State::Running)
	{
		ProcessInput();
		Update();
		Render();
	}

}

void CApp::ProcessInput()
{
	// SDL Events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_state = State::Stopped;
				break;
		}
	}
	
	// Keyboard Events
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		m_state = State::Stopped;
		
}

void CApp::Update()
{
}

void CApp::Render()
{
	// Clear background
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// how wide is bar?
	int bar_width = m_width  / BINS;

	// how high is bar?
	int bar_height = m_heigth - (2 * BIN_MARGIN);

	// Set for later drawing
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_Rect bin_rect{
		BIN_MARGIN,	// x 
		BIN_MARGIN, // y
		bar_width - 2 * BIN_MARGIN, 	// w
		bar_height	// h
	};

	// create tmp vector to store bins
	std::vector<float> bins;
	bins.reserve(BINS);

	// wait until new sample available // this blocks from exiting.. 
	m_stream.wait();

	/*
	if (m_stream.empty())
	{
		auto mTicksCount = SDL_GetTicks();
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 32))
		;
		return;
	}
	*/

	// pop sample
	auto block = m_stream.pop_front();

	// reduce to bins
	int i = 0;
	auto start = block.begin();

	// append max element for bin
	while (i < BINS)
	{
		int num_samples_for_bin = static_cast<int>(std::pow(i + 1, SCALE_EXP));
		auto end = start + num_samples_for_bin;

		bins.emplace_back(
			*std::max_element(start, end)
		);
		start = end;
		i++;
	}

	// if empty, then this is first sample
	if (m_lastSamples.empty())
		m_lastSamples = bins;
	else
	{

		/*
		for (size_t i = 0; i < bins.size(); i++)
		{
			float delta = bins[i] - m_lastSamples[i];

			// if delta bigger than 0, then only copy
			if (delta > 0.0f)
				m_lastSamples[i] = bins[i];
			// if smaller gradually decrease
			else if (delta < 0.0f)
				m_lastSamples[i] += delta < -0.01f ? -0.01f : delta;
			 
		}
		*/

		std::transform(
			m_lastSamples.begin(), m_lastSamples.end(),
			bins.begin(),
			m_lastSamples.begin(),
			[](float first, float second)
			{
				float delta = second - first;
				// if delta bigger than 0, then only copy
				if (delta > 0.0f)
					first = second;
				// if smaller gradually decrease
				else if (delta < 0.0f)
					first += delta < -0.01f ? -0.01f : delta;

				return first;
			}
		);
		
	}
	

	for (int i = 0; i < BINS; i++)
	{
		// replace with actual value
		const float& f = m_lastSamples[i];
	
		// heigth of bar
		bin_rect.h = bar_height * f;

		// starting position
		bin_rect.x = BIN_MARGIN + i * bar_width;
		bin_rect.y = bar_height - bin_rect.h + BIN_MARGIN;

		// set render color
		SDL_SetRenderDrawColor(
			m_renderer, 
			125, 
			255 * sinf(PI / 2 * ( static_cast<float>(i + 1) / BINS)), 
			255 * cosf(PI / 2 * ( static_cast<float>(i + 1) / BINS)), 
			255
		);

		// render
		SDL_RenderFillRect(m_renderer, &bin_rect);


	}

	// test text
	// SDL_Rect msg_rect {0,0,m_width,20};
	// SDL_RenderCopy(m_renderer, m_fonttexture, nullptr, &msg_rect);

	// swap buffers
	SDL_RenderPresent(m_renderer);
	

}

void CApp::Stop()
{	
	// Delete texture
	SDL_FreeSurface(m_fontsurface);
	SDL_DestroyTexture(m_fonttexture);
	
	// Stop SDL
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

