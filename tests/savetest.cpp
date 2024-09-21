
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Включите ваши заголовочные файлы, где определены функции
// Например: #include "game_functions.h"

// Определения функций, если они находятся не в заголовочном файле (удалите, если они в .h файле)
void saveProgress(int dialogueIndex1, bool isCharacter1Speaking) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";

    // Создаем директорию, если она не существует
    if (!std::filesystem::exists(saveDirectory)) {
        std::filesystem::create_directories(saveDirectory);
    }

    // Открываем файл для записи
    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile << dialogueIndex1 << "\n" << isCharacter1Speaking << "\n";
        saveFile.close();
    } else {
        std::cerr << "Error: Could not open save file for writing: " << saveFilePath << std::endl;
    }
}

void loadProgress(int& dialogueIndex1, bool& isCharacter1Speaking) {
    std::string saveFilePath = "saves/mysave.txt";
    std::ifstream loadFile(saveFilePath);
    if (loadFile.is_open()) {
        loadFile >> dialogueIndex1;
        loadFile >> isCharacter1Speaking;
        loadFile.close();
    } else {
        std::cerr << "Error: Could not open save file for reading: " << saveFilePath << std::endl;
    }
}

enum class GameState {
    Menu,
    Playing,
    Settings,
    SaveLoad,
    Choice,
    Credits
};

void skipToChoices(int& currentDialogueIndex1, std::vector<std::string>& dialogues1, GameState& state, sf::Text& dialogue1) {
    if (dialogues1.empty()) {
        std::cerr << "Error: dialogues1 is empty, cannot skip to choices." << std::endl;
        return;
    }
    currentDialogueIndex1 = dialogues1.size() - 1;
    dialogue1.setString(dialogues1[currentDialogueIndex1]);
    sf::FloatRect textRect1 = dialogue1.getLocalBounds();
    dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));  // Adjusted for screen resolution 1280x720
    state = GameState::Choice;
}

// Тесты для saveProgress
TEST(SaveProgressTest, SavesCorrectData) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";
    
    // Удаляем файл, если он существует
    if (std::filesystem::exists(saveFilePath)) {
        std::filesystem::remove(saveFilePath);
    }
    
    // Убедимся, что директория существует
    std::filesystem::create_directories(saveDirectory);

    // Сохраняем тестовые данные
    int dialogueIndex = 5;
    bool isCharacter1Speaking = true;
    saveProgress(dialogueIndex, isCharacter1Speaking);

    // Проверяем, что файл был создан
    ASSERT_TRUE(std::filesystem::exists(saveFilePath)) << "Error: save file does not exist.";

    // Открываем файл для чтения и проверяем данные
    std::ifstream saveFile(saveFilePath);
    ASSERT_TRUE(saveFile.is_open()) << "Error: Could not open save file.";

    int savedDialogueIndex;
    bool savedIsCharacter1Speaking;
    saveFile >> savedDialogueIndex;
    saveFile >> savedIsCharacter1Speaking;

    // Проверяем, что сохраненные данные совпадают с исходными
    EXPECT_EQ(dialogueIndex, savedDialogueIndex);
    EXPECT_EQ(isCharacter1Speaking, savedIsCharacter1Speaking);

    saveFile.close();
}

// Тесты для loadProgress
TEST(LoadProgressTest, LoadsCorrectData) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";

    // Создаем директорию, если она не существует
    std::filesystem::create_directories(saveDirectory);

    // Сохраняем тестовые данные в файл
    std::ofstream saveFile(saveFilePath);
    ASSERT_TRUE(saveFile.is_open()) << "Error: Could not open save file for writing.";
    saveFile << 7 << "\n" << false << "\n";
    saveFile.close();

    // Загружаем данные
    int dialogueIndex = 0;
    bool isCharacter1Speaking = true;
    loadProgress(dialogueIndex, isCharacter1Speaking);

    // Проверяем, что загруженные данные совпадают с ожидаемыми
    EXPECT_EQ(dialogueIndex, 7);
    EXPECT_EQ(isCharacter1Speaking, false);

    // Удаляем файл после теста
    std::filesystem::remove(saveFilePath);
}

TEST(LoadProgressTest, HandlesFileNotFoundError) {
    std::string saveFilePath = "saves/mysave.txt";

    // Удаляем файл, если он существует
    if (std::filesystem::exists(saveFilePath)) {
        std::filesystem::remove(saveFilePath);
    }

    // Загружаем данные из несуществующего файла
    int dialogueIndex = 5;
    bool isCharacter1Speaking = true;
    loadProgress(dialogueIndex, isCharacter1Speaking);

    // Ожидаем, что значения останутся неизменными, так как файл не существует
    EXPECT_EQ(dialogueIndex, 5);
    EXPECT_EQ(isCharacter1Speaking, true);
}

// Тесты для skipToChoices
TEST(SkipToChoicesTest, SkipsToChoicesState) {
    int currentDialogueIndex1 = 0;
    std::vector<std::string> dialogues1 = {"Hello", "How are you?", "Choose your path:"};
    sf::Text dialogue1;
    GameState state = GameState::Playing;

    skipToChoices(currentDialogueIndex1, dialogues1, state, dialogue1);

    EXPECT_EQ(currentDialogueIndex1, dialogues1.size() - 1);
    EXPECT_EQ(dialogue1.getString(), "Choose your path:");
    EXPECT_EQ(state, GameState::Choice);
}

TEST(SkipToChoicesTest, HandlesEmptyDialogues) {
    int currentDialogueIndex1 = 0;
    std::vector<std::string> dialogues1 = {};
    sf::Text dialogue1;
    GameState state = GameState::Playing;

    skipToChoices(currentDialogueIndex1, dialogues1, state, dialogue1);

    // Ожидаем, что индекс не изменится и состояние не поменяется
    EXPECT_EQ(currentDialogueIndex1, 0);
    EXPECT_EQ(state, GameState::Playing);
    EXPECT_EQ(dialogue1.getString(), ""); // Поскольку вектор пуст, текст останется пустым
}

// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
