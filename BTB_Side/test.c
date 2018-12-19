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
	int SLEEP_T = 1000;

	for (int i=0; i<MAX_PROBES; i++){
		if (i%2){//odd, should cause spy to take longer
			//longJump();
		}
		else{//even, spy should take short time
			//shortJump();
		}
		//usleep(SLEEP_T);
		unsigned long long start_t = rdtsc();
		spyJump();
		unsigned long long end_t = rdtsc();
		printf("%lld\n",end_t-start_t);
	}
	return 0;
}