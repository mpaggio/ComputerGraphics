#pragma once
#include "lib.h"
#include "strutture.h"
#include <random>


vec2 randomPosition(int width, int height) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(270, width - 270);
    float posX = static_cast<float>(disX(gen));
    float posY = static_cast<float>(height - 80);
    return glm::vec2(posX, posY);
}

vec2 randomPositionForTarget(int width, int height) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(70, width - 70);
    float posX = static_cast<float>(disX(gen));
    float posY = static_cast<float>(height - 80);
    return glm::vec2(posX, posY);
}

float randomTime() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(1.5f, 5.0f);
    return dis(gen);  // Restituisce un solo valore casuale tra 1.5 e 5.0
}


bool elementShouldSpawn(float lastSpownTime, float interval) {
    float currentTime = static_cast<float>(glfwGetTime()) / 1000.0f;
    return (currentTime - lastSpownTime >= interval);
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

bool checkCollision(Curva obj1, Curva obj2) {
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


