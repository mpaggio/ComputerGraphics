#pragma once
#include "strutture.h"
extern float Tens, Bias, Cont;
extern Curva Derivata, tangenti, curva;
//extern bool visualizzaTg;
extern float* t;
int pval = 200;
extern bool  visualizzaTg;

/// /////////////////////////////////// Disegna geometria //////////////////////////////////////
//Per Curve di hermite
#define PHI0(t)  (2.0*t*t*t-3.0*t*t+1)
#define PHI1(t)  (t*t*t-2.0*t*t+t)
#define PSI0(t)  (-2.0*t*t*t+3.0*t*t)
#define PSI1(t)  (t*t*t-t*t)


float dx(int i, float* t, float Tens, float Bias, float Cont, Curva* curva)
{
	if (i == 0)
		return  0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (curva->CP[i + 1].x - curva->CP[i].x) / (t[i + 1] - t[i]);
	if (i == curva->CP.size() - 1)
		return  0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (curva->CP[i].x - curva->CP[i - 1].x) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 + Cont) * (curva->CP.at(i).x - curva->CP.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (curva->CP.at(i + 1).x - curva->CP.at(i).x) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 - Cont) * (curva->CP.at(i).x - curva->CP.at(i - 1).x) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 + Cont) * (curva->CP.at(i + 1).x - curva->CP.at(i).x) / (t[i + 1] - t[i]);
}
float dy(int i, float* t, float Tens, float Bias, float Cont, Curva* curva)
{
	if (i == 0)
		return 0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (curva->CP.at(i + 1).y - curva->CP.at(i).y) / (t[i + 1] - t[i]);
	if (i == curva->CP.size() - 1)
		return  0.5 * (1.0 - Tens) * (1.0 - Bias) * (1.0 - Cont) * (curva->CP.at(i).y - curva->CP.at(i - 1).y) / (t[i] - t[i - 1]);

	if (i % 2 == 0)
		return  0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 + Cont) * (curva->CP.at(i).y - curva->CP.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 - Cont) * (curva->CP.at(i + 1).y - curva->CP.at(i).y) / (t[i + 1] - t[i]);
	else
		return  0.5 * (1.0 - Tens) * (1.0 + Bias) * (1.0 - Cont) * (curva->CP.at(i).y - curva->CP.at(i - 1).y) / (t[i] - t[i - 1]) + 0.5 * (1 - Tens) * (1 - Bias) * (1 + Cont) * (curva->CP.at(i + 1).y - curva->CP.at(i).y) / (t[i + 1] - t[i]);
}

float DX(int i, float* t)
{
	//Nei vertici di controllo per i quali non sono stati modificati i parametri Tens, Bias, Cont il valore della derivata della componente x della curva è quello originale, altrimenti è quello che è stato modificato nella funzione 
	//keyboardfunc  in seguito alla modifica dei valori Tens, Bias e Cont.

	if (curva.Derivata.at(i).x == 0)
		return dx(i, t,0.0,0.0,0.0, &curva);

	if (curva.Derivata.at(i).x != 0)
		return curva.Derivata.at(i).x;

}

float DY(int i, float* t)
{
	// Nei vertici di controllo per i quali non sono stati modificati i parametri Tens, Bias, Cont il valore della derivata della componente y della curva è quello originale, altrimenti è quello che è stato modificato nella funzione
		//keyboardfunc  in seguito alla modifica dei valori Tens, Bias e Cont.

	if (curva.Derivata.at(i).y == 0)
		return dy(i, t, 0.0, 0.0, 0.0, &curva);

	if (curva.Derivata.at(i).y != 0)
		return curva.Derivata.at(i).y;

}

void InterpolazioneHermite(float* t, Curva* curva, vec4 color_top, vec4 color_bot)
{
	float tg, ampiezza, tm, x, y;
	int is = 0, i;
	float step_tg = 1.0 / (float)(pval - 1);

	for (tg = 0.0; tg <= 1; tg += step_tg) {
		//Localizzo tg nell'intervallo [t[is], t[is+1]]
		if (tg > t[is + 1]) {
			is++;
		}
		
		//Ampiezza dell'intervallo [t[is], t[is+1]] = t[is+1] - t[is]
		ampiezza = t[is + 1] - t[is];

		//Mappo tg appartenente a [t[is], t[is+1]] in [0,1] --> ottengo tm
		tm = (tg - t[is]) / ampiezza;
		
		//Valuto PH_x(tm) = PHI_(is)(tm) = x_(is)*PHI0(tm) + x*(is+1)*PSI0(tm) + dx(is)*PHI1(tm)*ampiezza + dx(is+1)*PSI1(tm)*ampiezza
		x = curva->CP[is].x * PHI0(tm) + curva->CP[is + 1].x * PSI0(tm) + DX(is, t) * PHI1(tm) * ampiezza + DX(is + 1, t) * PSI1(tm) * ampiezza;
		//Valuto PH_y(tm) = PHI_(is)(tm) = y_(is)*PHI0(tm) + y*(is+1)*PSI0(tm) + dy(is)*PHI1(tm)*ampiezza + dy(is+1)*PSI1(tm)*ampiezza
		y = curva->CP[is].y * PHI0(tm) + curva->CP[is + 1].y * PSI0(tm) + DY(is, t) * PHI1(tm) * ampiezza + DY(is + 1, t) * PSI1(tm) * ampiezza;

		curva->vertices.push_back(vec3(x,y,0.0));
		curva->colors.push_back(color_top);
		curva->nv = curva->vertices.size();
	}

	if (visualizzaTg) {
		for (i = 0; i < curva->CP.size(); i++) {
			curva->tg.push_back(vec3(curva->CP[i].x + DX(i, t) / 50.0, curva->CP[i].y + DY(i, t) / 50.0, 0.0));
			curva->col_tg.push_back(vec4(0.0, 0.0, 1.0, 1.0));
			curva->tg.push_back(vec3(curva->CP[i].x - DX(i, t) / 50.0, curva->CP[i].y - DY(i, t) / 50.0, 0.0));
			curva->col_tg.push_back(vec4(0.0, 0.0, 1.0, 1.0));
			curva->ntg = curva->tg.size();
		}
	}
}

void CostruisciHermite( Curva* curva)
{
	curva->vertices.clear();
	curva->colors.clear();
	vec4 color_top = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 color_bot = vec4(1.0, 0.0, 0.0, 1.0);
	InterpolazioneHermite(t, curva, color_top, color_bot);
}