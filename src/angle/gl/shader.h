#pragma once

#include "../engine/kernel.h"
#include "errors.h"
#include <string>

#ifndef __SHADER_H__
#define __SHADER_H__

// Type of OpenGL shader
enum class ShaderType {
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER,
    ComputeShader = GL_COMPUTE_SHADER,
};


// Base typed shader class
template<const ShaderType _ShaderType>
class API XShader {
private:
    unsigned int m_ProgramID;

public:
    inline XShader(void)
        : m_ProgramID{ (unsigned int)-1 } {}

    inline XShader(const XShader<_ShaderType>& _Copy)
        : m_ProgramID{ _Copy.m_ProgramID } {}

    inline XShader(const std::string& _Src) {
        GL(m_ProgramID = glCreateShader(static_cast<GLuint>(_ShaderType)));

        const char* str = _Src.c_str();
        GL(glShaderSource(m_ProgramID, 1, &str, nullptr));
        GL(glCompileShader(m_ProgramID));
        compile_status();
    }

    inline ~XShader(void) { GL(del()); }

    inline void del(void) {
        if (m_ProgramID != (unsigned int)-1) {
            GL(glDeleteShader(m_ProgramID));

            m_ProgramID = (unsigned int)-1;
        }
    }

    inline unsigned int id() const { return m_ProgramID; }

private:
    inline void compile_status() {
        int status;
        GL(glGetShaderiv(m_ProgramID, GL_COMPILE_STATUS, &status));

        if (status == GL_FALSE) {
            const char* shader_type;
            switch (_ShaderType) {
            case ShaderType::VertexShader: shader_type = "VertexShader"; break;
            case ShaderType::FragmentShader: shader_type = "FragmentShader"; break;
            case ShaderType::GeometryShader: shader_type = "GeometryShader"; break;
            case ShaderType::ComputeShader: shader_type = "ComputeShader"; break;
            default: shader_type = "<unknown shader type>"; break;
            }

            int length;
            GL(glGetShaderiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length));

            char* err_log = new char[length];

            GL(glGetShaderInfoLog(m_ProgramID, length, &length, err_log));
            printf("XShader: Failed to compile %s: %s\n",
                shader_type, err_log);

            delete[] err_log;

            del();
        }
    }
};

// A wrapper class for XShader that implements VertexShader
class API VertexShader final : public XShader<ShaderType::VertexShader> {
public:
    inline VertexShader(void)
        : XShader<ShaderType::VertexShader>() {}

    inline VertexShader(const VertexShader& _Copy)
        : XShader<ShaderType::VertexShader>(_Copy) {}

    inline VertexShader(const std::string& _Src)
        : XShader<ShaderType::VertexShader>(_Src) {}
};

// A wrapper class for XShader that implements FragmentShader
class API FragmentShader final : public XShader<ShaderType::FragmentShader> {
public:
    inline FragmentShader(void)
        : XShader<ShaderType::FragmentShader>() {}

    inline FragmentShader(const FragmentShader& _Copy)
        : XShader<ShaderType::FragmentShader>(_Copy) {}

    inline FragmentShader(const std::string& _Src)
        : XShader<ShaderType::FragmentShader>(_Src) {}
};

// A wrapper class for XShader that implements GeometryShader
class API GeometryShader final : public XShader<ShaderType::GeometryShader> {
public:
    inline GeometryShader(void)
        : XShader<ShaderType::GeometryShader>() {}

    inline GeometryShader(const GeometryShader& _Copy)
        : XShader<ShaderType::GeometryShader>(_Copy) {}

    inline GeometryShader(const std::string& _Src)
        : XShader<ShaderType::GeometryShader>(_Src) {}
};

// A wrapper class for XShader that implements ComputeShader
class API ComputeShader final : public XShader<ShaderType::ComputeShader> {
public:
    inline ComputeShader(void)
        : XShader<ShaderType::ComputeShader>() {}

    inline ComputeShader(const ComputeShader& _Copy)
        : XShader<ShaderType::ComputeShader>(_Copy) {}

    inline ComputeShader(const std::string& _Src)
        : XShader<ShaderType::ComputeShader>(_Src) {}
};

class API Shader;

class API UniformLocation {
private:
    int m_Location;

public:
    UniformLocation(const Shader& _Shader, const std::string& _Name);

    inline int get(void) const {
        return m_Location;
    }
};

// Shader
class API Shader {
    friend class UniformLocation;

private:
    unsigned int m_ProgramID;

public:
    inline Shader() { GL(m_ProgramID = glCreateProgram()); }
    inline ~Shader() { GL(glDeleteProgram(m_ProgramID)); }

    // Attach new shader program for Shader
    template<ShaderType _ShaderType>
    void attach(const XShader<_ShaderType>& _Shader) const;

    template<>
    void attach(const XShader<ShaderType::ComputeShader>& _Shader) const;

    template<>
    void attach(const XShader<ShaderType::FragmentShader>& _Shader) const;

    template<>
    void attach(const XShader<ShaderType::GeometryShader>& _Shader) const;

    template<>
    void attach(const XShader<ShaderType::VertexShader>& _Shader) const;

    // Link attached shader programs
    void link() const;

    inline UniformLocation get_uniform_location(const std::string& _Name) const {
        return UniformLocation(*this, _Name);
    }

    // Uniform: 1 float
    inline void __fastcall u1f(const UniformLocation& _Location, float _X) {
        GL(glUniform1f(_Location.get(), _X));
    }

    // Uniform: 2 float
    inline void __fastcall u2f(const UniformLocation& _Location, float _X, float _Y) {
        GL(glUniform2f(_Location.get(), _X, _Y));
    }

    // Uniform: 3float
    inline void __fastcall u3f(const UniformLocation& _Location, float _X, float _Y, float _Z) {
        GL(glUniform3f(_Location.get(), _X, _Y, _Z));
    }

    // Uniform: 4 float
    inline void __fastcall u4f(const UniformLocation& _Location, float _X, float _Y, float _Z, float _W) {
        GL(glUniform4f(_Location.get(), _X, _Y, _Z, _W));
    }

    inline void __fastcall u1i(const UniformLocation& _Location, int _X) {
        GL(glUniform1i(_Location.get(), _X));
    }

    inline void __fastcall u2i(const UniformLocation& _Location, int _X, int _Y) {
        GL(glUniform2i(_Location.get(), _X, _Y));
    }

    inline void __fastcall u3i(const UniformLocation& _Location, int _X, int _Y, int _Z) {
        GL(glUniform3i(_Location.get(), _X, _Y, _Z));
    }

    inline void __fastcall u4i(const UniformLocation& _Location, int _X, int _Y, int _Z, int _W) {
        GL(glUniform4i(_Location.get(), _X, _Y, _Z, _W));
    }

    inline void bind(void) const { GL(glUseProgram(m_ProgramID)); }
    inline void unbind(void) const { GL(glUseProgram(0)); }
};


#endif // !__SHADER_H__