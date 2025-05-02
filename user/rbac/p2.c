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

void execute_action(int action_id) {
	//simulate an action based on the action_id
	switch(action_id) {
		case 1:
			printf("Executing action 1: Performing a calculation...\n");
			int result = 5*5; //simulate a calculation
			printf("Result of calculation: %d\n", result);
			break;
		case 2:
			printf("Executing action 2: Processing data...\n");
			//simulate data processing (could be an array or something simple
			int i = 0;
			for (i = 0; i < 5; i++) {
				printf("Processing data index %d\n", i);
			}
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

	while(1) {
		action_counter++;
		if (action_counter % 3 == 0) {
			printf("DELAY>>>>>>>\n");
			simulate_delay(5); //simulate a delay for every 3rd action
		} else if (action_counter % 2 == 0) {
			inside_counter++;
			execute_action(inside_counter % 2 + 1); //regular action like processing data
		} else {
			sorting_task(data, 10); //trigger sorting task every other cycle
		}
		yield(); //yield to next process
	}
}

//In this code, execute_action() performs different tasks based on the action_id — either performing a simple calculation or simulating data processing. These tasks represent real work being done, instead of just printing messages.
