#include <iostream>

#include "GameTypes.h"
#include "GraphTypes.h"
#include "InputManager.h"
#include "GameInstance.h"

InputManager::InputManager()
{
	m_pGameInst = nullptr;
}

InputManager::~InputManager()
{

}

void InputManager::SetGameInstance(GameInstance* pGameInst)
{
	m_pGameInst = pGameInst;
}

void InputManager::Event_MouseButtonPressed(sf::Mouse::Button mouseButton)
{
	switch (mouseButton)
	{
	case sf::Mouse::Left:
		std::cout << "Pressed left\n";
		break;
	case sf::Mouse::Middle:
		std::cout << "Pressed middle\n";
		break;
	case sf::Mouse::Right:
		std::cout << "Pressed right\n";
		break;
	default:
		std::cout << "Pressed unknown\n";
		break;
	}
	
	m_pressedMouseButtons.insert(mouseButton);
}

void InputManager::Event_MouseButtonReleased(sf::Mouse::Button mouseButton)
{
	switch (mouseButton)
	{
	case sf::Mouse::Left:
		std::cout << "Release left\n";
		break;
	case sf::Mouse::Middle:
		std::cout << "Release middle\n";
		break;
	case sf::Mouse::Right:
		std::cout << "Release right\n";
		break;
	default:
		std::cout << "Release unknown\n";
		break;
	}

	m_pressedMouseButtons.erase(mouseButton);
}

void InputManager::Event_MouseMoved(sf::Vector2i mousePosition)
{
	//std::cout << "Moved: " << mousePosition.x << ", " << mousePosition.y << "\n";
	m_latestMousePos = mousePosition;

	if (m_pGameInst == nullptr)
		return;

	m_pGameInst->OnMouseMoved(mousePosition);
}

void InputManager::Event_KeyPressed(sf::Keyboard::Key key)
{
	m_pressedKeys.insert(key);
}

void InputManager::Event_KeyReleased(sf::Keyboard::Key key)
{
	m_pressedKeys.erase(key);
}

bool InputManager::Is_MouseButtonPressed(sf::Mouse::Button mouseButton)
{
	return (m_pressedMouseButtons.find(mouseButton) != m_pressedMouseButtons.end());
}

bool InputManager::Is_KeyPressed(sf::Keyboard::Key key)
{
	return (m_pressedKeys.find(key) != m_pressedKeys.end());
}
