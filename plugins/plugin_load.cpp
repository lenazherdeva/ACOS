#include <gnu/lib-names.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <vector>
#include <string>
#include "plugin_load.h"
#include "plugin.h"

int plugin_load(const std::string &filename, std::vector<Plugin> &plugins)
{
    fprintf(stderr, "trying to load '%s'\n", filename.c_str());
    void * plugin = dlopen(filename.c_str(), RTLD_NOW);
    if (!plugin) {
        perror("dlopen");
        fprintf(stderr, "dlerror: %s\n", dlerror());
        return -1;
    }
    struct Plugin (*init_func)(void);
    *(void **) (&init_func) = dlsym(plugin, "init");  // man 3 dlsym, dlopen
    struct Plugin to_load = (*init_func)();
    plugins.push_back(to_load);
    fprintf(stderr, "plugin '%s' was successfully loaded\n", filename.c_str());
    return 0;
}