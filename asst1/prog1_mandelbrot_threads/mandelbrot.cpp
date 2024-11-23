#include <stdio.h>
#include <pthread.h>

// Use this code to time your threads
#include "CycleTimer.h"

/*

  15418 Spring 2012 note: This code was modified from example code
  originally provided by Intel.  To comply with Intel's open source
  licensing agreement, their copyright is retained below.

  -----------------------------------------------------------------

  Copyright (c) 2010-2011, Intel Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

<<<<<<< HEAD
// Core computation of Mandelbrot set membershop
// Iterate complex number c to determine whether it diverges
=======

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  // For exit()
#include "CycleTimer.h"  // 用于测量线程执行时间

// Mandelbrot 集合计算核心函数
// 通过迭代判断复数 c 是否发散
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c
static inline int mandel(float c_re, float c_im, int count)
{
    float z_re = c_re, z_im = c_im;
    int i;
<<<<<<< HEAD
    for (i = 0; i < count; ++i)
    {

        if (z_re * z_re + z_im * z_im > 4.f)
            break;

=======
    // 最大迭代次数内，检查复数是否发散
    for (i = 0; i < count; ++i) {
        if (z_re * z_re + z_im * z_im > 4.f)  // 若模平方大于4，则视为发散
            break;

        // 计算新的复数 z 的实部和虚部
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c
        float new_re = z_re * z_re - z_im * z_im;
        float new_im = 2.f * z_re * z_im;
        z_re = c_re + new_re;
        z_im = c_im + new_im;
    }
    return i;
}

// 串行计算 Mandelbrot 集合图像的函数
// 生成图像数据，记录每个像素迭代的次数
void mandelbrotSerial(
    float x0, float y0, float x1, float y1,  // 复数平面上的区域范围
    int width, int height,                  // 图像宽度和高度
    int startRow, int endRow,               // 计算的行范围
    int maxIterations,                      // 最大迭代次数
    int output[])                           // 输出数组，用于存储计算结果
{
    // 计算每个像素对应的复数步长
    float dx = (x1 - x0) / width;
    float dy = (y1 - y0) / height;

<<<<<<< HEAD
    for (int j = startRow; j < endRow; j++)
    {
        for (int i = 0; i < width; ++i)
        {
=======
    // 遍历指定行范围内的每个像素
    for (int j = startRow; j < endRow; j++) {
        for (int i = 0; i < width; ++i) {
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c
            float x = x0 + i * dx;
            float y = y0 + j * dy;

            int index = (j * width + i);
            output[index] = mandel(x, y, maxIterations);  // 计算每个像素的迭代次数
        }
    }
}

<<<<<<< HEAD
// Struct for passing arguments to thread routine
typedef struct
{
    float x0, x1;
    float y0, y1;
    unsigned int width;
    unsigned int height;
    int maxIterations;
    int *output;
    int threadId;
    int numThreads;
} WorkerArgs;

//
// workerThreadStart --
//
// Thread entrypoint.
void *workerThreadStart(void *threadArgs)
{
    WorkerArgs *args = static_cast<WorkerArgs *>(threadArgs);

    // // 计时代码
    // double startTime = CycleTimer::currentSeconds();

    // 修改工作分配策略
    for (int j = args->threadId; j < args->height; j += args->numThreads)
    {
        for (int i = 0; i < args->width; ++i)
        {
            float x = args->x0 + i * ((args->x1 - args->x0) / args->width);
            float y = args->y0 + j * ((args->y1 - args->y0) / args->height);
            int index = j * args->width + i;
            args->output[index] = mandel(x, y, args->maxIterations);
        }
    }

    // // 计时代码
    // double endTime = CycleTimer::currentSeconds();
    // printf("Thread %d: [%.3f] ms\n", args->threadId, (endTime - startTime) * 1000);
=======
// 用于传递给线程的参数结构体
typedef struct {
    float x0, x1;          // 复数平面上的 x 轴范围
    float y0, y1;          // 复数平面上的 y 轴范围
    int width;             // 图像的宽度
    int height;            // 图像的高度
    int maxIterations;     // 最大迭代次数
    int* output;           // 输出数组，存储每个像素的迭代结果
    int threadId;          // 线程的 ID
    int numThreads;        // 线程总数
} WorkerArgs;

// 线程的入口函数
void* workerThreadStart(void* threadArgs) {

    WorkerArgs* args = (WorkerArgs*) threadArgs;  // 将传入的参数转换为 WorkerArgs 类型

    // 计算每个线程需要处理的行范围
    int totalRows = args->height;
    int rowsPerThread = totalRows / args->numThreads;
    int startRow = args->threadId * rowsPerThread;
    int endRow = (args->threadId == args->numThreads - 1) 
                    ? totalRows  // 最后一个线程负责剩余的行
                    : startRow + rowsPerThread;

    // 调用串行计算函数，计算指定行范围内的 Mandelbrot 集合
    mandelbrotSerial(
        args->x0, args->y0, args->x1, args->y1,
        args->width, args->height,
        startRow, endRow,
        args->maxIterations,
        args->output);
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c

    return NULL;  // 线程结束
}

// 使用多线程计算 Mandelbrot 集合的主函数
void mandelbrotThread(
    int numThreads,        // 线程数
    float x0, float y0,    // 复数平面上的起始点 (x0, y0)
    float x1, float y1,    // 复数平面上的终止点 (x1, y1)
    int width, int height, // 图像宽度和高度
    int maxIterations,     // 最大迭代次数
    int output[])          // 输出数组
{
    const static int MAX_THREADS = 32;  // 允许的最大线程数

    if (numThreads > MAX_THREADS) {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    pthread_t workers[MAX_THREADS];   // 线程数组
    WorkerArgs args[MAX_THREADS];     // 线程参数数组

<<<<<<< HEAD
    for (int i = 0; i < numThreads; i++)
    {
        // TODO: Set thread arguments here.
=======
    // 初始化每个线程的参数
    for (int i = 0; i < numThreads; i++) {
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c
        args[i].threadId = i;
        args[i].x0 = x0;
        args[i].x1 = x1;
        args[i].y0 = y0;
        args[i].y1 = y1;
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].output = output;
        args[i].numThreads = numThreads;
    }

<<<<<<< HEAD
    // Fire up the worker threads.  Note that numThreads-1 pthreads
    // are created and the main app thread is used as a worker as
    // well.

    for (int i = 1; i < numThreads; i++)
=======
    // 创建并启动工作线程（主线程也参与计算）
    for (int i = 1; i < numThreads; i++) {
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c
        pthread_create(&workers[i], NULL, workerThreadStart, &args[i]);
    }

    // 主线程处理自己的任务
    workerThreadStart(&args[0]);

<<<<<<< HEAD
    // wait for worker threads to complete
    for (int i = 1; i < numThreads; i++)
=======
    // 等待所有子线程完成
    for (int i = 1; i < numThreads; i++) {
>>>>>>> 165155cf79abcc3d56f092198693727cf8ec2c4c
        pthread_join(workers[i], NULL);
    }
}


// void mandelbrotOpenMP(
//     int numThreads,        // 线程数
//     float x0, float y0,    // 复数平面上的起始点 (x0, y0)
//     float x1, float y1,    // 复数平面上的终止点 (x1, y1)
//     int width, int height, // 图像宽度和高度
//     int maxIterations,     // 最大迭代次数
//     int output[])          // 输出数组
// {
//     // TODO: finish openmp version of mandelbrot
//     #pragma omp parallel{
//         // ...
//     }
//     # pragma omp parallel for{
//         // ...
//     }

// }
