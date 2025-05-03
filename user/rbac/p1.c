// Process 1 - resource monitoring

#include <syscall.h>
#include <stdio.h>

void monitor_resource(int *resource_counter) {
	//simulate resource consumption by incrementing a counter
	(*resource_counter)++;
	printf("Resource monitoring: System resource usage is now %d\n", *resource_counter);
}

static int tick = 0;

int main (int argc, char **argv) {
	//int resource_counter = 0;
	int loop = 50;

	do {
		printf("\n");
		tick++;
		int fake_cpu = tick %100;
		int fake_mem = (tick * 3) %256;

		printf("[P1] CPU Load: %d%%\n", fake_cpu);
		printf("[P1] Memory Usage: %dMB\n", fake_mem);

		loop--;
		yield(); //yield to next process
	} while (loop > 0);

	return 0;
}

//This function simply increments a counter, simulating an increase in resource usage (e.g., CPU or memory usage). Each time monitor_resource() is called, it simulates checking or consuming resources.

//P1 acts like a privileged daemon/service monitoring system health (e.g., top, systemd metrics).
