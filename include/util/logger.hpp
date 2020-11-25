#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace HokusBlokus::Util {
	class Logger {
		static Logger* loggerInstance;

	public:
		static Logger& getInstance();

		template <typename T>
		friend Logger& operator<<(Logger& logger, T const& value) {
			std::ofstream logFile = std::ofstream(std::filesystem::current_path().string() + "/HokusBlokus.log", std::ios::app);
			logFile << value;
			logFile.close();
			//std::cout << value;

			return logger;
		}
	};
}  // namespace HokusBlokus::Util