#include <stdio.h>
#include <iostream>

bool intrusion_detection(int sensor_data[2], int camera_data[9][9])
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sum += (sensor_data[0] + sensor_data[1]) * camera_data[i][j];
        }
    }
    std::cout << "Sum is: " << sum << std::endl;
    return sum > 1900 ? true : false;
}

// int main()
// {

//     int signal[2] = {3, 4};
    // int camera_data[9][9] = {
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5},
    //     {5, 5, 5, 5, 5, 5, 5, 5, 5}};

//     if (intrusion_detection(signal, camera_data))
//     {
//         std::cout << "Intrusion detected!" << std::endl;
//     }
//     return 0;
// }