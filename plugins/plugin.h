#ifndef ACOS_PLUGIN_H
#define ACOS_PLUGIN_H

typedef int (*function_type)(int argc, char ** argv);

struct Plugin
{
    const char * name;
    function_type function;
};

#endif
