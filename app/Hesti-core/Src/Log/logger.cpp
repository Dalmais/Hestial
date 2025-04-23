#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <unistd.h>

Logger::~Logger() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
    if (m_tcpSocket != -1) {
        close(m_tcpSocket);
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(const std::string& filePath, bool useTcp) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_logFile.open(filePath, std::ios::app);
    m_tcpEnabled = useTcp;

    if (m_tcpEnabled) {
        m_tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_tcpSocket < 0) {
            std::cerr << "⚠️ Failed to create TCP socket\n";
            m_tcpEnabled = false;
            return;
        }

        sockaddr_in server{};
        server.sin_family = AF_INET;
        server.sin_port = htons(45678);
        server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // 127.0.0.1

        if (connect(m_tcpSocket, (struct sockaddr*)&server, sizeof(server)) < 0) {
            std::cerr << "⚠️ Could not connect to TCP log server\n";
            close(m_tcpSocket);
            m_tcpSocket = -1;
            m_tcpEnabled = false;
        }
    }
}

void Logger::info(const std::string& message) {
    log("INFO", message);
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    std::string timestamp = currentTimestamp();
    std::string fullMessage = "[" + timestamp + "][" + level + "] " + message;

    if (m_logFile.is_open()) {
        m_logFile << fullMessage << std::endl;
    }

    if (m_tcpEnabled && m_tcpSocket != -1) {
        sendToTcp(fullMessage);
    }
}

void Logger::sendToTcp(const std::string& message) {
    std::string data = message + "\n";
    send(m_tcpSocket, data.c_str(), data.size(), 0);
}

std::string Logger::currentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t raw = std::chrono::system_clock::to_time_t(now);
    std::tm* timeinfo = std::localtime(&raw);

    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}
