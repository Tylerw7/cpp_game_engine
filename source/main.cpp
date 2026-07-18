#include <iostream>
#include <GLFW/glfw3.h>


int main() {
    if (!glfwInit()) {
        return -1;
    }

    // create a window
    GLFWwindow* window = glfwCreateWindow (1280,720, "GameDevelopmentProject", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 2000, 150);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}