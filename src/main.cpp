#include "core/Jogo.h"
#include "core/IProvedorInput.h"
#include "renderer/NullRenderer.h"
#include "enums/ModoJogo.h"
#include "sim/ProvedorInputSim.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <json/json.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

static void configurarLog() {
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(spdlog::level::info);

    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/minecin.log", 1024 * 1024, 3);
    fileSink->set_level(spdlog::level::debug);

    auto logger = std::make_shared<spdlog::logger>(
        "minecin",
        spdlog::sinks_init_list{consoleSink, fileSink});
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
    spdlog::set_pattern("[%H:%M:%S] [%l] %v");
}

static ModoJogo lerModoDoScript(const std::string& caminho) {
    std::ifstream arquivo(caminho);
    if (!arquivo) return ModoJogo::Tempo;
    Json::Value raiz;
    Json::CharReaderBuilder builder;
    std::string erros;
    if (!Json::parseFromStream(builder, arquivo, &raiz, &erros))
        return ModoJogo::Tempo;
    std::string modo = raiz.get("modo", "Tempo").asString();
    return (modo == "Blocos") ? ModoJogo::Blocos : ModoJogo::Tempo;
}

class InputNulo : public IProvedorInput {
public:
    bool isHeld(Tecla)     const override { return false; }
    bool wasPressed(Tecla) const override { return false; }
    void poll()                  override {}
};

int main(int argc, char* argv[]) {
    configurarLog();

    bool        simulacao = false;
    std::string scriptPath;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--simulacao" && i + 1 < argc) {
            simulacao  = true;
            scriptPath = argv[++i];
        }
    }

    NullRenderer renderer;

    if (simulacao) {
        spdlog::info("Modo simulacao: {}", scriptPath);

        ProvedorInputSim input;
        input.carregarScript(scriptPath);

        ModoJogo modo = lerModoDoScript(scriptPath);
        spdlog::info("ModoJogo: {}", modo == ModoJogo::Blocos ? "Blocos" : "Tempo");

        Jogo jogo(renderer, input);
        jogo.inicializar(modo);

        constexpr float DT    = 1.0f / 30.0f;
        constexpr int   LIMIT = 5000;
        int             frames = 0;

        while (!jogo.terminou() && frames < LIMIT) {
            jogo.processar(DT);
            input.poll();
            ++frames;
        }

        spdlog::info("Simulacao concluida em {} frames", frames);
        jogo.imprimirResumo();

    } else {
        spdlog::info("Modo normal (sem janela) — use --simulacao <script.json>");

        InputNulo input;
        Jogo      jogo(renderer, input);
        jogo.inicializar(ModoJogo::Tempo);

        constexpr float DT    = 1.0f / 30.0f;
        constexpr int   LIMIT = 2000;
        int             frames = 0;

        while (!jogo.terminou() && frames < LIMIT) {
            jogo.processar(DT);
            input.poll();
            ++frames;
        }

        spdlog::info("Frames simulados: {}", frames);
        jogo.imprimirResumo();
    }

    return 0;
}
