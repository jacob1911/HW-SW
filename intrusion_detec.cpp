#include <stdio.h>


bool intrusion_detection(int sensor_data[2], int camera_data[9][9]){
    int sum=0;
    for(int i=0;i<9;i++){
        for(int j=0;i<9;i++){
            sum += (sensor_data[0]+sensor_data[1])*camera_data[i][j];
        }
    }
    std::cout << "Sum is" << sum << std::endl;
    return sum > 1900? true : false;
 
}