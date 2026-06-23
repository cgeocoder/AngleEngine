#pragma once

#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include "vertex_buffer.h"
#include <vector>
#include "errors.h"

struct VBElem {
	unsigned int type;
	unsigned int count;
	bool norm;
};

class VertexBufferLayout {
private:
	std::vector<VBElem> m_Elem;
	unsigned int m_Stride;

public:
	inline VertexBufferLayout() : m_Stride{ 0 } {};

	template<typename _Ty>
	inline void push(unsigned int _Count) { static_assert(false); }

	template<>
	inline void push<float>(unsigned int _Count) {
		m_Elem.push_back({ GL_FLOAT, _Count, false });
		m_Stride += sizeof(GLfloat) * _Count;
	}

	inline const std::vector<VBElem>& get_elements(void) const {
		return m_Elem;
	}

	inline const unsigned int get_stride(void) const {
		return m_Stride;
	}
};

class VertexArray {
private:
	unsigned int m_ID;

public:
	inline VertexArray() {
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	inline ~VertexArray() {
		glDeleteVertexArrays(1, &m_ID);
	}

	inline void bind(void) const {
		glBindVertexArray(m_ID);
	}

	inline void unbind(void) const {
		glBindVertexArray(0);
	}

	inline void attach_buffer(
		const VertexBuffer& _VB,
		const VertexBufferLayout& _VBL
	) {
		_VB.bind();

		const auto& elems = _VBL.get_elements();

		for (size_t i = 0, offset = 0; i < elems.size(); ++i) {
			const auto& elem = elems.at(i);

			// Включает спецификацию под номером 0
			// Привязывается к текущему VertexBuffer
			GL(glEnableVertexAttribArray(i));

			// Изменяет спецификацию под номером 0
			// Arg2: Количество компонентов вершины
			// Arg3: Тип компонентов
			// Arg4: Нормализайия компонентов (?)
			// Arg5: Шаг - через сколько байт идет следущая вершина
			// Arg6: Определяет смещение первого компонента
			GL(glVertexAttribPointer(
				i, elem.count, elem.type, 
				elem.norm, _VBL.get_stride(), (void*)offset
			));

			offset += elem.count * 4; // * type size
		}

	}
};

#endif // !__VERTEX_ARRAY_H__