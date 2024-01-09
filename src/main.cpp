#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TRANSPARENCY_FACTOR 0.05f

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void checkSuccess(unsigned int shaderId, GLenum status);


float window_transparency = 1.0f;

const char *vertexShaderSource = "#version 450 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec3 vertexColor;\n"
    "\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   if (aPos.x > 0) {\n"
    "       vertexColor = vec3(1.0, 0.3, 0.1);\n"
    "   }\n"
    "   if (aPos.x < 0) {\n"
    "       vertexColor = vec3(0.2, 1.0, 0.1);\n"
    "   }\n"
    "   if (aPos.x == 0) {\n"
    "       vertexColor = vec3(0.2, 0.1, 1.0);\n"
    "   }\n"
    "}";

const char *fragmentShaderSource = "#version 450 core\n"
    "out vec4 FragColor;\n"
    "in vec3 vertexColor;\n"
    "uniform vec4 outColor;\n"
    "\n"
    "void main() {\n"
    // "    FragColor = vec4(vertexColor, 1.0);\n"
    "   FragColor = outColor;"
    "}";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL - hello-triangle", NULL, NULL);
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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkSuccess(vertexShader, GL_COMPILE_STATUS);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkSuccess(fragmentShader, GL_COMPILE_STATUS);

    // unsigned int yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
    // glCompileShader(yellowFragmentShader);
    // checkSuccess(yellowFragmentShader, GL_COMPILE_STATUS);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkSuccess(shaderProgram, GL_LINK_STATUS);
    
    // unsigned int yellowShaderProgram = glCreateProgram();
    // glAttachShader(yellowShaderProgram, vertexShader);
    // glAttachShader(yellowShaderProgram, yellowFragmentShader);
    // glLinkProgram(yellowShaderProgram);
    // checkSuccess(yellowShaderProgram, GL_LINK_STATUS);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // float vertices[] = {
    //     // 0.5f, 0.5f, 0.0f,
    //     // 0.5f, -0.5f, 0.0f,
    //     // -0.5f, -0.5f, 0.0f,
    //     // -0.5f, 0.5f, 0.0f,
    //     // -1.0f, 0.0f, 0.0f,
    //     // 0.0f, 1.0f, 0.0f,
    //     // 1.0f, 0.0f, 0.0f,
    //     // 0.0f, -1.0f, 0.0f,
    //     0.0f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,
    //     0.5f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f
    // };

    float firstTriangle[] = {
        -0.5f, 0.0f, 0.0f,
        // -3.7f, 0.7f, 0.0f,
        0.0f, 0.5f, 0.0f,
        // 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        // 0.0f, -1.0f, 0.0f
    };

    float secondTriangle[] {
        0.5f, 0.0f, 0.0f,
        // 1.7f, 0.7f, 0.0f,
        0.0f, 0.5f, 0.0f,
        // 0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        // 0.0f, -1.0f, 0.0f
    };

    // unsigned int t1_indices[] = {
    //     // 0, 1, 3,
    //     // 1, 2, 3,
    //     // 0, 2, 1,
    //     // 4, 3, 2,
    //     // 5, 3, 0,
    //     // 6, 0, 1,
    //     // 7, 1, 2,
    //     // 5, 7, 6,
    //     // 4, 7, 6
    //     0, 1, 2,
    //     // 0, 3, 4
    // };

    // unsigned int t2_indices[] = {
    //     0, 3, 4
    // };

    // unsigned int VBO, VAO1, VAO2, EBO1, EBO2;
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    // glGenBuffers(1, &EBO1);
    // glGenVertexArrays(1, &VAO2);
    // glGenBuffers(1, &EBO2);

    glBindVertexArray(VAOs[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t2_indices), t2_indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    while (!glfwWindowShouldClose(window)) {
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, window_transparency);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float blueValue = (cos(timeValue) / 2.0f) + 0.5f;
        float redValue = (tan(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, sizeof(t2_indices), GL_UNSIGNED_INT, 0);
        
        // glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, sizeof(t1_indices), GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glDeleteVertexArrays(1, &VAO1);
    // glDeleteVertexArrays(1, &VAO2);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO1);
    // glDeleteBuffers(1, &EBO2);
    glDeleteBuffers(2, VBOs);
    glDeleteVertexArrays(2, VAOs);
    glDeleteProgram(shaderProgram);
    // glDeleteProgram(yellowShaderProgram);

    glfwTerminate();
    return 0;
}

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


void checkSuccess(unsigned int shaderId, GLenum status) {
    int success;
    char infoLog[512];

    if (status == GL_COMPILE_STATUS)
        glGetShaderiv(shaderId, status, &success);
    else 
        glGetProgramiv(shaderId, status, &success);

    if (!success) {
        if (status == GL_COMPILE_STATUS)
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        else
            glGetProgramInfoLog(shaderId, 512, NULL, infoLog);

        std::cout << "ERROR::SHADER\n" << infoLog << std::endl;
        exit(-1);
    }
}