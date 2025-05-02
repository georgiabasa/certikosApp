// Process 3 - status reporting

#include <syscall.h>
#include <stdio.h>

void report_status(int cycle_counter, int resource_usage, int action_count) {
	//simulate reporting the current system status
	printf("Status Report (Cycle %d):\n", cycle_counter);
	printf("Resource Usage: %d\n", resource_usage);
	printf("Actions Executed: %d\n", action_count);
}

int main(int argc, char **argv) {
	int cycle_counter = 0;
	int resource_usage = 0;
	int action_count = 0;

	while (1) {
		cycle_counter++;
		report_status(cycle_counter, resource_usage, action_count); //report system status
		yield(); //yield to next process
	}
}

//In this part, the function report_status() would print a report that contains the current state of the system (e.g., resource usage, actions completed). It aggregates the data from the other processes, giving a meaningful status update.
