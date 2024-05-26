#include "header.h"

float Random(int min, int max){
    return min + (float) rand()/((float)RAND_MAX/max) ;
}

void writeRandom(pid_t id, int min, int max){

    FILE *fp;         // id
    char filename[20];// 3152 ".txt"

    if(snprintf(filename, 20, "%d.txt",id)== -1){
        perror("error in writing to child's file\n");
        exit(-100);
        }

    fp = fopen(filename, "w");
    fprintf(fp, "%.2f", Random(min,max));
    fclose(fp);
    // sleep(3);
}