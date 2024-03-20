#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

double calculateMemoryUsage() {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    double total_mem = 0.0;
    double free_mem = 0.0;
    
    // 读取文件的每一行
    while (std::getline(meminfo, line)) {
        std::istringstream iss(line);
        std::string key;
        double value;
        
        // 解析每一行的键值对
        if (iss >> key >> value) {
            if (key == "MemTotal:") {
                total_mem = value;
            } else if (key == "MemFree:" || key == "Buffers:" || key == "Cached:") {
                // 将“MemFree”，“Buffers”和“Cached”三个字段的值相加以获得空闲内存
                free_mem += value;
            }
        }
    }
    
    // 计算内存使用率
    double mem_usage = 100.0 * (1.0 - (free_mem / total_mem));
    return mem_usage;
}

int main() {
    double memory_usage = calculateMemoryUsage();
    std::cout << "内存使用率：" << memory_usage << "%" << std::endl;
    
    return 0;
}

//g++ -std=c++11 -o memdata  memData.cpp -lstdc++