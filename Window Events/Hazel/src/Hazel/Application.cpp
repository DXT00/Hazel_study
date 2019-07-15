#include "hzpch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

namespace Hazel {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//std::placeholders::_1 占位符-->表示OnEvent(e)的第一个参数，也就是e
		// m_Data.EventCallback = std::bind(&Application::OnEvent, this, std::placeholders::_1)
		//data.EventCallback(event);
		//相当于--》Application::OnEvent(event)
	
	}
	
	
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& e) {
			m_Running = false;
			return true;		
		});

		HZ_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
	
	void Application:: Run() {

		
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
	
}
	