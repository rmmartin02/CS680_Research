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
#include <papi.h>

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
	//branch instruc, branch mispred, brnanch unconditional
	int Events[3] = { PAPI_BR_INS,PAPI_BR_MSP,PAPI_BR_UCN };
	long long int values[3];
	int num_hwcntrs = 0;
	if ((num_hwcntrs = PAPI_num_counters()) <= PAPI_OK)  
		printf("Heck.");
	printf("This system has %d available counters.\n", num_hwcntrs);

	if (num_hwcntrs > 2)
    num_hwcntrs = 2;

     /* Start counting events */
	if (PAPI_start_counters(Events, num_hwcntrs) != PAPI_OK)
		printf("Heck.");
	setaffinity(3);
	spyJump();
	if (PAPI_stop_counters(values, 3) != PAPI_OK)
		printf("Heck.");
	for(int i = 0; i<3; i++){
		printf("%lld\n",values[i]);
	}

	//trojanJump();

	if (PAPI_start_counters(Events, num_hwcntrs) != PAPI_OK)
     		printf("Heck.");
	spyJump();
	if (PAPI_stop_counters(values, 3) != PAPI_OK)
		printf("Heck.");
	for(int i = 0; i<3; i++){
		printf("%lld\n",values[i]);
	}
	return 0;
}
//gcc -I/usr/local/include -O0 trojTest.c /usr/local/lib/libpapi.a -o trojTest.c