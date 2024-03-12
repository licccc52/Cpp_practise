#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


struct NetworkStats {
    long long RceivePackets;
    long long TransmitBytes;
};

NetworkStats getNetworkStats(const std::string& interface) {
    NetworkStats stats = {0, 0};

    std::ifstream file("/proc/net/dev");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find(interface) != std::string::npos) {
                std::istringstream iss(line);
                // Skipping interface name
                std::string skip;
                for (int i = 0; i <= 16; ++i) {
                    iss >> skip;
                    if(i==2)
                    {
                        stats.RceivePackets = std::stoll(skip);
                    }
                    else if(i==10)
                    {
                        stats.TransmitBytes = std::stoll(skip);
                    }
                    // std::cout << skip <<"   ";
                }
                // std::cout<< std::endl;
                // std::cout << "------------------------------" << std::endl;
                break;
            }
        }
        file.close();
    }

    return stats;
}

int main() {
 
    NetworkStats stats1 = getNetworkStats("lo:");
    NetworkStats stats2 = getNetworkStats("ens33:");

    std::cout << "lo本地:" << " Receive bytes: " << stats1.RceivePackets << ", Transmit bytes: " << stats1.TransmitBytes << std::endl;
    std::cout << " ens33:" << " Receive bytes: " << stats2.RceivePackets << ", Transmit bytes: " << stats2.TransmitBytes << std::endl;

    return 0;
}
 //g++ -std=c++11 -o netdata  netData.cpp -lstdc++^C