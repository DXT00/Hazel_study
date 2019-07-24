#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
namespace Hazel {

	class Renderer {
	public:
		static void BeginScene(OrthographicCamera &camera);
		static void EndScene();

		//dispatch to the RenderCommand,and submit it into Command Queue!
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData * s_SceneData;

	};

}