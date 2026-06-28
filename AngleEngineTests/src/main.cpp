#include <angle.h>
#include <filesystem>

using namespace angle;

class MyApp : public App {
private:
    Window window;

public:
	MyApp() {
        window = Window({ 900, 700 }, "Angle Engine");
        window.set_swap_interval(1);

        set_current_context();
        angle::debug::disable_notification(angle::debug::DebugSeverity::Info);
	}

	~MyApp() {
		log.info("MyApp::~MyApp()");
	}

	void run() override {
        Shader shader;
        UniformLocation u_texture;

        {
            File v_sh("..\\AngleEngine\\res\\shaders\\vertex_shader.glsl");
            shader.attach(VertexShader(v_sh.raw_str()));

            File f_sh("..\\AngleEngine\\res\\shaders\\fragment_shader.glsl");
            shader.attach(FragmentShader(f_sh.raw_str()));
        }

        shader.link();
        shader.bind(); 

        Texture2D tex{ "..\\AngleEngine\\res\\logo\\logo.png" };
        tex.bind();

        u_texture = shader.get_uniform_location("u_Texture");
        shader.u1i(u_texture, 0);

        constexpr int pos_len = 16;
        float pos[pos_len] = {
            -0.5f, -0.5f,     0.0f, 0.0f,
            0.5f, -0.5f,    1.0f, 0.0f,
            0.5f, 0.5f,     1.0f, 1.0f,
            -0.5f, 0.5f,     0.0f, 1.0f
        };

        VertexArray vao;
        VertexBuffer vbo(pos, pos_len * sizeof(float));
        IndexBuffer ibo({ 0, 1, 2, 2, 3, 0 });

        VertexArrayConfig va_conf;
        va_conf.add_config<float>(2);
        va_conf.add_config<float>(2);

        vao.attach_buffer(vbo, va_conf);

        vao.unbind();
        vbo.unbind();
        ibo.unbind();
        shader.unbind();

        float a = 0.0f;
        while (window.is_open()) {
            window.clear();

            shader.bind();
            window.draw(vao, ibo, shader);

            window.update();
        }
	}
};

set_entry_point_class(MyApp);
