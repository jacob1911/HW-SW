#pragma once
#include<cstdlib>

class Sensor{
private:
    int time_wait;
    int time_acc;
    int measurement;
    
public:
    Sensor(int _time_wait){
        time_wait = _time_wait;
        time_acc = time_wait;
    }

    int get_reading(int delta_time){
        time_acc += delta_time;
        if(time_acc >= time_wait){
            measurement = rand() % 6;
            time_acc = 0;
        }
        return measurement;
    }
};

