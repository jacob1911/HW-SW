#pragma once
#include<cstdlib>

class Camera{
private:
    int time_wait;
    int time_acc;
public:
    int camera[9][9];

    Camera(int _time_wait){
        time_wait = _time_wait;
        time_acc = time_wait;
    }

    void update_camera(int delta_time){
        time_acc += delta_time;
        
        if(time_acc >= time_wait){
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    camera[i][j] = rand() % 10;
                }
            }
            time_acc = 0;
        }
    }
};

