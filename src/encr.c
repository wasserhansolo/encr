/**
 * @file encr.c
 * @author Christian Kuepper <wasser@chello.at>
 * @date 04.05.2014
 *
 * @brief Main program module.
 * This program encypts text from the stdin
 * 
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

/**
 * getlinefromstdin
 * @brief read line from stdin and encrypt it in a child process, print it
 * @details
 * The function reads from the stdin, cutts the newline (if there is any) forks a child process, which encrypts it and takes a certain (random) ammount of time to do this and prints it to the stdout.
 *
 */

int getlinefromstdin();

/**
 * terminate
 * @brief
 * handles SIGTERM event and waits for all the child to terminate
 * also lets the father live until all children sent the SIGCHLD signal
 * @param signal the SIGCHLD signal
 */
void terminate();

/**
 * childhandler
 * @brief
 * handles SIGCHLD event and waits for the child to terminate
 * @param signal the SIGCHLD signal
 */
void childhandler(int signal);

/**
 * siginthandler
 * @brief
 * handles SIGINT,SIGQUIT event and frees the linebuffer memory
 * @param signal the SIGCHLD signal
 */
void siginthandler(int sig);

#define LINEBUFFERSIZE (1024) /**< defines the size of the Linebuffer to allocate */
int status=1;
int ischild=0;
char  *linebuffer;

/**
 * Mandatory usage function.
 * @brief This function writes helpful usage information about the program to stderr.
 */
static void usage(void) {
	(void) fprintf(stderr, "USAGE: %s encrypts given text\n encr [<stdin>|-help]\n", "encr");
	exit(EXIT_FAILURE);
}

/**
 * Program entry point.
 * @brief The program starts here. 
 * @details
 * signalhandling is called if SIGTERM, SIGCHLD, SIGINT or SIGQUIT is called
 * @function getlinefromstin is the function which implements the whole logic
 * @param argc The argument counter. ( if argument is given, usage message is called)
 * @param argv The argument vector.
 * @return Returns EXIT_SUCCESS if getlinefromstdin() was successful.
 */

int main(int argc, char** argv)
{
    if(argc>1){ (void)usage(); }
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

