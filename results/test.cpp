#include<cstdio>
#include "intrusion_detection.cpp"

int main(){
    int i, j;
    int s1, s2;
    int cam[9][9];
    int sum;
    int comp;
    FILE *in, *golden;
    in = fopen("in.dat", "r");
    golden = fopen("results.golden.dat", "r");
    
    for(int n = 0; n < 5; n++){
        fscanf(in, "%d", &s1);
        fscanf(in, "%d", &s2);
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                fscanf(in, "%d", &cam[i][j]);
            }
        }

        sum = intrusion_detection(s1, s2, cam);
        fscanf(golden, "%d", &comp);
        if(sum != comp){
            printf("FAIL");
            fclose(in);
            fclose(golden);
            return 1;
        }
    }
    fclose(in);
    fclose(golden);
    printf("PASS");
    return 0;
}