#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <netinet/in.h>

namespace rd{

class Logger {
public:
    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    void init(const std::string& filePath, bool useTcp = false);
    void info(const std::string& message);
    void error(const std::string& message);

private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(const std::string& level, const std::string& message);
    void sendToTcp(const std::string& message);
    std::string currentTimestamp();

    std::ofstream m_logFile;
    std::mutex m_logMutex;
    bool m_tcpEnabled = false;
    int m_tcpSocket = -1;
};

} // end of namespace rd
