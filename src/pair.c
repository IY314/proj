#include <string.h>

#include "pair.h"

struct Pair *create_pair(char *key, char *value) {
    struct Pair *pair = malloc(sizeof(struct Pair));
    pair->key = malloc(strlen(key) + 1);
    strcpy(pair->key, key);
    pair->value = malloc(strlen(value) + 1);
    strcpy(pair->value, value);
    return pair;
}

void free_pair(struct Pair *pair) {
    free(pair->key);
    free(pair->value);
    free(pair);
}

struct PairArray *create_pair_array() {
    struct PairArray *pair_array = malloc(sizeof(struct PairArray));
    pair_array->pairs = malloc(sizeof(struct Pair *) * 2);
    pair_array->size = 0;
    return pair_array;
}

void push_pair_array(struct PairArray *pair_array, struct Pair *pair) {
    if (pair_array->size == pair_array->cap) {
        pair_array->cap *= 2;
        pair_array->pairs = realloc(pair_array->pairs, sizeof(struct Pair *) * pair_array->cap);
    }

    pair_array->pairs[pair_array->size++] = pair;
}

struct Pair *get_pair(struct PairArray *pair_array, char *key) {
    for (size_t i = 0; i < pair_array->size; i++) {
        if (!strcmp(pair_array->pairs[i]->key, key)) {
            return pair_array->pairs[i];
        }
    }

    return NULL;
}

void set_pair(struct PairArray *pair_array, char *key, char *value) {
    struct Pair *pair = get_pair(pair_array, key);
    if (pair == NULL) {
        push_pair_array(pair_array, create_pair(key, value));
    } else {
        free(pair->value);
        pair->value = malloc(strlen(value) + 1);
        strcpy(pair->value, value);
    }
}

void free_pair_array(struct PairArray *pair_array) {
    for (size_t i = 0; i < pair_array->size; i++) {
        free_pair(pair_array->pairs[i]);
    }
    free(pair_array->pairs);
    free(pair_array);
}