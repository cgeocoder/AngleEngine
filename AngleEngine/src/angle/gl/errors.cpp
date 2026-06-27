#include "errors.h"
#include "../engine/kernel.h"

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string>

#ifdef _DEBUG

namespace angle::debug {

    static bool g_notification_severity[4];
    static std::vector<DebugCallbackInfo> g_debug_callback_info;

    void enable_notification(DebugSeverity severity) {
        if (severity >= DebugSeverity::Low && severity <= DebugSeverity::Info)
            g_notification_severity[(unsigned int)severity] = true;
    }

    void disable_notification(DebugSeverity severity) {
        if (severity >= DebugSeverity::Low && severity <= DebugSeverity::Info)
            g_notification_severity[(unsigned int)severity] = false;
    }

    void add_debug_info(const wchar_t* file, const char* code, long line) {
        g_debug_callback_info.push_back({ file, code, line });
    }

    void clear_debug_info() {
        g_debug_callback_info.clear();
    }

    static inline bool is_ebable(DebugSeverity severity) {
        return g_notification_severity[(unsigned int)severity];
    }

    void APIENTRY DebugErrorCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam) {

        const char* severity_str;

        switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            if (!is_ebable(DebugSeverity::Low))
                return;

            severity_str = "Low severity";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            if (!is_ebable(DebugSeverity::Medium))
                return;

            severity_str = "Ledium severity";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            if (!is_ebable(DebugSeverity::Hight))
                return;

            severity_str = "Hight severity";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            if (!is_ebable(DebugSeverity::Info))
                return;

            severity_str = "Info notification";
            break;
        default:
            severity_str = "???";
            break;
        }

        std::vector<DebugCallbackInfo> dci = *(std::vector<DebugCallbackInfo>*)userParam;

        printf(
            "[OpenGL] (%s): %s\nError traceroute:\n",
            severity_str,
            message
        );

        size_t sep = ((std::wstring)std::filesystem::current_path()).length();

        for (auto& info : dci) {
            printf(
                ">> at %ls:%ld\t| '%s'\n",
                std::wstring(info.file).substr(sep).c_str(),
                info.line,
                info.code
            );
        }

        printf("\n");

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            printf("\nExit with error code 0x%p\n", (void*)GL_DEBUG_SEVERITY_HIGH);
            exit(GL_DEBUG_SEVERITY_HIGH);
            break;
        }
    }

    void InitDebugOutput() {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(DebugErrorCallback, &g_debug_callback_info);

        enable_notification(DebugSeverity::Low);
        enable_notification(DebugSeverity::Medium);
        enable_notification(DebugSeverity::Hight);
        enable_notification(DebugSeverity::Info);
    }
}

#endif // !_DEBUG