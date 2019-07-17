#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}


	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer * layer)
	{
		m_Layers.emplace(m_Layers.begin()+ m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverLayer(Layer * overlay)
	{
		m_Layers.emplace_back( overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer * layer)
	{
		auto it = find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverLayer(Layer * overlay)
	{
		auto it = find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}
