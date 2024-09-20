#include <gtest/gtest.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>

// Подключаем оригинальные функции
#include "saves/saves.h"

// Проверяем успешное сохранение данных в файл
TEST(SaveProgressTest, SavesCorrectData) {
    int dialogueIndex = 5;
    bool isCharacter1Speaking = true;

    saveProgress(dialogueIndex, isCharacter1Speaking);

    std::ifstream saveFile("saves/mysave.txt");
    ASSERT_TRUE(saveFile.is_open());

    int savedDialogueIndex;
    bool savedIsCharacter1Speaking;
    saveFile >> savedDialogueIndex;
    saveFile >> savedIsCharacter1Speaking;

    EXPECT_EQ(dialogueIndex, savedDialogueIndex);
    EXPECT_EQ(isCharacter1Speaking, savedIsCharacter1Speaking);

    saveFile.close();
}

// Проверяем, что при ошибке сохранения данные не сохраняются
TEST(SaveProgressTest, HandlesFileOpenError) {
    // Удаляем директорию, чтобы вызвать ошибку открытия файла
    std::filesystem::remove_all("saves");

    int dialogueIndex = 5;
    bool isCharacter1Speaking = true;

    saveProgress(dialogueIndex, isCharacter1Speaking);

    std::ifstream saveFile("saves/mysave.txt");
    ASSERT_FALSE(saveFile.is_open());  // Файл не должен существовать, так как не удалось сохранить
}

// Проверяем успешную загрузку данных из файла
TEST(LoadProgressTest, LoadsCorrectData) {
    // Предварительно сохраняем данные
    std::ofstream saveFile("saves/mysave.txt");
    saveFile << 7 << "\n" << false << "\n";
    saveFile.close();

    int dialogueIndex = 0;
    bool isCharacter1Speaking = true;

    loadProgress(dialogueIndex, isCharacter1Speaking);

    EXPECT_EQ(dialogueIndex, 7);
    EXPECT_EQ(isCharacter1Speaking, false);
}

// Проверяем, что функция корректно обрабатывает отсутствие файла
TEST(LoadProgressTest, HandlesFileNotFoundError) {
    // Удаляем файл перед тестированием
    std::filesystem::remove("saves/mysave.txt");

    int dialogueIndex = 0;
    bool isCharacter1Speaking = true;

    loadProgress(dialogueIndex, isCharacter1Speaking);

    // Ожидаем, что значения останутся неизменными
    EXPECT_EQ(dialogueIndex, 0);
    EXPECT_EQ(isCharacter1Speaking, true);
}

// Проверяем успешный переход к состоянию выбора
TEST(SkipToChoicesTest, SkipsToChoicesState) {
    int currentDialogueIndex1 = 2;
    std::vector<std::string> dialogues1 = {"Text1", "Text2", "Choice text"};
    sf::Text dialogue1;
    GameState state = GameState::Playing;

    skipToChoices(currentDialogueIndex1, dialogues1, state, dialogue1);

    EXPECT_EQ(currentDialogueIndex1, 2);
    EXPECT_EQ(dialogue1.getString(), "Choice text");
    EXPECT_EQ(state, GameState::Choice);
}

// Проверяем, что при пустом векторе диалогов программа не падает
TEST(SkipToChoicesTest, HandlesEmptyDialogues) {
    int currentDialogueIndex1 = 0;
    std::vector<std::string> dialogues1 = {};
    sf::Text dialogue1;
    GameState state = GameState::Playing;

    skipToChoices(currentDialogueIndex1, dialogues1, state, dialogue1);

    // Ожидаем, что значения останутся неизменными
    EXPECT_EQ(currentDialogueIndex1, 0);
    EXPECT_EQ(dialogue1.getString(), "");
    EXPECT_EQ(state, GameState::Playing);
}

// Проверяем успешный переход в состояние игры при нажатии на кнопку старта
TEST(HandleMenuStateTest, ClicksStartButton) {
    sf::RenderWindow window;
    sf::Text startButton, settingsButton, saveButton, quitButton;

    startButton.setPosition(0, 0);
    startButton.setString("START");
    startButton.setCharacterSize(24);

    settingsButton.setPosition(0, 30);
    saveButton.setPosition(0, 60);
    quitButton.setPosition(0, 90);

    GameState state = GameState::Menu;
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = 1;
    event.mouseButton.y = 1;

    handleMenuState(event, state, window, startButton, settingsButton, saveButton, quitButton);

    EXPECT_EQ(state, GameState::Playing);
}

// Проверяем, что при нажатии вне кнопок состояние не меняется
TEST(HandleMenuStateTest, ClicksOutsideButtons) {
    sf::RenderWindow window;
    sf::Text startButton, settingsButton, saveButton, quitButton;

    startButton.setPosition(0, 0);
    startButton.setString("START");
    startButton.setCharacterSize(24);

    settingsButton.setPosition(0, 30);
    saveButton.setPosition(0, 60);
    quitButton.setPosition(0, 90);

    GameState state = GameState::Menu;
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = 500;
    event.mouseButton.y = 500;

    handleMenuState(event, state, window, startButton, settingsButton, saveButton, quitButton);

    EXPECT_EQ(state, GameState::Menu);
}

// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
