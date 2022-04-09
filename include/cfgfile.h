#pragma once

#include "pair.h"

struct PairArray *parse_file(char *path);

int dump_file(struct PairArray *pair_array, char *path);
