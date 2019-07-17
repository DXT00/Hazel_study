#pragma once
#include"Hazel/Layer.h"
#include"Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Application.h"


namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:

		bool OnKeyPressedEvent(KeyPressedEvent&e);
		bool OnKeyReleasedEvent(KeyReleasedEvent&e);
		bool OnMouseMovedEvent(MouseMovedEvent&e);
		bool OnMouseScrolledEvent(MouseScrolledEvent&e);
		
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent&e);
		bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		float m_Time = 0.0f;
	};

}

