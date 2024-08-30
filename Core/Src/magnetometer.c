#include "magnetometer.h"

static I2C_HandleTypeDef *hi2c;
static MagCalSettings *settings;

static void magcal_preload(MagCalSettings *settings) {
	settings->biasVector[0] = 12.3750;
	settings->biasVector[1] = -56.4750;

	settings->scaleMatrix[0][0] = 0.8898;
	settings->scaleMatrix[0][1] = -0.5961;
	settings->scaleMatrix[1][0] = 0.8007;
	settings->scaleMatrix[1][1] = 1.1952;
}

void initialize_magnetometer(I2C_HandleTypeDef *i2cHandlePtr, MagCalSettings *settings) {
	hi2c = i2cHandlePtr;
	settings = settings;

	magcal_preload(settings);
}

//calibration sequence based on: https://www.atlantis-press.com/article/25847616.pdf
void magnetometer_settings() {
	float magRange[2][2]; //minimum, maximum for each axis
	float mag[2];
	char buf[20];

	//load initial values.
	HAL_Delay(500);
	ICM20948_readMagnetometer_XY(hi2c, mag);
	magRange[0][0] = mag[0];
	magRange[0][1] = mag[0];
	magRange[1][0] = mag[1];
	magRange[1][1] = mag[1];

	//find minimum and maximum of X and Y axis.
	OLED_ShowString(0, 0, "Min/Max XY");
	uint16_t i = 0;
	while (1) {
		ICM20948_readMagnetometer_XY(hi2c, mag);
		snprintf(buf, 20, "%.3f|%.3f", mag[0], mag[1]);
		OLED_ShowString(0, 10, buf);

		for (i = 0; i < 2; i++) {
			if (mag[i] < magRange[i][0]) magRange[i][0] = mag[i];
			if (mag[i] > magRange[i][1]) magRange[i][1] = mag[i];

			snprintf(buf, 20, "%.3f|%.3f", magRange[i][0], magRange[i][1]);
			OLED_ShowString(0, 10 * (i + 2), buf);
		}

		OLED_Refresh_Gram();
		if (user_is_pressed()) break;
	}

	//hard iron offset (center of ellipse).
	settings->biasVector[0] = (magRange[0][1] + magRange[0][0]) / 2;
	settings->biasVector[1] = (magRange[1][1] + magRange[1][0]) / 2;

	//calculate step size (to get an even number of readings).
	float xStep = (magRange[0][1] - magRange[0][0]) / MAGNETOMETER_CAL_SAMPLES;
	float yStep = (magRange[1][1] - magRange[1][0]) / MAGNETOMETER_CAL_SAMPLES;

	//read ellipse points.
	i = 0;
	float magVals[2][MAGNETOMETER_CAL_SAMPLES];

	OLED_Clear();
	OLED_ShowString(0, 0, "Tracing ellipse");
	snprintf(buf, 20, "%.3f|%.3f", xStep, yStep);
	OLED_ShowString(0, 20, buf);
	OLED_Refresh_Gram();

	//trace ellipse (and also get b).
	float b = -1, dist;
	while (i < MAGNETOMETER_CAL_SAMPLES) {
		ICM20948_readMagnetometer_XY(hi2c, mag);
		if (i == 0 ||
				(abs_float(mag[0] - magVals[0][i-1]) > xStep
				&& abs_float(mag[1] - magVals[1][i-1]) > yStep)) {
			magVals[0][i] = mag[0];
			magVals[1][i] = mag[1];

			snprintf(buf, 40, "On %i of %i", i+1, MAGNETOMETER_CAL_SAMPLES);
			OLED_ShowString(0, 10, buf);
			OLED_Refresh_Gram();
			i++;
		}

		dist = dist_squared(settings->biasVector[0], mag[0], settings->biasVector[1], mag[1]);
		if (b < 0 || dist < b) {
			b = dist;
		}
	}

	b = (float) sqrt((double) b);
	//find major axis points on ellipse.
	uint16_t j = 0;
	uint16_t a1, a2;
	float a = 0;
	for (i = 0; i < MAGNETOMETER_CAL_SAMPLES - 1; i++) {
		for (j = i + 1; j < MAGNETOMETER_CAL_SAMPLES; j++) {
			dist = dist_squared(magVals[0][i], magVals[0][j], magVals[1][j], magVals[1][j]);
			if (dist > a) {
				a = dist;
				a1 = i; a2 = j;
			}
		}
	}

	//calculate required parameters.
	a = (float) sqrt((double) a) / 2;

	//re-using mag as [k1, k2].
	mag[0] = abs_float(magVals[1][a1] - settings->biasVector[1]) / a;
	mag[1] = abs_float(magVals[0][a1] - settings->biasVector[0]) / a;

	//check if rotation should be clockwise or counter-clockwise (re-use i = clockwise).
	i = (magVals[0][a1] > settings->biasVector[0] && magVals[1][a1] > settings->biasVector[1])
			|| (magVals[0][a2] > settings->biasVector[0] && magVals[1][a2] > settings->biasVector[1]);

	//soft iron matrix.
	settings->scaleMatrix[0][0] = mag[1];
	settings->scaleMatrix[0][1] = mag[0];
	settings->scaleMatrix[1][0] = -(mag[0]) * a / b;
	settings->scaleMatrix[1][1] = mag[1] * a / b;
	if (!i) {
		//flip if counter-clockwise.
		settings->scaleMatrix[0][1] = -(settings->scaleMatrix[0][1]);
		settings->scaleMatrix[1][0] = -(settings->scaleMatrix[1][0]);
	}

	//User indication.
	OLED_Clear();
	OLED_ShowString(0, 0, "MagCal done");
	snprintf(buf, 20, "%.4f %.4f", settings->biasVector[0], settings->biasVector[1]);
	OLED_ShowString(0, 10, buf);
	snprintf(buf, 20, "%.4f %.4f", settings->scaleMatrix[0][0], settings->scaleMatrix[0][1]);
	OLED_ShowString(0, 20, buf);
	snprintf(buf, 20, "%.4f %.4f", settings->scaleMatrix[1][0], settings->scaleMatrix[1][1]);
	OLED_ShowString(0, 30, buf);
	OLED_Refresh_Gram();

	while(!user_is_pressed());

	OLED_Clear();
	OLED_Refresh_Gram();
}

void correctMagnetometer(float magnetometer[2]) {
	float x = magnetometer[0] - settings->biasVector[0], y = magnetometer[1] - settings->biasVector[1];
	magnetometer[0] = settings->scaleMatrix[0][0] * x + settings->scaleMatrix[0][1] * y;
	magnetometer[1] = settings->scaleMatrix[1][0] * x + settings->scaleMatrix[1][1] * y;
}
