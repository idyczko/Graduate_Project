/*
 * KALMAN.h
 *
 * Created: 2015-11-01 15:48:24
 *  Author: Igor
 */ 


#ifndef KALMAN_H_
#define KALMAN_H_
typedef struct {
	float q; //process noise covariance
	float r; //measurement noise covariance
	float x; //value
	float p; //estimation error covariance
	float k; //kalman gain
} kalman_state;


kalman_state kalman_init(float q, float r, float p, float intial_value);

void kalman_update(kalman_state* state, float measurement);


#endif /* KALMAN_H_ */