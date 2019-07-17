#pragma once
#include"Hazel/Event/Event.h"


namespace Hazel {

	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		
		inline const std::string &GetString()const { return m_DegugName; }


	protected:
		std::string m_DegugName;
	};



}


