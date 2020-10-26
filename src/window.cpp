#include "window.h"

Window* Window::GetInstance() {
    static Window instance;

    return &instance;
}

void Window::Init(int width, int height, string title, function<void()> OnDraw) {
    glfwInit();
    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(this->window);

    this->OnDraw = OnDraw;
}

void Window::Update() {
    while (!glfwWindowShouldClose(this->window)) {
        this->OnDraw();
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void Window::Shutdown() {
    glfwTerminate();
}
