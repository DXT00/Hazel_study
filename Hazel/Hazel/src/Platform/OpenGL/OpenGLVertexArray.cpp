#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace Hazel {
	static uint32_t ShaderDataTypeToBufferType(const ShaderDataType & type) {
		switch (type)
		{
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Float2:		return GL_FLOAT;
		case ShaderDataType::Float3:		return GL_FLOAT;
		case ShaderDataType::Float4:		return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::False:			return GL_FALSE;
		case ShaderDataType::True:			return GL_TRUE;


		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!")
			return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendereID);
	//	glBindVertexArray(m_RendereID);
	}


	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendereID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendereID);

	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);

	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBufer)
	{
		HZ_CORE_ASSERT(vertexBufer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!!")

		glBindVertexArray(m_RendereID);
		vertexBufer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBufer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetElementCount(),
				ShaderDataTypeToBufferType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void *)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBufer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendereID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	


}
