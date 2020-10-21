#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace HokusBlokus::Util {
	class Logger {
		std::string logFileDestination;
		std::stringstream stringstream;

	public:
		Logger(const std::string& logFileDestination);

		template <typename T>
		friend Logger& operator<<(Logger& logger, T const& value) {
			logger.stringstream << value;
			std::ofstream logFile = std::ofstream(logger.logFileDestination + "/HokusBlokus.log");
			logFile << logger.stringstream.str();
			logFile.close();

			std::cout << value;

			return logger;
		}
	};
}  // namespace HokusBlokus::Util