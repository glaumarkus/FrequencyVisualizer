#include <FFTVisualizer.h>
#include <LEDController.h>


CApp::CApp(uint16_t width, uint16_t height, Audio::Streamer* streamer) :
    m_width(width),
    m_heigth(height),
	m_streamer(streamer),
	m_stream(streamer->GetFFTSamples()),
    m_window(nullptr),
    m_renderer(nullptr),
	/*
	m_font(nullptr),
	m_fontsurface(nullptr),
	m_fonttexture(nullptr),
	*/
    m_state(CApp::State::NotInitialized)
	//m_hw(1.0f / 40.0f, 0.1f, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
	//m_hw(1.0f / 40.0f, 0.1f, {0, 1, 2, 3, 4, 5, 6})
{
	// add my 10 strips
	m_visualizers.emplace_back(LEDVisualizer2(1.0f / 10, 0.5f, {0,19,20,39,40,59,60,79,80,99,100}));
	m_visualizers.emplace_back(LEDVisualizer2(2.0f / 10, 0.5f, {1,18,21,38,41,58,61,78,81,98,101}));
	m_visualizers.emplace_back(LEDVisualizer2(3.0f / 10, 0.5f, {2,17,22,37,42,57,62,77,82,97,102}));
	m_visualizers.emplace_back(LEDVisualizer2(4.0f / 10, 0.5f, {3,16,23,36,43,56,63,76,83,96,103}));
	m_visualizers.emplace_back(LEDVisualizer2(5.0f / 10, 0.5f, {4,15,24,35,44,55,64,75,84,95,104}));
	m_visualizers.emplace_back(LEDVisualizer2(6.0f / 10, 0.5f, {5,14,25,34,45,54,65,74,85,94,105}));
	m_visualizers.emplace_back(LEDVisualizer2(7.0f / 10, 0.5f, {6,13,26,33,46,53,66,73,86,93,106}));
	m_visualizers.emplace_back(LEDVisualizer2(8.0f / 10, 0.5f, {7,12,27,32,47,52,67,72,87,92,107}));
	m_visualizers.emplace_back(LEDVisualizer2(9.0f / 10, 0.5f, {8,11,28,31,48,51,68,71,88,91,108}));
	m_visualizers.emplace_back(LEDVisualizer2(10.0f / 10, 0.5f, {9,10,29,30,49,50,69,70,89,90,109}));
}

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
	SDL_Rect bin_rect{
		BIN_MARGIN,	// x 
		BIN_MARGIN, // y
		bar_width - 2 * BIN_MARGIN, 	// w
		bar_height	// h
	};

	// create tmp vector to store bins
	std::vector<float> bins;
	bins.reserve(BINS);

	// check if streamer has correct state
	if (m_streamer->GetState() != Audio::A_Recorder::State::Running)
	{
		auto mTicksCount = SDL_GetTicks();
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 32))
		;
		return;
	}

	//t.Update("Waiting for Popping");

	// wait until new sample available // this blocks from exiting.. 
	m_stream.wait();

	Timer t("Render Loop");

	// pop sample
	auto block = m_stream.pop_front();

	t.Update("Popped");

	// reduce to bins
	int i = 0;
	int start = 0;
	int end;

	// append max element for bin
	while (i < BINS)
	{
		end = static_cast<int>(floorf(std::pow(i + 1, SCALE_EXP)));

		bins.emplace_back(
			*std::max_element(&block.at(start + START), &block.at(end + START))
		);
		start = end;
		i++;
	}

	t.Update("Made bins");

	// if empty, then this is first sample
	if (m_lastSamples.empty())
		m_lastSamples = bins;
	else
	{
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
					//first += delta > MAX_INC ? MAX_INC : delta;
				// if smaller gradually decrease
				else if (delta < 0.0f)
					first += delta < MAX_DECAY ? MAX_DECAY : delta;

				return first;
			}
		);
		
	}

	t.Update("Transformed bins");
	

	for (int i = 0; i < BINS; i++)
	{
		// replace with actual value
		const float& f = m_lastSamples[i];

		// led strip		
		if (i <  10)
		{
			m_visualizers[i].ProcessInput(f);
		}

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

	t.Update("Rendered SDL");
	for (auto& c : m_visualizers)
		c.Render();
	t.Update("Updated Visualizers");
	led_controller.Render();
	t.Update("Rendered visualizers");

	// swap buffers
	SDL_RenderPresent(m_renderer);

	//m_state = State::Stopped;

}

void CApp::Stop()
{	
	// Delete texture
	/*
	SDL_FreeSurface(m_fontsurface);
	SDL_DestroyTexture(m_fonttexture);
	*/

	// Stop SDL
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

