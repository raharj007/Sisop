#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int i;
	int flag;
}prima;

void *run1(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;
	if(numb->i==2 || numb->i==3 || numb->i==5 || numb->i==7){
		(numb->flag)++;	
	}
	printf("thread 1: %d\n",numb->flag);	
}

void *run2(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%2;
	if(hasil!=0){
		(numb->flag)++;	
	}
	printf("thread 2: %d\n",numb->flag);
}

void *run3(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%3;
	if(hasil!=0){
		(numb->flag)++;	
	}
	printf("thread 3: %d\n",numb->flag);
}

void *run4(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%5;
	if(hasil!=0){
		(numb->flag)++;	
	}
	printf("thread 4: %d\n",numb->flag);
}

void *run5(void* prim) {
	int hasil;	
	prima *numb=(prima*)prim;	
	hasil=numb->i%7;
	if(hasil!=0){
		(numb->flag)++;	
	}
	printf("thread 5: %d\n",numb->flag);
}
/*
void *run6(void* prim) {
	
}*/

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
		//pthread_create(&primsel, NULL, run6, (void*)prim);
		pthread_join(prim1, NULL);
		pthread_join(prim2, NULL);
		pthread_join(prim3, NULL);
		pthread_join(prim5, NULL);
		pthread_join(prim7, NULL);
		//pthread_join(&primsel, NULL);
		printf("jumlah flag= %d\n",prim.flag);
		if(prim.flag>=4){
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
		case 1 : no2();
		case 2 : no2();
		case 3 : no2();
	}
	return 0;
}
