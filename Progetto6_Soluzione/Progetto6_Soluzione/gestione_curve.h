#pragma once
#include "strutture.h"
float dx(int i, float* t, float Tens, float Bias, float Cont, Curva* curva);
float dy(int i, float* t, float Tens, float Bias, float Cont, Curva* curva);
float DX(int i, float* t);
float DY(int i, float* t);
void InterpolazioneHermite(float* t, Curva* curva, vec4 color_top, vec4 color_bot);
void CostruisciHermite( Curva* curva);