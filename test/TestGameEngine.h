#include "../Engine/TextGameEngine.h"

class TestGameEngine : public TextGameEngine
{
protected:
    void HandleInput(sf::Event event) override;
    void Render() override;

public:
    TestGameEngine();
    ~TestGameEngine();
};