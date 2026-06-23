#include "angle/angle.h"
#include "angle/index_buffer.h"
#include "angle/vertex_buffer.h"
#include "angle/vertex_array.h"
#include "angle/window.h"
#include "angle/filesystem.h"

int main(void) {
    typedef unsigned int uint;

    angle::PreInit();

    Window window({900, 700}, "Angle Engine");
    window.set_swap_interval(1);

    angle::Init();
    angle::debug::disable_notification(angle::debug::DebugSeverity::Info);

    File::add_env_path_val("shader", "src\\res\\shaders\\");

    GL(Shader shader);

    GL(shader.attach(VertexShader(File("shader", "vertex_shader.glsl").raw_str())));
    GL(shader.attach(FragmentShader(File("shader", "fragment_shader.glsl").raw_str())));
    GL(shader.link());
    GL(shader.bind());

    GL(UniformLocation color = shader.get_uniform_location("u_Color"));

    const int pos_len = 8;
    float pos[pos_len] = {
        0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f, 0.5f
    };

    VertexArray vao;

    GL(VertexBuffer vbo(pos, pos_len * sizeof(float)));

    VertexBufferLayout layout;
    layout.push<float>(2);

    vao.attach_buffer(vbo, layout);

    GL(IndexBuffer ibo({ 0, 1, 2, 2, 3, 0 }));
    
    shader.unbind();
    vbo.unbind();
    vao.unbind();
    ibo.unbind();

    float a = 0.0f;
    while (window.is_open()) {
        GL(window.clear());

        shader.bind();
        GL(shader.u4f(color, std::sinf(a += 0.01f), 0.3f, 0.4f, 1.0f));
        window.draw(vao, ibo, shader);

        window.update();
    }

    angle::Terminate();

    return 0;
}