#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOOM_FILTER_SIZE 13  // Bit array size
#define NUM_HASH_FUNCTIONS 3  // Number of hash functions

// Hash functions
int hash1(int key) {
    return (3*key) % BLOOM_FILTER_SIZE;
}

int hash2(int key) {
    return (2 * key) % BLOOM_FILTER_SIZE;
}

int hash3(int key) {
    return (key*key)% BLOOM_FILTER_SIZE;
}

// Initialize Bloom filter
void initialize_bloom_filter(int *bloom_filter) {
    memset(bloom_filter, 0, BLOOM_FILTER_SIZE * sizeof(int));
}

// Insert element into Bloom filter
void insert(int *bloom_filter, int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);
    int index3 = hash3(key);

    bloom_filter[index1] = 1;
    bloom_filter[index2] = 1;
    bloom_filter[index3] = 1;
}

// Check membership in Bloom filter
const char* member(int *bloom_filter, int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);
    int index3 = hash3(key);

    if (bloom_filter[index3] == 1 && bloom_filter[index1] == 1 && bloom_filter[index2] == 1) {
        return "maybe";
    } else {
        return "no";
    }
}

// Print the Bloom filter state
void print_bloom_filter(int *bloom_filter) {
    printf("Bloom filter: ");
    for (int i = 0; i < BLOOM_FILTER_SIZE; i++) {
        printf("%d ", bloom_filter[i]);
    }
    printf("\n");
}

// Main function to demonstrate Bloom filter with user commands
int main() {
    int bloom_filter[BLOOM_FILTER_SIZE];
    initialize_bloom_filter(bloom_filter);

    char command[10];
    int key;

    printf("Enter commands (insert <key>, member <key>, print, or exit).\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "exit") == 0) {
            break;
        } else if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(bloom_filter, key);
            printf("Inserted key %d into the Bloom filter.\n", key);
        } else if (strcmp(command, "member") == 0) {
            scanf("%d", &key);
            printf("Membership of %d: %s\n", key, member(bloom_filter, key));
        } else if (strcmp(command, "print") == 0) {
            print_bloom_filter(bloom_filter);
        } else {
            printf("Unknown command. Please use 'insert', 'member', 'print', or 'exit'.\n");
        }
    }

    return 0;
}
