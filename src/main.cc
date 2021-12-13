/**
 * @file main.cc
 * @author Mit Bailey (mitbailey99@gmail.com)
 * @brief
 * @version See Git tags for version information.
 * @date 2021.12.13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <unistd.h>
#include "meb_convert.h"
#include "meb_print.h"

#define CYCLE_TIME 0.01

/**
 * @brief
 *
 * @param setpoint Desired value.
 * @param pv Process variable, the actual real current value.
 * @param Kp Proportional gain (optional, 0 by default).
 * @param Ki Integral action (optional, 0 by default).
 * @param Kd Derivative action (optional, 0 by default).
 * @return float
 */
float PIDController(float setpoint, float pv, float Kp = 0.f, float Ki = 0.f, float Kd = 0.f)
{
    // Static declarations.
    static float error = 0.f;
    static float prev_error = 0.f;
    static float ierr = 0.f;
    static float It = 0.f;

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

int main()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    for (int i = 0; (pv > setpoint + 0.0001) || (pv < setpoint - 0.0001); i++)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 0, 0);
        // pv += (pid_out / 2.f);
        pv += pid_out;
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
        usleep(SEC_TO_USEC(CYCLE_TIME));
    }

    bprintlf("final pv: %.08f", pv);
}