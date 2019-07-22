#pragma once
#include "Hazel/Renderer/Buffer.h"
namespace Hazel {
	




	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() ;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& GetLayout() const { return m_BufferLayout; };
	private:
		uint32_t m_VertexBuffer;
		BufferLayout m_BufferLayout;

	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* Indices, uint32_t count);
		virtual uint32_t GetCount() const { return m_Count; }
		virtual ~OpenGLIndexBuffer() ;
		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		uint32_t m_IndexBuffer;
		uint32_t m_Count;

	};

}

