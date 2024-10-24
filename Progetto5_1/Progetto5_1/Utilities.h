#pragma once
#include "strutture.h"
vec2 randomPosition(int width, int height);
void findBB(Figura* fig);
bool checkCollision(Figura obj1, Figura obj2);