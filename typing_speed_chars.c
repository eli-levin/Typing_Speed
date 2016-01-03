#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int char_count;
struct sigaction act;
pthread_t thread1;
int TIME_LIMIT;

void AlarmSignalHandler(int sig){

	//if another alarm occurs while in signal handler, ignore it
	signal(SIGALRM, SIG_IGN);
	
	//reset terminal stty to cooked (default setting)
	system ("/bin/stty cooked");

	//stop counting chars
	float per = (float)TIME_LIMIT;

	float rate = (char_count/per);

	char* good = "wonderful";
	char* bad = "bad";
	char* mystr;

	mystr = ((rate < 10) ? bad : good); //bad tpying is < 10 chars per second :)

	printf("\n\nYou are extremely %s at typing!\n", mystr);
	printf("|----> Score : %.3f chars per second (%d Total chars).\n\n", rate, char_count);
	
	//Done
	if(pthread_detach(thread1)){
		perror("Failed to detach thread:");
		exit(1);
	}

	exit(0);
}

void* get_input(){

	printf("\n|-------------------START TYPING!-------------------|\n");

	//change terminal input to raw so every character is counted as carriage return
	system ("/bin/stty raw");
	//this should be undone in signal handler

	char c;
	ssize_t redd;
	while(1){
		c = getchar();
		char_count++;
	}
}

int main(int argc, char*argv[]){

	if(argc > 2){
		printf("Incorrect number of arguments:\n");
		exit(1);
	}
	if(argc < 2){
		TIME_LIMIT = 5;
	}
	else{
		TIME_LIMIT = atoi(argv[1]);
		if ( (TIME_LIMIT > 60) || (TIME_LIMIT < 1) )
		{
			printf("Usage: time limit must be between 1 and 60 inclusively.\n");
			exit(1);
		}
	}

	char_count = 0;
	//install signal handler for SIGALRM
	act.sa_handler = AlarmSignalHandler;
	act.sa_flags = 0;
	if((sigemptyset(&act.sa_mask) == -1) || (sigaction(SIGALRM, &act, NULL) == -1))
	{
		perror("Failed to set SIGALRM handler:");
		return -1;
	}

	printf("\nYou have %d seconds starting in ", TIME_LIMIT);
	int i;
	for (i = 3; i > 0; i--)
	{
		printf("%d... ", i);
		fflush(stdout);
		sleep(1);
	}


	pthread_create(&thread1,NULL,&get_input,NULL);

	alarm(TIME_LIMIT);
	while(1);

	return 0;
}
