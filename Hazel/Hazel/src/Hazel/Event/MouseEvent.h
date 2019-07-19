#pragma once

#include "Event.h"


namespace Hazel {
	class HAZEL_API MouseMovedEvent : public Event 
	{
	public:
		MouseMovedEvent(float x,float y) : //keep track the amount of time that the key has repeated
			m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << " , " << GetY();
			return ss.str();
		}

		
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);

	private:
		float m_MouseX,m_MouseY;
	};


	class HAZEL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : //keep track the amount of time that the key has repeated
			m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << " , " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	/*	static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventype()const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseScrolled"; }
		virtual int GetCategoryFlags() const override { return EventCategoryInput| EventCategoryMouse; }*/


	private:
		float m_XOffset, m_YOffset;
	};


	class HAZEL_API MouseButtonEvent : public Event 
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	protected:
		MouseButtonEvent(int button)
					:m_Button(button) {}

		int m_Button;
	};


	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent 
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class HAZEL_API MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button)
			:MouseButtonEvent(button) {};

		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}
