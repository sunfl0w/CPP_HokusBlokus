#include "logger.hpp"

namespace HokusBlokus::Util {
    void Logger::initLogger(const std::string& logName, const std::string& logPath, bool enableStdOut) {
        loggerLogName = logName;
        loggerLogPath = logPath;
        loggerEnableStdOut = enableStdOut;

        if(!std::filesystem::exists(logPath)) {
            std::cout << "Specified log path: " << logPath << " does not exist";
            return;
        }

        std::ofstream logFile = std::ofstream(loggerLogPath + "/" + loggerLogName, std::ios::app);
        std::time_t now = std::time(nullptr);
		logFile << "Starting logger. " << std::ctime(&now);
		logFile.close();
    }

    Logger& Logger::getInstance() {
        if(loggerInstance == nullptr) {
            loggerInstance = new Logger();
        }
        return *loggerInstance;
    }

    Logger *Logger::loggerInstance = 0;
}