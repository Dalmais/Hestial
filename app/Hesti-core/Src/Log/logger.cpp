#include "Log/logger.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <ctime>

namespace rd {

Logger::Logger() :
    m_running(false),
    m_serverSocket(-1){
}

Logger::~Logger() {
    m_running = false;

    if (m_supervisorThread.joinable()) {
        m_supervisorThread.join();
    }

    if (m_serverSocket != -1) {
        close(m_serverSocket);
    }

    std::lock_guard<std::mutex> lock(m_clientsMutex);
    for (int fd : m_clients) {
        close(fd);
    }

    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

void Logger::init(const std::string& filePath, bool enableTcp) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_logFile.open(filePath, std::ios::app);

    if (enableTcp) {
        supervisor();  // Lancer automatiquement la supervision
    }
}

void Logger::supervisor() {
    if (m_running) return;

    m_running = true;
    m_supervisorThread = std::thread(&Logger::acceptLoop, this);
}

void Logger::acceptLoop() {
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket < 0) {
        std::cerr << "[Logger] Failed to create TCP socket.\n";
        m_running = false;
        return;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(45678);

    if (bind(m_serverSocket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "[Logger] Bind failed.\n";
        close(m_serverSocket);
        m_serverSocket = -1;
        m_running = false;
        return;
    }

    listen(m_serverSocket, 5);
    std::cout << "[Logger] Supervisor listening on port 45678\n";

    while (m_running) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) continue;

        std::lock_guard<std::mutex> lock(m_clientsMutex);
        m_clients.push_back(clientSocket);
        std::cout << "[Logger] Client connected.\n";
    }
}

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(m_logMutex);
    std::string timestamp = currentTimestamp();
    std::string fullMessage = "[" + timestamp + "][" + level + "] " + message;

    if (m_logFile.is_open()) {
        m_logFile << fullMessage << std::endl;
    }

    broadcast(fullMessage + "\n");
}

void Logger::broadcast(const std::string& message) {
    std::lock_guard<std::mutex> lock(m_clientsMutex);

    for (auto it = m_clients.begin(); it != m_clients.end();) {
        ssize_t sent = send(*it, message.c_str(), message.length(), 0);
        if (sent < 0) {
            close(*it);
            it = m_clients.erase(it);
        } else {
            ++it;
        }
    }
}

void Logger::info(const std::string& message) {
    log("INFO", message);
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}

std::string Logger::currentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t raw = std::chrono::system_clock::to_time_t(now);
    std::tm* timeinfo = std::localtime(&raw);

    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

} // end of namespace rd
