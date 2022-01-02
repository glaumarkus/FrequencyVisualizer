#include <signal.h>
#include <LEDEnsemble.h>
#include <LEDController.h>


Ensemble::Ensemble(LEDConfiguration& config, LEDController& controller, Audio::Streamer* streamer) : 
    m_streamer(streamer),
    m_stream(streamer->GetFFTSamples()),
    m_state(State::NotInitialized),
	m_controller(controller),
	m_config(config)
{
	
    // add visualizers
	std::vector<int> v0{0,79,80,159,160,239,240,319,320,399,400,479,480,559,560};
	std::vector<int> v1{1,78,81,158,161,238,241,318,321,398,401,478,481,558,561};
	std::vector<int> v2{2,77,82,157,162,237,242,317,322,397,402,477,482,557,562};
	std::vector<int> v3{3,76,83,156,163,236,243,316,323,396,403,476,483,556,563};
	std::vector<int> v4{4,75,84,155,164,235,244,315,324,395,404,475,484,555,564};
	std::vector<int> v5{5,74,85,154,165,234,245,314,325,394,405,474,485,554,565};
	std::vector<int> v6{6,73,86,153,166,233,246,313,326,393,406,473,486,553,566};
	std::vector<int> v7{7,72,87,152,167,232,247,312,327,392,407,472,487,552,567};
	std::vector<int> v8{8,71,88,151,168,231,248,311,328,391,408,471,488,551,568};
	std::vector<int> v9{9,70,89,150,169,230,249,310,329,390,409,470,489,550,569};
	std::vector<int> v10{10,69,90,149,170,229,250,309,330,389,410,469,490,549,570};
	std::vector<int> v11{11,68,91,148,171,228,251,308,331,388,411,468,491,548,571};
	std::vector<int> v12{12,67,92,147,172,227,252,307,332,387,412,467,492,547,572};
	std::vector<int> v13{13,66,93,146,173,226,253,306,333,386,413,466,493,546,573};
	std::vector<int> v14{14,65,94,145,174,225,254,305,334,385,414,465,494,545,574};
	std::vector<int> v15{15,64,95,144,175,224,255,304,335,384,415,464,495,544,575};
	std::vector<int> v16{16,63,96,143,176,223,256,303,336,383,416,463,496,543,576};
	std::vector<int> v17{17,62,97,142,177,222,257,302,337,382,417,462,497,542,577};
	std::vector<int> v18{18,61,98,141,178,221,258,301,338,381,418,461,498,541,578};
	std::vector<int> v19{19,60,99,140,179,220,259,300,339,380,419,460,499,540,579};
	std::vector<int> v20{20,59,100,139,180,219,260,299,340,379,420,459,500,539,580};
	std::vector<int> v21{21,58,101,138,181,218,261,298,341,378,421,458,501,538,581};
	std::vector<int> v22{22,57,102,137,182,217,262,297,342,377,422,457,502,537,582};
	std::vector<int> v23{23,56,103,136,183,216,263,296,343,376,423,456,503,536,583};
	std::vector<int> v24{24,55,104,135,184,215,264,295,344,375,424,455,504,535,584};
	std::vector<int> v25{25,54,105,134,185,214,265,294,345,374,425,454,505,534,585};
	std::vector<int> v26{26,53,106,133,186,213,266,293,346,373,426,453,506,533,586};
	std::vector<int> v27{27,52,107,132,187,212,267,292,347,372,427,452,507,532,587};
	std::vector<int> v28{28,51,108,131,188,211,268,291,348,371,428,451,508,531,588};
	std::vector<int> v29{29,50,109,130,189,210,269,290,349,370,429,450,509,530,589};
	std::vector<int> v30{30,49,110,129,190,209,270,289,350,369,430,449,510,529,590};
	std::vector<int> v31{31,48,111,128,191,208,271,288,351,368,431,448,511,528,591};
	std::vector<int> v32{32,47,112,127,192,207,272,287,352,367,432,447,512,527,592};
	std::vector<int> v33{33,46,113,126,193,206,273,286,353,366,433,446,513,526,593};
	std::vector<int> v34{34,45,114,125,194,205,274,285,354,365,434,445,514,525,594};
	std::vector<int> v35{35,44,115,124,195,204,275,284,355,364,435,444,515,524,595};
	std::vector<int> v36{36,43,116,123,196,203,276,283,356,363,436,443,516,523,596};
	std::vector<int> v37{37,42,117,122,197,202,277,282,357,362,437,442,517,522,597};
	std::vector<int> v38{38,41,118,121,198,201,278,281,358,361,438,441,518,521,598};
	std::vector<int> v39{39,40,119,120,199,200,279,280,359,360,439,440,519,520,599};

	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.03f, v0));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.05f, v1));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.07f, v2));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.1f, v3));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.12f, v4));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.15f, v5));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.17f, v6));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.2f, v7));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.23f, v8));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.25f, v9));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.28f, v10));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.3f, v11));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.33f, v12));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.35f, v13));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.38f, v14));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.4f, v15));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.42f, v16));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.45f, v17));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.47f, v18));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.5f, v19));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.53f, v20));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.55f, v21));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.57f, v22));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.6f, v23));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.62f, v24));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.65f, v25));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.68f, v26));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.7f, v27));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.72f, v28));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.75f, v29));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.78f, v30));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.8f, v31));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.82f, v32));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.85f, v33));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.88f, v34));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.9f, v35));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.93f, v36));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.95f, v37));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 0.97f, v38));
	m_visualizers.emplace_back(LEDVisualizer2(m_controller, 1.0f, v39));
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
{}

void Ensemble::Update()
{}

void Ensemble::Render()
{
    
    // allocate memory for bins
    std::vector<float> bins;
    bins.reserve(m_visualizers.size());

    // check state
    if (m_streamer->GetState() != Audio::Recorder::State::Running)
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
		end = static_cast<int>(floorf(std::pow(i + 1, m_config.exp)));

		bins.emplace_back(
			*std::max_element(&block.at(start + m_config.start), &block.at(end + m_config.start))
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
			[m_config.max_dec](float first, float second)
			{
				float delta = second - first;
				// if delta bigger than 0, then only copy
				if (delta > 0.0f)
					first = second;
				// if smaller gradually decrease
				else if (delta < 0.0f)
					first += delta < m_config.max_dec ? m_config.max_dec : delta;

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
	m_controller.Render();

}
