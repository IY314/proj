#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proj.h"

const char *get_home() {
    // Get home environment variable
    const char *const home = getenv("HOME");
    if (home == NULL) {
        errexit("proj: $HOME not set\n");
    }

    return home;
}

int main(const int argc, char *const *argv) {
    const char *const home = get_home();

    char *const config_path = malloc(strlen(home) + 14);
    if (config_path == NULL) {
        perror("proj: malloc");
        exit(1);
    }

    sprintf(config_path, "%s/%s", home, PROJ_CONFIG_PATH);

    if (access(config_path, F_OK) == -1) {
        make_config();
    }

    free(config_path);

    if (argc < 2) {
        errexit("Usage: proj <subcmd> [args]\n");
    } else {
        if (!strcmp(argv[1], "new")) {
            parse_new(argc - 1, &argv[1]);
        } else if (!strcmp(argv[1], "setdir")) {
            parse_setdir(argc - 1, &argv[1]);
        } else {
            errexit("Usage: proj <subcmd> [args]\n");
        }
    }
}
