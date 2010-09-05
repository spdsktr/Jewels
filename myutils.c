#include <sys/time.h>   /*for timing calls*/
#include <stdio.h>
#include <unistd.h>

/*FUNCTION usleep*/
/*This function halts program execution for the specified
  number of microseconds */
void mu_sleep(long time)
{
   usleep(time);
#if 0
	struct timeval t; /*the gettimeofday results*/
	unsigned long usec_start, /*the starting time of the function */ 
                      usec; /*the amount of time since the function
                                   started*/

	/*get the time of the start of the function*/
	gettimeofday(&t, NULL);	
	usec = usec_start = 1000000 * t.tv_sec + t.tv_usec;
	
	/* loop until the amount of time elapsed is greater than time*/
	while((usec - usec_start) < time)
	{
		gettimeofday(&t, NULL);
		usec = 1000000 * t.tv_sec + t.tv_usec;
	}		

#endif
}	

#if 0

long get_time()
{
    struct timeval t; /*the gettimeofday results*/
    gettimeofday(&t, NULL);
    return 1000000 * t.tv_sec + t.tv_usec;
}

#endif
