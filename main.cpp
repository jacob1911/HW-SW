#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "intrusion_detection.cpp"
#include "camera.h"
#include "sensor.h"
#include "valid_pin.cpp"

#define INTRUSION_THRESHOLD 1900

enum class alarm_type
{
    inactive,
    active,
    alarmed
};

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;

int main()
{
    // Initializing system
    srand(static_cast<unsigned>(time(0)));
    Sensor s1(60);
    Sensor s2(60);
    Camera c(120);

    int pin_attempts = 0;

    // Time tracking variables are initialized
    auto prev_time = Time::now();
    auto cur_time = Time::now();
    auto start_alarmed = Time::now();

    // Setting the system to initially be INACTIVE
    alarm_type alarm = alarm_type::inactive;

    while(true){

        // Switching execution based on state of system
        switch(alarm)
        {
        // The system is INACTIVE
        case alarm_type::inactive:{
            int pin = rand() % 10;
            std::cout << "Attempts pin code: " << pin << std::endl;
            if(valid_pin(pin)){
                std::cout << "Pin code is correct! System is now active." << std::endl;
                alarm = alarm_type::active;
            }
            else{
                std::cout << "Pin code was incorrect." << std::endl;
            }
            break;
        }
        
        // The system is ACTIVE
        case alarm_type::active:{
            // Time variables are updated
            cur_time = Time::now();
            int delta_time = std::chrono::duration_cast<ms>(cur_time - prev_time).count();
            prev_time = cur_time;

            // Sensors are updated and checked for new readings
            bool cam_check = c.update(delta_time);
            bool s1_check = s1.update(delta_time);
            bool s2_check = s2.update(delta_time);
            
            // If any new readings happend, an intrusion check is performed
            if(cam_check || s1_check || s2_check){
                // sum is calculated
                int sum = intrusion_detection(s1.read(), s2.read(), c.camera);
                std::cout << "Sum is " << sum << std::endl;
                
                // If the sum is greater than the instrusion threshold, the system is
                // set the the ALARMED state
                if(sum > INTRUSION_THRESHOLD){
                    std::cout << "Intrusion detected!" << std::endl;
                    alarm = alarm_type::alarmed;
                    start_alarmed = Time::now();
                    
                }
            }
            break;
        }

                
        // System is ALARMED
        case alarm_type::alarmed:{
            // Entering a pin can be attempted 3 times. Entering a correct pin
            // will mean leaving the ALARMED state
            if(pin_attempts < 3){
                int pin = rand() % 10;
                if(valid_pin(pin)){
                    alarm = alarm_type::active;
                    std::cout << "Correct pin entered." << std::endl; 
                }
                else{
                    std::cout << "Wrong pin entered." << std::endl;
                    pin_attempts++;
                    if(pin_attempts == 3){
                        std::cout << "Too many pin attempts. Please wait." << std::endl;
                    } 
                }
            }
            // If 10 seconds pass while in the alarmed state, we will exit it
            if (Time::now() - start_alarmed > std::chrono::seconds(10))
            {
                std::cout << "Broke after waiting 10 seconds." << std::endl;
                alarm = alarm_type::active;
            }
            // If the ALARMED state is exited
            if(alarm == alarm_type::active){
                std::cout << "Alarm deactivated." << std::endl;
                // Resetting pin attempts
                pin_attempts = 0;
            }                
            break;
        }
            
        
        default:
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
