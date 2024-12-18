#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();//pointer to beginning of data
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    //Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char * message = (char * )alloca(length * sizeof(char));//to do with stack watch video on it slightly confusing
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader");
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;

}
//taking in source code of shaders as the strings WHEN WRITING SHADERS OPENGL REQUIRES A STRING
static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
    unsigned int program  = glCreateProgram();//returns unsigned int
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program ,vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);//READ THE DOCS ON THESE
    //shaders in program now so dont need them anymore
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

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
    //written in shader language
    std::string vertexShader
        = "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    //color is rgba in this example at least just think of 1 as 100%
    std::string fragmentShader
        ="#version 330 core\n"
        "\n"
        "layout(location = 0)out vec4 color;"
        "void main()\n"
        "{\n"
        "color = vec4(1.0,1.0,0.0,1.0);\n"
        "}\n";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

        
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