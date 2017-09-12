# kernel-clock-timer
This is a simple kernel timer created using the procfs

This assignment entailed the implementation of a Simple Clock Module & Calendar User Interface.   

The program consists of two parts:  A user-space component and a kernel module.  The user-space component creates a kernel timer using itimerval to keep track of the time, and prints the current date and time to the screen when it receives a signal from the kernel module.

The kernel module is responsible for creating a file in the /proc filesystem; /proc/myclock.  This file is a read-only file which, when read, returns Unix Time in seconds, and milliseconds since the last recorded second, separated by a comma and a single space in the form:

     seconds_since_jan_1_1970, milliseconds_since_last_second

The user-space component of our simple clock initially prints out the time, and then waits for a signal from our kernel module after a pre-designated period of time (here three seconds).  The user-space component then goes through the process of printing out the value that it reads from /proc/myclock in a standardized format similar to:
	Wed, Mar 23, 10:22:42 pm 2012

and then waits for the next kernel signal before repeating this process for a grand total of 300 times, over a total of 15 minutes!  At the end of the run, the time at which the timer initially started is displayed alongside the time at which it finished for ease of comparison.   The program was run on a Gentoo virtual box.
