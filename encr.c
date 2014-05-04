#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void getlinefromstdin();
void encryptandprint();
void terminate();

#define LINEBUFFERSIZE (1024)

int main(int argc, char** argv)
{
    printf("My pid: %d",getpid());
    
    
    //if sigterm signal is cought, execute terminate()
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = terminate;
    sigaction(SIGTERM, &action, NULL);
    
    getlinefromstdin();
    return EXIT_SUCCESS;
}

void getlinefromstdin(){
   
    char  *linebuffer;
    linebuffer = malloc(sizeof(char)*LINEBUFFERSIZE);
    
    
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
            encryptandprint(linebuffer);
                break;
            
            default:
            
            
            fgets(linebuffer, LINEBUFFERSIZE, stdin);
            
            int status=0;
            waitpid(child,&status,0);
            
            //remove newline from string
            
            if(linebuffer[strlen(linebuffer)-1]=='\n') {
                linebuffer[strlen(linebuffer)-1]=0;
            }

            
            
                break;
    }
    
    
    free(linebuffer);

    
}


void encryptandprint(char * linebuffer){
    
    char *linetoencrypt;
    linetoencrypt=malloc(sizeof(char)*LINEBUFFERSIZE);
    strcpy(linetoencrypt,linebuffer);
    sleep(10);
    printf("encryptandprint %s",linebuffer);
    
}

void terminate(){

    printf("just caught SIGTERM SIGNAL");
}

