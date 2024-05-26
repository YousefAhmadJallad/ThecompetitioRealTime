#include "header.h"
#include "local.h"


extern  char result[10];
extern char number_of_Rounds[10];

FILE *file;


int received;


int main(int argc, char *argv[])
{
    FILE *fp;
    void catcher(int);

    int fid5;  // for p5
    int fd[2]; // for unnamed pipes


    int to_Child[2];
    int to_Parent[2];


    char sendPipe[100];
    char recPipe[100];

	// pipe initialization for communicating between p5 and parent
    if (pipe(to_Child) == -1 || pipe(to_Parent) == -1)
    {
        printf("Error on pipe creation: %d", errno);
        exit(1);
    }

    printf("Pipes are created: C(%d,%d), P(%d,%d)\n", to_Child[0], to_Child[1], to_Parent[0], to_Parent[1]);


    // pipe creation to send pid of children
    if (pipe(fd) == -1)
    {
        perror("Pipe");
        exit(2);
    }
 

    // initialize signal receiving function
    if (signal(SIGINT, catcher) == SIG_ERR)
    {
        perror("Sigset can not set SIGINT");
        exit(SIGINT);
    }

    
//    ./parent 1
    int num_rounds = 5; // default value for number of rounds

    // Check if user provided a number of rounds
    if (argc == 2)
    {
        num_rounds = atoi(argv[1]);
    }

    // Seed the random number generator with the current time
    srand(time(NULL));
    pid_t child[5]; // array of child processes ids



    
     pid_t pd;
     pd = fork();
     if (pd == 0 ) {
      execl("../The-competition---C-RealTime/OpenGL/game","../The-competition---C-RealTime/OpenGL/game",(char* )NULL);
     }
     else if(pd == -1){
        perror("OpenGL fork failed");
        exit(-198);
     }

    // Fork child processes
    for (int i = 0; i < 5; i++)
    {
        pid_t pid = fork();
        
        if (pid < 0)
        {
            fprintf(stderr, "Fork failed.\n");
            exit(2);
        }

        else if (pid > 0)
        { // parent proccess
            char message[BUFSIZ];
            if (read(fd[0], message, BUFSIZ) == -1)
            { // read from pipe
                perror("read");
                exit(3);
            }

            child[i] = atoi(message);
        }
        
        
        else if (pid == 0)
        {
            close(to_Child[1]);     // Child does not write to itself
            close(to_Parent[0]);    // Child does not read what it writes


            // Child process
            int id = getpid();
            // sleep(1);
            char msg[BUFSIZ];
            sprintf(msg, "%d", id); //msg = id;

                // sleep(1);
            if (write(fd[1], msg, BUFSIZ) == -1)
            {
                perror("write");
                exit(31);
            }

            ///////////////////////////////////////
            char index[12];
            // convert to string
            sprintf(index, "%d", i);   // index = i
            snprintf(sendPipe, sizeof(sendPipe), "%d", to_Parent[1]);
            snprintf(recPipe, sizeof(recPipe), "%d", to_Child[0]);

            // gcc parent.c -o parent
            // gcc child.c -o child
            // ./parent


            execl("./child", "./child", index, sendPipe, recPipe, NULL); // call child.c
            perror("execl");
            exit(-4);
        }
    } // end of forking



    close(to_Child[0]);     // Parent does not read childs input
    close(to_Parent[1]);    // Parent does not write to itself

    for (int j = 0; j < num_rounds; j++)
    {   
        received = 0;
        sprintf(number_of_Rounds,"%0.2f",j);
        
        
        // Generate random min and max values between 1 and 100
        int min_value = rand() % 100 + 1;
        int max_value = rand() % 100 + 1;

        // Make sure min_value is less than max_value
        while (min_value >= max_value)
        {
            min_value = rand() % 100 + 1;
        }

        // Write the range values to the file
        fp = fopen("range.txt", "w");
        fprintf(fp, "%d,%d", min_value, max_value);
        fclose(fp);

        printf("Random Ranges Are Generated Successfully\n");
        printf("Please Wait... waking the children up...\n");


        for (int i = 0; i < 4; ++i)
        {
            kill(child[i], SIGINT);
            sleep(1);
        }
  

        // wait for the 4 signals from children
        while (received < 4);
        // {
            // pause(); // sleep forever 
            // printf("received in loop %d\n", received);
            // fflush(stdout);
        // }

        printf("All Values Are Received\n");

        // open files and read the random values and send them in the message to p5
        char message[BUFSIZ] = "";
        printf("reading random values from files\n");

        for (int i = 0; i < 4; ++i)
        {
            char filename[20];
            sprintf(filename, "%d", child[i]); // filename = child[i] 3152
            strcat(filename, ".txt"); // "3152" + ".txt"  string1.concate(string2);
            fp = fopen(filename, "r");
            if (fp == NULL)
            {
                perror("error opening file\n");
                exit(-20);
            }
            char *line = malloc(sizeof(char) * 50);
            fgets(line, 50, fp);
            strcat(message, line);
            if (i < 3)
            {
                strcat(message, ",");
            }

        } // end of reading the random values

        printf("done reading the random values\n");

        ///////////////////////////////////

        printf("message to p5 : [%s]\n", message);
        file = fopen("OpenGL/file.txt","w");
        fprintf(file,"%s",message);
        fclose(file);

        // Send the message to the 5th child
        sleep(2);
        if (write(to_Child[1], message, sizeof(message)) == -1) // write but p5 doesn't read it
        {
            perror("error writing to pipe in parent\n");
            exit(-21);
        }
        close(fid5);
        printf("message has been sent to p5\n");
        ///////////////////




        // receive sum1 and sum2
        if (read(to_Parent[0], message, BUFSIZ) != -1)
        {
            printf("message received from pipe in parent: %s\n", message);
            char *reader;
            reader = strtok(message, ",");
            float sum1 = atof(reader);
            reader = strtok(NULL, ",");
            float sum2 = atof(reader);
            printf("sum1 = %.2f, sum2 = %.2f\n", sum1, sum2);
            if (sum1 > sum2)
            {
                printf("sum1 is greater than sum2\n");
               strcpy(result,"Team 1 win");
            }
            else if (sum1 < sum2)
            {
                printf("sum1 is less than sum2\n");
                strcpy(result,"Team2 win ");
            }
            else
            {
                printf("sum1 is equal to sum2\n");
                strcpy(result,"Team 1 equal Team2");
            }
        }
        else
        {
            perror("error reading from pipe\n");
            exit(-22);
        }
close(fid5);
    } // end of rounds loop

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // remove the 4 files
    int status;
    char *values[4];
    for (int i = 0; i < 4; i++)
    {
        // To Remove the files after finishing the process
        char filename[20];
        sprintf(filename, "%d", child[i]);
        strcat(filename, ".txt");
        while (remove(filename) == -1)
            ;
        kill(child[i], SIGKILL); // kill the child process
    }



    while (kill(child[4], SIGKILL) == -1)
        ; // to confirm the kill

    while (remove("range.txt") == -1)
        ; // to confirm the delete
    //////////////////////////////////////////////////////////////////////

    // end of programm
    printf("Terminating Parent\n");
    return 0;

}

////////////8888888888888///////////////
void catcher(int sigNum)
{
    received++;
}
