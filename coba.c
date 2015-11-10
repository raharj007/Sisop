#include <stdio.h>
#include <pthread.h>

typedef struct{
	FILE *file, *file1, *file2;
	char buff[100];
	char buff2[100];
}strak;

void *run(void* file) {
	strak *nyalin=(strak*)file;
	nyalin->file = fopen("/home/black00/Sisop/test.txt", "r");
	fscanf(nyalin->file, "%[^\n]", nyalin->buff);
	nyalin->file1 = fopen("/home/black00/Sisop/test1.txt", "w+");
	fprintf(nyalin->file1, "%s\n", nyalin->buff);
	fclose(nyalin->file);
	fclose(nyalin->file1);
}

void *run2(void *file){
	strak *nyalin=(strak*)file;
	nyalin->file1 = fopen("/home/black00/Sisop/test1.txt", "r");
	fscanf(nyalin->file1, "%[^\n]", nyalin->buff2);
	nyalin->file2 = fopen("/home/black00/Sisop/test2.txt", "w+");
	fprintf(nyalin->file2, "%s\n", nyalin->buff2);
	fclose(nyalin->file1);
	fclose(nyalin->file2);
}

int main(){
	strak file;	
	pthread_t salin1, salin2;
	pthread_create(&salin1, NULL, run, &file);
	pthread_create(&salin2, NULL, run2, &file);
	
	pthread_join(salin1, NULL);
	pthread_join(salin2, NULL);
	
	return 0;
}
