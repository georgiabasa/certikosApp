// P2 - Simulated system activity logger

#include <syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int tick = 0;
	int loop = 50;

	while (loop--) {
		tick++;

		if (tick % 5 == 0) {
			printf("LOG|P2|Tick:%d|Task:COMMS|Status:OK\n", tick);
		} else if (tick % 3 == 0) {
			printf("LOG|P2|Tick:%d|Task:NAV_CTRL|Status:COMPLETE\n", tick);
		} else {
			printf("LOG|P2|Tick:%d|Task:IDLE_OP|CPU_LOAD:%d%%\n", tick, (tick * 11) % 90);
		}

		yield();
	}

	return 0;
}

// P2 — Task Activity Logger (Execution Verifier)

// Logs deterministic simulation of task outcomes: communication checks, navigation control, etc.

// Purpose: Mimics logic of activity execution and error detection.
