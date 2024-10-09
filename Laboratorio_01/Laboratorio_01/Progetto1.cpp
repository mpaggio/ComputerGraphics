// Progetto1.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <chrono>
 

/* Definition of functions (author: Marco Paggetti) */
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

double r = 1.0f, g = 0.0f, b = 0.0f;
double timeValue = 0.0;
// double timeValue = std::chrono::high_resolution_clock::now();  --> per usare il tempo corrente
bool stopColorChange = false;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())   //se glfwInit() dà valore falso, return -1
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); //Abilita il double buffering

    /* Create a windowed mode window and its OpenGL context */
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;

        glfwTerminate(); //LIbera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //crea  il context corrente e lo associa a window. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico


     



    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Adding the event functions to the window */
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (!stopColorChange) {
            // Little increment of the time value
            timeValue += 0.0001;
            // Sin(x) / 2.0 --> [0,1]
            r = (sin(timeValue) + 1.0) / 2.0;
            // +2.0 is for the offset of the sin function
            g = (sin(timeValue + 2.0) + 1.0) / 2.0;
            // +4.0 is for the offset of the sin function
            b = (sin(timeValue + 4.0) + 1.0) / 2.0;
        }

        /* Render here */
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

         
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    
    glfwTerminate();


    return 0;
}


/*
 *  Funcions that handles the press of a button of the mouse.
 *  window: the main window of the program
 *  button: an integer representing the mouse button clicked
 *  action: the type of action done with the mouse button (clicked, released, ...)
 *  mods: an integer representing the modifiers pressed (shift, ctrl, ...)
*/
void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && (mods & GLFW_MOD_CONTROL)) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Mouse clicked at coordinates: x = " << xpos << ", y = " << ypos << std::endl;
    }
    else if (action == GLFW_RELEASE) {
        std::cout << "Mouse click released!" << std::endl;
    }
    else {
        std::cout << "Mouse clicked normally!" << std::endl;
    }
}

/*
 *  Funcions that handles the moves of the mouse cursor.
 *  window: the main window of the program
 *  xpos: the x-coordinate of the mouse cursor
 *  ypos: the y-coordinate of the mouse cursor
*/
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "Cursor position: x = " << xpos << ", y = " << ypos << std::endl;
}

/*
 *  Funcions that handles the scroll of the mouse wheel.
 *  window: the main window of the program
 *  xoffset: the x direction of the scroll (+1/-1)
 *  yoffset: the y direction of the scroll (+1/-1)
*/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "Scrolled: x = " << xoffset << ", y = " << yoffset << std::endl;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

/*
 *  Funcions that handles the pression of a key of the keyboard.
 *  window: the main window of the program
 *  key: an integer representing the key pressed
 *  scancode: an integer representing the scancode of the key
 *  action: the action made with the key (pression, release, ...)
 *  mods: the modifiers pressed with the key
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        stopColorChange = !stopColorChange;
    }
}
 