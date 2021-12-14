/**
 * @file pid.cc
 * @author Mit Bailey (mitbailey99@gmail.com)
 * @brief 
 * @version See Git tags for version information.
 * @date 2021.12.14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <unistd.h>
#include "pid.hcc"
#include "meb_convert.h"
#include "meb_print.h"

float PIDController(float setpoint, float pv, float Kp = 0.f, float Ki = 0.f, float Kd = 0.f)
{
    // Static declarations.
    static float error = 0.f;
    static float prev_error = 0.f;
    static float ierr = 0.f;

    // Error calculations.
    prev_error = error;
    error = setpoint - pv;
    ierr += error; // Integral error.
    float derr = error - prev_error; // Derivative error.

    // Calculate P, I, and D components of the output.
    float P = Kp * error;
    float I = Ki * ierr * CYCLE_TIME;
    float D = Kd * derr / CYCLE_TIME;

    return P + I + D;
}