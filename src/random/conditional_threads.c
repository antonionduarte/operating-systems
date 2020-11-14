#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int inSync = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cnd = PTHREAD_COND_INITIALIZER;

void myThrSign() {
	// locks mtx (cond_wait in myThrWait unlocked it so this can run)
	pthread_mutex_lock(&mtx);
		inSync = 1;
		// unlocks conditional 
		pthread_cond_signal(&cnd);
	// unlocks mtx 
	pthread_mutex_unlock(&mtx);
}

void myThrWait() {
	pthread_mutex_lock(&mtx);
		// unlocks mtx, allowing myThrSign to run, but locks execution in here.
		// a while is necessary here instead of an if becausex
		// it is necessary to re-evaluate the condition
		// to see if the thread can advance
		while (!inSync) pthread_cond_wait(&cnd, &mtx);

	// unlocks mtx
	pthread_mutex_unlock(&mtx);
}

void* child(void* arg) {
	printf("child begins and sleeps 3s\n"); 
	sleep(3);
	myThrSign();
	printf("child ends\n");
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t p;
	printf("parent begins\n");
	pthread_create(&p, NULL, child, NULL);
	// this myThrWait() blocks the execution of the main thread,
	// while the "child" thread is executing,
	// otherwise "parent ends" would have been printed
	// before the execution of the "child" thread
	myThrWait();
	printf("parent ends\n");
	return 0;
}