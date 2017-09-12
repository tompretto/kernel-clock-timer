//		user.c
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>//for "exit(0)";
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>

#define SIZE 300

	int 	ready;

main()
{	
	void 	timeout();
	void showtime();

	int	n, k, t;
	struct	itimerval	myvalue,myovalue;
	struct timeval mytv;//my time value structure

	printf("Tom's  timer program.\n");

    	gettimeofday(&mytv, NULL);
	printf("Start time:  %s\n",ctime(&mytv.tv_sec) );

for(k=0; k<SIZE; k++){
	//printf("Setting signal handler\n");
	if ((signal(SIGALRM, timeout)) == SIG_ERR) {
		printf("Error in setting signal handler\n");
		exit(0);
	}

	//printf("Clearing timer\n");
	timerclear(&myvalue.it_interval);
	timerclear(&myvalue.it_value);
	timerclear(&myovalue.it_interval);
	timerclear(&myovalue.it_value);
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(0);
	}

	//printf("Setting timer\n");
	myvalue.it_value.tv_sec = 3; /* timeout interval in seconds */
		/* set tv_usec for microsecond timeout */
	if (( n = setitimer(ITIMER_REAL,&myvalue,&myovalue)) < 0 ) {
		printf("Error in clearing timer\n");
		exit(0);
	}

	ready=0;
	
//	printf("Waiting for signal...\n");
//	for(;;);

	while(!ready);
	//got the signal, now go print out 
	showtime(k);
}
	printf("Start time: %s\n", ctime(&mytv.tv_sec) );
	gettimeofday(&mytv, NULL);
	printf("End time:  %s\n", ctime(&mytv.tv_sec) );
}
void
timeout(int	arg)
{
	ready=1;//We have received the signal!
	//printf("Executed timeout!\n");
	//exit(0);
}

void showtime(int iteration){
	char proc_time[40];
    	char* date;//full current date needing to be tokenized
    	char* year;
    	char* month;
    	char* weekday;//Mon, Tues, ...
    	char* day_of_month;//01, 02, ...
	char* am_pm;

    	int current_time;
    	int hours;
    	int minutes;
    	int seconds;

    	int myclock_fd;
	struct timeval mytv;//my time value structure

    	memset(proc_time, 0, sizeof(proc_time));

//ropen the proc file
  	myclock_fd = open("/proc/myclock", O_RDONLY);
	if(myclock_fd < 0) {
	        perror("Bad read file open");
	        exit(-1);
	}

    	read(myclock_fd, proc_time, sizeof(proc_time));

    	gettimeofday(&mytv, NULL);
    	date = ctime(&mytv.tv_sec);

    	weekday = strtok(date, " ");
    	month = strtok(NULL, " ");
    	day_of_month = strtok(NULL, " ");
    	strtok(NULL, " ");
    	year = strtok(NULL, " ");

    	current_time = atoi(proc_time);

	hours = (current_time-25200)/3600%24;
	if(hours>12){hours-=12;}
	minutes = current_time/60%60;
	seconds = current_time%60;
	am_pm = (hours<=12)?("am"):("pm");

    	printf("%s %s, %s, %02d:%02d:%02d %s %s\n", weekday,month, day_of_month, hours, minutes, seconds, am_pm, year);

	
    	close(myclock_fd);
}
