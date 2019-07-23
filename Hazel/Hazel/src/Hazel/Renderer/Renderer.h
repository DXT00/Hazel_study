#pragma once
#include "RenderCommand.h"
namespace Hazel {

	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		//dispatch to the RenderCommand,and submit it into Command Queue!
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}