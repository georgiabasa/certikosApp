// P2 - TaskAnalyzer

#include <syscall.h>
#include <stdio.h>
#include <string.h>
#include "command_table.h"

RuntimeTask current = {0};
int tick = 0;

// find task metadata by name
const TaskMeta* get_meta(const char* name) {
	int i = 0;
	for (i = 0; i < sizeof(task_meta) / sizeof(TaskMeta); i++) {
		if (strcmp(task_meta[i].name, name) == 0)
			return &task_meta[i];
	}
	return NULL;
}

// simulate task outcome (use command_table result as prediction)
int simulate_outcome(const char* task, int current_tick) {
	// wraparound safe access
	const CommandEntry* entry = &command_table[current_tick % COMMAND_CYCLE_LEN];
	if (strcmp(entry->task, task) == 0)
		return strcmp(entry->status, "OK") == 0 ? 1 : 0;
	return 1; //default assume access
}

void log_task(const RuntimeTask* task) {
	printf("microSAT|P2|Tick:%d|Task:%s|State:%d|Retries:%d|Result:%s\n", tick, task->task, task->state, task->retries, task->result);
}

int main(int argc, char **argv) {
	int cmd_index = 0;
	int loop = COMMAND_CYCLE_LEN;

	while (loop--) {
		printf("\n");

		// if a task is done or never assigned, fetch next
		if (current.state == COMPLETE || current.state == FAILED || current.task == NULL) {
			CommandEntry entry = command_table[cmd_index % COMMAND_CYCLE_LEN];
			const TaskMeta* meta = get_meta(entry.task);

			if (!meta) {
				printf("Unknown task: %s\n", entry.task);
				cmd_index++;
				tick++;
				yield();
				continue;
			}

			// simulate skipping low_priority if a critical one is pending (e.g., after a fail)
			if (!meta->critical && current.retries == 2) {
				printf("Skipping low-priority task %s due to prior failure.\n", entry.task);
				cmd_index++;
				tick++;
				yield();
				continue;
			}

			current.task = entry.task;
			current.state = INIT;
			current.retries = 0;
			current.time_left = meta->duration;
			current.result = "PENDING";
			current.last_tick = tick;

			printf("New Task Fetched: %s\n", current.task);
			cmd_index++;
		}

		// process state machine
		switch (current.state) {
			case INIT:
				printf("Task %s entering WAIT.\n", current.task);
				current.state = WAIT;
				break;

			case WAIT:
				printf("Task %s WAIT tick.\n", current.task);
				current.state = EXEC;
				break;

			case EXEC:
				current.time_left--;
				printf("Executing %s | Remaining: %d ticks\n", current.task, current.time_left);
				if (current.time_left == 0) {
					int ok = simulate_outcome(current.task, tick);
					if (ok) {
						current.result = "OK";
						current.state = COMPLETE;
					} else {
						current.retries++;
						if (current.retries >= 3) {
							current.result = "RETRY_FAIL";
							current.state = FAILED;
						} else {
							current.result = "FAIL";
							current.state = INIT; //retry
							printf("Retry #%d for task %s\n", current.retries, current.task);
							current.time_left = get_meta(current.task)->duration;
						}
					}
				}
				break;

			case COMPLETE:
			case FAILED:
				//already handled next cycle
				break;
		}

		log_task(&current);
		tick++;
		yield();
	}
	return 0;
}

//1. Per-task state machine: INIT → WAIT → EXEC → COMPLETE.
//2. Retry logic on FAIL (max 2 attempts → escalation).
//3. Simulated execution time per task type.
//4. Critical task prioritization (ATTITUDE_ADJ, THERMAL_CTRL, etc.) — skips IDLE, COMMS_CHECK, etc., if time is tight.
//5. Internal memory only (no shared memory, fits CertiKOS model).

//REAL SUBSYSTEM MAPPING
//Task		Subsystem		Notes
//-------------------------------------------------------
//NAV_UPDATE	Guidance/Nav		Critical path
//ATTITUDE_ADJ	Attitude Control	Life-critical
//THERMAL_CTRL	Thermal Mgmt		Protects systems
//PAYLOAD_TX	Comm subsystem		Opportunistic
//COMMS_CHECK	Telemetry check		Maintenance
//IDLE		NOP			Skippable
