#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

namespace HokusBlokus::Util::Logging {
	/**
	 * @brief A very light logger class
	 * 
	 */
	class Logger {
		/**
		 * @brief The name of the log file
		 * 
		 */
		std::string logName;

		/**
		 * @brief The path to the log file
		 * 
		 */
		std::string logPath;

		/**
		 * @brief Specifies wheter to output log data to stdOut also
		 * 
		 */
		bool enableStdOut;

	public:
		/**
		 * @brief Constructs a new Logger
		 * 
		 */
		Logger();

		/**
		 * @brief Constructs a new Logger
		 * 
		 * @param logName The name of the log file
		 * @param logPath The path to the log file
		 * @param enableStdOut Specifies wheter to output log data to stdOut also
		 */
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