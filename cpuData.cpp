#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<double> get_cpu_avg_load() {
    std::vector<double> res;
    double avg_load = -1;
    std::ifstream loadavg_file("/proc/loadavg");
    if (loadavg_file.is_open()) {
        std::string line;
        std::getline(loadavg_file, line);
        std::istringstream iss(line);
        // 第一个值是最近 1 分钟的平均负载
        for(int i=0; i < 3; i++)
        {
            iss >> avg_load;
            res.push_back(avg_load);
        }

        loadavg_file.close();
    }
    return res;
}

int main() {
    std::vector<double> avg_load = get_cpu_avg_load();

    if (avg_load.size() == 3) {
        std::cout << " 1分钟平均负载: " << avg_load[0] << std::endl;
        std::cout << " 5分钟平均负载: " << avg_load[1] << std::endl;
        std::cout << "15分钟平均负载: " << avg_load[2] << std::endl;
    } else {
        std::cerr << "获取平均负载失败" << std::endl;
    }
    return 0;
}
