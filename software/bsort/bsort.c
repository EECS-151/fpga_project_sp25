#include "types.h"
#include "benchmark.h"
#include "ascii.h"
#include "uart.h"

// Source: Sanjay Chintapally
// Email: sanjay.chintapally@berkeley.edu
// New test written for branch predictor benchmarking

#define SIZE 500

static int32_t unsorted_array[SIZE];
static int32_t sorted_array[SIZE];

// Function to compare the unsorted array with the sorted array
uint32_t compare_arrays() {
    uint32_t mismatch_count = 0;
    for (uint32_t i = 0; i < SIZE; i++) {
        if (unsorted_array[i] != sorted_array[i]) {
            mismatch_count++;
        }
    }
    return mismatch_count;
}

// Function to perform bubble sort
uint32_t bubble_sort() {
    int32_t i, j;
    for (i = 0; i < SIZE - 1; i++) {
        for (j = 0; j < SIZE - i - 1; j++) {
            if (unsorted_array[j] > unsorted_array[j + 1]) {
                int32_t temp = unsorted_array[j];
                unsorted_array[j] = unsorted_array[j + 1];
                unsorted_array[j + 1] = temp;
            }
        }
    }
    return compare_arrays();
}

// Function to generate an unsorted array
void generate_unsorted_array() {
    for (int32_t i = 0; i < SIZE; i++) {
        unsorted_array[i] = SIZE - i; // Fill the array with values from SIZE to 1
    }
}

// Function to generate a sorted array
void generate_sorted_array() {
    for (int32_t i = 0; i < SIZE; i++) {
        sorted_array[i] = i + 1; // Fill the array with values from 1 to SIZE
    }
}

typedef void (*entry_t)(void);

int main(int argc, char**argv) {
    generate_unsorted_array();
    generate_sorted_array();
    run_and_time(&bubble_sort);
    // go back to the bios - using this function causes a jr to the addr,
    // the compiler "jals" otherwise and then cannot set PC[31:28]
    uint32_t bios = ascii_hex_to_uint32("40000000");
    entry_t start = (entry_t) (bios);
    start();
    return 0;
}
