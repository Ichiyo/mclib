#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <stdatomic.h>
#define NUM_THREADS	10

int acnt;
int cnt;

void *PrintHello(void *threadid)
{
	for(int n = 0; n < 1000; ++n)
	{
			++cnt;
			++acnt;
			// for this example, relaxed memory order is sufficient, e.g.
			// atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
	}
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for(t = 0; t < NUM_THREADS; ++t)
	{
		printf("In main: creating thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		if (rc)
		{
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for( t = 0; t < NUM_THREADS; ++t)
	{
		pthread_join(threads[t], NULL);
	}

	printf("The atomic counter is %u\n", acnt);
	printf("The non-atomic counter is %u\n", cnt);
	/* Last thing that main() should do */
	pthread_exit(NULL);
}
