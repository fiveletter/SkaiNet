/*
 * main.cpp
 *
 *  Created on: May 8, 2016
 *      Author: stewww
 */

#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
#include <algorithm>
#include <fstream>
#include "camera_control.h"
#include <iomanip>

#define PI                              3.14159265

// Using https://docs.google.com/spreadsheets/d/1dVvRKKmJEkJiPHRwzPk96dDeOD7zv3IpdrqrKPCfoHw/edit#gid=1510746868 for PID + static error calculations

const double taskFrequency = 10;                            ///< Frequency of the task running the PID loop
const double sineWaveAmplitudeScale = 2.0;                  ///< This is going to be how many half-screens off we are from the target
const double sineWaveFrequencyScale = 30 / taskFrequency;   ///< Some arbitrary frequency scalar
const double expansionSpeed = 0.03;                         ///< How fast the sine wave will expand
const double maximumExpansion = 1.0;                        ///< Capping the expansion

const double FOVOfCameraInDeg = 70;
const double halfScreensToError = (FOVOfCameraInDeg / 2);   ///< Error is just going to be degrees from the target
const double rotationPerSec = 0.25;                         ///< 100% effort rotations per sec
const double effortToErrorFix = 1 * 360 * rotationPerSec / taskFrequency;                          ///< Effort to how much we fix our "error" by


const int randMinDegrees = -5;
const int randMaxDegrees = 5;


// Blame the eclipse CDT for this....
/*
 * typedef struct {
    double P_Gain;
    double I_Gain;
    double D_Gain;
    double outputMin;
    double outputMax;
} PID_Config_S ;
 */
PID_Config_S myPIDConfig = {
        1.5/FOVOfCameraInDeg,   ///< P_Gain
        2.0/FOVOfCameraInDeg,   ///< I_Gain
        0.0/FOVOfCameraInDeg,   ///< D_Gain
        -1.0,
        1.0
};

PID_Variables_S pidVars = {
        &myPIDConfig,
};


//float runPIDController(PID_Variables_S * variables, float error);




double generateSineWave(double param)
{
    double result = std::min((param * expansionSpeed), maximumExpansion) * sin (param * sineWaveFrequencyScale *PI/180) + (rand() % (randMaxDegrees - randMinDegrees) - (double)(randMaxDegrees + randMinDegrees) / 2) / halfScreensToError;
    return sineWaveAmplitudeScale * result;
}

int main ()
{
    srand (time(NULL));
    std::ofstream output;
    output.open("Output.csv");

    // Used to describe the cumulative efforts of the PID controller to close the loop on the input
    double PIDCorrection = 0;
    // Treate x as ms
    printf("Time,Static Error,PID Correction\n");
    for (int x = 0; x < (taskFrequency * 15); x++)
    {
        double sineWaveOutput = generateSineWave(x);
        double errorInDegrees = sineWaveOutput * halfScreensToError - PIDCorrection;
        // Run PID control and check its effort with proportional "fix"
        PIDCorrection += effortToErrorFix * runPIDController(&pidVars, errorInDegrees);
        printf("%lf,%lf,%lf\n", (double)x / taskFrequency, sineWaveOutput, PIDCorrection / halfScreensToError);
        //output << std::setprecision(3) << (double)x / taskFrequency << "," << sineWaveOutput << "," << PIDCorrection / halfScreensToError << "\n";
        output << "P: " << std::setw(10) << std::setprecision(2) << pidVars.proportionalOut << ", I: " << std::setw(10) << pidVars.integralOut << ", D: " << std::setw(10) << pidVars.derivativeOut << ", PID: " << std::setw(5) << pidVars.PIDOut << "\n";
    }

}
