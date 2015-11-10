#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int i;
	int flag;
}prima;

typedef struct{
	FILE *file, *file1, *file2;
	char buff[100];
	char buff2[100];
}strak;

void *first(void* file) {
	strak *nyalin=(strak*)file;
	nyalin->file = fopen("/home/black00/Sisop/test.txt", "r");
	fscanf(nyalin->file, "%[^\n]", nyalin->buff);
	nyalin->file1 = fopen("/home/black00/Sisop/test1.txt", "w+");
	fprintf(nyalin->file1, "%s\n", nyalin->buff);
	fclose(nyalin->file);
	fclose(nyalin->file1);
}

void *second(void *file){
	strak *nyalin=(strak*)file;
	nyalin->file1 = fopen("/home/black00/Sisop/test1.txt", "r");
	fscanf(nyalin->file1, "%[^\n]", nyalin->buff2);
	nyalin->file2 = fopen("/home/black00/Sisop/test2.txt", "w+");
	fprintf(nyalin->file2, "%s\n", nyalin->buff2);
	fclose(nyalin->file1);
	fclose(nyalin->file2);
}

int no3(){
	strak file;	
	pthread_t salin1, salin2;
	pthread_create(&salin1, NULL, first, &file);
	pthread_create(&salin2, NULL, second, &file);
	
	pthread_join(salin1, NULL);
	pthread_join(salin2, NULL);
	
	return 0;
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
	printf("Pilih soal nomor [1, 2, 3]: \n");
	scanf("%d", &pilih);
	
	switch(pilih){
		case 1 : no2(); break;
		case 2 : no2(); break;
		case 3 : no3(); break;
	}
	return 0;
}
