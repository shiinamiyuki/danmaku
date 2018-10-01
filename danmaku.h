//
// Created by xiaoc on 2018/9/18.
//

#ifndef DANMAKU_DANMAKU_H
#define DANMAKU_DANMAKU_H

#include "window.h"
#include "particle.h"
#include <vector>
#include <cstdio>
#include <ctime>

const int N = 1000;

class Danmaku : public Window {
    std::vector<Particle> p;
    std::vector<double> sinTable, cosTable;
    double t;
public:
    Danmaku() : Window() {
        t = 0;
        double x = 0;
        while (x < M_PI * 2) {
            sinTable.emplace_back(sin(x));
            cosTable.emplace_back(cos(x));
            x += 0.001;
        }
    }

    inline double lookupSin(double x) {
        double sign = 1;
        if (x < 0) {
            sign = -1;
            x = -x;
        }
        return sign * sinTable[fmod(x, 2 * M_PI) / 2 / M_PI * sinTable.size()];
    }

    inline double lookupCos(double x) {
        if (x < 0)
            x = -x;
        return cosTable[fmod(x, 2 * M_PI) / M_PI / 2 * sinTable.size()];
    }

    void update() override {

        double v = sin(t * 6) + 1.1;

        for (int i = 0; i < 640 * 4; i++) {
            double a = i * (3.14159 / 31);
            p.emplace_back(Particle(Vector3(1, 1, 1), Vector3(0, 0, 1),
                                    Vector3(v * lookupSin(t + a), v * lookupCos(t + a), 0)));
        }
//#pragma  omp parallel for schedule(dynamic, 1)
        for (int i = 0; i < p.size(); i++) {
            p[i].update();
        }
        for (int i = 0; i < p.size(); i++) {
            if (!p[i].alive()) {
                std::swap(p[i], p[p.size() - 1]);
                p.pop_back();
                i--;
            }
        }
        t += 0.01;

    }

    void paintGL() override {
        for (auto &i :p) {
            i.paint();
        }
    }

    void show() override {
        while (!glfwWindowShouldClose(window)) {
            auto start = clock();
            update();
            glClear(GL_COLOR_BUFFER_BIT);
            auto mid = clock();
            paintGL();
            glfwSwapBuffers(window);
            glfwPollEvents();
            char s[50];
            auto e = clock();
            sprintf(s, "count = %d, %lfFPS, %3lf:%3lf", (int) p.size(),
                    1.0 / (double) (e - start) * CLOCKS_PER_SEC),
                    (mid - start) / CLOCKS_PER_SEC * 1000.0, (e - mid) / CLOCKS_PER_SEC * 1000.0;
            glfwSetWindowTitle(window, s);
            while (GetTickCount() - start < 1000 / 60) {
                Sleep(1);
            }
        }
        glfwTerminate();
    }
};

#endif //DANMAKU_DANMAKU_H
