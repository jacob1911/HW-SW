#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "intrusion_detec.cpp"

enum class system_state
{
    inactive,
    active,
    alarmed
};

using steady_clock_type = std::chrono::steady_clock;

int get_pin(int num)
{
    return rand() % num;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    system_state alarm = system_state::inactive;

    // Wait for valid PIN
    while (alarm == system_state::inactive)
    {
        int pin = get_pin(10);
        alarm = (pin % 2 == 0) ? system_state::active : system_state::inactive;
        std::cout << "Pincode is: " << pin << std::endl;
    }

    std::cout << "System is active" << std::endl;

    while (true)
    {
        int signal[2] = {0};
        signal[0] = get_pin(6);

        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        signal[1] = get_pin(6);

        int camera_data[9][9] = {{0}};
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                camera_data[i][j] = get_pin(10);
            }
        }

        if (intrusion_detection(signal, camera_data))
        {
            std::cout << "Intrusion detected!" << std::endl;
            alarm = system_state::alarmed;

            auto start = steady_clock_type::now();
            while (alarm == system_state::alarmed)
            {
                alarm = (get_pin(10) % 2 == 0) ? system_state::active : system_state::alarmed;

                if (steady_clock_type::now() - start > std::chrono::seconds(10))
                {
                    alarm = system_state::inactive;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            std::cout << "Alarm deactivated" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    return 0;
}
