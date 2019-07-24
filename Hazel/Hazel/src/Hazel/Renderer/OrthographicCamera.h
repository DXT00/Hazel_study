#pragma once
#include "glm/glm.hpp"
namespace Hazel {
	class OrthographicCamera
	{
	public:
		//OrthographicCamera(){}
		OrthographicCamera(float left, float right, float bottom, float top);
	
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() const{ return m_Position; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		float GetRotation()const { return m_Rotation; }

		inline void SetViewMatrix(glm::mat4 view) {m_ViewMatix = view;}
		inline void SetProjectionMatrix(glm::mat4 projection) {m_ProjectionMatrix = projection;}
		inline void SetViewProjectionMatrix(glm::mat4 viewProjection) { m_ViewProjectionMatrix = viewProjection; }

		inline const glm::mat4 &GetViewMatrix()const { return m_ViewMatix; };
		inline const glm::mat4 &GetProjectionMatrix()const { return m_ProjectionMatrix; };
		inline const glm::mat4 &GetViewProjectionMatrix()const { return m_ViewProjectionMatrix; };


		~OrthographicCamera();
	private:
		void RecalculateViewMatrix();
	private:
		float m_zFar, m_zClose;
		float m_FOV;
		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		glm::mat4 m_ViewMatix;// is the inverse of the transformMatrix of the Camera!
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_Rotation = 0.0f;//rotate along z axis


	};

}

