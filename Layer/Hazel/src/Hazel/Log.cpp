#include "hzpch.h"
#include "Log.h"


namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger; //static 对象需要在类外初始化
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {

		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stderr_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);


	}
	

}
