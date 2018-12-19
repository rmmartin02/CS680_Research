#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <limits.h>
#include <string.h>

#include "shortJump.h"
#include "longJump.h"

__attribute__((always_inline)) inline uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

void setaffinity(int coreid) {
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(coreid, &mask);
  if(sched_setaffinity( 0, sizeof(mask), &mask ) == -1 ) {
    perror("couldn't set affinity");
  }
}

int main(){
	setaffinity(3);
	int MAX_PROBES = 100;
	int SLEEP_T = 1000;
	int NUM_BITS = 1000;

	unsigned long long bits[NUM_BITS];
	unsigned long long overallAvg;

	for (int n=0; n<NUM_BITS; n++){
		unsigned long long avg = 0;
		for (int i=0; i<MAX_PROBES; i++){
			usleep(SLEEP_T);
			unsigned long long start_t = rdtsc();
			shortJump();
			unsigned long long end_t = rdtsc();
			printf("%lld\n",end_t-start_t);
			avg += end_t-start_t;
		}
		avg/=MAX_PROBES;
		//printf("%lld\n",avg);
		//printf("\n");
		overallAvg += avg;
		bits[n] = avg;
	}
	overallAvg/=NUM_BITS;
	//printf("%lld\n",overallAvg);
	return 0;
}