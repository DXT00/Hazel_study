#include "hzpch.h"
#include "OpenGLContext.h"
#include "Hazel/Core.h"

namespace Hazel {

	
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "windowHandle is null!");

	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Vendor :{0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("OpenGL Renderer :{0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("OpenGL Version :{0}",  glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);

	}

}

