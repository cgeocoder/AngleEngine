#include "errors.h"
#include "vertex_array.h"

VertexArrayConfig::VertexArrayConfig() : m_Stride{ 0 } {};

template<>
void VertexArrayConfig::add_config<float>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_FLOAT, _Count, false, sizeof(float) });
	m_Stride += sizeof(float) * _Count;
}

template<>
void VertexArrayConfig::add_config<double>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_DOUBLE, _Count, false, sizeof(double) });
	m_Stride += sizeof(double) * _Count;
}

template<>
void VertexArrayConfig::add_config<char>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_BYTE, _Count, true, sizeof(char) });
	m_Stride += sizeof(char) * _Count;
}

template<>
void VertexArrayConfig::add_config<unsigned char>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_UNSIGNED_BYTE, _Count, true, sizeof(unsigned char) });
	m_Stride += sizeof(unsigned char) * _Count;
}

template<>
void VertexArrayConfig::add_config<short>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_SHORT, _Count, true, sizeof(short) });
	m_Stride += sizeof(short) * _Count;
}

template<>
void VertexArrayConfig::add_config<unsigned short>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_UNSIGNED_SHORT, _Count, true, sizeof(unsigned short) });
	m_Stride += sizeof(unsigned short) * _Count;
}

template<>
void VertexArrayConfig::add_config<int>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_INT, _Count, true, sizeof(int) });
	m_Stride += sizeof(int) * _Count;
}

template<>
void VertexArrayConfig::add_config<unsigned int>(unsigned int _Count) {
	m_VertexBufferAttribs.push_back({ GL_UNSIGNED_INT, _Count, true, sizeof(unsigned int) });
	m_Stride += sizeof(unsigned int) * _Count;
}


VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::bind(void) const {
	glBindVertexArray(m_ID);
}

void VertexArray::unbind(void) const {
	glBindVertexArray(0);
}

void VertexArray::attach_buffer(
	const VertexBuffer& _VertexBuffer,
	const VertexArrayConfig& _VertexArrayConf
) {
	_VertexBuffer.bind();

	const auto& elems = _VertexArrayConf.get_attribs();

	for (size_t i = 0, offset = 0; i < elems.size(); ++i) {
		const auto& elem = elems.at(i);
		// Включает спецификацию под номером i
		// Привязывается к текущему VBO
		GL(glEnableVertexAttribArray(i));

		// Изменяет спецификацию под номером i
		// 2: Количество компонентов вершины
		// 3: Тип компонентов
		// 4: Нормализация компонентов (?)
		// 5: Шаг - через сколько байт идет следущая вершина
		// 6: Определяет смещение первого компонента
		GL(glVertexAttribPointer(
			i, elem.count, elem.type,
			elem.norm, _VertexArrayConf.get_stride(), (void*)offset
		));

		offset += (size_t)elem.count * elem.type_size;
	}
}