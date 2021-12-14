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

#include <stdlib.h>
#include <unistd.h>
#include "pid.hcc"
#include "test.hcc"
#include "meb_convert.h"
#include "meb_print.h"

int main()
{
    bprintlf("Direct test...");
    int retval = test::direct();
    bprintlf("Constant offset test...");
    retval += test::constant_offset();
    bprintlf("Constant multiple test...");
    retval += test::constant_multiple();
    bprintlf("Increasing offset test...");
    retval += test::increasing_offset();
    bprintlf("Increasing multiple test...");
    retval += test::increasing_multiple();

    if (retval >= 5)
    {
        bprintlf(BLUE_FG "Tests completed successfully!");
    }
    else
    {
        bprintlf(FATAL "%d tests failed!", 5 - retval);
    }
}