#include "Logger.h"

#include <ctime>
#include <string>
#include <chrono>
#include <iostream>
#include <stdio.h>

std::vector<LogEntry> Logger::messages;

std::string CurrentDateTimeToString() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	std::strftime(&output[0], output.size(), "%b-%d-%Y %H:%M:%S", &timeinfo);
	return output;
}

void Logger::Log(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_INFO;
	logEntry.message = "LOG: [" + CurrentDateTimeToString() + "]:" + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_ERROR;
	logEntry.message = "ERR: [" + CurrentDateTimeToString() + "]:" + message;
	std::cout << "\x1B[91m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}

void Logger::Close(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_CLOSE;
	logEntry.message = "CLOSE: [" + CurrentDateTimeToString() + "]:" + message;
	std::cout << "\033[33m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}
