#include "window.h"
#include "times.h"

Window* Window::GetInstance() {
    static Window instance;

    return &instance;
}

void Window::Init(int width, int height, string title, function<void()> OnTick) {
    // 初始化GLFW，设置OpenGL版本号与核心模式
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS必须
#endif

    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(this->window);

    this->OnTick = OnTick;
}

void Window::Update() {
    while (!glfwWindowShouldClose(this->window)) {
        this->OnTick();
        glfwSwapBuffers(this->window);
        glfwPollEvents();
        Time::GetInstance()->Tick();
    }
}

void Window::Shutdown() {
    glfwTerminate();
}

GLFWwindow* Window::GetFlag() {
    return this->window;
}