#include "uart.hpp"
#include <thread>
#include <chrono>  

int main() {
    UART uart("COM9");
    DataLogger dataLogger("data_uart.txt");

    if (uart.isValid() && dataLogger.isValid()) {
        while (true) {
            std::vector<char> receivedData = uart.readData();
            if (!receivedData.empty()) {
                dataLogger.logData(receivedData);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}