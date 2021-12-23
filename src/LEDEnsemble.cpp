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
	std::vector<int> v0{0,79,80,159,160,239,240};
	std::vector<int> v1{1,78,81,158,161,238,241};
	std::vector<int> v2{2,77,82,157,162,237,242};
	std::vector<int> v3{3,76,83,156,163,236,243};
	std::vector<int> v4{4,75,84,155,164,235,244};
	std::vector<int> v5{5,74,85,154,165,234,245};
	std::vector<int> v6{6,73,86,153,166,233,246};
	std::vector<int> v7{7,72,87,152,167,232,247};
	std::vector<int> v8{8,71,88,151,168,231,248};
	std::vector<int> v9{9,70,89,150,169,230,249};
	std::vector<int> v10{10,69,90,149,170,229,250};
	std::vector<int> v11{11,68,91,148,171,228,251};
	std::vector<int> v12{12,67,92,147,172,227,252};
	std::vector<int> v13{13,66,93,146,173,226,253};
	std::vector<int> v14{14,65,94,145,174,225,254};
	std::vector<int> v15{15,64,95,144,175,224,255};
	std::vector<int> v16{16,63,96,143,176,223,256};
	std::vector<int> v17{17,62,97,142,177,222,257};
	std::vector<int> v18{18,61,98,141,178,221,258};
	std::vector<int> v19{19,60,99,140,179,220,259};
	std::vector<int> v20{20,59,100,139,180,219,260};
	std::vector<int> v21{21,58,101,138,181,218,261};
	std::vector<int> v22{22,57,102,137,182,217,262};
	std::vector<int> v23{23,56,103,136,183,216,263};
	std::vector<int> v24{24,55,104,135,184,215,264};
	std::vector<int> v25{25,54,105,134,185,214,265};
	std::vector<int> v26{26,53,106,133,186,213,266};
	std::vector<int> v27{27,52,107,132,187,212,267};
	std::vector<int> v28{28,51,108,131,188,211,268};
	std::vector<int> v29{29,50,109,130,189,210,269};
	std::vector<int> v30{30,49,110,129,190,209,270};
	std::vector<int> v31{31,48,111,128,191,208,271};
	std::vector<int> v32{32,47,112,127,192,207,272};
	std::vector<int> v33{33,46,113,126,193,206,273};
	std::vector<int> v34{34,45,114,125,194,205,274};
	std::vector<int> v35{35,44,115,124,195,204,275};
	std::vector<int> v36{36,43,116,123,196,203,276};
	std::vector<int> v37{37,42,117,122,197,202,277};
	std::vector<int> v38{38,41,118,121,198,201,278};
	std::vector<int> v39{39,40,119,120,199,200,279};
	
	m_visualizers.emplace_back(LEDVisualizer2(1.0f / 40, 1, v0));
	m_visualizers.emplace_back(LEDVisualizer2(2.0f / 40, 1, v1));
	m_visualizers.emplace_back(LEDVisualizer2(3.0f / 40, 1, v2));
	m_visualizers.emplace_back(LEDVisualizer2(4.0f / 40, 1, v3));
	m_visualizers.emplace_back(LEDVisualizer2(5.0f / 40, 1, v4));
	m_visualizers.emplace_back(LEDVisualizer2(6.0f / 40, 1, v5));
	m_visualizers.emplace_back(LEDVisualizer2(7.0f / 40, 1, v6));
	m_visualizers.emplace_back(LEDVisualizer2(8.0f / 40, 1, v7));
	m_visualizers.emplace_back(LEDVisualizer2(9.0f / 40, 1, v8));
	m_visualizers.emplace_back(LEDVisualizer2(10.0f / 40, 1, v9));
	m_visualizers.emplace_back(LEDVisualizer2(11.0f / 40, 1, v10));
	m_visualizers.emplace_back(LEDVisualizer2(12.0f / 40, 1, v11));
	m_visualizers.emplace_back(LEDVisualizer2(13.0f / 40, 1, v12));
	m_visualizers.emplace_back(LEDVisualizer2(14.0f / 40, 1, v13));
	m_visualizers.emplace_back(LEDVisualizer2(15.0f / 40, 1, v14));
	m_visualizers.emplace_back(LEDVisualizer2(16.0f / 40, 1, v15));
	m_visualizers.emplace_back(LEDVisualizer2(17.0f / 40, 1, v16));
	m_visualizers.emplace_back(LEDVisualizer2(18.0f / 40, 1, v17));
	m_visualizers.emplace_back(LEDVisualizer2(19.0f / 40, 1, v18));
	m_visualizers.emplace_back(LEDVisualizer2(20.0f / 40, 1, v19));
	m_visualizers.emplace_back(LEDVisualizer2(21.0f / 40, 1, v20));
	m_visualizers.emplace_back(LEDVisualizer2(22.0f / 40, 1, v21));
	m_visualizers.emplace_back(LEDVisualizer2(23.0f / 40, 1, v22));
	m_visualizers.emplace_back(LEDVisualizer2(24.0f / 40, 1, v23));
	m_visualizers.emplace_back(LEDVisualizer2(25.0f / 40, 1, v24));
	m_visualizers.emplace_back(LEDVisualizer2(26.0f / 40, 1, v25));
	m_visualizers.emplace_back(LEDVisualizer2(27.0f / 40, 1, v26));
	m_visualizers.emplace_back(LEDVisualizer2(28.0f / 40, 1, v27));
	m_visualizers.emplace_back(LEDVisualizer2(29.0f / 40, 1, v28));
	m_visualizers.emplace_back(LEDVisualizer2(30.0f / 40, 1, v29));
	m_visualizers.emplace_back(LEDVisualizer2(31.0f / 40, 1, v30));
	m_visualizers.emplace_back(LEDVisualizer2(32.0f / 40, 1, v31));
	m_visualizers.emplace_back(LEDVisualizer2(33.0f / 40, 1, v32));
	m_visualizers.emplace_back(LEDVisualizer2(34.0f / 40, 1, v33));
	m_visualizers.emplace_back(LEDVisualizer2(35.0f / 40, 1, v34));
	m_visualizers.emplace_back(LEDVisualizer2(36.0f / 40, 1, v35));
	m_visualizers.emplace_back(LEDVisualizer2(37.0f / 40, 1, v36));
	m_visualizers.emplace_back(LEDVisualizer2(38.0f / 40, 1, v37));
	m_visualizers.emplace_back(LEDVisualizer2(39.0f / 40, 1, v38));
	m_visualizers.emplace_back(LEDVisualizer2(40.0f / 40, 1, v39));
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
