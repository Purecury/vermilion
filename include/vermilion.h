#ifndef VERMILION_H_INCLUDED
#define VERMILION_H_INCLUDED

#define DEBUG

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


#define NOERROR_CUTOFF 101

#define VN_SUCCESS(x)(x < NOERROR_CUTOFF)
#define VN_FAIL(x)(x >= NOERROR_CUTOFF)

#ifdef DEBUG
#define DEBUG_FAIL(message, ...) printf("[FAIL] (%s:%d): " message, __FILE__, __LINE__, ##__VA_ARGS__)
#define DEBUG_PASS(message, ...) printf("[PASS] (%s:%d): " message, __FILE__, __LINE__, ##__VA_ARGS__)
#define DEBUG_WARNING(message, ...) printf("[WARNING] (%s:%d): " message, __FILE__, __LINE__, ##__VA_ARGS__)
#define DEBUG_INFO(message, ...) printf("[INFO] (%s:%d): " message, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_FAIL(message, ...)
#define DEBUG_PASS(message, ...)
#define DEBUG_WARNING(message, ...)
#define DEBUG_INFO(message, ...)
#endif


#define KB(b)((size_t)(b * 1000))
#define MB(b)(KB(b) * 1000)
#define GB(b)(MB(b) * 1000)
#define TB(b)(GB(b) * 1000)
#define TO_PAGE_UP(x)(((x) + 4095) / 4096)
#define ALIGN_PAGE(x)((((x) + 4095) / 4096) * 4096)

#define TRUE 1
#define FALSE 0

typedef enum vnstatus {
    VNSTATUS_SUCCESS = 0,
    VNSTATUS_UNKNOWN_ERROR = NOERROR_CUTOFF,
} vnstatus_t;

typedef struct startinfo {
    const char** arg;
    int argCount;
    int tId;
} startinfo_t;

#endif
