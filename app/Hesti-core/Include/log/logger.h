#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <vector>
#include <thread>
#include <atomic>
#include <netinet/in.h>

namespace rd {

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void init(const std::string& filePath, bool enableTcp = false);
    void info(const std::string& message);
    void error(const std::string& message);

    void supervisor(); // Lance le serveur de supervision dans un thread

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(const std::string& level, const std::string& message);
    std::string currentTimestamp();
    void acceptLoop();
    void broadcast(const std::string& message);

    std::ofstream m_logFile;
    std::mutex m_logMutex;

    // Supervision TCP
    std::atomic<bool> m_running{false};
    int m_serverSocket = -1;
    std::vector<int> m_clients;
    std::mutex m_clientsMutex;
    std::thread m_supervisorThread;
};

} // end of namespace rd
