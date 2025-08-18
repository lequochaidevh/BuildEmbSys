#pragma once

#include<spdlog/spdlog.h>
#include<spdlog/common.h>

#include<spdlog/fmt/ostr.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include <pch.h>

// #define _DEBUG 1

namespace ViSolEngine {
	class VISOL_API Logger {
	public:
		static void init();
		static VISOL_FORCE_INLINE Shared<spdlog::logger> getCoreLogger() { return sCoreLogger; }
		static VISOL_FORCE_INLINE Shared<spdlog::logger> getClientLogger() { return sClientLogger; }
	private:
		static Shared<spdlog::logger> sCoreLogger;
		static Shared<spdlog::logger> sClientLogger;
	};
}

#define LOG_WITH_DETAILS(logger, level, ...) logger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)

#if _DEBUG
#define CORE_LOG_TRACE(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getCoreLogger(), spdlog::level::trace, __VA_ARGS__)
#define CORE_LOG_DEBUG(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getCoreLogger(), spdlog::level::debug, __VA_ARGS__)
#define CORE_LOG_INFO(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getCoreLogger(), spdlog::level::info, __VA_ARGS__)
#define CORE_LOG_WARN(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getCoreLogger(), spdlog::level::warn, __VA_ARGS__)
#define CORE_LOG_ERROR(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getCoreLogger(), spdlog::level::err, __VA_ARGS__)
#define CORE_LOG_CRITICAL(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getCoreLogger(), spdlog::level::critical, __VA_ARGS__)

#define LOG_TRACE(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getClientLogger(), spdlog::level::trace, __VA_ARGS__)
#define LOG_DEBUG(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getClientLogger(), spdlog::level::debug, __VA_ARGS__)
#define LOG_INFO(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getClientLogger(), spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getClientLogger(), spdlog::level::warn, __VA_ARGS__)
#define LOG_ERROR(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getClientLogger(), spdlog::level::err, __VA_ARGS__)
#define LOG_CRITICAL(...) LOG_WITH_DETAILS(ViSolEngine::Logger::getClientLogger(), spdlog::level::critical, __VA_ARGS__)
#else
#define CORE_LOG_TRACE(...)
#define CORE_LOG_DEBUG(...)
#define CORE_LOG_INFO(...)
#define CORE_LOG_WARN(...)
#define CORE_LOG_ERROR(...)
#define CORE_LOG_CRITICAL(...)

#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)
#endif
