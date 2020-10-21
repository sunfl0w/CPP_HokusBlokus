#include "logger.hpp"

namespace HokusBlokus::Util {
    Logger::Logger(const std::string &logFileDestination) {
        this->logFileDestination = logFileDestination;
    }
}