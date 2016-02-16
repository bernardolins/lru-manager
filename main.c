#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 20

void *processo(void *arg) {
	int id = *(int*)arg;
	printf("Processo[%d] inicializou!\n", id);
	pthread_exit(NULL);

}

int main(int argc, char **argv) {
	int i;
	int *arg;
	pthread_t threads[N];

	for(i = 0; i < N; i++) {
		arg = malloc(sizeof(int));
		*arg = i;
		pthread_create(&threads[i], NULL, processo, (void*)arg);
	}	

	for(i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_exit(NULL);
}
