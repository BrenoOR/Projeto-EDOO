#ifndef MINECIN_MUNDO_MAPA_H
#define MINECIN_MUNDO_MAPA_H

#include <vector>
#include <memory>
#include <optional>
#include "mundo/Pedra.h"

class GerenciadorAssets;

class Mapa {
public:
    static constexpr int   COLS      = 17;
    static constexpr int   ROWS      = 16;
    static constexpr float TAM_BLOCO = 40.0f;

    void construir(GerenciadorAssets& assets);
    void mostrar(IRenderer& r) const;
    void removerMortos();
    std::vector<Pedra*>& blocos() { return _blocosAtivos; }
    int contarMineraveis() const;
    std::optional<Pedra*> blocoEm(int col, int row) const;

private:
    std::vector<std::vector<std::unique_ptr<Pedra>>> _grade;
    std::vector<Pedra*> _blocosAtivos;
};

#endif // MINECIN_MUNDO_MAPA_H
