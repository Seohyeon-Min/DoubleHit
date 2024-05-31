
#include "Engine/Engine.h"
#include "Game/Mode1.h"
#include "Game/Splash.h"

int main() {
    Engine& engine = Engine::Instance();
    engine.Start("DoubleHit");

    engine.AddFont("Assets/Font_Basic.png");

    Splash splash;
    engine.GetGameStateManager().AddGameState(splash);
    Mode1 mode1;
    engine.GetGameStateManager().AddGameState(mode1);

    while (engine.HasGameEnded() == false) {
        engine.Update();
    }

    engine.Stop();

    return 0;
}
