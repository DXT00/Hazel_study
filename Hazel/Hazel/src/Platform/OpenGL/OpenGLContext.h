#pragma once
#include "Hazel/Renderer/GraphicsContext.h"
#include<GLFW/glfw3.h>
#include <glad/glad.h>
namespace Hazel {


	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow * windowHandle);

		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow * m_WindowHandle;
	};

}


