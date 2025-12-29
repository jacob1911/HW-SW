#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "intrusion_detection.cpp"
#include "camera.h"
#include "sensor.h"

enum class system_state
{
    inactive,
    active,
    alarmed
};

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;


int delta_time;

int main()
{
    srand(static_cast<unsigned>(time(0)));
    Sensor s1(60);
    Sensor s2(60);
    Camera c(120);

    system_state alarm = system_state::inactive;

    // Wait for valid PIN
    while (alarm == system_state::inactive)
    {
        int pin = rand() % 10;
        alarm = (pin % 2 == 0) ? system_state::active : system_state::inactive;
        std::cout << "Pincode is: " << pin << std::endl;
    }

    std::cout << "System is active" << std::endl;

    auto prev_time = Time::now();
    auto cur_time = Time::now();

    while (true)
    {
        cur_time = Time::now();
        delta_time = std::chrono::duration_cast<ms>(cur_time - prev_time).count();
        prev_time = cur_time;
        c.update_camera(delta_time);
        int sum = intrusion_detection(s1.get_reading(delta_time), s2.get_reading(delta_time), c.camera);
        std::cout << "Sum is " << sum << std::endl;
        if (sum > 1900)
        {
            std::cout << "Intrusion detected!" << std::endl;
            alarm = system_state::alarmed;
            auto start = Time::now();

            while (alarm == system_state::alarmed)
            {
                alarm = ((rand() % 2) == 0) ? system_state::active : system_state::alarmed;

                if (Time::now() - start > std::chrono::milliseconds(10))
                {
                    std::cout << "Broke because of 10seconds";
                    alarm = system_state::inactive;
                }

                // std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            std::cout << "Alarm deactivated" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    return 0;
}
