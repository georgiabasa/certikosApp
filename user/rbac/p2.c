// P2 - Simulated system activity logger

#include <syscall.h>
#include <stdio.h>
#include "command_table.h"

int main(int argc, char **argv) {
	int tick = 0;
	int loop = COMMAND_CYCLE_LEN;

	while (loop--) {
		CommandEntry entry = command_table[tick % 10]; // wrap around for demo
        	printf("µSAT|P2|Tick:%d|Task:%s|Status:%s|Code:%d\n", tick, entry.task, entry.status, entry.code);

		tick++;
		yield();
	}

	return 0;
}

// P2 — Task Activity Logger (Execution Verifier)

// Logs deterministic simulation of task outcomes: communication checks, navigation control, etc.

// Purpose: Mimics logic of activity execution and error detection.
