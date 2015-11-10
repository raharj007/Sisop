#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#define PANJANG 1024
#define AKHIRAN " \t\r\n"

void cd(char *line, char *nulis)
{
	int i=0;
	char *args[20];
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
		if(args[1]==NULL){		
			args[1]="/home";			
			chdir(args[1]);
		}
		else {
			chdir(args[i-1]);
		}
	}
}

void univ(char *line, char *nulis)
{
	int i=0;
	char *args[20], *cek, *fix;
	while(nulis!=NULL){
		args[i]=nulis;
		nulis=strtok(NULL, AKHIRAN);		
		i++;
	}
	/*cek=strstr(args[0], "&");
	printf("%s\n", cek);
	if(strcmp(cek, "&")==0){
		fix=strtok(args[0], "&");
		printf("%s\n", fix);
	}*/
	args[i] = NULL; 	
	execvp(args[0], args);
}

void mandek(int signum){
	pid_t pid;
	pid=fork();
	if(pid>0){
		wait();
	}
	else{	
	}
}

int main(){
	char *nulis;
	char line[PANJANG];
	signal(SIGINT, mandek);
	while(1){
		printf("Terminal@Tirtonadi $ ");
		//getchar();
		if(!fgets(line, PANJANG, stdin)) break;
		if((nulis = strtok(line, AKHIRAN))){
			if(strcmp(nulis, "exit") == 0){
				exit(0);	
			}
			else if(strcmp(nulis, "cd") == 0){
				cd(nulis, line);			
			}
			else{
				pid_t pid;
				pid=fork();
				if(pid==0){	
					univ(nulis, line);
				}
				else{
					wait();
				}
			}	
		}
	}
	return 0;
}
