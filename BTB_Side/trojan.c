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

#include "shortJump.h"
#include "longJump.h"


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
	while(1){
		if (time(0)%2){//returns time in seconds
			shortJump();
		}
		else{
			longJump();
		}
	}
	return 0;
}