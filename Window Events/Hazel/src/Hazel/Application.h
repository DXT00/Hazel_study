#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Hazel/Event/ApplicationEvent.h"
#include "Window.h"
namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	
	//To be define in a client
	 Application *CreateApplication();
}
