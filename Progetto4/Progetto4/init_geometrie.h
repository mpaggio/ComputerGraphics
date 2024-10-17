/*
#pragma once //: � una direttiva che indica al compilatore di includere il file una sola volta per unit� di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file gi� inclusi.
//Non � parte dello standard C++, quindi la sua disponibilit� e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, � supportata dalla maggior parte dei compilatori moderni.
*/

#pragma once

#include "strutture.h"
void INIT_TRIANGLE(Figura* fig);
void INIT_CIRCLE(float cx, float cy, float raggiox, float raggioy, Figura* fig);
void INIT_BUTTERFLY(float cx, float cy, float raggiox, float raggioy, Figura* fig);
void INIT_HEART(float cx, float cy, float raggiox, float raggioy, Figura* fig);