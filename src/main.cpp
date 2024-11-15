#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <ncurses/ncurses.h>

int WIDTH = 640;
int HEIGHT = 480;

double xcenter = 0.0;
double ycenter = 0.0;
double scale = 0.5;
float iterations = 300;
int fractal = 0; //0 = Mandelbrot, 1 = Julia
double xjulia = 0.0;
double yjulia = 0.0;

double prevTime = 0.0f;
double currentTime = 0.0f;
double timeDiff;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        ycenter = ycenter + 0.01f / scale;
        if (ycenter > 2.0f)
        {
            ycenter = 2.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        ycenter = ycenter - 0.01f / scale;
        if (ycenter < -2.0f)
        {
            ycenter = -2.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        xcenter = xcenter - 0.01f / scale;
        if (xcenter < -2.0f)
        {
            xcenter = -2.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        xcenter = xcenter + 0.01f / scale;
        if (xcenter > 1.0f)
        {
            xcenter = 1.0f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        scale = scale * 1.05f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        scale = scale * 0.95f;
        if (scale < 0.5f)
        {
            scale = 0.5f;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        iterations *= 1.05f;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        iterations *= 0.95f;
        if (iterations < 50)
        {
            iterations = 10;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        yjulia = yjulia + 0.01f / scale;
    }

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        yjulia = yjulia - 0.01f / scale;
    }

    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        xjulia = xjulia - 0.01f / scale;
    }

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        xjulia = xjulia + 0.01f / scale;
    }
}

static void update_window_title(GLFWwindow* window)
{
    currentTime = glfwGetTime();
    timeDiff = currentTime - prevTime;

    std::string FPS = std::to_string(1.0 / timeDiff);
    std::string ms = std::to_string(timeDiff * 1000);
    std::string new_title = "Fractal Explorer - " + FPS + " fps - " + ms + " ms";
    glfwSetWindowTitle(window, new_title.c_str());
    prevTime = currentTime;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    initscr();
    int console_width, console_height;
    getmaxyx(stdscr, console_height, console_width);
    WINDOW* console_window = newwin(console_height, console_width, 0, 0);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Fractal Explorer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }


    const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
    const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model
    
    //std::cout << vendor << renderer << std::endl;
    
    

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
 
    glBindVertexArray(VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("vertex.vs", "fragment.fs");

    box(console_window, 0, 0);

    mvwprintw(console_window, 1, console_width/2-15, "Current Graphics Device:");
    move(2, 35);
    mvwprintw(console_window, 2, console_width/2-20, reinterpret_cast<const char*>(renderer));
    

    WINDOW* parameters_win = newwin(10, 40, 3, 3);
    box(parameters_win, 0, 0);
    
    refresh();
    wrefresh(console_window);
    wrefresh(parameters_win);
  

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        update_window_title(window);

        processInput(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setInt("width", WIDTH);
        shader.setInt("height", HEIGHT);
        shader.setDouble("xcenter", xcenter);
        shader.setDouble("ycenter", ycenter);
        shader.setDouble("scale", scale);
        shader.setDouble("xjulia", xjulia);
        shader.setDouble("yjulia", yjulia);
        shader.setInt("max_iterations", (int)iterations);
        shader.setInt("fractal", fractal);

        mvwprintw(parameters_win, 0, 3, "Fractal Data");
        mvwprintw(parameters_win, 1, 1, "Re: %.16f", xcenter);
        mvwprintw(parameters_win, 2, 1, "Im: %.16f", ycenter);
        mvwprintw(parameters_win, 3, 1, "Zoom: %18.1f", scale);
        mvwprintw(parameters_win, 4, 1, "Iterations: %6d", int(iterations));
        wrefresh(parameters_win);

        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    endwin();
    return 0;
}
