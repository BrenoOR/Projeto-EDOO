#ifndef MINECIN_SISTEMAS_SISTEMACOLISAO_H
#define MINECIN_SISTEMAS_SISTEMACOLISAO_H

#include <vector>

class Personagem;
class Pedra;
class Mapa;

class SistemaColisao {
public:
    // Empurra o personagem para fora dos blocos sólidos no grid.
    void resolverMovimento(Personagem& p, const Mapa& mapa);

    // Aplica ação da picareta: quebrar/restaurar pedras ou teleportar oponente.
    void resolverAcao(Personagem& atacante, Personagem& alvo,
                      const std::vector<Pedra*>& pedras);
};

#endif // MINECIN_SISTEMAS_SISTEMACOLISAO_H
