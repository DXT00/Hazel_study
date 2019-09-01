#pragma once
#include "hzpch.h"
#include "Shader.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include<glad/glad.h>
namespace Hazel {



	Shader * Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc,fragmentSrc);

		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI")

		
		return nullptr;
	}


	
}