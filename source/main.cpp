#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>


int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window
    GLFWwindow* window = glfwCreateWindow (1280,720, "GameDevelopmentProject", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 2000, 150);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return-1;
    }



    // -----------------------------------------------------
    // SHADER CODE
    // -----------------------------------------------------


    std::string vertexShaderSource = R"(
      #version 330 core
      layout (location = 0) in vec3 position;

      void main() {
        gl_Position = vec4(position.x, position.y, position.z, 1.0);
      }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // creates shader on GPU
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader,1,&vertexShaderCStr,nullptr);
    glCompileShader(vertexShader);  // Shader compiler

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex_Shader_Compilation_Failed: " << infoLog << std::endl;
    }

    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main() {
            FragColor = vec4(1.0,0.0,0.0,1.0);
        }
    )";

    GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader,1,&fragmentShaderCStr,nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infolog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infolog);
        std::cerr << "Error: FRAGMENT_SHADER_COMPILATION_FAILED: " << infolog << std::endl;
    }

    GLuint shaderProgram =  glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);  // link all shaders together

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);  // Get link status
    if (!success) {
        char infolog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infolog);
        std::cerr << "Error: SHADDER_PROGRAM_LINKING_FAILED: " << infolog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // -----------------------------------------------------
    //  END SHADER CODE
    // -----------------------------------------------------



    // triangle
    std::vector<float> vertices = {
        0.0f,0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f
    };

    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);



    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window); // command used to swap buffers
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
};