#pragma once
#include "strutture.h"
#include "lib.h"
vec2 randomPosition(int width, int height);
void findBB(Figura* fig);
void findBB(Curva* fig);
bool checkCollision(Curva obj1, Figura obj2);
bool checkCollision(Curva obj1, Curva obj2);
void updateBB(Figura* fig);
void updateBB(Curva* fig);