#pragma once

#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "vertex_buffer.h"
#include <vector>
#include "errors.h"

// Структура конфигурации для glVertexAttribPointer 
// (см. "docs.gl/gl4/glVertexAttribPointer")
struct VertexBufferAttrib {
	unsigned int type;
	unsigned int count;
	bool norm;

	unsigned int type_size;
};

// Класс конфигурации VAO
class VertexArrayConfig {
private:
	// Массив концигураций для разных VBO
	std::vector<VertexBufferAttrib> m_VertexBufferAttribs;

	// Шаг, зависящий от параметров и количетва VBO
	unsigned int m_Stride;

public:
	VertexArrayConfig();

	// Добавляет конфигурацию для glVertexAttribPointer 
	// (см. "docs.gl/gl4/glVertexAttribPointer")
	// @param typename _Ty	- Тип данных VBO
	// @param _Count		- Количество значений типа _Ty на одну вершину
	template<typename _Ty>
	inline void add_config(unsigned int _Count) { 
		static_assert(false, "There is no method implementation for this type");
	}

	template<>
	void add_config<float>(unsigned int _Count);

	template<>
	void add_config<double>(unsigned int _Count);

	template<>
	void add_config<char>(unsigned int _Count);

	template<>
	void add_config<unsigned char>(unsigned int _Count);

	template<>
	void add_config<short>(unsigned int _Count);

	template<>
	void add_config<unsigned short>(unsigned int _Count);

	template<>
	void add_config<int>(unsigned int _Count);

	template<>
	void add_config<unsigned int>(unsigned int _Count);

	// Возвращает std::vector аттрибутов добавленных VBO
	inline const std::vector<VertexBufferAttrib>& get_attribs(void) const {
		return m_VertexBufferAttribs;
	}

	// Возвращает шаг
	inline const unsigned int get_stride(void) const {
		return m_Stride;
	}
};

// Класс конфигурации VBO
class VertexArray {
private:
	unsigned int m_ID;

public:
	VertexArray();
	~VertexArray();

	void bind(void) const;
	void unbind(void) const;

	// Свяывает VBO с VertexArrayConfig
	// @param _VertexBuffer		- VBO
	// @param _VertexArrayConf	- VertexArrayConfig
	void attach_buffer(const VertexBuffer& _VertexBuffer,const VertexArrayConfig& _VertexArrayConf);
};

#endif // !__VERTEX_ARRAY_H__
