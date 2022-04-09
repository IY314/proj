#pragma once

struct Pair {
    char *key;
    char *value;
};

struct Pair *create_pair(char *key, char *value);
void free_pair(struct Pair *pair);

struct PairArray {
    struct Pair **pairs;
    size_t size, cap;
};

struct PairArray *create_pair_array();
void push_pair_array(struct PairArray *pair_array, struct Pair *pair);
struct Pair *get_pair(struct PairArray *pair_array, char *key);
void set_pair(struct PairArray *pair_array, char *key, char *value);
void free_pair_array(struct PairArray *pair_array);
