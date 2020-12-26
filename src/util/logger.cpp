#include "logger.hpp"

namespace HokusBlokus::Util::Logging {
    Logger logger;
    
    Logger::Logger() {}

    Logger::Logger(const std::string& logName, const std::string& logPath, bool enableStdOut) {
        this->logName = logName;
        this->logPath = logPath;
        this->enableStdOut = enableStdOut;

        if(!std::filesystem::exists(this->logPath)) {
            std::cout << "Specified log path: " << this->logPath << " does not exist";
            return;
        }

        std::ofstream logFile = std::ofstream(this->logPath + "/" + this->logName, std::ios::app);
        std::time_t now = std::time(nullptr);
		logFile << "Starting logger. " << std::ctime(&now);
		logFile.close();
    }
}