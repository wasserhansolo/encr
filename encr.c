#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void getlinefromstdin();
void encryptandprint();

#define LINEBUFFERSIZE (1024)

int main(int argc, char** argv)
{
    getlinefromstdin();
    return EXIT_SUCCESS;
}


void getlinefromstdin(){
   
    
 static char  *linebuffer;
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
                printf("child forktest");
                break;
            default:
                printf("father forktest:");
            
            fgets(linebuffer, LINEBUFFERSIZE, stdin);
            
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
    sleep(5);
    printf("encryptandprint %s",linebuffer);
    
}
