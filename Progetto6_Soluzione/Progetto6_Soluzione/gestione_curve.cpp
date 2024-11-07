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
	//Nei vertici di controllo per i quali non sono stati modificati i parametri Tens, Bias, Cont il valore della derivata della componente x della curva � quello originale, altrimenti � quello che � stato modificato nella funzione 
	//keyboardfunc  in seguito alla modifica dei valori Tens, Bias e Cont.

	if (curva.Derivata.at(i).x == 0)
		return dx(i, t,0.0,0.0,0.0, &curva);

	if (curva.Derivata.at(i).x != 0)
		return curva.Derivata.at(i).x;

}

float DY(int i, float* t)
{
	// Nei vertici di controllo per i quali non sono stati modificati i parametri Tens, Bias, Cont il valore della derivata della componente y della curva � quello originale, altrimenti � quello che � stato modificato nella funzione
		//keyboardfunc  in seguito alla modifica dei valori Tens, Bias e Cont.

	if (curva.Derivata.at(i).y == 0)
		return dy(i, t, 0.0, 0.0, 0.0, &curva);

	if (curva.Derivata.at(i).y != 0)
		return curva.Derivata.at(i).y;

}

void InterpolazioneHermite(float* t, Curva* curva, vec4 color_top, vec4 color_bot)
{
	float p_t = 0, p_b = 0, p_c = 0, x, y;
	float passotg = 1.0 / (float)(pval - 1);
	int j;

	 
	float tg = 0, tgmapp, ampiezza;
	int i = 0;
	int is = 0; //indice dell'estremo sinistro dell'intervallo [t(i),t(i+1)] a cui il punto tg
	//appartiene


	 
	
	
	for (tg = 0; tg <= 1; tg += passotg)
	{
		//Localizzo l'intervallo a cui tg appartiente
		if (tg > t[is + 1]) is++;
		 
		ampiezza = (t[is + 1] - t[is]);

		//mappo tg nell'intervallo [0,1]

		tgmapp = (tg - t[is]) / ampiezza;
		 
		x = curva->CP[is].x * PHI0(tgmapp) + DX(is, t) * PHI1(tgmapp) * ampiezza + curva->CP[is + 1].x * PSI0(tgmapp) + DX(is + 1, t) * PSI1(tgmapp) * ampiezza;
		y = curva->CP[is].y * PHI0(tgmapp) + DY(is, t) * PHI1(tgmapp) * ampiezza + curva->CP[is + 1].y * PSI0(tgmapp) + DY(is + 1, t) * PSI1(tgmapp) * ampiezza;
		 
		curva->vertices.push_back(vec3(x, y, 0.0));
		curva->colors.push_back(color_top);
		curva->nv = curva->vertices.size();
		 
	}

	 
	if (visualizzaTg)
	{
		for (size_t i = 0; i < curva->CP.size(); i++)
		{
			 //Individuo le coordinate  dell'estremo destro del segmento tangente nel vertice di controllo i.esimo: si trova a partire da CP[i] nella direzione della tangente 

			curva->tg.push_back(vec3(curva->CP[i].x + DX(i, t) / 50, curva->CP[i].y + DY(i, t) / 50, 0.0));
			curva->col_tg.push_back(vec4(0.0, 0.0, 1.0, 1.0));
			//Individuo le coordinate  dell'estremo sinistro del segmento tangente nel vertice di controllo i.esimo: si trova a partire da CP[i] nella direzione della tangente (verso opposto)
			curva->tg.push_back(vec3(curva->CP[i].x - DX(i, t) / 50, curva->CP[i].y - DY(i, t) / 50, 0.0));
			curva->col_tg.push_back(vec4(0.0, 0.0, 1.0, 1.0));
			curva->ntg = curva->tg.size();

		}
	}
	 
	 
}

void CostruisciHermite( Curva* curva)
{
	curva->vertices.clear();
	curva->colors.clear();
	curva->tg.clear();
	vec4 color_top = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 color_bot = vec4(1.0, 0.0, 0.0, 1.0);


	InterpolazioneHermite(t, curva, color_top, color_bot);

}