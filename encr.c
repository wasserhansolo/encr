#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void getlinefromstdin();
void encryptandprint();
void terminate();
void childhandler();

#define LINEBUFFERSIZE (1024)
int status=1;

int main(int argc, char** argv)
{
    printf("My pid: %d",getpid());
    
    
    //if sigterm signal is cought, execute terminate()
    struct sigaction term;
    memset(&term, 0, sizeof(struct sigaction));
    term.sa_handler = terminate;
    sigaction(SIGTERM, &term, NULL);
    signal(SIGCHLD, childhandler);
    
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
    sleep(5);
    printf("\nencryptandprint %s",linebuffer);
    exit(EXIT_SUCCESS);
    
}

void childhandler(int signal){
    printf("Cought signal %d!\n",signal);
	if (signal==SIGCHLD) {
		printf("Child ended\n");
		wait(NULL);
	}
}


void terminate(){
    
    //pid_t kidpid;
   // int status;
    
   // while ((kidpid = waitpid(-1, &status, WNOHANG)) > 0)
   // {
   //     printf("Child %d terminated\n", kidpid);
   // }
    int status;
    while(wait(&status)>0){}
    printf("just caught SIGTERM SIGNAL status:%i",status);
    exit(EXIT_SUCCESS);
}

