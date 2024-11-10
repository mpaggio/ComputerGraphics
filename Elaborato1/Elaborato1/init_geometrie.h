/*
#pragma once //: È una direttiva che indica al compilatore di includere il file una sola volta per unità di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file già inclusi.
//Non è parte dello standard C++, quindi la sua disponibilità e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, è supportata dalla maggior parte dei compilatori moderni.
*/

#pragma once

#include "strutture.h"
void INIT_TRIANGLE(Figura* fig);
void INIT_CIRCLE(float cx, float cy, float raggiox, float raggioy, Figura* fig);
void INIT_BUTTERFLY(float cx, float cy, float raggiox, float raggioy, Figura* fig);
void INIT_HEART(float cx, float cy, float raggiox, float raggioy, Figura* fig);
void INIT_PIANO(Figura* fig);
void INIT_FORMA(Curva* curva);
void INIT_CUPOLA_NAVICELLA(Curva* curva);
void INIT_CORPO_NAVICELLA(Curva* curva);
void INIT_ALIENO(Curva* curva);
void INIT_PROIETTILE(Curva* curva);
void INIT_CIRCLE_WITH_SPIKES(float cx, float cy, float raggio, int nSpines, Figura* fig);