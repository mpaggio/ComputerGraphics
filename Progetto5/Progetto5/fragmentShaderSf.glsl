#version 330 core
in vec4 ourColor;
out vec4 FragColor;  
uniform vec2 resolution;
uniform float currentTime;
 
vec3 col;
float smooth_;
void main()
{
    /*gl_FragCoord è una variabile built-in che contiene le coordinate del fragment corrente nello spazio di coordinate del viewport.
    resolution.xy:  contiene la risoluzione del viewport.*/

    vec2 ndcCoords = 2.0 * gl_FragCoord.xy / resolution.xy - 1.0; //Questa espressione converte le coordinate del viewport in coordinate normalizzate(-1, 1)
    //nello spazio NDC(Normalized Device Coordinates).* 
    vec2 center = vec2(0.0) + vec2(sin(currentTime), cos(currentTime)) * 0.2;   //// Definisce il centro della finestra in coordinate NDC. 
                                                                  // TO DO Il centro si muove nel tempo descrivendo un cerchio di raggio 0.2.


    float dist = distance(ndcCoords, center); //Calcola la distanza euclidea tra il  frammento corrente ed  centro della finestra
    float tmp = mod(dist, 0.3);  // qualsiasi distanza, per quanto grande sia, sarà all'interno di un intervallo compreso tra 0 e 0.4. Il 
                                    //resto della divisione per 0.4 fornisce valori tra 0 e 0.4 esclusi
  
    float s = smoothstep(0.2, 0.3, tmp);  //Provare Todo
    //float s = step(0.2, tmp); //step resituisce 0 se tmp è minore di 0.2 e restituisce 1 altrimenti. Al diminuire del primo input, diminuisce l'ampiezza della fascia nera
    FragColor = vec4(s * 0.2 , s * 0.3, s * 0.4, 1.0);  //Se il frammento appartiene ad una fascia concentrica di ampiezza 0.4 viene colorato di bianco, altrimenti rimane nero.


     
}


