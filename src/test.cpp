/*
 * @Author: Zhou Zijian 
 * @Date: 2024-02-21 01:47:27 
 * @Last Modified by: Zhou Zijian
 * @Last Modified time: 2024-02-21 02:40:22
 */

#ifdef __ARM_NEON
#include <arm_neon.h>
#endif
#include "TimePerf.h"
#include "test.h"

void test1(float *input1, float *input2, float *output, int size)
{
    TIMEPERF(test1);
    for (int i = 0; i < size; i++) {
        output[i] = input1[i] + input2[i];
    }
}

void test2(float *input1, float *input2, float *output, int size)
{
    TIMEPERF(test2);
#pragma clang loop vectorize(enable)
    for (int i = 0; i < size; i++) {
        output[i] = input1[i] + input2[i];
    }
}

void test3(float *input1, float *input2, float *output, int size)
{
    TIMEPERF(test3);
    int i = 0;
#ifdef __ARM_NEON
    for (; i < size - 3; i += 4) {
        float32x4_t v1 = vld1q_f32(input1 + i);
        float32x4_t v2 = vld1q_f32(input2 + i);
        float32x4_t v3 = vaddq_f32(v1, v2);
        vst1q_f32(output + i, v3);
    }
#endif
    for (; i < size; i++) {
        output[i] = input1[i] + input2[i];
    }
}

void test4(float *input1, float *input2, float *output, int size)
{
    TIMEPERF(test4);
    int i = 0;
    int alignSize = 0;
#ifdef __ARM_NEON
    alignSize = size & (~0x3);
    asm volatile(
        "1: \n"
        "ld1 {v0.4s}, [%[input1]], #16 \n"
        "ld1 {v1.4s}, [%[input2]], #16 \n"
        "fadd v0.4s, v0.4s, v1.4s    \n"
        "subs %w[size], %w[size], #4 \n"
        "st1 {v0.4s}, [%[output]], #16 \n"
        "bgt 1b \n"
        : [output] "+r"(output)
        : [input1] "r"(input1), [input2] "r"(input2), [size] "r"(size)
        : "memory", "v0", "v1"
    );
#endif
    int restSize = size - alignSize;
    for (; i < restSize; i++) {
        output[i] = input1[i] + input2[i];
    }
}