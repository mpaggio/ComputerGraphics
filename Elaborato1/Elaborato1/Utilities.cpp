#pragma once
#include "lib.h"
#include "strutture.h"
#include <random>


extern float speed, deltaTime, lastFrame, minSpeed;


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

void findBB(Curva* fig) {
    int n;
    n = fig->vertices.size();
    float minx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
    float miny = fig->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

    float maxx = fig->vertices[0].x; // Assumiamo che il primo elemento sia il minimo iniziale
    float maxy = fig->vertices[0].y; // Assumiamo che il primo elemento sia il minimo iniziale

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

    fig->min_BB_obj = vec4(minx, miny, 0.0, 1.0);
    fig->max_BB_obj = vec4(maxx, maxy, 0.0, 1.0);

}


bool checkCollision(Figura obj1, Figura obj2) {
    // guardo collisioni su asse x

    bool collisionX = obj1.min_BB.x <= obj2.max_BB.x &&
        obj1.max_BB.x >= obj2.min_BB.x;
    
    // guardo collisioni su asse y

    bool collisionY = obj1.min_BB.y <= obj2.max_BB.y &&
        obj1.max_BB.y >= obj2.min_BB.y;

    
    //Si ha collisione se c'è collisione sia nella direzione x che nella direzione y

    return collisionX && collisionY;
}

bool checkCollision(Curva obj1, Figura obj2) {
    // guardo collisioni su asse x

    bool collisionX = obj1.min_BB.x <= obj2.max_BB.x &&
        obj1.max_BB.x >= obj2.min_BB.x;

    // guardo collisioni su asse y

    bool collisionY = obj1.min_BB.y <= obj2.max_BB.y &&
        obj1.max_BB.y >= obj2.min_BB.y;


    //Si ha collisione se c'è collisione sia nella direzione x che nella direzione y

    return collisionX && collisionY;
}

void updateBB(Figura* fig)
{
    //Aggiorno le coordinate del Bounding Box applicandogli la stessa matrice di modellazione della sua shape
    fig->min_BB = fig->min_BB_obj;
    fig->max_BB = fig->max_BB_obj;
    fig->min_BB = fig->Model * fig->min_BB;
    fig->max_BB = fig->Model * fig->max_BB;
}

void updateBB(Curva* fig)
{
    //Aggiorno le coordinate del Bounding Box applicandogli la stessa matrice di modellazione della sua shape
    fig->min_BB = fig->min_BB_obj;
    fig->max_BB = fig->max_BB_obj;
    fig->min_BB = fig->Model * fig->min_BB;
    fig->max_BB = fig->Model * fig->max_BB;
}


void updateSpeed(float s, float ts, float str) {
    if (ts < minSpeed) {
        ts = minSpeed;
    }
    float delta = ts - s;
    speed += delta * (1.0f - exp(-str * delta));
}


void updateDeltaTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
