#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <map>

template<typename _Ty>
class Vec2 {
    typedef Vec2<_Ty> Vec2T;

public:
    inline Vec2(const Vec2T& vec) : x{ vec.x }, y{ vec.y } {}
    inline Vec2(_Ty X, _Ty Y) : x{ X }, y{ Y } {}

    _Ty x, y;
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;

namespace GL {
    void Init(void) {
        if (!glfwInit()) {
            printf("GL::Init() glfwInit() failed");
            exit(-1);
        }
    }

    void InitContext(void) {
        if (glewInit() != GLEW_OK) {
            printf("GL::InitContext() glewInit() failed");
            exit(-1);
        }
    }

    void Terminate(void) {
        glfwTerminate();
    }
}

class VertexBuffer {
private:
    unsigned int m_BufferID;

public:


};

enum class ShaderType {
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER,
    ComputeShader = GL_COMPUTE_SHADER,
};

template<const ShaderType _ShaderType>
class XShader {
private:
    unsigned int m_ProgramID;

public:
    XShader(void)
        : m_ProgramID{ (unsigned int) -1 } {}

    XShader(const XShader<_ShaderType>& _Copy) 
        : m_ProgramID{ _Copy .m_ProgramID} {}

    XShader(const std::string& _Src) {
        m_ProgramID = glCreateShader(static_cast<GLuint>(_ShaderType));

        const char* str = _Src.c_str();
        glShaderSource(m_ProgramID, 1, &str, nullptr);
        glCompileShader(m_ProgramID);
        compile_status();
    }
     
    ~XShader(void) { 
        del();
    }

    void del(void) {
        if (m_ProgramID != (unsigned int) -1) {
            glDeleteShader(m_ProgramID);

            m_ProgramID = (unsigned int) -1;
        }
    }

    inline unsigned int id() const {
        return m_ProgramID;
    }

private:
    void compile_status() {
        int status;
        glGetShaderiv(m_ProgramID, GL_COMPILE_STATUS, &status);

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
            glGetShaderiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);

            char* err_log = (char*)_alloca(length * sizeof(char));

            glGetShaderInfoLog(m_ProgramID, length, &length, err_log);
            printf("XShader: Failed to compile %s: %s\n", 
                shader_type, err_log);

            _freea(err_log);

            del();
        }
    }
};

class VertexShader final : public XShader<ShaderType::VertexShader> {
public:
    inline VertexShader(void)
        : XShader<ShaderType::VertexShader>() {}

    inline VertexShader(const VertexShader& _Copy)
        : XShader<ShaderType::VertexShader>(_Copy) {}

    inline VertexShader(const std::string& _Src)
        : XShader<ShaderType::VertexShader>(_Src) {}
};

class FragmentShader final : public XShader<ShaderType::FragmentShader> {
public:
    inline FragmentShader(void)
        : XShader<ShaderType::FragmentShader>() {}

    inline FragmentShader(const FragmentShader& _Copy)
        : XShader<ShaderType::FragmentShader>(_Copy) {}

    inline FragmentShader(const std::string& _Src)
        : XShader<ShaderType::FragmentShader>(_Src) {}
};

class GeometryShader final : public XShader<ShaderType::GeometryShader> {
public:
    inline GeometryShader(void)
        : XShader<ShaderType::GeometryShader>() {}

    inline GeometryShader(const GeometryShader& _Copy)
        : XShader<ShaderType::GeometryShader>(_Copy) {}

    inline GeometryShader(const std::string& _Src)
        : XShader<ShaderType::GeometryShader>(_Src) {}
};

class ComputeShader final : public XShader<ShaderType::ComputeShader> {
public:
    inline ComputeShader(void)
        : XShader<ShaderType::ComputeShader>() {}

    inline ComputeShader(const ComputeShader& _Copy)
        : XShader<ShaderType::ComputeShader>(_Copy) {}

    inline ComputeShader(const std::string& _Src)
        : XShader<ShaderType::ComputeShader>(_Src) {}
};

class File {
private:
    std::string m_Src;

    // tag - path

    static inline std::map<std::string, std::string>& get_path_map() {
        static std::map<std::string, std::string> path_map;
        return path_map;
    }

public:
    static inline void add_path(const std::string& _Tag, const std::string& _Path) {
        get_path_map()[_Tag] = _Path;
    }

    File(const std::string& _Tag, const std::string& _Filename) {
        auto& path_ma = get_path_map();

        if (path_ma.find(_Tag) == path_ma.end()) {
            return;
        }

        std::ifstream file{ path_ma.at(_Tag) + _Filename };

        if (!file.is_open()) {
            __debugbreak();
        }

        std::string line;
        while (std::getline(file, line))
            m_Src.append(line + '\n');

        file.close();
    }

    File(const std::string& _File) {
        std::ifstream file{ _File };

        if (!file.is_open()) {
            __debugbreak();
        }

        std::string line;
        while (std::getline(file, line))
            m_Src.append(line + '\n');

        file.close();
    }

    inline std::string& raw_str() {
        return m_Src;
    }
};

class Shader {
private:
    unsigned int m_ProgramID;

public:
    Shader() {
        m_ProgramID = glCreateProgram();
    }

    ~Shader() {
        glDeleteProgram(m_ProgramID);
    }

    template<ShaderType _ShaderType>
    void attach(const XShader<_ShaderType>& _Shader) const {
        if (_Shader.id() != (unsigned int)-1) {
            glAttachShader(m_ProgramID, _Shader.id());
        }
        else {
            printf("Shader::attach() failed");
        }
    }

    void link() const {
        glLinkProgram(m_ProgramID);
        glValidateProgram(m_ProgramID);
    }

    void bind(void) const {
        glUseProgram(m_ProgramID);
    }

    void unbind(void) const {
        glUseProgram(0);
    }
};

class Window {
private:
    GLFWwindow* m_Window;
    Vec2i m_Size;
    std::string m_Title;

public:
    Window(const Vec2i& size, const std::string& title) : m_Size{ size } {
        m_Window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);

        if (!m_Window) {
            __debugbreak();
        }

        glfwMakeContextCurrent(m_Window);
    }

    inline void set_title(const std::string& title) {
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    inline bool is_open(void) {
        return !glfwWindowShouldClose(m_Window);
    }

    inline void clear(void) {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    inline void render(void) {
        glfwSwapBuffers(m_Window);

        glfwPollEvents();
    }
};

int main(void) {
    typedef unsigned int uint;

    GL::Init();

    Window window({900, 700}, "Angle Engine");

    GL::InitContext();

    File::add_path("shader", "src\\res\\shaders\\");

    Shader shader;

    __debugbreak();

    shader.attach(VertexShader(File("shader", "vertex_shader.glsl").raw_str()));
    shader.attach(FragmentShader(File("shader", "fragment_shader.glsl").raw_str()));
    shader.link();
    shader.bind();

    __debugbreak();

    const int pos_len = 6;
    float pos[pos_len] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    uint buffer_id;

    // OpenGL creates a buffer
    glGenBuffers(1, &buffer_id);

    // Set fuffer with buffer_id as current
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

    glBufferData(GL_ARRAY_BUFFER, pos_len * sizeof(float), (void*)pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (window.is_open()) {
        window.clear();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.render();
    }

    GL::Terminate();
    return 0;
}