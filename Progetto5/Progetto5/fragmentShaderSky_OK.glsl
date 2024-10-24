#version 330 core
in vec4 ourColor;
out vec4 FragColor;  
uniform vec2 resolution;
uniform float currentTime;
 
vec3 col;
 
const vec3 skyColor = vec3(0.1, 0.8, 1.0);
// Funzione hash semplice per generare un valore pseudo-casuale
float random(vec2 n) {
    return fract(sin(dot(n, vec2(12.9898, 78.233))) );
}


void main()
{
    // Coordinate normalizzate del frammento
    vec2 normalizedCoords = 2.0 * gl_FragCoord.xy / resolution.xy - 1.0;

    // Colore iniziale delle nuvole
    vec3 cloudColor = vec3(0.4, 0.44, 0.70);

    // Parametri delle nuvole
    int numberOfClouds = 6;
    float cloudDensity = 0.4;
    float cloudScale = 0.4;

    // Genera le nuvole come sovrapposizione di cerchi
    for (int i = 0; i < numberOfClouds; i++)
    {
        // Centro casuale del cerchio
        vec2 circleCenter = vec2(random(vec2(float(i), currentTime * 0.01)) * 2.0 - 1.0,
            random(vec2( currentTime * 0.001, float(i))) * 2.0 - 1.0);

        // Distanza del frammento dal centro del cerchio
        float distanceToCenter = length(normalizedCoords - circleCenter);

        // Densità della nuvola in questo punto
        float cloudHeight = smoothstep(cloudScale, 0.0, distanceToCenter);

        // Aggiungi la densità della nuvola al colore finale
        cloudColor += vec3(cloudDensity) * cloudHeight;
    }

    // Calcola il colore finale del frammento, interpolando tra cielo e nuvole
    FragColor = vec4(mix(skyColor, cloudColor, cloudColor.b), 1.0);
}