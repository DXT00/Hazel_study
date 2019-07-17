#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif

#else 
	#error Hazel only support windows!
#endif


#ifdef HZ_DEBUG
#define HZ_ENABLE_ASSERTS
#endif

#ifdef  HZ_ENABLE_ASSERTS
	#define HZ_ASSET(x,...){if(!(x)){HZ_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
	#define HZ_CORE_ASSET(x,...){if(!(x)){HZ_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
#else
	#define HZ_ASSET(x,...)
	#define HZ_CORE_ASSET(x,...)
#endif //  HZ_ENABLE_ASSERTS



#define BIT(x) (1<<x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
