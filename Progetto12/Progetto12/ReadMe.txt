VERTEX SHADER:

out vec3 N, V /*direzione di vista*/, L /*luce*/, R /*direzione di riflessione*/

N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);
V = normalize(viewPos - eyePosition.xyz);
L = normalize((eyeLightPos - eyePosition).xyz);
R = reflect(-L, N);

if (sceltaShader == 3){
	gl_Position = Projection * View * Model * vec4();
	...
} 





FRAGMENT SHADER:

in vec3 L, V, N, R;

if (sceltaShader == 3){
	// ambientale
}