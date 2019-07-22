#include "hzpch.h"
#include "Buffer.h"
#include <glad/glad.h>
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {


	
	VertexBuffer * VertexBuffer::Create(float * vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")	
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);

		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI")

		return nullptr;
	}






	Hazel::IndexBuffer * IndexBuffer::Create(uint32_t *Indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
			case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(Indices, count);

		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI")

		return nullptr;
	}




}