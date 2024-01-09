#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TRANSPARENCY_FACTOR 0.05f

float window_transparency = TRANSPARENCY_FACTOR;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    std::cout << "Resize window to (" << width << ", " << height << ")" << std::endl; 
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);
    
    if (action == GLFW_RELEASE || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_RIGHT && window_transparency < 1.0f)
            window_transparency += TRANSPARENCY_FACTOR;

        if (key == GLFW_KEY_LEFT && window_transparency > 0.0f)
            window_transparency -= TRANSPARENCY_FACTOR;
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL - helloworld", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    while (!glfwWindowShouldClose(window)) {
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, window_transparency);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}