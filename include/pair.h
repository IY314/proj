#pragma once

struct Pair {
    char *key;
    char *value;
};

struct Pair *create_pair(const char *const key, const char *const value);
void free_pair(struct Pair *const pair);

struct PairArray {
    struct Pair *const *pairs;
    size_t size, cap;
};

struct PairArray *create_pair_array();
void push_pair_array(struct PairArray *const pair_array,
                     const struct Pair *pair);
struct Pair *get_pair(const struct PairArray *const pair_array,
                      const char *const key);
void set_pair(struct PairArray *const pair_array, const char *const key,
              const char *const value);
void free_pair_array(struct PairArray *const pair_array);
