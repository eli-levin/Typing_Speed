#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

int char_count;
struct sigaction act;
pthread_t thread1;

void AlarmSignalHandler(int sig){

	//if another alarm occurs while in signal handler, ignore it
	signal(SIGALRM, SIG_IGN);
	
	//reset terminal stty to cooked (default setting)
	system ("/bin/stty cooked");

	//stop counting chars

	float rate = (char_count/10.0f);

	char* good = "wonderful";
	char* bad = "shitty";
	char* mystr;

	mystr = ((char_count < 50) ? bad : good);

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
	char_count = 0;
	//install signal handler for SIGALRM
	act.sa_handler = AlarmSignalHandler;
	act.sa_flags = 0;
	if((sigemptyset(&act.sa_mask) == -1) || (sigaction(SIGALRM, &act, NULL) == -1))
	{
		perror("Failed to set SIGALRM handler:");
		return -1;
	}

	pthread_create(&thread1,NULL,&get_input,NULL);

	alarm(5);
	while(1);

	return 0;
}