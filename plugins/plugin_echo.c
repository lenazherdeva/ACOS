#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "plugin.h"

int plugin_echo(int argc, char ** argv)
{
    (void)argc;  /* else will get warning: unused variable */
    int p = fork();
    if (p == 0) {
        return execvp("echo", argv);
    } else if (p > 0) {
        int status;
        waitpid(p, &status, 0);
        return status;
    } else {
        return p;
    }
}

struct Plugin init()
{
    struct Plugin self = {"echo", plugin_echo};
    return self;
};