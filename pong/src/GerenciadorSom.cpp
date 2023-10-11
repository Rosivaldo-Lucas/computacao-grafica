#include "../includes/GerenciadorSom.hpp"

GerenciadorSom::GerenciadorSom() {
  if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) < 0) {
    std::cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << std::endl;
  }
}

GerenciadorSom::~GerenciadorSom() {
  Mix_CloseAudio();
}

bool GerenciadorSom::carregarSom(const char *arquivo) {
  Mix_Chunk *som = Mix_LoadWAV(arquivo);

  if (som == nullptr) {
    std::cerr << "Erro ao carregar o som: " << Mix_GetError() << std::endl;

    return false;
  }

  this->sonsCarregados[arquivo] = som;

  return true;
}

void GerenciadorSom::reproduzirSom(const char *arquivo) {
  auto it = this->sonsCarregados.find(arquivo);

  if (it != sonsCarregados.end()) {
    Mix_Chunk *som = it->second;

    std::thread soundThread([som] {
      if (Mix_PlayChannel(-1, som, 0) == -1) {
        std::cerr << "Erro ao reproduzir som: " << Mix_GetError() << std::endl;
      }
    });

    soundThread.detach();
  } else {
    std::cerr << "Som não carregado: " << arquivo << std::endl;
  }
}
