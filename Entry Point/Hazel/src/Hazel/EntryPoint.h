#pragma once
#include<stdio.h>

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();//ÓÉclientÉú³É

int main(int argc,char **argv) {
	printf("Hazel Engine");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
	return 0;
}



#endif // HZ_PLATFORM_WINDOWS
