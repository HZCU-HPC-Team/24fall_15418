#include <algorithm>

// Generate random data
void initRandom(float *values, int N) {
    for (int i=0; i<N; i++)
    {
        // random input values
        values[i] = .001f + 2.998f * static_cast<float>(rand()) / RAND_MAX;
    }
}

// Generate data that gives high relative speedup
void initGood(float *values, int N) {
    for (int i=0; i<N; i++)
    {
        // Generate values that are small and close to each other
        values[i] = 0.001f + (0.002f * static_cast<float>(i) / N);
    }
}

// Generate data that gives low relative speedup
void initBad(float *values, int N) {
    for (int i=0; i<N; i++)
    {
        // Generate values that are large and vary significantly
        values[i] = 1000.0f + (1000.0f * static_cast<float>(i) / N);
    }
}

