/*
 * camera_control.h
 *
 *  Created on: May 8, 2016
 *      Author: stewww
 */

#ifndef CAMERA_CONTROL_H_
#define CAMERA_CONTROL_H_


#include <algorithm>

typedef struct {
    double P_Gain;
    double I_Gain;
    double D_Gain;
    double outputMin;
    double outputMax;
} PID_Config_S ;

typedef struct {
    PID_Config_S * pid_config;
    double proportionalOut;
    double integralOut;
    double derivativeOut;
    double errorOut;
    double PIDOut;
} PID_Variables_S ;

extern const double taskFrequency;

double runPIDController(PID_Variables_S * variables, double error)
{
    // Calculating proportional error
    variables->proportionalOut =  error * variables->pid_config->P_Gain;

    // Calculating integral error
    variables->integralOut += error * variables->pid_config->I_Gain / taskFrequency;

    // Calculate the derivative error
    variables->derivativeOut = (variables->errorOut - error) * variables->pid_config->D_Gain;

    // Calculate the saturation error to correct our integral error
    double outputPreSat = variables->proportionalOut + variables->integralOut + variables->derivativeOut;
    double output = std::max(outputPreSat, variables->pid_config->outputMin);
    output = std::min(output, variables->pid_config->outputMax);
    variables->integralOut -= (outputPreSat - output);
    variables->PIDOut = output;
    return variables->PIDOut;
}

#endif /* CAMERA_CONTROL_H_ */
