#pragma once
#include<memory>
#include "Hazel/Renderer/Buffer.h"
namespace Hazel {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBufer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBufers()const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer()const = 0;

		static VertexArray *Create();
	};


}

