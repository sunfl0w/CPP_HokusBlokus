#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

namespace HokusBlokus::Util {
	class Logger {
		static Logger* loggerInstance;
		static std::string loggerLogName;
		static std::string loggerLogPath;
		static bool loggerEnableStdOut;

	public:
		static void initLogger(const std::string& logName, const std::string& logPath, bool enableStdOut);

		static Logger& getInstance();

		template <typename T>
		friend Logger& operator<<(Logger& logger, T const& value) {
			std::ofstream logFile = std::ofstream(logger.loggerLogPath + "/" + logger.loggerLogName, std::ios::app);
			logFile << value;
			logFile.close();

			if(logger.loggerEnableStdOut) {
				std::cout << value;
			}

			return logger;
		}
	};
}  // namespace HokusBlokus::Util