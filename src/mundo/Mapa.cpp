#include "mundo/Mapa.h"
#include "mundo/Magnetita.h"
#include "mundo/Cobre.h"
#include "mundo/Ouro.h"
#include "mundo/Muro.h"
#include "core/GerenciadorAssets.h"
#include <random>
#include <algorithm>

// true = muro, false = passagem
static constexpr bool MURO_COL8[Mapa::ROWS] = {
    true, false, true, true, true, true, false,
    true, true,  true, false, true, true, true, true, true
};

struct CelulaTemp {
    enum class Tipo { Vazio, Pedra, Magnetita, Cobre, Ouro, Muro } tipo = Tipo::Vazio;
    int durabilidade = 0;
};

// Gera uma grade 16x17
static std::vector<std::vector<CelulaTemp>> gerarGrade() {
    std::mt19937 rng(std::random_device{}());

    std::vector<int> pesos = {80, 7, 3, 10, 27};
    std::vector<CelulaTemp::Tipo> tipos = {
        CelulaTemp::Tipo::Pedra,
        CelulaTemp::Tipo::Magnetita,
        CelulaTemp::Tipo::Ouro,
        CelulaTemp::Tipo::Cobre,
        CelulaTemp::Tipo::Vazio,
    };

    std::vector<CelulaTemp> ordem;
    ordem.reserve(127);

    for (int i = 0; i < 127; ++i) {
        int soma = 0;
        for (int p : pesos) soma += p;

        std::uniform_int_distribution<int> dist(0, soma - 1);
        int a = dist(rng);

        int idx = 0;
        for (int f = 0; f < static_cast<int>(pesos.size()); ++f) {
            if (pesos[f] > a) { idx = f; break; }
            a -= pesos[f];
        }

        CelulaTemp cel;
        cel.tipo = tipos[idx];
        if (cel.tipo == CelulaTemp::Tipo::Pedra) {
            std::uniform_int_distribution<int> d2(0, 10);
            int b = d2(rng);
            cel.durabilidade = (b < 6) ? 15 : (b < 10) ? 22 : 30;
        }
        ordem.push_back(cel);

        pesos[idx]--;
        if (pesos[idx] == 0) {
            pesos.erase(pesos.begin() + idx);
            tipos.erase(tipos.begin() + idx);
        }
    }

    // Grade iniciada como Vazio
    std::vector<std::vector<CelulaTemp>> grade(
        Mapa::ROWS, std::vector<CelulaTemp>(Mapa::COLS));

    // Coluna central de muros
    for (int row = 0; row < Mapa::ROWS; ++row) {
        if (MURO_COL8[row]) grade[row][8].tipo = CelulaTemp::Tipo::Muro;
    }

    // Preenche lado esquerdo (cols 0-7), pulando spawn do J1 em (15, 0)
    int a = 0;
    for (int y = 0; y < Mapa::ROWS; ++y)
        for (int x = 0; x < 8; ++x)
            if (!(y == 15 && x == 0))
                grade[y][x] = ordem[a++];

    for (int y = 0; y < Mapa::ROWS; ++y)
        for (int x = 0; x < 8; ++x)
            grade[y][Mapa::COLS - 1 - x] = grade[y][x];

    return grade;
}

void Mapa::construir(GerenciadorAssets&) {
    _grade.clear();
    _grade.resize(ROWS);
    for (auto& row : _grade) row.resize(COLS);
    _blocosAtivos.clear();

    auto celulaGrade = gerarGrade();

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            const auto& cel = celulaGrade[row][col];
            Rect b(col * TAM_BLOCO, row * TAM_BLOCO, TAM_BLOCO, TAM_BLOCO);

            std::unique_ptr<Pedra> p;
            switch (cel.tipo) {
                case CelulaTemp::Tipo::Pedra:
                    p = std::make_unique<Pedra>(b, cel.durabilidade); break;
                case CelulaTemp::Tipo::Magnetita:
                    p = std::make_unique<Magnetita>(b); break;
                case CelulaTemp::Tipo::Cobre:
                    p = std::make_unique<Cobre>(b); break;
                case CelulaTemp::Tipo::Ouro:
                    p = std::make_unique<Ouro>(b); break;
                case CelulaTemp::Tipo::Muro:
                    p = std::make_unique<Muro>(b); break;
                default: break;
            }

            if (p) {
                _blocosAtivos.push_back(p.get());
                _grade[row][col] = std::move(p);
            }
        }
    }
}

void Mapa::mostrar(IRenderer& r) const {
    for (const auto& row : _grade)
        for (const auto& p : row)
            if (p) p->mostrar(r);
}

void Mapa::removerMortos() {
    for (auto& row : _grade)
        for (auto& p : row)
            if (p && p->estaMorto()) p.reset();

    _blocosAtivos.clear();
    for (const auto& row : _grade)
        for (const auto& p : row)
            if (p) _blocosAtivos.push_back(p.get());
}

int Mapa::contarMineraveis() const {
    int count = 0;
    for (const auto& row : _grade)
        for (const auto& p : row)
            if (p && p->eDestruivel()) ++count;
    return count;
}

std::optional<Pedra*> Mapa::blocoEm(int col, int row) const {
    if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
        return std::nullopt;
    return _grade[row][col]
        ? std::optional<Pedra*>(_grade[row][col].get())
        : std::nullopt;
}
