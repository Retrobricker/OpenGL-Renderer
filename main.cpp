#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    glfwMakeContextCurrent();

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

    

    //Tell GLFW we want to call the framebuffer_size_callback funciton every time it is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Ready your engines! While loop so it stays open
    /*
    The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW has been instructed to close. 
    If so, the function returns true and the render loop stops running, after which we can close the application.
    The glfwPollEvents function checks if any events are triggered 
    (like keyboard input or mouse movement events), updates the window state, and 
    calls the corresponding functions (which we can register via callback methods). 
    The glfwSwapBuffers will swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) 
    that is used to render to during this render iteration and show it as output to the screen.
    */
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Terminates GLFW library
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWWindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

