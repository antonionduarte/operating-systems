#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int counter = 0; // shared global variable
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* mythreads_test(void* arg) {
	for (int i = 0; i < 10000; i++) {
		pthread_mutex_lock(&mtx);
			counter = counter + 1;
		pthread_mutex_unlock(&mtx);
		return NULL;
	}
}

int main(int argc, char* argv[]) {
	// variables where both thread ids will be stored
	pthread_t p1; 
	pthread_t p2; 

	// create both threads
	pthread_create(&p1, NULL, mythreads_test, "A");
	pthread_create(&p2, NULL, mythreads_test, "B");
	
	// wait for both threads to finish
	pthread_join(p1, NULL); pthread_join(p2, NULL);

	printf("main: done\n [counter: %d]\n [should: %d]\n", counter, 10000 * 2);

	// TODO: problem with this solution
	// is that it doesn't really change the speed of the program's 
	// execution since the locks are happening
	// in a way that doesn't make it fast or smth? idgaf
	// fml i just want love

	return 0;
}