#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int getlinefromstdin();
void terminate();
void childhandler();
void siginthandler();

#define LINEBUFFERSIZE (1024)
int status=1;
int ischild=0;
char  *linebuffer;

int main(int argc, char** argv)
{
    signal(SIGTERM, terminate);
    signal(SIGCHLD, childhandler);
    signal(SIGINT, siginthandler);
    signal(SIGQUIT,siginthandler);

    return getlinefromstdin();
}

int getlinefromstdin(){
   
    linebuffer = malloc(sizeof(char)*LINEBUFFERSIZE);
    while(1){
    
        fgets(linebuffer, LINEBUFFERSIZE, stdin);
        
        //remove newline from string
        
        if(linebuffer[strlen(linebuffer)-1]=='\n') {
            linebuffer[strlen(linebuffer)-1]=0;
        }
        
        
    pid_t child;
        
    switch (child = fork()){
            case -1:
                perror("cannot create child process");
                free(linebuffer);
                exit(EXIT_FAILURE);
                break;
    
            case 0:
            //child does the work
        {   ischild=1;
            char *linetoencrypt;
            linetoencrypt=malloc(sizeof(char)*LINEBUFFERSIZE);
            strcpy(linetoencrypt,linebuffer);
            srand(time(NULL));
            int randomint = rand();
            int randomforsleep = randomint % 9;
            sleep(randomforsleep);
            char *encrypted = crypt(linetoencrypt,"salt");
            (void)printf("encr: %s --> %s\n",linetoencrypt, encrypted);
            exit(EXIT_SUCCESS);}
                break;
            
            default:
                {
                    //nothing to do for father (lets the children do the work)
                }
                break;
    }
    }
    free(linebuffer);
    return(EXIT_FAILURE);
}

void childhandler(int signal){
	if (signal==SIGCHLD) {
		wait(NULL);
	}
}

void siginthandler(int sig){
    if(!ischild){
    (void)printf("\n Exiting: you hit ctrl+c");
        free(linebuffer);
        exit(EXIT_SUCCESS);}
}

void terminate(){
    (void)printf("Caught SIGTERM SIGNAL status:%i",status);
    int status;
    while(wait(&status)>0){}
    free(linebuffer);
    exit(EXIT_SUCCESS);
}

