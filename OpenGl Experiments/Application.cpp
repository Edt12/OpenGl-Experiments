#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

 

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) 
    {
        std::cout << "error";
    }
        
    std::cout << glGetString(GL_VERSION) << std::endl;
    unsigned int buffer;
    glGenBuffers(1, &buffer);/* 1 is number of buffers and unsigned int is just its id */
    glBindBuffer(GL_ARRAY_BUFFER, buffer);/*Selects the buffer  GL_ARRAY_BUFFER is just type basically just says its an array*/
    float positions[6] = {
        -0.5,-0.5,
        0.0,0.5,
        0.5,-0.5
    };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);/*Reads docs.gl for function defintion*/
    glEnableVertexAttribArray(0);//takes in index of vertex and enables it
     /*After defining the data we are now describing the data to opengl*/
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,0);//end value is pointer to first vertex 

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}