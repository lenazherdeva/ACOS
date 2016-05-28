#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <malloc.h>
#include <cstring>
#include "plugin_load.h"

std::vector<std::string> parse_input(std::string input)
{
    std::vector<std::string> words;
    words.push_back("");
    char quote_opened = 0;
    bool was_backslash = 0;
    for (char c : input) {
        bool skip = 0;
        if ((c == '"' || c == '\'') && !was_backslash) {
            skip = 1;
            if (c == quote_opened) {
                quote_opened = 0; // close already opened quote
            } else if (quote_opened == 0) {
                quote_opened = c; // open quote
            } else {
                skip = 0; // we found quote in another quote
            }
        }
        if (c == '\\' && !was_backslash) {
            was_backslash = 1;
        } else {
            was_backslash = 0;
        }
        if (isspace(c) && !quote_opened) {
            if (!words.back().empty())
                words.push_back("");
        } else if (!skip && !was_backslash) {
            words.back().push_back(c);
        }
    }
    if (quote_opened) {
        std::cerr << "WARN: quote " << quote_opened << " was not closed" << std::endl;
    }
    if (words.back().empty())
        words.pop_back();
    return words;
}

int calculate_function(const Plugin &plugin, const std::vector<std::string> &words)
{
    char ** argv = (char **)malloc((words.size() + 1) * sizeof(char *));
    for (size_t i = 0; i < words.size(); ++i) {
        argv[i] = (char *)malloc((words[i].size() + 1) * sizeof(char));
        memcpy(argv[i], words[i].c_str(), words[i].size());
        argv[i][words[i].size()] = 0;
    }
    argv[words.size()] = (char *)0;
    int code = plugin.function(words.size(), argv);
    for (size_t i = 0; i < words.size(); ++i) {
        free(argv[i]);
    }
    free(argv);
    return code;
}


std::string input;
std::vector<Plugin> commands;

int help(int, char **)
{
    printf("Hello; welcome to plugin manager\n");
    printf("you can load your own plugin by typing\n'load_plugin path_to_plugin'\n");
    printf("list of available commands:\n");
    for (const Plugin &p : commands) {
        printf("%s\n", p.name);
    }
    return 0;
}

int main()
{
    commands.push_back({"help", help});
    while (1) {
        std::cout << "type command >>> ";
        std::getline(std::cin, input);
        if (!std::cin) {
            std::cout << "exit" << std::endl;
            break;
        }
        auto words = parse_input(input);
        if (words.size() == 2 && words[0] == "load_plugin") {
            plugin_load(words[1], commands);
        }
        for (const Plugin &plugin : commands) {
            if (words[0] == plugin.name) {
                calculate_function(plugin, words);
            }
        }
    }
    return 0;
}
