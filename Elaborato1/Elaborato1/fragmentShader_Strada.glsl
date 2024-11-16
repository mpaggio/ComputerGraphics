#ifdef GL_ES
precision mediump float;
#endif

uniform float time;       // Tempo globale (rimane per altri calcoli se necessario)
uniform float speed;      // Costante della velocità della strada, modificabile esternamente
uniform vec2 resolution;  // Risoluzione della finestra
uniform float deltaTime;  // Tempo tra i fotogrammi

// Funzione per il movimento fluido
vec3 road(vec2 uv)
{
    vec3 c1 = vec3(0.1, 0.9, 0.1); // colore verde del prato
    vec3 c2 = vec3(0.1, 0.6, 0.1); // colore verde del prato

    uv.x += speed * deltaTime * 0.005;  // Moltiplica la velocità per deltaTime

    // Cambia il colore in base alla posizione della strada
    if (abs(uv.x) < 0.35)
    {
        c1 = vec3(0.9, 0.1, 0.1); // strisce rosse
        c2 = vec3(0.9, 0.9, 0.9); // strisce bianche
    }
    if (abs(uv.x) < 0.32)
    {
        c1 = vec3(0.5, 0.5, 0.5); // asfalto grigio
        c2 = vec3(0.5, 0.5, 0.5); // asfalto grigio
    }
    if (abs(uv.x) < 0.015)
    {
        c1 = vec3(0.5, 0.5, 0.5); // asfalto grigio
        c2 = vec3(0.9, 0.9, 0.9); // strisce bianche
    }

    // Movimento della strada basato sulla velocità
    float t = time * speed; // La velocità della strada è determinata dalla variabile speed

    // Ripetizione orizzontale della strada
    float rep = fract(uv.y + t);

    // Sfumature della strada
    float blur = 0.1 + dot(uv, uv) * 0.05;  // Una leggera sfocatura

    // Calcola il colore finale della strada
    vec3 ground = mix(c1, c2, smoothstep(0.25 - blur * 0.25, 0.25 + blur * 0.25, rep) *
                              smoothstep(0.75 + blur * 0.25, 0.75 - blur * 0.25, rep));

    return ground;
}

void main(void)
{
    vec2 res = resolution.xy / resolution.y;
    vec2 uv = gl_FragCoord.xy / resolution.y;

    // Centra il sistema di coordinate
    uv -= res / 2.0;

    // Colore finale: solo la strada, senza cielo
    vec3 color = road(uv);
    
    // Imposta il colore del pixel
    gl_FragColor = vec4(color, 1.0);
}
