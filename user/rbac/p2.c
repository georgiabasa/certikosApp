// Process 2 - action execution

#include <syscall.h>
#include <stdio.h>

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

	while(1) {
		action_counter++;
		execute_action(action_counter % 2 + 1); //cycle between action 1 and 2
		yield(); //yield to next process
	}
}

//In this code, execute_action() performs different tasks based on the action_id — either performing a simple calculation or simulating data processing. These tasks represent real work being done, instead of just printing messages.
