// Process 3 - status reporting

#include <syscall.h>
#include <stdio.h>

int calculate_checksum(int *data, int length) {
	int checksum = 0;
	int i = 0;
	for (i = 0; i < length; i++) {
		checksum += data[i];
	}
	return checksum;
}

void validate_data_integrity(int *data, int length, int expected_checksum) {
	int checksum = calculate_checksum(data, length);
	if (checksum != expected_checksum) {
		printf("Data integrity violation detected! Checksum mismatch.\n");
	} else {
		printf("Data integrity check passed.\n");
	}
}

void report_status(int cycle_counter, int resource_usage, int action_count) {
	//simulate reporting the current system status
	printf("Status Report (Cycle %d):\n", cycle_counter);
	printf("Resource Usage: %d\n", resource_usage);
	printf("Actions Executed: %d\n", action_count);
}

int main(int argc, char **argv) {
	static int cycle = 0;
	//int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //sample data
	//int expected_checksum = calculate_checksum(data, 10);
	int loop = 15;

	do {
		cycle++;
		printf("[P3] Performing routine integrity check...\n");
		int result = (cycle ^ 0xAA) & 0xFF; //dummy "hash"
		if (result % 2 == 0)
			printf("[P3] Integrity OK (code %d)\n", result);
		else
			printf("[P3] Integrity WARNING (code %d)\n", result);
		loop--;
		yield(); //yield to next process
	} while (loop > 0);

	return 0;
}

//In this part, the function report_status() would print a report that contains the current state of the system (e.g., resource usage, actions completed). It aggregates the data from the other processes, giving a meaningful status update.

//P3 represents a system watchdog or audit logger, ensuring tasks behave as expected and catching anomalies.
