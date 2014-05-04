#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void getlinefromstdin();
void encryptandprint();
void terminate();
void childhandler();
void siginthandler();

#define LINEBUFFERSIZE (1024)
int status=1;

int main(int argc, char** argv)
{
    printf("My pid: %d",getpid());
    
    
    //if sigterm signal is cought, execute terminate()
    //struct sigaction term;
    //memset(&term, 0, sizeof(struct sigaction));
    //term.sa_handler = terminate;
    //sigaction(SIGTERM, &term, NULL);
    signal(SIGTERM, terminate);
    signal(SIGCHLD, childhandler);
    signal(SIGINT, siginthandler);
    signal(SIGQUIT,siginthandler);
    
    getlinefromstdin();
    return EXIT_SUCCESS;
}

void getlinefromstdin(){
   
    char  *linebuffer;
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
                exit(EXIT_FAILURE);
                break;
    
            case 0:
            
            printf("\nfrom child pid: %i\n",  getpid());
            encryptandprint(linebuffer);
            exit(EXIT_SUCCESS);
                break;
            
            default:
            
            
            //fgets(linebuffer, LINEBUFFERSIZE, stdin);
        {
            waitpid(-1,&status, WNOHANG);
            //waitpid(child,&status,0);
            printf("child exit status: %i",status);
            
            
        }   //remove newline from string
            
            //if(linebuffer[strlen(linebuffer)-1]=='\n') {
            //    linebuffer[strlen(linebuffer)-1]=0;
            //}

            
            
                break;
    }
    }
    
    free(linebuffer);

    
}


void encryptandprint(char * linebuffer){
    
    char *linetoencrypt;
    linetoencrypt=malloc(sizeof(char)*LINEBUFFERSIZE);
    strcpy(linetoencrypt,linebuffer);
    int randomint = 0;
    srand(time(NULL));
    randomint = rand();
    printf("randomint: %i",randomint);
    int randomforsleep = randomint % 9;
    printf("randomforsleep: %i",randomforsleep);
    sleep(randomforsleep);
    char *encrypted = crypt(linebuffer,"salt");
    printf("\nencryptandprint %s --> encrypted: %s",linebuffer, encrypted);
    exit(EXIT_SUCCESS);
    
}

void childhandler(int signal){
    printf("Cought signal %d!\n",signal);
	if (signal==SIGCHLD) {
		printf("Child ended\n");
		wait(NULL);
	}
}

void siginthandler(int sig){
    printf("\n Exiting: you hit ctrl+c");
    exit(EXIT_SUCCESS);
}

void terminate(){
    printf("just caught SIGTERM SIGNAL status:%i",status);
    int status;
    while(wait(&status)>0){}
    exit(EXIT_SUCCESS);
}

