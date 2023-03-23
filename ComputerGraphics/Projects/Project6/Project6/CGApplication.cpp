#include "CGApplication.h"

//
// FUNCIÓN: CGApplication::run()
//
// PROPÓSITO: Ejecuta la aplicación
//
void CGApplication::run()
{
    initWindow();
    initOpenGL();
    initModel();
    mainLoop();
    cleanup();
}

//
// FUNCIÓN: CGApplication::initWindow()
//
// PROPÓSITO: Inicializa la ventana
//
void CGApplication::initWindow()
{
    glfwInit();

    window = glfwCreateWindow(WIDTH, HEIGHT, "Computer Graphics", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwMakeContextCurrent(window);
}

//
// FUNCIÓN: CGApplication::initOpenGL()
//
// PROPÓSITO: Inicializa el entorno gráfico
//
void CGApplication::initOpenGL()
{
    glewInit();
}

//
// FUNCIÓN: CGApplication::initModel()
//
// PROPÓSITO: Inicializa el modelo
//
void CGApplication::initModel()
{
    limitFPS = 1.0 / 60.0;
    lastTime = glfwGetTime();
    deltaTime = 0;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    model.Initialize(width, height);
    //model.initialize(width, height);
}

//
// FUNCIÓN: CGApplication::mainLoop()
//
// PROPÓSITO: Bucle principal que procesa los eventos de la aplicación
//
void CGApplication::mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        timing();
        glfwSwapBuffers(window);
    }
}

//
// FUNCIÓN: CGApplication::timing()
//
// PROPÓSITO: Renderizado
//
void CGApplication::timing()
{
    double nowTime = glfwGetTime();
    deltaTime += (nowTime - lastTime) / limitFPS;
    lastTime = nowTime;

    while (deltaTime >= 1.0)
    {
        model.Update();
        deltaTime--;
    }
    model.RenderScene();
}

//
// FUNCIÓN: CGApplication::cleanup()
//
// PROPÓSITO: Libera los recursos y finaliza la aplicación
//
void CGApplication::cleanup()
{
    model.Finalize();
    glfwDestroyWindow(window);
    glfwTerminate();
}

//
// FUNCIÓN: CGApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//
// PROPÓSITO: Respuesta a un evento de teclado sobre la aplicación
//
void CGApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    auto app = reinterpret_cast<CGApplication*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS || action == GLFW_REPEAT) app->model.KeyboardAction(key);

}

//
// FUNCIÓN: CAApplication::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//
// PROPÓSITO: Respuesta a un evento de ratón sobre la aplicación
//
void CGApplication::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto app = reinterpret_cast<CGApplication*>(glfwGetWindowUserPointer(window));
    app->model.MouseButton(button, action);
}

//
// FUNCIÓN: CGApplication::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
//
// PROPÓSITO: Respuesta a un evento de movimiento del cursor sobre la aplicación
//
void CGApplication::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto app = reinterpret_cast<CGApplication*>(glfwGetWindowUserPointer(window));
    app->model.MouseMove(xpos, ypos);
}

//
// FUNCIÓN: CGApplication::framebufferResizeCallback(GLFWwindow* window, int width, int height)
//
// PROPÓSITO: Respuesta a un evento de redimensionamiento de la ventana principal
//
void CGApplication::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto app = reinterpret_cast<CGApplication*>(glfwGetWindowUserPointer(window));
    if (height != 0) app->model.ReSize(width, height);
}
