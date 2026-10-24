#include <iostream>
#include <vector>
#include <cmath>

constexpr size_t N = 64 * 1024 * 1024; // 64M елементів (~256 MB)

__attribute__((noinline))
void vector_math(float* __restrict__ a, float* __restrict__ b, float* __restrict__ c, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] * b[i] + a[i] + 0.5f;
    }
}

__attribute__((noinline))
void heavy_transform(float* __restrict__ data, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        data[i] = std::sin(data[i]);
    }
}

__attribute__((noinline))
void process_pipeline(std::vector<float>& a, std::vector<float>& b, std::vector<float>& c) {
    vector_math(a.data(), b.data(), c.data(), a.size());
    heavy_transform(c.data(), 1024 * 1024);
}

int main() {
    std::cout << "Starting program...\n";
    std::vector<float> a(N, 1.5f);
    std::vector<float> b(N, 2.5f);
    std::vector<float> c(N, 0.0f);

    for (int epoch = 0; epoch < 5; ++epoch) {
        process_pipeline(a, b, c);
    }

    std::cout << "Done! Verification sum: " << c[0] + c[N - 1] << std::endl;
    return 0;
}
