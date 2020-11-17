#include "logger.hpp"

namespace HokusBlokus::Util {
    Logger& Logger::getInstance() {
        if(loggerInstance == nullptr) {
            loggerInstance = new Logger();
        }
        return *loggerInstance;
    }

    Logger *Logger::loggerInstance = 0;
}