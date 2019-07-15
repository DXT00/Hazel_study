#pragma once
#include<vector>
#include "Hazel/Core.h"
#include "Layer.h"


namespace Hazel {

	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer *layer);
		void PushOverLayer(Layer *layer);

		void PopLayer(Layer *layer);
		void PopOverLayer(Layer *layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
		int m_LayerInsertIndex = 0;


	};



}

