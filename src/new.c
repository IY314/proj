#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpg/mpg.h>

#include "proj.h"

void parse_new(const int argc, char *const *argv) {
    // Check argument validity
    if (argv == NULL) return;

    // Check for project type
    if (argc < 2) {
        errexit("Usage: proj new <type> [args]\n");
    } else {
        if (!strcmp(argv[1], "c-cxx")) {
            struct Project *proj = get_proj("proj new", argc - 1, &argv[1]);
            if (proj == NULL) {
                printf("proj: %s\n", mpg_msg);
                mpg_quit();
                exit(mpg_status);
            }

            int status = build_proj_dir(proj);
            if (status == 0) {
                printf("proj: created project '%s'\n", proj->name);
            } else {
                printf("proj: failed to create project '%s'\n", proj->name);
            }

            destroy_proj(proj);
        }
    }
}
