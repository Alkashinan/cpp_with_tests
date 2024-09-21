
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "func.cpp"


// Функции для сохранения и загрузки прогресса игры
void saveProgress(int dialogueIndex1, bool isCharacter1Speaking);
void loadProgress(int& dialogueIndex1, bool& isCharacter1Speaking);

// Функция для перехода к выбору опций диалога
void skipToChoices(int& currentDialogueIndex1, std::vector<std::string>& dialogues1, GameState& state, sf::Text& dialogue1);

// Функции для обработки ввода пользователя в различных состояниях игры
void handleMenuState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton);
void handlePlayingState(const sf::Event& event, GameState& state, int& currentDialogueIndex1, std::vector<std::string>& dialogues1, sf::Text& dialogue1, bool& isCharacter1Speaking);
void handleSettingsState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Music& music, sf::RectangleShape& volumeSlider, sf::RectangleShape& brightnessSlider, sf::RectangleShape& volumeKnob, sf::RectangleShape& brightnessKnob, sf::Sprite& gameBackground);
void handleChoiceState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Text& choice1, sf::Text& choice2, std::vector<std::string>& dialogues1, std::vector<DialogueOption>& choices, int& currentDialogueIndex1, sf::Text& dialogue1, bool& isCharacter1Speaking);
void handleSaveLoadState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Text& saveProgressButton, sf::Text& loadProgressButton, int& currentDialogueIndex1, bool& isCharacter1Speaking, std::vector<std::string>& dialogues1, sf::Text& dialogue1);
void handleCreditsState(const sf::Event& event, GameState& state);

// Функции для отображения элементов интерфейса в различных состояниях игры
void drawMenuState(sf::RenderWindow& window, sf::Sprite& menuBackground, sf::RectangleShape& menuBox, sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton);
void drawPlayingState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::Text& dialogue1);
void drawSettingsState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::RectangleShape& volumeSlider, sf::RectangleShape& volumeKnob, sf::RectangleShape& brightnessSlider, sf::RectangleShape& brightnessKnob);
void drawSaveLoadState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::Text& saveProgressButton, sf::Text& loadProgressButton);
void drawChoiceState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& choiceBox, sf::Text& choice1, sf::Text& choice2);
void drawCreditsState(sf::RenderWindow& window, sf::Text& creditsText);

// Функции для инициализации различных элементов интерфейса
void initButtons(sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton, sf::Font& font);
void initSlider(sf::RectangleShape& slider, sf::Vector2f size, sf::Color color, sf::Vector2f position);
void initChoiceBox(sf::RectangleShape& choiceBox);

// Функция для воспроизведения фоновой музыки
void playMusic(sf::Music& music);

