// Process 2 - action execution

#include <syscall.h>
#include <stdio.h>

void simulate_delay(int delay_cycles) {
	int i = 0;
	for (i = 0; i < delay_cycles; i++) {
		yield(); //yield to next process
	}
	printf("Action completed after %d cycles of delay.\n", delay_cycles);
}

void sorting_task(int *data, int length) {
	//simple Bubble Sort for demostration
	printf("[P2] Action: Sorting data...\n");
	int i = 0;
	int j = 0;
	for(i = 0; i < length - 1; i++) {
		for (j = 0; j < length - i - 1; j++) {
			if (data[j] > data[j+1]) {
				int temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}
	printf("Sorting task completed.\n");
}

void simulate_encoding() {
	printf("[P2] Action: Encoding data...\n");
	int i = 0;
	for (i = 0; i < 3; i++) {
		int result = (i+1) * 42; //dummy transformation
		printf("Encoded[%d] = %d\n", i, result);\
	}
}

void checksum_calculation() {
	printf("[P2] Action: Checksum verification...\n");
	int checksum = 0;
	int i = 0;
	for (i = 0; i <= 5; i++) checksum ^= i;
	printf("Checksum: %d\n", checksum);
}

void data_filtering() {
	printf("[P2] Action: Data filtering...\n");
	int values[5] = {12, 87, 35, 2, 50};
	int i = 0;
	for (i = 0; i < 5; i++)
		if (values[i] > 30) printf("Allowed: %d\n", values[i]);
}

void execute_action(int action_id) {
	//simulate an action based on the action_id
	switch(action_id) {
		case 1:
			checksum_calculation();
			break;
		case 2:
			simulate_encoding();
			break;
		case 3:
			data_filtering();
			break;
		default:
			printf("Unkown action\n");
			break;
	}
}

int main(int argc, char **argv) {
	int action_counter = 0;
	int inside_counter = 0;
	int data[10] = {9, 7, 5, 3, 2, 8, 1, 4, 6, 10}; //example data for sorting
	int loop = 15;

	do {
		action_counter++;
		if (action_counter % 4 == 0) {
			printf("DELAY>>>>>>>\n");
			simulate_delay(5); //simulate a delay for every 4 actions
		} else if (action_counter % 2 == 0) {
			inside_counter++;
			execute_action(inside_counter % 3 + 1); //regular action like processing data
		} else {
			sorting_task(data, 10); //trigger sorting task every other cycle
		}
		loop--;
		yield(); //yield to next process
	} while (loop > 0);

	return 0;
}

//In this code, execute_action() performs different tasks based on the action_id — either performing a simple calculation or simulating data processing. These tasks represent real work being done, instead of just printing messages.

//P2 mimics secure application components (like a cryptographic service, data sanitizer, validator).
