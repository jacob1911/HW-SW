#include <stdio.h>


bool intrusion_detection(int sensor_data_1, int sensor_data_2, int camera_data[9][9]){
    int sum=0;
    for(int i=0;i<9;i++){
        for(int j=0;i<9;i++){
            sum += sensor_data_1+sensor_data_2*camera_data[i][j];
        }
    }
 
}