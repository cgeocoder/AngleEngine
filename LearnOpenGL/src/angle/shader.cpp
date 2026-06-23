#include "shader.h"

UniformLocation::UniformLocation(const Shader& _Shader, const std::string& _Name) {
    GL(m_Location = glGetUniformLocation(_Shader.m_ProgramID, _Name.c_str()));
}

template<>
void Shader::attach(const XShader<ShaderType::VertexShader>& _Shader) const {
    if (_Shader.id() != (unsigned int)-1)
        GL(glAttachShader(m_ProgramID, _Shader.id()));
    else
        printf("Shader::attach() failed");
}

template<>
void Shader::attach(const XShader<ShaderType::FragmentShader>& _Shader) const {
    if (_Shader.id() != (unsigned int)-1)
    {
        GL(glAttachShader(m_ProgramID, _Shader.id()));
    }
    else
        printf("Shader::attach() failed");
}

template<>
void Shader::attach(const XShader<ShaderType::GeometryShader>& _Shader) const {
    if (_Shader.id() != (unsigned int)-1)
    {
        GL(glAttachShader(m_ProgramID, _Shader.id()));
    }
    else
        printf("Shader::attach() failed");
}

template<>
void Shader::attach(const XShader<ShaderType::ComputeShader>& _Shader) const {
    if (_Shader.id() != (unsigned int)-1)
    {
        GL(glAttachShader(m_ProgramID, _Shader.id()));
    }
    else
        printf("Shader::attach() failed");
}

void Shader::link() const {
    GL(glLinkProgram(m_ProgramID));
    GL(glValidateProgram(m_ProgramID));
}