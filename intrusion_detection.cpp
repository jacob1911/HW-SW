int intrusion_detection(int s1, int s2, int camera_data[9][9])
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sum += (s1 + s2) * camera_data[i][j];
        }
    }
    return sum;
}