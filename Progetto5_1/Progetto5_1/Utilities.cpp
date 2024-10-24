#pragma once
#include "lib.h"
#include "strutture.h"
#include <random>

vec2 randomPosition(int width, int height) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(0.0f, static_cast<float>(width));
    std::uniform_real_distribution<> disY(0.0f, static_cast<float>(height));
    return glm::vec2(disX(gen), disY(gen));
}

void findBB(Figura* fig) {
    int n;
    n = fig->vertices.size();
    float minx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
    float miny = fig->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

    float maxx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il massimo iniziale
    float maxy = fig->vertices[0].y; // Assumiamo che il primo elemento sia il massimo iniziale

    for (int i = 1; i < n; i++) {
        if (fig->vertices[i].x < minx) {
            minx = fig->vertices[i].x;
        }
        if (fig->vertices[i].x > maxx) {
            maxx = fig->vertices[i].x;
        }

        if (fig->vertices[i].y < miny) {
            miny = fig->vertices[i].y;
        }

        if (fig->vertices[i].y > maxy) {
            maxy = fig->vertices[i].y;
        }
    }
     
    fig->min_BB_obj=vec4(minx,miny,0.0,1.0);
    fig->max_BB_obj = vec4(maxx, maxy, 0.0,1.0);

}

 