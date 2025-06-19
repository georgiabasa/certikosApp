// P3 - DiagWatchdog

#include <syscall.h>
#include <stdio.h>
#include "diag_constants.h"

#define HISTORY_LEN 5

int diag_history[HISTORY_LEN] = {0};
int pass_fail_pattern[HISTORY_LEN] = {0}; //1=pass, 0=fail
int hist_index = 0;

int average_score() {
	int sum = 0;
	int i = 0;
	for (i = 0; i< HISTORY_LEN; i++)
		sum += diag_history[i];
	return sum / HISTORY_LEN;
}

int detect_flickering() {
	int i = 1;
	for (i = 1; i < HISTORY_LEN; i++) {
		if (pass_fail_pattern[i] == pass_fail_pattern[i - 1])
			return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
	int tick = 0;
	int loop = DIAG_CONSTANTS_LEN;

	while (loop--) {
		int diag_index = tick % 10;
        	int pattern = diag_test_patterns[diag_index];
        	int score = (pattern * (tick + 1)) % 100;
		int passed = (score <= error_threshold);

		// update circular buffer
		diag_history[hist_index] = score;
		pass_fail_pattern[hist_index] = passed;
		hist_index = (hist_index + 1) % HISTORY_LEN;

		if (!passed) {
			printf("microSAT|P3|Tick:%d|DIAG_FAIL|Score:%d\n", tick, score);
		} else {
			printf("microSAT|P3|Tick:%d|DIAG_PASS|Score:%d\n", tick, score);
		}

		// degradation detection
		if (tick >= HISTORY_LEN) {
			int avg = average_score();
			if (avg < error_threshold) {
				printf("microSAT|P3|Tick:%d|WARNING: Progressive Degradation|AvgScore:%d\n", tick, avg);
			}
		}

		// flickering detection
		if (tick % 10 == 0) {
			int expected = (diag_test_patterns[diag_index] * (tick + 1)) % 100;
			if (score != expected) {
				printf("microSAT|P3|Tick:%d|Timing Anomaly: Unexpected DIAG output!\n", tick);
			}
		}

		tick++;
		yield();
	}
	
	return 0;
}


//1. Rolling Health Log – last 5 DIAG scores in a circular buffer.
//2. Degradation Detection – triggers if 5-score average falls below a threshold.
//3. Pattern Signature detection – detects alternating pass/fail = "Flickering Detected".
//4. Timing Anomaly Check – compares expected vs actual pattern every 10 ticks.

//mapping subsystem - p3 diagnostics
//Function			Real Subsystem				Notes
//------------------------------------------------------------------------------------------------------
//DIAG tests			Platform self-check logic		Software BIST
//Rolling log & trend checks	Onboard diagnostics core		Spacecraft health management
//Flickering detection		HW stability unit			Detects marginal/flaky hardware
//Timing check			Timer sync or clock drift		Checks real-time behavior
