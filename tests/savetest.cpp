
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../functions/func.h"

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


// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
