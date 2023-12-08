#include "Logger.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

namespace fs = std::filesystem;

// Define the static constant variable DISK_USAGE_THRESHOLD
const double Logger::DISK_USAGE_THRESHOLD = 0.9; // Set the threshold to 90%

Logger::Logger(const std::string& logDirectory, const std::string& logFilename, const std::string& tcpHost, int tcpPort) {
    this->logDirectory = logDirectory;
    fs::create_directories(logDirectory); // Create log directory if it doesn't exist

    logFilePath = logDirectory + "/" + logFilename;
    this->tcpHost = tcpHost;
    this->tcpPort = tcpPort;
}

Logger::~Logger() {
    // Nothing specific to clean up here
}

void Logger::log(const std::string& message) {
    logToFile(message); // Log to file
    logToTcp(message);  // Log to TCP
}

void Logger::logToFile(const std::string& message) {
    std::ofstream logFile(logFilePath, std::ios::app);

    if (logFile.is_open()) {
        time_t rawTime;
        struct tm* timeInfo;
        char buffer[80];

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);

        std::stringstream logStream;
        logStream << "[" << buffer << "] " << message << std::endl;

        logFile << logStream.str();
        logFile.close();

        // Check and clean older log files if necessary
        cleanOldLogFiles();
    } else {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}

void Logger::logToTcp(const std::string& message) {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        return;
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(tcpPort);

    if (inet_pton(AF_INET, tcpHost.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Error: Invalid host address." << std::endl;
        close(sockfd);
        return;
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Unable to connect to the server." << std::endl;
        close(sockfd);
        return;
    }

    // Send the message to the server
    if (write(sockfd, message.c_str(), message.length()) < 0) {
        std::cerr << "Error: Unable to send data to the server." << std::endl;
    }

    // Close the socket
    close(sockfd);
}

void Logger::cleanOldLogFiles() {
    // Get the total size of log files in the directory
    uint64_t totalLogSize = 0;
    for (const auto& entry : fs::directory_iterator(logDirectory)) {
        if (entry.is_regular_file()) {
            totalLogSize += fs::file_size(entry.path());
        }
    }

    // Calculate the remaining disk space
    uint64_t remainingSpace = fs::space(logDirectory).available;

    // Check if disk usage exceeds the threshold
    if (totalLogSize > DISK_USAGE_THRESHOLD * remainingSpace) {
        // Clean older log files
        for (const auto& entry : fs::directory_iterator(logDirectory)) {
            if (entry.is_regular_file()) {
                fs::remove(entry.path());
            }
        }
    }
}
