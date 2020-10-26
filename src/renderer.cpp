#include <glad/glad.h>

#include "renderer.h"
#include "lib/file.h"

// VAO: 顶点数组对象，索引顶点各种属性
// VBO: 顶点缓冲对象，索引显存的顶点数据
void InitDraw(float vertices[], int count, unsigned int& vao, unsigned int& vbo) {
    glGenVertexArrays(1, &vao); // 创建1个顶点缓冲对象
    glGenBuffers(1, &vbo); // 创建1个顶点缓冲对象
    
    glBindVertexArray(vao); // 绑定VAO，接下来的顶点状态操作都将基于VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // 绑定VBO，类型为顶点属性

    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * count, vertices, GL_STATIC_DRAW); // 传入顶点数据到VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr); // 解析传入的顶点数据给着色器使用，VBO → VAO
    glEnableVertexAttribArray(0); // 启用第0位顶点属性

    // 解除绑定VAO与VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ComplieShader(int shader, string src) {
    const char* code = src.c_str();

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success;
    char log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, log);
        cout << "Shader Compile Error: " << log << endl;
    }
}

int InitShader(string path) {
    string vert_src = File::ReadFile(path + ".vs");
    string frag_src = File::ReadFile(path + ".fs");
    
    int vert_shader = glCreateShader(GL_VERTEX_SHADER);
    int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    ComplieShader(vert_shader, vert_src);
    ComplieShader(frag_shader, frag_src);

    int program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    int success;
    char log[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, log);
        cout << "Shader Link Error: " << log << endl;
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    
    return program;
}

Renderer* Renderer::GetInstance() {
    static Renderer instance;

    return &instance;
}

void Renderer::Init(int width, int height) {
    if (!gladLoadGL()) {
        cout << "Glad Load GL Failed!" << endl;
        exit(-1);
    }
    
    glViewport(0, 0, width, height);

    this->shader = InitShader("shader/test");

    // 模型的三个顶点（XYZ）
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f // top
    };

    InitDraw(vertices, sizeof(vertices) / sizeof(float), this->vao, this->vbo);
}

void Renderer::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(this->shader); // 调用着色器
    glBindVertexArray(this->vao); // 绑定VAO，使用相应顶点属性
    glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三个顶点组成的面
}