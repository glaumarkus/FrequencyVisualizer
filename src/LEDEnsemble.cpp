#include <signal.h>
#include <LEDEnsemble.h>
#include <LEDController.h>

void my_handler(int s){
           printf("Caught signal %d\n",s);
           exit(1); 

}

Ensemble::Ensemble(Audio::Streamer* streamer) : 
    m_streamer(streamer),
    m_stream(streamer->GetFFTSamples()),
    m_state(State::NotInitialized)
{
	
    // add visualizers
	std::vector<int> v0{0,19,20,39,40,59,60,79,80,99,100};
	std::vector<int> v1{1,18,21,38,41,58,61,78,81,98,101};
	std::vector<int> v2{2,17,22,37,42,57,62,77,82,97,102};
	std::vector<int> v3{3,16,23,36,43,56,63,76,83,96,103};
	std::vector<int> v4{4,15,24,35,44,55,64,75,84,95,104};
	std::vector<int> v5{5,14,25,34,45,54,65,74,85,94,105};
	std::vector<int> v6{6,13,26,33,46,53,66,73,86,93,106};
	std::vector<int> v7{7,12,27,32,47,52,67,72,87,92,107};
	std::vector<int> v8{8,11,28,31,48,51,68,71,88,91,108};
	std::vector<int> v9{9,10,29,30,49,50,69,70,89,90,109};

    m_visualizers.emplace_back(1.0f / 10, 0.5f, v0);
	m_visualizers.emplace_back(2.0f / 10, 0.5f, v1);
	m_visualizers.emplace_back(3.0f / 10, 0.5f, v2);
	m_visualizers.emplace_back(4.0f / 10, 0.5f, v3);
	m_visualizers.emplace_back(5.0f / 10, 0.5f, v4);
	m_visualizers.emplace_back(6.0f / 10, 0.5f, v5);
	m_visualizers.emplace_back(7.0f / 10, 0.5f, v6);
	m_visualizers.emplace_back(8.0f / 10, 0.5f, v7);
	m_visualizers.emplace_back(9.0f / 10, 0.5f, v8);
	m_visualizers.emplace_back(10.0f / 10, 0.5f, v9);
}

Ensemble::~Ensemble()
{
    Stop();
}

void Ensemble::AddVisualizer(const LEDVisualizer2& vis)
{
    m_visualizers.emplace_back(vis);
}

bool Ensemble::Initialize()
{
    m_state = State::ReadyToRun;
    return true;
}

void Ensemble::Start()
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

void Ensemble::Stop()
{}

void Ensemble::ProcessInput()
{
	/*
    // check if CTRL+C
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
	*/
}

void Ensemble::Update()
{}

void Ensemble::Render()
{
    
    // allocate memory for bins
    std::vector<float> bins;
    bins.reserve(m_visualizers.size());

    // check state
    if (m_streamer->GetState() != Audio::A_Recorder::State::Running)
	{   
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
		return;
	}


    // wait for input
    m_stream.wait();
    auto block = m_stream.pop_front();

    // make bins
	int i = 0;
	int start = 0;
	int end;

	// append max element for bin
	while (i < m_visualizers.size())
	{
		end = static_cast<int>(floorf(std::pow(i + 1, SCALE_EXP)));

		bins.emplace_back(
			*std::max_element(&block.at(start + START), &block.at(end + START))
		);
		start = end;
		i++;
	}



    
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
				// if smaller gradually decrease
				else if (delta < 0.0f)
					first += delta < MAX_DECAY ? MAX_DECAY : delta;

				return first;
			}
		);
		
	}



    // process bins
    for (int i = 0; i < m_visualizers.size(); i++)
    {
        m_visualizers[i].ProcessInput(bins[i]);
        m_visualizers[i].Render();
    }
    


    // render controller
	auto controller = GetController();
    controller->Render();




}
