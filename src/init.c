#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "pair.h"
#include "proj.h"

void make_config() {
    char *home = getenv("HOME");
    if (home == NULL) {
        fprintf(stderr, "proj: $HOME not set\n");
        exit(1);
    }

    char *config_path = malloc(strlen(home) + strlen(PROJ_CONFIG_PATH) + 2);
    sprintf(config_path, "%s/%s", home, PROJ_CONFIG_PATH);

    if (mkdir(config_path, S_IRWXU) == -1) {
        if (errno != EEXIST) {
            free(config_path);
            perror("proj");
            exit(1);
        }
    }

    char *config_file = malloc(strlen(config_path) + 8);
    sprintf(config_file, "%s/config", config_path);

    free(config_path);

    FILE *fp = fopen(config_file, "w");

    free(config_file);

    if (fp == NULL) {
        perror("proj: fopen");
        exit(1);
    }

    fprintf(fp, "PROJECTDIR=%s/Projects\n", home);
    fclose(fp);
}
