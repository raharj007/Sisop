#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*typedef struct{
	char buff[100];
	char buff2[100];
}strak;*/

void *run(void *filename) {
	FILE *file, *file1;
	char line[101];
	char **filename_ = (char **) filename;
	//strak *nyalin=(strak*)file;
	file = fopen(filename_[0], "r");
	//fscanf(nyalin->file, "%[^\n]", nyalin->buff);
	file1 = fopen(filename_[1], "w+");
	//fprintf(nyalin->file1, "%s\n", nyalin->buff);
	while (fgets(line, 100, file))
    	{
       		fprintf(file1, "%s", line);
    	}
	fclose(file);
	fclose(file1);
}

void *run2(void *filename){
	FILE *file1, *file2;
	//strak *nyalin=(strak*)file;
	char line[101];
	char **filename_ = (char **) filename;
	file1 = fopen(filename_[1], "r");
	//fscanf(nyalin->file1, "%[^\n]", nyalin->buff2);
	file2 = fopen(filename_[2], "w+");
	//fprintf(nyalin->file2, "%s\n", nyalin->buff2);
	while (fgets(line, 100, file1))
    	{
       		fprintf(file2, "%s", line);
    	}
	fclose(file1);
	fclose(file2);
}

int salinfile(){
	//strak file;	
	pthread_t salin1, salin2;	
	char **filename = (char **) malloc(sizeof(char*) * 3);
	int i;
	for(i=0; i<3; i++)
	{
		char a[10];
		if(i==0) strcpy(a, "copy");
		else if(i==1) strcpy(a, "temp");
		else if(i==2) strcpy(a, "write");
		printf("Masukkan nama file %s : ", a);
        	filename[i] = (char *) malloc(sizeof(char)*101);
        	scanf("%s", filename[i]);
        	if (access(filename[i], F_OK) != 0)
        	{
            		printf("File can not be accessed!\n");
            		exit(EXIT_FAILURE);
        	}
        	fflush(stdin);
	}
	pthread_create(&salin1, NULL, run, (void *)filename);
	pthread_create(&salin2, NULL, run2, (void *)filename);
	
	pthread_join(salin1, NULL);
	pthread_join(salin2, NULL);
	
	free(filename);
}

int main()
{
	salinfile();
}
