#pragma once

#include "pair.h"

struct PairArray *parse_file(const char *const path);

int dump_file(const struct PairArray *const pair_array, const char *const path);
