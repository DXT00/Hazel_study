#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Hazel/Event/ApplicationEvent.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"
namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;//Singleton
	};
	
	//To be define in a client
	 Application *CreateApplication();
}
