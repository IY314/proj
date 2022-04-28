#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfgfile.h"
#include "proj.h"

struct PairArray *parse_file(const char *const path) {
    // Check argument validity
    if (path == NULL) {
        return NULL;
    }

    static FILE *fp;
    static struct PairArray *pair_array;
    static char *line, *key, *value;
    static size_t len;
    static ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL) {
        return NULL;
    }

    pair_array = create_pair_array();

    line = NULL;
    len = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        key = strtok(line, "=");
        value = strtok(NULL, "\n");
        push_pair_array(pair_array, create_pair(key, value));
    }

    fclose(fp);
    free(line);

    return pair_array;
}

int dump_file(const struct PairArray *const pair_array,
              const char *const path) {
    // Check argument validity
    if (pair_array == NULL || pair_array->size == 0 || path == NULL ||
        path[0] == '\0') {
        return -1;
    }

    static FILE *fp;
    static size_t i;

    fp = fopen(path, "w");
    if (fp == NULL) {
        return -1;
    }

    for (i = 0; i < pair_array->size; i++) {
        fprintf(fp, "%s=%s\n", pair_array->pairs[i]->key,
                pair_array->pairs[i]->value);
    }

    fclose(fp);
    return 0;
}

void parse_setdir(const int argc, char *const *argv) {
    if (argc != 2) {
        errexit("proj: setdir: invalid number of arguments\n");
    }

    static char *dir, *home, *config_path;
    static struct PairArray *pair_array;
    static int status;

    dir = argv[1];
    home = get_home();

    config_path = malloc(strlen(home) + 14);
    sprintf(config_path, "%s/.proj/config", home);
    pair_array = parse_file(config_path);
    set_pair(pair_array, "PROJECTDIR", dir);
    status = dump_file(pair_array, config_path);
    free(config_path);
    if (status == 0) {
        printf("proj: setdir: set project directory to '%s'\n", dir);
    } else {
        printf("proj: setdir: failed to set project directory to '%s'\n", dir);
    }
}
