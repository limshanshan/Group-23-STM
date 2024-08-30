#ifndef INC_CMDS_H_
#define INC_CMDS_H_

#include "main.h"
#include <stdlib.h>
#include <string.h>
#include "cmdFLAG.h"
#include "calc_conversions.h"

enum _cmdOpType {
	DRIVE,			//is a drive command, i.e., robot will move.

	//Commands related to relaying information.
	DIST_INFO,		//toggle start/stop of accumulative distance tracking.
	MARKER_INFO		//arbitary marker.
};
enum _cmdDistType {
	TARGET_DIST,			//drive for this distance
	STOP_AWAY_FRONT,		//stop when roughly this distance away from front.
	STOP_L_IR,			//stop when left IR sensor is more than threshold.
	STOP_R_IR,			//stop when right IR sensor is more than threshold.
};

typedef enum _cmdOpType CmdOpType;
typedef enum _cmdDistType CmdDistType;

struct command_t {
	//command op type
	CmdOpType opType;

	//command string
	uint8_t shdSend; 	//if command should be tracked for finishing.
	uint8_t *string;
	uint8_t str_size;

	/* start: DRIVE parameters */
	//motor directives
	int8_t direction;				//-1: backward, 0: stop, 1: forward
	uint8_t spd;			//0 to 100
	float steerAngle;	//-25 to 25

	//distance directives
	CmdDistType distType;
	float value;				//for angle != 0: angle to turn; for angle = 0: distance to drive.
	/* end: DRIVE parameters */

	struct command_t *nxt;
};

typedef struct command_t Command;

void cmd_process(UART_HandleTypeDef *uart, uint8_t *buf, uint8_t size);
Command *cmd_pop();
Command *cmd_peek();
Command *cmd_peek_next_drive();
void cmd_end(UART_HandleTypeDef *uart, Command *cmd);
uint8_t cmd_type_match(Command *a, Command *b);

#endif /* INC_CMDS_H_ */
