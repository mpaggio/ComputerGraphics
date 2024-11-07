#version 330 core
 
in vec4 ourColor;
uniform vec2 resolution;
 
uniform float time;
uniform int numberOfClouds;
out vec4 FragColor; // Colore del fragment
vec3 finalColor;
 // Parametri delle onde
const int numLayers = 5;
const float amplitudes[numLayers] = float[](0.3, 0.4, 0.6, 0.8, 1.0);
const float frequencies[numLayers] = float[](3.18, 2.34, 2.14, 1.4, 1.23);
const float levels[numLayers] = float[](-0.8, -0.6, -0.4, -0.2, 0.0);

//Colore iniziale del cielo
const vec3 skyColor = vec3(0.1, 0.8, 1.0);

/// Funzione per generare onde sinusoidali.
// Combina diverse funzioni seno con frequenze e ampiezze variabili 
// per creare un effetto più naturale.
// Il parametro `time` introduce un movimento nel tempo.

float onde(float x, float amplitude) {
	float n = sin(x*8.0 + time) * 0.05 +
		sin(x*27.3 + time*0.5) * 0.005 + 
		sin(time) * 0.01;
	return n * amplitude;
}

float random(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))));
}


void main()
{

//Mappiamo le coordinate del frammento nel sistema NDC (sistema di Cordinate Normalizzate di Device)
     //vec2 ndc = vec2 ((gl_FragCoord.x / resolution.x- 0.5) * 2, (gl_FragCoord.y / resolution.y - 0.5) * 2);
     vec2 normalizedCoords = 2.0 * gl_FragCoord.xy / resolution.xy - 1.0;

const float waterColorFactor = 0.8;
 
 
    // Inizializzazione del colore del mare
    float seaColor = 0.0;

    // Verifica se il frammento è nella parte inferiore dello schermo
    if (normalizedCoords.y > -1.0 && normalizedCoords.y < -0.1) {
    
        //vengono generate diverse onde di rumore sinusoidale
        // con diverse frequenze e ampiezze.
        float noiseValues[numLayers];
        for (int i = 0; i < numLayers; i++) {
                 noiseValues[i] = onde(normalizedCoords.x,amplitudes[i]);
             }

        
        // Calcolo del colore del mare:
    // - Si itera attraverso i diversi livelli di onde per determinare il livello d'acqua in quel punto.
    // - Il valore di `seaColor` rappresenta la profondità dell'acqua e viene utilizzato per calcolare un colore appropriato.
    // - Un valore di `seaColor` più alto indica acque più profonde e un colore più scuro.

        for (int i = 0; i < numLayers; i++) {
            if (normalizedCoords.y < levels[i] - noiseValues[i]) {
                seaColor = float(i + 1) / float(numLayers);
                break;
            
            }
        }
        //Il colore finale del frammento viene ottenuto miscelando 
        // il colore del mare con un altro colore di base.
         vec3 water_color = seaColor * vec3(0.2,0.1,1.0);;
		 finalColor = mix(vec3(ourColor.r,ourColor.g,ourColor.b),water_color,0.8);
         FragColor= vec4(finalColor, 1.0);
      }
      else
      {
        // Colore iniziale delle nuvole
        vec3 cloudColor = vec3(0.4, 0.44, 0.70);
     
        float cloudDensity = 0.8;  // Densità delle nuvole
         float cloudScale = 0.4;    // Scala delle nuvole
         for (int i = 0; i < numberOfClouds; i++)
         {
             // Centro casuale del cerchio
             vec2 circleCenter = vec2(random(vec2(float(i), time * 0.001)) * 2.0 - 1.0,
                 random(vec2(time * 0.0001, float(i))) * 2.0 - 1.0);

             // Distanza del frammento dal centro del cerchio
             float distanceToCenter = length(normalizedCoords - circleCenter);

             // Densità della nuvola in questo punto
             float cloudHeight = smoothstep(cloudScale, 0.0, distanceToCenter);

             // Aggiungi la densità della nuvola al colore finale
             cloudColor += vec3(cloudDensity) * cloudHeight;
         }
         FragColor = vec4(mix(skyColor, cloudColor, cloudColor.b), 1.0);

       
       } 
    

}
 