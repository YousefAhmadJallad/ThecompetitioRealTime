#include "header.h"
#include "functions.h"
#include "local.h"

extern  char L_sum1[10];
extern  char L_sum2[10];
extern  char value1_T1[10];
extern  char value2_T1[10];
extern char value1_T2[10];
extern char value2_T2[10];

enum PROCCESS_NUM {P1=1, P2=2, P3=3, P4=4, P5=5};
enum PROCCESS_NUM proccess;

int min;
int max;

void fun(int sigNum){
  // read from file range.txt
  FILE *fp = fopen("range.txt", "r");
  if (fp == NULL) {
    perror("Error opening file\n");
    exit(1);
  }
  fscanf(fp,"%d,%d",&min,&max);
  // end reading of ranges
  /////////////////////////////////
  writeRandom(getpid(), min, max);
}


///////////////////////////////

///////////////////////////////
///////////////////////////////

//////////////////////////////

int main(int argc, char *args[])
{  
    // args[0] is call of executable file ./
    // args[1] is the index of the proccess
    // args[2] is sendpipe
    // args[3] is recvpipe


    if ( signal(SIGINT, fun) == SIG_ERR ) {
      perror("Sigset can not set SIGINT");
      exit(SIGINT);
    }


    if(argc == 4) {

    // Seed the random number generator with the current time
    srand(time(NULL));


    FILE *fp;

    proccess = (atoi(args[1])+1);
    int out = atoi(args[2]); // send
    int in = atoi(args[3]); // rcv
    
    
    // for p5

    switch(proccess) {
       
        case 5: // if p == p5
      
        // printf("p5>in = %d; out = %d\n", in, out);

        char message[BUFSIZ]; 
      
      
        while(1){
          printf("p5>p5 is waiting for data\n");
          if ( read(in, message, BUFSIZ) != -1 ){// read from pipe
              printf("message received in p5: %s\n", message);
          }
          else{
            perror("read pipe in p5");
            exit(-100);
          }


          float values[4];
          char *splitter = strtok(message, ",");
          values[0] = atof(splitter);    
          splitter = strtok(NULL, ",");
          values[1] = atof(splitter);
          splitter = strtok(NULL, ",");
          values[2] = atof(splitter);
          splitter = strtok(NULL, ",");
          values[3] = atof(splitter);

    

          sprintf(message,"%f,%f",values[0]+values[1], values[2]+values[3]); //sum1,sum2

          // Rama & Maymona
          sprintf(L_sum1,"%0.2f",values[0] + values[1]);
          sprintf(L_sum2,"%0.2f",values[2] + values[3]);
          sprintf(value1_T1,"%0.2f",values[0]);
          sprintf(value2_T1,"%0.2f",values[1]);
          sprintf(value1_T2,"%0.2f",values[2]);
          sprintf(value2_T2,"%0.2f",values[3]);
         

          printf("Sending sum1, sum2 to parent from p5\n");

          sleep(1);
          printf("message will be sent to parent from p5: %s\n",message);
          if(write(out, message, sizeof(message)) == -1){ // write sum1 and sum2 into the fifo
              perror("write");
              exit(18);
            }
            printf("p5>message sent from p5\n");
            // then repeat
        }


            break;
        
        default: // else
            // code of regular proccess
            while(1){
              pause() ;
              sleep(proccess);
              kill(getppid(),SIGINT);
              printf("sending signal to parent... p%d\n",proccess);
            }

    }

  }// end if

    else{
      perror("wrong number of arguments");
      exit(-17);
    }


  return 0;
}
