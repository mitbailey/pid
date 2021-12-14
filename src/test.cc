/**
 * @file test.cc
 * @author Mit Bailey (mitbailey99@gmail.com)
 * @brief
 * @version See Git tags for version information.
 * @date 2021.12.14
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include "test.hcc"
#include "pid.hcc"
#include "meb_convert.h"
#include "meb_print.h"

int test::direct()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    int i = 0;
    for (; (pv > setpoint + LEEWAY) || (pv < setpoint - LEEWAY); i++)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 0, 0);

        pv += pid_out;
#ifndef SUPPRESS_PRINTS
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
#endif
        usleep(SEC_TO_USEC(CYCLE_TIME));

        if (i > 5000)
        {
            bprintlf(RED_FG "DID NOT CONVERGE! (%d >= 5000 ITERATIONS, PV = %.06f)", i, pv);
            return 0;
        }
    }

    bprintlf(GREEN_FG "CONVERGED IN %d ITERATIONS (PV = %.06f)", i, pv);
    return 1;
}

int test::constant_offset()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    int i = 0;
    for (; (pv > setpoint + LEEWAY) || (pv < setpoint - LEEWAY); i++)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 0.25, 0.001);

        pv += pid_out + 1;
#ifndef SUPPRESS_PRINTS
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
#endif
        usleep(SEC_TO_USEC(CYCLE_TIME));

        if (i > 5000)
        {
            bprintlf(RED_FG "DID NOT CONVERGE! (%d >= 5000 ITERATIONS, PV = %.06f)", i, pv);
            return 0;
        }
    }

    bprintlf(GREEN_FG "CONVERGED IN %d ITERATIONS (PV = %.06f)", i, pv);
    return 1;
}

int test::constant_multiple()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    int i = 0;
    for (; (pv > setpoint + LEEWAY) || (pv < setpoint - LEEWAY); i++)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 0.25, 0.001);

        pv += pid_out * 1.5;
#ifndef SUPPRESS_PRINTS
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
#endif
        usleep(SEC_TO_USEC(CYCLE_TIME));

        if (i > 5000)
        {
            bprintlf(RED_FG "DID NOT CONVERGE! (%d >= 5000 ITERATIONS, PV = %.06f)", i, pv);
            return 0;
        }
    }

    bprintlf(GREEN_FG "CONVERGED IN %d ITERATIONS (PV = %.06f)", i, pv);
    return 1;
}

int test::constant_multiple_large()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    int i = 0;
    for (; (pv > setpoint + LEEWAY) || (pv < setpoint - LEEWAY); i++)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 0.25, 0.001);

        pv += pid_out * 15;
#ifndef SUPPRESS_PRINTS
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
#endif
        usleep(SEC_TO_USEC(CYCLE_TIME));

        if (i > 5000)
        {
            bprintlf(RED_FG "DID NOT CONVERGE! (%d >= 5000 ITERATIONS, PV = %.06f)", i, pv);
            return 0;
        }
    }

    bprintlf(GREEN_FG "CONVERGED IN %d ITERATIONS (PV = %.06f)", i, pv);
    return 1;
}

int test::increasing_offset()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    int i = 0;
    for (float offset = 0.f; (pv > setpoint + LEEWAY) || (pv < setpoint - LEEWAY); i++, offset += 0.001)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 40, 0.004);

        pv += pid_out + offset;
#ifndef SUPPRESS_PRINTS
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
#endif
        usleep(SEC_TO_USEC(CYCLE_TIME));

        if (i > 5000)
        {
            bprintlf(RED_FG "DID NOT CONVERGE! (%d >= 5000 ITERATIONS, PV = %.06f)", i, pv);
            return 0;
        }
    }

    bprintlf(GREEN_FG "CONVERGED IN %d ITERATIONS (PV = %.06f)", i, pv);
    return 1;
}

int test::increasing_multiple()
{
    float setpoint = 0;
    float pv = 100;
    float pid_out = 0.f;

    int i = 0;
    for (float multiple = 1.f; (pv > setpoint + LEEWAY) || (pv < setpoint - LEEWAY); i++, multiple += 0.001)
    {
        pid_out = PIDController(setpoint, pv, 0.25, 40, 0.001);

        pv += pid_out * multiple;
#ifndef SUPPRESS_PRINTS
        bprintlf("(%d): pid_out, pv: %.04f, %.04f", i, pid_out, pv);
#endif
        usleep(SEC_TO_USEC(CYCLE_TIME));

        if (i > 5000)
        {
            bprintlf(RED_FG "DID NOT CONVERGE! (%d >= 5000 ITERATIONS, PV = %.06f)", i, pv);
            return 0;
        }
    }

    bprintlf(GREEN_FG "CONVERGED IN %d ITERATIONS (PV = %.06f)", i, pv);
    return 1;
}
