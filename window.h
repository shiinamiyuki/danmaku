//
// Created by xiaoc on 2018/9/18.
//

#ifndef DANMAKU_WINDOW_H
#define DANMAKU_WINDOW_H
#include <GLFW/glfw3.h>
#include <windows.h>
#include <GL/gl.h>
#include <cmath>

class Window {
protected:
    GLFWwindow *window;
    int width,height;
public:
    Window() {
        width = 1600;
        height = 1400;
        window = glfwCreateWindow(1600, 1400, "Hello World", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        if (!window) {
            glfwTerminate();
        }
        resize();
    }

    virtual void show() {
        while (!glfwWindowShouldClose(window)) {
            update();
            glClear(GL_COLOR_BUFFER_BIT);
            paintGL();
            glfwSwapBuffers(window);

            glfwPollEvents();
            Sleep(1000 / 60);
        }
        glfwTerminate();
    }

    virtual void resize() {
        glViewport(0.0, 0.0, width, height);
        glScaled(1.0, (double)width / height, 1.0);
    }

    virtual void update() {}

    virtual void paintGL() {


    }

    virtual ~Window() {}
};
#endif //DANMAKU_WINDOW_H
