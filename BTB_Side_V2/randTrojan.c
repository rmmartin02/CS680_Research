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
#include <sys/mman.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "spyJump.h"
#include "trojanJump.h"


void setaffinity(int coreid) {
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(coreid, &mask);
  if(sched_setaffinity( 0, sizeof(mask), &mask ) == -1 ) {
    perror("couldn't set affinity");
  }
}

int main(){
	//setup list of random bits
	int lenBits = 10;
	int bits[lenBits];
	srand(time(0));
	for(int i = 0; i<lenBits; i++){
		bits[i] = rand()%2;
		printf("%d\n",bits[i]);
	}

	setaffinity(3);

	int idx = 0;
	long int curTime = time(0)%2;
	while(1){
		while (time(0)%2==curTime){//returns time in seconds
			if(bits[idx]){
				trojanJump();
			}
			//printf("%ld %ld\n",time(0)%2,curTime);
		}
		curTime = time(0)%2;
		idx = (idx+1)%lenBits;
	}
	return 0;
}