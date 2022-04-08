#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpg.h>

void parse_new(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: proj new <type> [args]\n");
        exit(1);
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

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: proj <subcmd> [args]\n");
        exit(1);
    } else {
        if (!strcmp(argv[1], "new")) {
            parse_new(argc - 1, &argv[1]);
        }
    }
}
