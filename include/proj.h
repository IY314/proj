#pragma once

#define PROJ_CONFIG_PATH ".proj"
#define PROJ_CONFIG_FILE ".proj/config"

#define printerr(...) fprintf(stderr, __VA_ARGS__)
#define errexit(...)       \
    printerr(__VA_ARGS__); \
    exit(1)

const char *get_home();

void parse_new(const int argc, char *const *argv);
void parse_setdir(const int argc, char *const *argv);

void make_config();
