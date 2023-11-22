#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int serialPort;
    struct termios tty;
    const char* portName = "/dev/ttyUSB0";  

    serialPort = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);     // Open the serial port

    if (serialPort == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        return 1;
    }

    // Set serial port parameters
    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Error getting serial port attributes." << std::endl;
        close(serialPort);
        return 1;
    }

    cfsetospeed(&tty, B115200);  // Set baud rate
    cfsetispeed(&tty, B115200);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;  // No parity
    tty.c_cflag &= ~CSTOPB;  // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;  // 8 data bits

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting serial port attributes." << std::endl;
        close(serialPort);
        return 1;
    }

    char buffer[100];     // Read data from the serial port
    ssize_t bytesRead;

    while (true) {
        bytesRead = read(serialPort, buffer, sizeof(buffer));

        if (bytesRead > 0)
		{ 
            std::cout.write(buffer, bytesRead);     // Read data from the serial port
        } 
		if (bytesRead < 0)
		{ 
            std::cerr << "Error reading from serial port." << std::endl;
            break;
        }
    }

    close(serialPort);     // Close the serial port

    return 0;
}
