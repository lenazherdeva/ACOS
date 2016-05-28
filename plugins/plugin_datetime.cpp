#include "plugin.h"
#include <iostream>
#include <ctime>


int plugin_datetime(int argc, char ** argv)
{
    time_t raw_time;
    struct tm * time_info;
    char buffer[80];

    time (&raw_time);
    time_info = localtime(&raw_time);

    strftime(buffer, 80,"%m.%d.%Y %I:%M:%S",time_info);
    std::string str(buffer);

    std::cout << str << std::endl;
    return 0;
}

/*
 * C++ plugin also works because of extern "C"
 */

extern "C" struct Plugin init()
{
    struct Plugin self = {"datetime", plugin_datetime};
    return self;
};