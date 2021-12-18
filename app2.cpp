#include <LEDController.h>
#include <LEDVisualizer.h>


int main()
{

    for (int i = 0; i < 21; i++)
    {
        
        LEDVisualizer2 vis(static_cast<float>(i) / 21.0f, 1.0f, {0, 1, 2, 3, 4, 5, 6, 7, 8});
        std::vector<float> tests {1.0f};

        for (auto f : tests)
        {
            vis.ProcessInput(f);
            vis.Render();
            auto controller = GetController();
            controller->Render();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

    }


    return 0;
}