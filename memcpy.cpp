#include <iostream>

void* my_memcpy(void* dest, const void* src, size_t n) {
    // 将 void* 类型的指针转换为 char* 类型，以便按字节复制
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);

    // 逐字节复制数据
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }

    return dest;
}

int main() {
    // 测试数据
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[5];

    // 调用手写的 memcpy() 函数复制数据
    my_memcpy(arr2, arr1, sizeof(arr1));

    // 输出复制后的数据
    for (int i = 0; i < 5; ++i) {
        std::cout << arr2[i] << " ";
    }

    return 0;
}
