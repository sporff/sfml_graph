#pragma once

#include <set>
#include <SFML/Graphics.hpp>

class GameInstance;

class InputManager	
{
public:
	InputManager();
	~InputManager();

	void SetGameInstance(GameInstance* pGameInst);

	void Event_MouseButtonPressed(sf::Mouse::Button mouseButton);
	void Event_MouseButtonReleased(sf::Mouse::Button mouseButton);
	void Event_MouseMoved(sf::Vector2i mousePosition);

	void Event_KeyPressed(sf::Keyboard::Key key);
	void Event_KeyReleased(sf::Keyboard::Key key);

	bool Is_MouseButtonPressed(sf::Mouse::Button mouseButton);
	bool Is_KeyPressed(sf::Keyboard::Key key);

private:
	GameInstance* m_pGameInst;

	// Input state tracking
	GameVector2i m_latestMousePos;
	std::set<sf::Mouse::Button> m_pressedMouseButtons;
	std::set<sf::Keyboard::Key> m_pressedKeys;
};

