#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel/Application.h"
#include <GLFW/glfw3.h>


namespace Hazel{
	Input* Input::s_Instance = new WindowsInput();
	
	WindowsInput::WindowsInput()
	{
	}


	WindowsInput::~WindowsInput()
	{
		
	}

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetKey(window, keycode);

		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}
	 
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetMouseButton(window, button);

		return status == GLFW_PRESS ;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {xpos,ypos};
	}

	float WindowsInput::GetMouseXImpl()
	{
		
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		
		auto[x, y] = GetMousePositionImpl();
		return y;
	}


}

