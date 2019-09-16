#include <Hazel.h>
#include <glm/gtc/matrix_transform.hpp>
#include"Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"


class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),m_CameraPosition(0.0f), m_SquarePosition(0.0f)//对应窗口大小 1280 ：720
	{

		float vertices[] = {
			//Position          //Color               
			-0.3f,-0.3f,0.0f,	1.0f,0.0f,0.0f,1.0f,
			 0.3f,-0.3f,0.0f,	0.0f,1.0f,0.0f,1.0f,
			 0.0f, 0.3f,0.0f,	0.0f,0.0f,1.0f,1.0f,

		};
		float squareVertices[] = {
			//Position          //Texture Coordinate
			-0.5f, -0.5f, 0.0f,  0.0f,0.0f,
			 0.5f, -0.5f, 0.0f,  1.0f,0.0f,
			 0.5f,  0.5f, 0.0f,  1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,  0.0f,1.0f

		};
		unsigned int indices[3] = { 0,1,2 };
		unsigned int squareIndices[6] = { 0,1,2,0,2,3 };

		Hazel::BufferLayout layout = {
				{  Hazel::ShaderDataType::Float3,"a_Position", false },
				{  Hazel::ShaderDataType::Float4,"a_Color",    false },


		};
		Hazel::BufferLayout squareLayout = {
			{  Hazel::ShaderDataType::Float3,"a_Position", false },
			{  Hazel::ShaderDataType::Float2,"a_TexCoord", false },


		};

		Hazel::Ref< Hazel::VertexBuffer> vertexBuffer;
		Hazel::Ref< Hazel::IndexBuffer> indexBuffer;
		m_VertexArray.reset(Hazel::VertexArray::Create());
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, 3));

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);


		Hazel::Ref< Hazel::VertexBuffer>squareVB;
		Hazel::Ref< Hazel::IndexBuffer> squareIB;
		m_SquareVA.reset(Hazel::VertexArray::Create());
		squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, 6));

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);


		const std::string vertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0f);

				}


				)";
		const std::string fragmentSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				layout(location = 1) out vec4 color1;

				in vec3 v_Position;
				in vec4 v_Color;
				
				void main()
				{

					color = v_Color;//vec4(v_Position*0.5+0.5, 1.0);

				}
				)";
		m_Shader.reset(Hazel::Shader::Create(vertexSrc, fragmentSrc));


		const std::string squareVertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
			

				void main()
				{
					v_Position = a_Position;
				
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);

				}


				)";
		const std::string squareFragmentSrc = R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				uniform vec3 u_Color;
				
				void main()
				{

					color = vec4(u_Color,1.0f);//vec4(v_Position*0.5+0.5, 1.0);

				}
				)";
		m_SquareShader.reset(Hazel::Shader::Create(squareVertexSrc, squareFragmentSrc));

		//m_Shader = std::make_unique<Shader>(vertexSrc,fragmentSrc);
		
		m_TextureShader.reset(Hazel::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Hazel::Texture2D::Create("assets/textures/awesomeface.png");
		m_FaceTexture = Hazel::Texture2D::Create("assets/textures/c.png");

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TextureShader)->SetUniformInt("u_Texture", 0);//0 --->texture slot

	}
	
	void OnUpdate(Hazel::TimeStep ts) override
	{
		HZ_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		//float timestep = ts;//相当一 timestep = float(ts)

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraRotation += m_CameraRotateSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraRotation -= m_CameraRotateSpeed * ts;
		}
		
		if (Hazel::Input::IsKeyPressed(HZ_KEY_J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_K))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}


		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->SetUniformFloat3("u_Color",m_SquareColor);

	
		for (int x = 0; x <5; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				glm::vec3 pos(x*0.11f, y*0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)*scale;
			
				Hazel::Renderer::Submit(m_SquareVA, m_SquareShader, transform);

			}
		}
		
		m_Texture->Bind();
		Hazel::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f),glm::vec3(1.0f)));
	
		m_FaceTexture->Bind();
		Hazel::Renderer::Submit(m_SquareVA, m_TextureShader,glm::translate(glm::mat4(1.0f),glm::vec3(0.25f,-0.25f,0.0f))*glm::scale(glm::mat4(1.0f), glm::vec3(0.7f)));

		//Triangle
		//Hazel::Renderer::Submit(m_VertexArray, m_Shader);

		Hazel::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Suqare Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override
	{

	}

public:
		inline Hazel::OrthographicCamera& GetCamera() { return m_Camera; }


	
private:
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::Shader> m_Shader;

	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Shader> m_SquareShader;

	Hazel::Ref<Hazel::Shader> m_TextureShader;

	Hazel::Ref<Hazel::Texture2D> m_Texture;
	Hazel::Ref<Hazel::Texture2D> m_FaceTexture;
	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
	float m_CameraMoveSpeed = 5;
	float m_CameraRotation = 0;
	float m_CameraRotateSpeed =180;//1s旋转180度

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 5;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}