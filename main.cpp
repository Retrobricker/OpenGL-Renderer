#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//Defining Vertex Shader. Uses version 3.3, 
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

int main() {
    //Initialize glfw
    //Hints provide glfw what version the user has, so for OpenGL 3.3 we set the major and minor
    //versions to 3 and 3. We tell GLFW to explicitly use the core profile.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Window creation
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Allows CPU to manage graphics for this specific window
    glfwMakeContextCurrent(window);

    //GLAD manages the function pointers for OpenGL. We must initialize GLAD before making any
    //OpenGL calls
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //Create viewport
    //OpenGL uses data specific here to eventually transform 2D coordinates to one on your screen
    //For example, a processed point of location (-0.5,0.5) 
    //would (as its final transformation) be mapped to (200,450) in screen coordinates.
    glViewport(0, 0, 800, 600);

    //store Reference ID to create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Attach shader source code and compile the shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Testing to see if shaders compiled
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Shaders compiled!" << std::endl;
    }


    //Tell GLFW we want to call the framebuffer_size_callback funciton every time it is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Vertices 
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    //glGenBuffers(how many, the reference id) to store onto the GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //Binding means "Every command I issue next should affect this buffer."
    //Binds VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) 
    //will be used to configure the currently bound buffer, which is VBO. 
    //Allocates memory on the GPU (sizeof vertices!)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    //Ready your engines! While loop so it stays open
    /*
    The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW has been instructed to close. 
    
    The glfwPollEvents function checks if any events are triggered 
    (like keyboard input or mouse movement events)

    The glfwSwapBuffers will swap the color buffer 
    (a large 2D buffer that contains color values for each pixel in GLFW's window) 
    that is used to render to during this render iteration and show it as output to the screen.

    Basically, instead of drawing the screen (left to right bottom to top) in front of the user,
    it draws it on a second buffer. When it is done, it swaps the front and back buffer, so you
    are always shown a fully drawn image.
    */
    while (!glfwWindowShouldClose(window)) {

        //input
        processInput(window);
        
        //renderer commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //check and call events and swap buffers
        //polls IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Terminates GLFW library
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window) {
    //Close window when pressing ESC
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    //Width and Height of new resizing passed
    glViewport(0, 0, width, height);
}



