//大端序转小端序
//网络字节序转主机字节序
#include <cstdint>
#include<iostream>

// 判断当前系统的字节序
bool isLittleEndian() {
    uint16_t test = 0x01;
    return (*(reinterpret_cast<uint8_t*>(&test)) == 0x01);
}

// 将16位整数从大端字节序转换为小端字节序
uint16_t swapEndian(uint16_t value) {
    return ((value >> 8) & 0x00FF) | ((value << 8) & 0xFF00);
}

// 将32位整数从大端字节序转换为小端字节序
uint32_t swapEndian(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >>  8) & 0x0000FF00) |
           ((value <<  8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

// 将64位整数从大端字节序转换为小端字节序
uint64_t swapEndian(uint64_t value) {
    return ((value >> 56) & 0x00000000000000FF) |
           ((value >> 40) & 0x000000000000FF00) |
           ((value >> 24) & 0x0000000000FF0000) |
           ((value >>  8) & 0x00000000FF000000) |
           ((value <<  8) & 0x000000FF00000000) |
           ((value << 24) & 0x0000FF0000000000) |
           ((value << 40) & 0x00FF000000000000) |
           ((value << 56) & 0xFF00000000000000);
}

int main() {
    // 示例
    uint16_t value16 = 0xABCD;
    uint32_t value32 = 0x12345678;
    uint64_t value64 = 0x0123456789ABCDEF;

    if (isLittleEndian()) {
        value16 = swapEndian(value16);
        value32 = swapEndian(value32);
        value64 = swapEndian(value64);
    }

    // 进行字节序转换后的值
    // 注意：输出结果可能会根据系统的字节序不同而不同
    std::cout << "16-bit swapped value: " << std::hex << value16 << std::endl;
    std::cout << "32-bit swapped value: " << std::hex << value32 << std::endl;
    std::cout << "64-bit swapped value: " << std::hex << value64 << std::endl;

    return 0;
}
