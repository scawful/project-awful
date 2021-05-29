#ifndef State_hpp
#define State_hpp

#include "../core.hpp"
#include "../Actor/Player.hpp"

class State 
{
private:
    
protected:
    // Variables
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
        
    // Resources
    std::map<std::string, sf::Texture> textures;
        
public:
    State(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~State();
    
    // Accessors
    const bool& getQuit() const;
    const bool getKeytime();
    
    // Functions
    void endState();
    void pauseState();
    void unpauseState();
    
    // True Virtual Boys
    virtual void updateMousePositions();
    virtual void updateKeytime(const float& dt);
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

    string changeState;
};

#endif /* State_hpp */
