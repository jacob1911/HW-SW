#include <stdio.h>
#include <stdlib.h>
#include <iostream>  
#include <chrono>
#include <ctime>
#include <thread>
#include "intrusion_detec.cpp"

enum class alarm_type{
    inactive,
    active,
    alarmed
};
using clock = std::chrono::steady_clock;

//Random Pin generator between 0-num
int get_pin(int num){
    return rand() % num;
}

int main(){
   
    alarm_type alarm = alarm_type::inactive; 

    // Something that checks for the valid P
    while(alarm == alarm_type::inactive){
        int pin = get_pin(10);
        pin % 2 == 0? alarm = alarm_type::active : alarm = alarm_type::inactive; 
            std::cout << "Pincode is: "<< pin << std::endl;
    }
   std::cout << "System is active " << std::endl;
    
    

    while(true){
        int signal[2]={0}; 
        signal[0] = get_pin(6);

        // ----------time.sleep(60ms)----------
        std::this_thread::sleep_for(std::chrono::milliseconds(60));


        signal[1] = get_pin(6);
        int camera_data[9][9] = {{0}};
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                camera_data[i][j] = get_pin(10);
            }
        }
        if (intrusion_detection(signal, camera_data)){
            std::cout << "Intrusion detected!" << std::endl;
            alarm = alarm_type::alarmed;
            
            auto start = clock::now();
            while (alarm == alarm_type::alarmed)
            {
                // Break if pin is correct
                get_pin(10) % 2 == 0? alarm = alarm_type::active : alarm = alarm_type::alarmed;

                //Break if after 10 seconds
                if(clock::now() - start > std::chrono::seconds(10)){
                    alarm = alarm_type::inactive;
                }
                

            }
            std::cout << "Alarm deactivated" << std::endl;
        }
        
        // ----------time.sleep(60ms)----------
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
    return 0;
}
