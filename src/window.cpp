#include "window.h"

Window* Window::GetInstance() {
    static Window instance;

    return &instance;
}

void Window::Init(int width, int height, string title) {
    glfwInit();
    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(this->window);
}

void Window::Update() {
    while (!glfwWindowShouldClose(this->window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void Window::Shutdown() {
    glfwTerminate();
}
