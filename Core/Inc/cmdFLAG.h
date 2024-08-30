#ifndef INC_CMDFLAG_H_
#define INC_CMDFLAG_H_

/* COMMAND FORMAT (IN ASCII)
 * NOTE: MAXIMUM LENGTH OF 20 characters.
 * <flag><speed><SEP><angle><SEP><val><END>
 *
 * <flag>: 1 char
 * - use one of the characters below to specify which action to take.
 *
 * ----------- FOR DRIVE COMMANDS ONLY ------------
 * <speed>: 1-3 chars
 * - specify speed to drive, from 0 to 100 (integer).
 *
 * <angle>: 1+ chars, in degrees
 * - specify angle to steer, from -25 to 25 (float).
 * - negative angle: steer left, positive angle: steer right.
 *
 *
 * <val>: 1+ chars, in cm
 * - specify distance to drive, from 0 to 500 (float).
 * - (ONLY FOR DIST_TARGET commands) when <angle> != 0:
 * 		specify turn angle to complete, from 0 to 360 (float).
 * ----------- FOR DRIVE COMMANDS ONLY ------------
 *
 * <SEP>: character specified below as CMD_SEP ('|').
 * <END>: character specified below as CMD_END ('\n').
 *
 * e.g., to drive FWD at speed 50 for 30cm going straight:
 * send 'T50|0|30\n'
 *
 * e.g., to drive BWD at speed 20 until 5cm away while wheels are steering left 10 degrees:
 * send 'w20|-10|5\n'
 *
 * For return messages, the robot will send back the following:
 * <INDICATOR><CMD_STR>
 *
 * <CMD_STR>: original command string sent (including end char)
 *
 * <INDICATOR>:
 * - CMD_RCV (specified below as 'r'): command has been received
 * - CMD_FIN (specified below as 'f'): command has been finished
 * */

#define CMD_FULLSTOP 'S'				//bring car to a complete stop. (all other fields are not required, i.e., send 'S\n')

#define CMD_FWD_DIST_TARGET 'T'		//go FWD for a target distance/angle.
#define CMD_FWD_DIST_AWAY 'W'		//go FWD until within a certain distance.
#define CMD_BWD_DIST_TARGET 't'	//go BWD for a target distance/angle.
#define CMD_BWD_DIST_AWAY 'w'		//go BWD until a certain distance apart.

#define CMD_FWD_DIST_L 'L'			//go FWD until left IR sensor is greater than value provided.
#define CMD_FWD_DIST_R 'R'			//go FWD until right IR sensor is greater than value provided.
#define CMD_BWD_DIST_L 'l'			//go BWD until left IR sensor is greater than value provided.
#define CMD_BWD_DIST_R 'r'			//go BWD until right IR sensor is greater than value provided.

#define CMD_MARKER 'M'				//signal command has been passed. (used for tracking)
#define CMD_DIST 'D'				//signal start/stop of accumulative distance tracking. (all other fields are not required, i.e., send 'D\n')
//NOTE: distance tracked is NOT displacement; i.e., send different signals for different directions.

#define CMD_SEPARATOR '|'						//separator.
#define CMD_END_CHAR '\n'					//end character.
#define CMD_RECEIVED 'r'						//received.
#define CMD_FINISH 'f'

#endif /* INC_CMDFLAG_H_ */
