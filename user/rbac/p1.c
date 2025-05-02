// Process 1 - resource monitoring

#include <syscall.h>
#include <stdio.h>

void monitor_resource(int *resource_counter) {
	//simulate resource consumption by incrementing a counter
	(*resource_counter)++;
	printf("Resource monitoring: System resource usage is now %d\n", *resource_counter);
}

int main (int argc, char **argv) {
	int resource_counter = 0;

	while(1) {
		monitor_resource(&resource_counter); //periodically monitor resource usage
		yield(); //yield to next process
	}
}

//This function simply increments a counter, simulating an increase in resource usage (e.g., CPU or memory usage). Each time monitor_resource() is called, it simulates checking or consuming resources.
