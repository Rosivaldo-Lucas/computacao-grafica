#ifndef __GERENCIADOR_SOM__
#define __GERENCIADOR_SOM__

#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>

class GerenciadorSom {

  private:
    std::map<std::string, Mix_Chunk*> sonsCarregados;

  public:
    GerenciadorSom();
    ~GerenciadorSom();

    bool carregarSom(const char *arquivo);

    void reproduzirSom(const char *arquivo);

};

#endif
