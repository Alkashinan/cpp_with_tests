
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Функции SaveProgress отвечает за провеку того, что сохранения загружаются корректно  
void saveProgress(int dialogueIndex1, bool isCharacter1Speaking) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";

   
    if (!std::filesystem::exists(saveDirectory)) {
        std::filesystem::create_directories(saveDirectory);
    }

    
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


TEST(SaveProgressTest, SavesCorrectData) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";
    
    
    if (std::filesystem::exists(saveFilePath)) {
        std::filesystem::remove(saveFilePath);
    }
    
    
    std::filesystem::create_directories(saveDirectory);

    
    int dialogueIndex = 5;
    bool isCharacter1Speaking = true;
    saveProgress(dialogueIndex, isCharacter1Speaking);

    
    ASSERT_TRUE(std::filesystem::exists(saveFilePath)) << "Error: save file does not exist.";

    
    std::ifstream saveFile(saveFilePath);
    ASSERT_TRUE(saveFile.is_open()) << "Error: Could not open save file.";

    int savedDialogueIndex;
    bool savedIsCharacter1Speaking;
    saveFile >> savedDialogueIndex;
    saveFile >> savedIsCharacter1Speaking;

    
    EXPECT_EQ(dialogueIndex, savedDialogueIndex);
    EXPECT_EQ(isCharacter1Speaking, savedIsCharacter1Speaking);

    saveFile.close();
}


TEST(LoadProgressTest, LoadsCorrectData) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";

    
    std::filesystem::create_directories(saveDirectory);

   
    std::ofstream saveFile(saveFilePath);
    ASSERT_TRUE(saveFile.is_open()) << "Error: Could not open save file for writing.";
    saveFile << 7 << "\n" << false << "\n";
    saveFile.close();

   
    int dialogueIndex = 0;
    bool isCharacter1Speaking = true;
    loadProgress(dialogueIndex, isCharacter1Speaking);

   
    EXPECT_EQ(dialogueIndex, 7);
    EXPECT_EQ(isCharacter1Speaking, false);

   
    std::filesystem::remove(saveFilePath);
}

TEST(LoadProgressTest, HandlesFileNotFoundError) {
    std::string saveFilePath = "saves/mysave.txt";

    
    if (std::filesystem::exists(saveFilePath)) {
        std::filesystem::remove(saveFilePath);
    }


    int dialogueIndex = 5;
    bool isCharacter1Speaking = true;
    loadProgress(dialogueIndex, isCharacter1Speaking);

  
    EXPECT_EQ(dialogueIndex, 5);
    EXPECT_EQ(isCharacter1Speaking, true);
}


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

    
    EXPECT_EQ(currentDialogueIndex1, 0);
    EXPECT_EQ(state, GameState::Playing);
    EXPECT_EQ(dialogue1.getString(), ""); // Поскольку вектор пуст, текст останется пустым
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
