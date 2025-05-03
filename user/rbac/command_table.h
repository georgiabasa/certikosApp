// Simulated Mission Logic

#ifndef COMMAND_TABLE_H
#define COMMAND_TABLE_H

#define COMMAND_CYCLE_LEN 60

typedef struct {
	int tick;
	const char* task;
	const char* status;
	int code;
} CommandEntry;

static const CommandEntry command_table[COMMAND_CYCLE_LEN] = {
	{0, "COMMS_CHECK", "OK", 200},
	{1,  "NAV_UPDATE", "OK", 220},
    	{2,  "PAYLOAD_TX", "FAIL", 501},
    	{3,  "THERMAL_CTRL", "OK", 210},
    	{4,  "ATTITUDE_ADJ", "OK", 202},
    	{5,  "IDLE", "OK", 100},
    	{6,  "IDLE", "OK", 100},
    	{7,  "PAYLOAD_TX", "OK", 200},
    	{8,  "NAV_UPDATE", "FAIL", 503},
    	{9,  "IDLE", "OK", 100},
	{10, "COMMS_CHECK", "OK", 200},
	{11,  "NAV_UPDATE", "OK", 220},
    	{12,  "PAYLOAD_TX", "FAIL", 501},
    	{13,  "THERMAL_CTRL", "OK", 210},
    	{14,  "ATTITUDE_ADJ", "OK", 202},
    	{15,  "IDLE", "OK", 100},
    	{16,  "IDLE", "OK", 100},
    	{17,  "PAYLOAD_TX", "OK", 200},
    	{18,  "NAV_UPDATE", "FAIL", 503},
    	{19,  "IDLE", "OK", 100},
	{20, "COMMS_CHECK", "OK", 200},
	{21,  "NAV_UPDATE", "OK", 220},
    	{22,  "PAYLOAD_TX", "FAIL", 501},
    	{23,  "THERMAL_CTRL", "OK", 210},
    	{24,  "ATTITUDE_ADJ", "OK", 202},
    	{25,  "IDLE", "OK", 100},
    	{26,  "IDLE", "OK", 100},
    	{27,  "PAYLOAD_TX", "OK", 200},
    	{28,  "NAV_UPDATE", "FAIL", 503},
    	{29,  "IDLE", "OK", 100},
	{30, "COMMS_CHECK", "OK", 200},
	{31,  "NAV_UPDATE", "OK", 220},
    	{32,  "PAYLOAD_TX", "FAIL", 501},
    	{33,  "THERMAL_CTRL", "OK", 210},
    	{34,  "ATTITUDE_ADJ", "OK", 202},
    	{35,  "IDLE", "OK", 100},
    	{36,  "IDLE", "OK", 100},
    	{37,  "PAYLOAD_TX", "OK", 200},
    	{38,  "NAV_UPDATE", "FAIL", 503},
    	{39,  "IDLE", "OK", 100},
	{40, "COMMS_CHECK", "OK", 200},
	{41,  "NAV_UPDATE", "OK", 220},
    	{42,  "PAYLOAD_TX", "FAIL", 501},
    	{43,  "THERMAL_CTRL", "OK", 210},
    	{44,  "ATTITUDE_ADJ", "OK", 202},
    	{45,  "IDLE", "OK", 100},
    	{46,  "IDLE", "OK", 100},
    	{47,  "PAYLOAD_TX", "OK", 200},
    	{48,  "NAV_UPDATE", "FAIL", 503},
    	{49,  "IDLE", "OK", 100},
	{50, "COMMS_CHECK", "OK", 200},
	{51,  "NAV_UPDATE", "OK", 220},
    	{52,  "PAYLOAD_TX", "FAIL", 501},
    	{53,  "THERMAL_CTRL", "OK", 210},
    	{54,  "ATTITUDE_ADJ", "OK", 202},
    	{55,  "IDLE", "OK", 100},
    	{56,  "IDLE", "OK", 100},
    	{57,  "PAYLOAD_TX", "OK", 200},
    	{58,  "NAV_UPDATE", "FAIL", 503},
    	{59,  "IDLE", "OK", 100}
};

#endif
