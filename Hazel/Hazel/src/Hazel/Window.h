#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"
#include "Hazel/Event/Event.h"

namespace Hazel {

	struct WindowProps {

		std::string Title;
		unsigned int Height;
		unsigned int Width;

		WindowProps(const std::string& title= "Hazel Engine",unsigned int width = 1280,unsigned int height = 720)
			:Title(title),Width(width),Height(height){}

	};

	class HAZEL_API Window { //ÿ��ƽ̨��ʵ�ַ�ʽ��һ���������Ǹ�������
	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;// �������Զ����� defaulted ���������� c++11

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Windows attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled)  = 0;//?
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& prop = WindowProps());  //for example: Mac Window ,Linux Window,windows Window


	};


}
