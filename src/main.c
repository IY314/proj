#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: proj <subcmd> [args]\n");
        exit(1);
    } else {
        if (!strcmp(argv[1], "new")) {
            parse_new(argc - 1, &argv[1]);
        } else if (!strcmp(argv[1], "setdir")) {
            
        } else {
            fprintf(stderr, "Usage: proj <subcmd> [args]\n");
            exit(1);
        }
    }
}
