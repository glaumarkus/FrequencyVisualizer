#include <LEDController.h>
#include <LEDVisualizer.h>


int main()
{

    LEDController* controller = controller->Get();
    
    LEDVisualizer2 vis(1.0f / 40.0f, 0.1f, {0, 1, 2, 3, 4, 5, 6});
    std::vector<float> tests {0.1, 0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.99};

    for (auto f : tests)
    {
        vis.ProcessInput(f);
        vis.Render();
        controller->Render();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}