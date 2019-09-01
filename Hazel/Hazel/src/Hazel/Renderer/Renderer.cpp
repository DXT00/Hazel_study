#include "hzpch.h"
#include "Renderer.h"
#include "OrthographicCamera.h"
#include"Platform/OpenGL/OpenGLShader.h"
namespace Hazel {

	Renderer::SceneData *  Renderer::s_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera &camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}



	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader,const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndex(vertexArray);

	}

}