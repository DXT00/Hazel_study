#pragma once

#include "Event.h"


namespace Hazel {


	class HAZEL_API KeyEvent:public Event //abstact 
	{
	public:
		inline int GetKeyCode()const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard)
		
	protected:
		KeyEvent(int keycode):m_KeyCode(keycode){} //you won't be able to make a KeyEvent
		int m_KeyCode;
	};


	/*-----------------------------------------------------------------------*/
	class HAZEL_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode,int repeatCount): //keep track the amount of time that the key has repeated
			KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		
		std::string ToString()const override{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << "repeats)";
			return ss.str();
		}

	
		EVENT_CLASS_TYPE(KeyPressed)
	//	EVENT_CLASS_CATEGORY( EventCategoryInput | EventCategoryKeyBoard)
	private:
		int m_RepeatCount;
	};



	/*-----------------------------------------------------------------------*/
	class HAZEL_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : //keep track the amount of time that the key has repeated
			KeyEvent(keycode) {}

		

		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode ;
			return ss.str();
		}


		EVENT_CLASS_TYPE(KeyReleased)
		//EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard)
	};



	/*-----------------------------------------------------------------------*/
	class HAZEL_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : //keep track the amount of time that the key has repeated
			KeyEvent(keycode) {}



		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}


		EVENT_CLASS_TYPE(KeyTyped)
	//		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard)
	};
}