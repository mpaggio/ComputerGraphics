#pragma once

/*
#pragma once //: � una direttiva che indica al compilatore di includere il file una sola volta per unit� di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file gi� inclusi.
//Non � parte dello standard C++, quindi la sua disponibilit� e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, � supportata dalla maggior parte dei compilatori moderni.
*/

int INIT_GLAD_GLFW( );
void INIT_VAO(Mesh* fig);
void INIT_SHADER(void);
void INIT_CAMERA_PROJECTION();
void INIT_Illuminazione();
int INIT_Cubemap(string SkyboxDir);
int  INIT_TEXTURE(string path);
void INIT_Scene(vector<std::string> path_texture, vector<int>* texture, int* cubemapTexture);
