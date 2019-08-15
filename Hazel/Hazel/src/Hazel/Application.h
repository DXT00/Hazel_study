#pragma once
#include "Core.h"

#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Event/Event.h"
#include "Hazel/Event/ApplicationEvent.h"

#include "Hazel/Core/TimeStep.h"
//#include "Layer.h"

#include "Hazel/ImGui/ImGuiLayer.h"
namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		TimeStep m_TimeStep;
		float m_LastFrameTime = 0.0f;


		

	private:
		static Application* s_Instance;//Singleton
	};

	//To be define in a client
	Application *CreateApplication();
}
