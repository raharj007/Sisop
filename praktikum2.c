#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	int i;
	int flag;
}prima;

void *nyalin1(void *filename) {
	FILE *file, *file1;
	char line[101];
	char **filename_ = (char **) filename;
	file = fopen(filename_[0], "r");
	file1 = fopen(filename_[1], "w+");
	while (fgets(line, 100, file))
    	{
       		fprintf(file1, "%s", line);
    	}
	fclose(file);
	fclose(file1);
}

void *nyalin2(void *filename){
	FILE *file1, *file2;
	char line[101];
	char **filename_ = (char **) filename;
	file1 = fopen(filename_[1], "r");
	file2 = fopen(filename_[2], "w+");
	while (fgets(line, 100, file1))
    	{
       		fprintf(file2, "%s", line);
    	}
	fclose(file1);
	fclose(file2);
}

int no3(){
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
	}
	pthread_create(&salin1, NULL, nyalin1, (void *)filename);
	pthread_create(&salin2, NULL, nyalin2, (void *)filename);
	
	pthread_join(salin1, NULL);
	pthread_join(salin2, NULL);
	
	free(filename);
}

void *run1(void* prim) {
	prima *numb=(prima*)prim;
	if(numb->i==2 || numb->i==3 || numb->i==5 || numb->i==7 || numb->i==11){
		(numb->flag)=(numb->flag)+2;	
	}
}

void *run2(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%2;
	if(hasil!=0){
		(numb->flag)++;	
	}
}

void *run3(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%3;
	if(hasil!=0){
		(numb->flag)++;	
	}
}

void *run4(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%5;
	if(hasil!=0){
		(numb->flag)++;	
	}
}

void *run5(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%7;
	if(hasil!=0){
		(numb->flag)++;	
	}
}

void *run6(void* prim) {
	int hasil, j;
	prima *numb=(prima*)prim;
	for(j=11;j<numb->i;j++){
		hasil=numb->i%j;
		if(hasil==0) break;
	}
	if(hasil!=0){
		(numb->flag)++;	
	}
}

int no2(){
	prima prim;
	prim.i=0;
	prim.flag=0;
	int n;
	pthread_t prim1, prim2, prim3, prim5, prim7, primsel;
	
	printf("Masukkan jumlah n: \n");
	scanf("%d", &n);
	for(prim.i=2;prim.i<=n;prim.i++){	
		pthread_create(&prim1, NULL, run1, &prim);
		pthread_create(&prim2, NULL, run2, &prim);
		pthread_create(&prim3, NULL, run3, &prim);
		pthread_create(&prim5, NULL, run4, &prim);
		pthread_create(&prim7, NULL, run5, &prim);
		pthread_create(&primsel, NULL, run6, &prim);
		pthread_join(prim1, NULL);
		pthread_join(prim2, NULL);
		pthread_join(prim3, NULL);
		pthread_join(prim5, NULL);
		pthread_join(prim7, NULL);
		pthread_join(primsel, NULL);
		if(prim.flag>=5){
			printf("%d\n",prim.i);		
		}
		prim.flag=0;
	}
	return 0;	
}

int main(){
	int pilih;
	pilih=1;
	while(pilih!=0){
		printf("Pilih soal nomor [2 / 3]: \n");
		scanf("%d", &pilih);
	
		switch(pilih){
			case 2 : no2(); break;
			case 3 : no3(); break;
		}
	}
	return 0;
}
