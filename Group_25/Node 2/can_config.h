#pragma once

#include "can_controller.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define F_OSC 42000000
#define TQ 8 //Set a time quanta


enum can_configs {
	sync = 1,
	proqSeg = 1,
	ps1 = 8,
	ps2 = 6,
	sjw = 1,
	brp_node1 = 8,
	brp_node2 = 42
};

enum BAUD_RATE {
	CAN_BAUD_100000 = 100000,
	CAN_BAUD_125000 = 125000,
	CAN_BAUD_250000 = 250000,
	CAN_BAUD_500000 = 500000
};



