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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBufer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBufers()const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer()const = 0;

		static VertexArray *Create();
	};


}

