#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sstream>
#include <ctime>

class Logger {
public:
    Logger(const std::string& logDirectory, const std::string& logFilename, const std::string& tcpHost, int tcpPort);
    ~Logger();

    void log(const std::string& message);

private:
    std::string logFilePath;
    std::string logDirectory;
    std::string tcpHost;
    int tcpPort;
    static const double DISK_USAGE_THRESHOLD; // Uppercase static constant

    void cleanOldLogFiles();
    void logToTcp(const std::string& message);
};

#endif // LOGGER_H
