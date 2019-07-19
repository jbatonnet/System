#ifndef _BREAKOUTGAME_H_
#define _BREAKOUTGAME_H_

#include <System/Objects/Applications/Game.h>

class BreakoutGame : public Game
{
public:
    void Initialize() override;
    void Load() override;
    void Update(u64 lastTime, u64 time) override;
    void Draw(u64 lastTime, u64 time) override;
    void Unload() override;
};

void BreakoutGame_Main();

#endif