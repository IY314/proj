#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"

struct Pair *create_pair(const char *const key, const char *const value) {
    static struct Pair *pair;

    pair = malloc(sizeof(struct Pair));
    if (pair == NULL) return NULL;

    pair->key = malloc(strlen(key) + 1);
    if (pair->key == NULL) {
        free(pair);
        return NULL;
    }

    strcpy(pair->key, key);
    pair->value = malloc(strlen(value) + 1);
    if (pair->value == NULL) {
        free(pair->key);
        free(pair);
        return NULL;
    }

    strcpy(pair->value, value);
    return pair;
}

void free_pair(struct Pair *const pair) {
    // Check argument validity
    if (pair == NULL) return;

    // Free fields
    free(pair->key);
    free(pair->value);
    free(pair);
}

struct PairArray *create_pair_array() {
    static struct PairArray *pair_array;

    pair_array = malloc(sizeof(struct PairArray));
    if (pair_array == NULL) return NULL;

    pair_array->pairs = malloc(sizeof(struct Pair *) * 2);
    if (pair_array->pairs == NULL) {
        free(pair_array);
        return NULL;
    }

    pair_array->size = 0;
    return pair_array;
}

void push_pair_array(struct PairArray *const pair_array,
                     const struct Pair *pair) {
    if (pair_array->size == pair_array->cap) {
        pair_array->cap *= 2;
        pair_array->pairs =
            realloc(pair_array->pairs, sizeof(struct Pair *) * pair_array->cap);
    }

    memcpy(pair_array->pairs[pair_array->size++], pair, sizeof(struct Pair));
}

struct Pair *get_pair(const struct PairArray *const pair_array,
                      const char *const key) {
    for (size_t i = 0; i < pair_array->size; i++) {
        if (!strcmp(pair_array->pairs[i]->key, key)) {
            return pair_array->pairs[i];
        }
    }

    return NULL;
}

void set_pair(struct PairArray *const pair_array, const char *const key,
              const char *const value) {
    static struct Pair *pair;

    pair = get_pair(pair_array, key);
    if (pair == NULL) {
        push_pair_array(pair_array, create_pair(key, value));
    } else {
        free(pair->value);
        pair->value = malloc(strlen(value) + 1);
        if (pair->value == NULL) {
            free(pair->key);
            free(pair);
            perror("proj: malloc");
            exit(1);
        }

        strcpy(pair->value, value);
    }
}

void free_pair_array(struct PairArray *const pair_array) {
    // Check argument validity
    if (pair_array == NULL) return;

    // Free elements
    for (size_t i = 0; i < pair_array->size; i++) {
        free_pair(pair_array->pairs[i]);
    }

    free(pair_array->pairs);
    free(pair_array);
}
