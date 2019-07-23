#pragma once
#include "Hazel/Renderer/RendererAPI.h"
namespace Hazel {
	class OpenGLRendererAPI:public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		~OpenGLRendererAPI();
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndex(const std::shared_ptr<VertexArray> &vertexArray) override;
	};

}

