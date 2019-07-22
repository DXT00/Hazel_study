#pragma once
#include <vector>
#include<unordered_map>
namespace Hazel {


	enum class ShaderDataType {
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		False,
		True,

	};
	static uint32_t GetTypeSize(ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::Int:			return 1 * sizeof(int);
		case ShaderDataType::Int2:			return 2 * sizeof(int);
		case ShaderDataType::Int3:			return 3 * sizeof(int);
		case ShaderDataType::Int4:			return 4 * sizeof(int);
		case ShaderDataType::Float:			return 1 * sizeof(float);
		case ShaderDataType::Float2:		return 2 * sizeof(float);
		case ShaderDataType::Float3:		return 3 * sizeof(float);
		case ShaderDataType::Float4:		return 4 * sizeof(float);
		case ShaderDataType::Mat3:			return 3 * 3 * sizeof(float);
		case ShaderDataType::Mat4:			return 4 * 4 * sizeof(float);
		case ShaderDataType::False:			return 1;
		case ShaderDataType::True:			return 1;


		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!")
			return 0;
	}

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		bool Normalized;
		uint32_t Offset;
		uint32_t Size;//一层layout的总字节数 （Int3 --> 3*sizeof(int)）
		BufferElement(ShaderDataType type, std::string name, bool normalized) :
			Type(type), Name(name), Normalized(normalized), Offset(0), Size(GetTypeSize(type)) {}

		uint32_t GetElementCount() const{
			switch (Type)
			{
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::False:		return 1;
			case ShaderDataType::True:		return 1;
			}
		}

	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement> elements)
			:m_Elements(elements) {
			CalculateStrideAndOffset();
		}

		inline const std::vector<BufferElement> &GetElements() const { return m_Elements; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		inline uint32_t GetStride() const { return m_Stride; };
		const void CalculateStrideAndOffset() {

			m_Stride = 0;
			int offset = 0;
			for (BufferElement &element : m_Elements) {
				m_Stride += element.Size;
				element.Offset = offset;
				offset += m_Stride;
			}

		};



	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;


	};



	//只是抽象类，不存任何数据
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static VertexBuffer *Create(float *vertices, uint32_t size);


	};
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		static IndexBuffer *Create(uint32_t *Indices, uint32_t count);
		virtual uint32_t GetCount() const = 0;


	};
}