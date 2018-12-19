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

#include "trojanJump.h"
#include "spyJump.h"

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
	int MAX_PROBES = 10000;
	int SLEEP_T = 100;
	unsigned long long start_t, end_t;

	for (int i=0; i<MAX_PROBES; i++){
		start_t = rdtsc();
		spyJump();
		end_t = rdtsc();
		printf("%lld\n",end_t-start_t);
		if (i%2){//odd, should cause spy to take longer
			trojanJump();
			usleep(SLEEP_T);
		}
		//usleep(SLEEP_T);
		start_t = rdtsc();
		spyJump();
		end_t = rdtsc();
		printf("%lld\n",end_t-start_t);
	}
	return 0;
}