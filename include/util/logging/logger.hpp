#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

namespace HokusBlokus::Util::Logging {
	class Logger {
		std::string logName;
		std::string logPath;
		bool enableStdOut;

	public:
		Logger();

		Logger(const std::string& logName, const std::string& logPath, bool enableStdOut);

		template <typename T>
		friend Logger& operator<<(Logger& logger, T const& value) {
			std::ofstream logFile = std::ofstream(logger.logPath + "/" + logger.logName, std::ios::app);
			logFile << value;
			logFile.close();

			if(logger.enableStdOut) {
				std::cout << value;
			}

			return logger;
		}
	};

	extern Logger logger;
}  // namespace HokusBlokus::Util