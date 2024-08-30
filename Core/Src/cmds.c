#include "cmds.h"

static Command *cur = NULL;

static Command *get_new_cmd() {
	Command *new = (Command *) malloc(sizeof(Command));
	new->opType = DRIVE;
	new->shdSend = 1;
	new->direction = 0;
	new->spd = 0;
	new->steerAngle = 0;
	new->value = 0;
	new->distType = TARGET_DIST;
	new->nxt = NULL;

	return new;
}

static void cmd_ack(UART_HandleTypeDef *uart, Command *cmd, uint8_t indicator) {
	uint8_t buf_size = cmd->str_size + 1;
	uint8_t *buf = (uint8_t *) malloc(buf_size * sizeof(uint8_t));
	*buf = indicator;
	memcpy(buf + 1, cmd->string, buf_size - 1);

	HAL_UART_Transmit(uart, buf, buf_size, HAL_MAX_DELAY);
	free(buf);
}

void cmd_process(UART_HandleTypeDef *uart, uint8_t *buf, uint8_t size) {
	Command *nxt = get_new_cmd();

	uint8_t c = *buf, *temp = buf;

	//first byte: command flag
	switch (c) {
		case CMD_DIST:
			nxt->opType = DIST_INFO;
			break;
		case CMD_MARKER:
			nxt->opType = MARKER_INFO;
			break;
		case CMD_FULLSTOP:
			nxt->direction = 0;
			break;

		case CMD_FWD_DIST_TARGET:
			nxt->direction = 1;
			nxt->distType = TARGET_DIST;
			break;

		case CMD_FWD_DIST_AWAY:
			nxt->direction = 1;
			nxt->distType = STOP_AWAY_FRONT;
			break;

		case CMD_BWD_DIST_TARGET:
			nxt->direction = -1;
			nxt->distType = TARGET_DIST;
			break;

		case CMD_BWD_DIST_AWAY:
			nxt->direction = -1;
			nxt->distType = STOP_AWAY_FRONT;
			break;

		case CMD_FWD_DIST_L:
			nxt->direction = 1;
			nxt->distType = STOP_L_IR;
			break;
		case CMD_FWD_DIST_R:
			nxt->direction = 1;
			nxt->distType = STOP_R_IR;
			break;
		case CMD_BWD_DIST_L:
			nxt->direction = -1;
			nxt->distType = STOP_L_IR;
			break;
		case CMD_BWD_DIST_R:
			nxt->direction = -1;
			nxt->distType = STOP_R_IR;
			break;
		default:
			//invalueid command, return.
			return;
	}

	if (nxt->opType == DRIVE && c != CMD_FULLSTOP) {
		temp++;
		nxt->spd = parse_uint16_t_until(&temp, CMD_SEPARATOR, 3);
		temp++;
		nxt->steerAngle = parse_float_until(&temp, CMD_SEPARATOR, 6);
		temp++;
		nxt->value = parse_float_until(&temp, CMD_END_CHAR, 6);
	} else {
		*(++temp) = CMD_END_CHAR;
	}

	//copy command.
	uint8_t str_size = temp - buf + 1;
	nxt->str_size = str_size;
	nxt->string = (uint8_t *) malloc(str_size * sizeof(uint8_t));
	memcpy(nxt->string, buf, str_size);


	if (cur == NULL) {
		cur = nxt;
	} else {
		Command *temp = cur;
		while (temp->nxt != NULL) {
			temp = temp->nxt;
		}
		temp->nxt = nxt;
	}

//	//acknowledge command has been received and queued.
//	cmd_ack(uart, nxt, CMD_RCV);
}


Command *cmd_pop() {
	Command *ret = cur;
	if (cur != NULL) cur = cur->nxt;
	return ret;
}

Command *cmd_peek() {
	return cur;
}

//find the nxt drive command (for chaining).
Command *cmd_peek_nxt_drive() {
	Command *temp = cur;
	while (temp != NULL && temp->opType != DRIVE) temp = temp->nxt;
	return temp;
}

void cmd_end(UART_HandleTypeDef *uart, Command *cmd) {
	if (cmd->shdSend) cmd_ack(uart, cmd, CMD_FINISH);
	free(cmd->string);
	free(cmd);
}

uint8_t cmd_type_match(Command *a, Command *b) {
	return (a->direction == b->direction)
			&& (a->spd == b->spd)
			&& (a->steerAngle == b->steerAngle)
			&& (a->distType == b->distType);
}
