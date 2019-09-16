#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"
namespace Hazel {

	class Renderer {
	public:

		static void Init();

		static void BeginScene(OrthographicCamera &camera);
		static void EndScene();

		//dispatch to the RenderCommand,and submit it into Command Queue!
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData * s_SceneData;

	};

}