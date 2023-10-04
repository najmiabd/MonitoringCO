#include "MQ7.h"
#include "Arduino.h"

float MQ71::getR0() {
	return R0;
}

float MQ71::readPpm() {
	return (float) _COEF_A0 * pow(
		readRs() / R0,
		_COEF_A1
	);
}

float MQ71::readRs() {
	return _LOAD_RES * readRsRL();
}

float MQ71::readRsRL() {
	float voltage = convertVoltage(
		analogRead(a_pin)
	);



	return (v_in - voltage) / voltage;
}

float MQ71::convertVoltage(int voltage) {

	return (float) voltage * (v_in / 1024.0);
}

void MQ71::calibrate() {
	#ifndef _R0	// 
	for (int i = 0; i <= CALIBRATION_SECONDS; i++) {
		delay(1000);
		R0 = readRs() / _CALIBRATION_CONSTANT;
	}

	#endif		// end
}


float MQ72::getR0() {
	return R0;
}


float MQ72::readPpm() {
	return (float) _COEF_A0 * pow(
		readRs() / R0,
		_COEF_A1
	);
}

float MQ72::readRs() {
	return _LOAD_RES * readRsRL();
}

float MQ72::readRsRL() {
	float voltage = convertVoltage(
		analogRead(a_pin)
	);

	return (v_in - voltage) / voltage;
}

float MQ72::convertVoltage(int voltage) {
	//
	return (float) voltage * (v_in / 1023.0);
}

void MQ72::calibrate() {
	#ifndef _R0	// 
	for (int i = 0; i <= CALIBRATION_SECONDS; i++) {
		delay(1000);
		R0 = readRs() / _CALIBRATION_CONSTANT;
	}

	#endif		// end
}


float MQ73::getR0() {
	return R0;
}


float MQ73::readPpm() {
	return (float) _COEF_A0 * pow(
		readRs() / R0,
		_COEF_A1
	);
}

float MQ73::readRs() {
	return _LOAD_RES * readRsRL();
}

float MQ73::readRsRL() {
	float voltage = convertVoltage(
		analogRead(a_pin)
	);

	return (v_in - voltage) / voltage;
}

float MQ73::convertVoltage(int voltage) {
	//
	return (float) voltage * (v_in / 1023.0);
}

void MQ73::calibrate() {
	#ifndef _R0	// 
	for (int i = 0; i <= CALIBRATION_SECONDS; i++) {
		delay(1000);
		R0 = readRs() / _CALIBRATION_CONSTANT;
	}

	#endif		// end
}


float MQ74::getR0() {
	return R0;
}


float MQ74::readPpm() {
	return (float) _COEF_A0 * pow(
		readRs() / R0,
		_COEF_A1
	);
}

float MQ74::readRs() {
	return _LOAD_RES * readRsRL();
}

float MQ74::readRsRL() {
	float voltage = convertVoltage(
		analogRead(a_pin)
	);

	return (v_in - voltage) / voltage;
}

float MQ74::convertVoltage(int voltage) {
	//
	return (float) voltage * (v_in / 1023.0);
}

void MQ74::calibrate() {
	#ifndef _R0	// 
	for (int i = 0; i <= CALIBRATION_SECONDS; i++) {
		delay(1000);
		R0 = readRs() / _CALIBRATION_CONSTANT;
	}

	#endif		// end
}

