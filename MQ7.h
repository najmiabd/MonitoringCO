#ifndef MQ7_H
#define MQ7_H
#include "Arduino.h"
#define CALIBRATION_SECONDS 30
#define _COEF_A0 100.0
#define _COEF_A1 -1.513
#define _LOAD_RES 1
#define _CALIBRATION_CONSTANT 5

class MQ71 {
public:
	MQ71(int pin) : a_pin(pin), v_in(5.0) { 
		;	// 5.0 Volts assumed / recommended
	}
	MQ71(int pin, float v_in) : a_pin(pin), v_in(v_in) {
		;
	}

	float readPpm();
	float readRs();
	float readRsRL();	// Rs / RL
	void calibrate();

	float getR0();

private:
	int a_pin;
	float v_in;

	#ifndef _R0 // If no hardcoded R0 value

	float R0;

	#else 		// else make constant

	const R0 = _R0;

	#endif		// end

	float convertVoltage(int voltage);
};

#endif


class MQ72 {
public:
	MQ72(int pin) : a_pin(pin), v_in(5.0) { 
		;	// 5.0 Volts assumed / recommended
	}
	MQ72(int pin, float v_in) : a_pin(pin), v_in(v_in) {
		;
	}

	float readPpm();
	float readRs();
	float readRsRL();	// Rs / RL
	void calibrate();

	float getR0();

private:
	int a_pin;
	float v_in;

	#ifndef _R0 // If no hardcoded R0 value

	float R0;

	#else 		// else make constant

	const R0 = _R0;

	#endif		// end

	float convertVoltage(int voltage);
};




class MQ73 {
public:
	MQ73(int pin) : a_pin(pin), v_in(5.0) { 
		;	// 5.0 Volts assumed / recommended
	}
	MQ73(int pin, float v_in) : a_pin(pin), v_in(v_in) {
		;
	}

	float readPpm();
	float readRs();
	float readRsRL();	// Rs / RL
	void calibrate();

	float getR0();

private:
	int a_pin;
	float v_in;

	#ifndef _R0 // If no hardcoded R0 value

	float R0;

	#else 		// else make constant

	const R0 = _R0;

	#endif		// end

	float convertVoltage(int voltage);
};




class MQ74 {
public:
	MQ74(int pin) : a_pin(pin), v_in(5.0) { 
		;	// 5.0 Volts assumed / recommended
	}
	MQ74(int pin, float v_in) : a_pin(pin), v_in(v_in) {
		;
	}

	float readPpm();
	float readRs();
	float readRsRL();	// Rs / RL
	void calibrate();

	float getR0();

private:
	int a_pin;
	float v_in;

	#ifndef _R0 // If no hardcoded R0 value

	float R0;

	#else 		// else make constant

	const R0 = _R0;

	#endif		// end

	float convertVoltage(int voltage);
};


