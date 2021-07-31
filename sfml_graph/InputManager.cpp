#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameTypes.h"
#include "GraphTypes.h"
#include "TileEntity.h"
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

void InputManager::Event_WindowResized(sf::Vector2i windowSize)
{
	if (m_pGameInst == nullptr)
		return;

	m_pGameInst->OnWindowResized(windowSize);
}

void InputManager::Event_MouseButtonPressed(sf::Mouse::Button mouseButton)
{	
	m_pressedMouseButtons.insert(mouseButton);
}

void InputManager::Event_MouseButtonReleased(sf::Mouse::Button mouseButton)
{
	m_pressedMouseButtons.erase(mouseButton);
}

void InputManager::Event_MouseMoved(sf::Vector2i mousePosition)
{
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
