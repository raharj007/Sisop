#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#define PANJANG 1024
#define AKHIRAN " \t\r\n"

void working(){
	char *buff, *scan;
	buff = (char *)malloc(sizeof(char)*PANJANG);
	if((scan = getcwd(buff, PANJANG))!=NULL)
		printf("%s", scan);
}

void cd(char *line, char *nulis)
{
	int i=0;
	char *args[20];
	while(nulis!=NULL){
		args[i]=nulis;
		nulis=strtok(NULL, AKHIRAN);		
		i++;
	}
	if(args[1]==NULL){		
		args[1]="/home";			
		chdir(args[1]);
	}
	else {
		chdir(args[i-1]);
	}
}

void background(char *line, char *nulis)
{
	int i=0;
	char *args[2], *cek;
	pid_t pid;
	pid=fork();
	if(pid==0){
		cek=strtok(nulis, "&");
		args[0] = nulis;
		args[1] = NULL; 	
		execvp(args[0], args);
	}
}

void univ(char *line, char *nulis)
{
	int i=0;
	char *args[20], *cek;
	pid_t pid;
	pid=fork();
	if(pid>0){
		wait();
	}
	else{
		while(nulis!=NULL){
			args[i]=nulis;
			nulis=strtok(NULL, AKHIRAN);		
			i++;
		}
		args[i] = NULL; 	
		execvp(args[0], args);
	}
}

void nothing(int signum){
}

int main(){
	char *nulis;
	char *fix;
	char line[PANJANG];
	signal(SIGTSTP, nothing);
	signal(SIGINT, nothing);
	while(1){
		printf("E20@Terminal ~");
		working();
		printf(" $ ");
		if(!fgets(line, PANJANG, stdin)) break;		
		if((nulis = strtok(line, AKHIRAN))){
			if(strcmp(nulis, "exit") == 0){
				exit(0);	
			}
			else if(strcmp(nulis, "cd") == 0){
				cd(nulis, line);			
			}
			else{
				char *src=nulis+strlen(nulis)-1;				
				strcpy(fix, src);				
				if(strcmp(fix, "&")==0){
					printf("&\n");
					background(nulis, line);				
				}
				else{
					univ(nulis, line);
				}				
			}	
		}
	}
	return 0;
}
