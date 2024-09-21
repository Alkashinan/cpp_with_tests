
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

enum class GameState {
    Menu,
    Playing,
    Settings,
    SaveLoad,
    Choice,
    Credits
};

// Structure to handle dialogue options and transitions
struct DialogueOption {
    std::string text;
    std::vector<std::string> nextDialogues;
};

// Save the current game progress to a file

void saveProgress(int dialogueIndex1, bool isCharacter1Speaking) {
    std::string saveDirectory = "saves";
    std::string saveFilePath = saveDirectory + "/mysave.txt";

    // Создаем директорию, если она не существует
    if (!std::filesystem::exists(saveDirectory)) {
        if (!std::filesystem::create_directories(saveDirectory)) {
            std::cerr << "Error: Failed to create directory " << saveDirectory << std::endl;
            return;
        } else {
            std::cout << "Directory " << saveDirectory << " created successfully.\n";
        }
    }

    // Проверяем, существует ли директория
    if (std::filesystem::exists(saveDirectory)) {
        std::cout << "Directory exists: " << saveDirectory << std::endl;
    } else {
        std::cerr << "Error: Directory does not exist: " << saveDirectory << std::endl;
        return;
    }

    // Открываем файл для записи
    std::ofstream saveFile(saveFilePath);
    if (saveFile.is_open()) {
        saveFile << dialogueIndex1 << "\n" << isCharacter1Speaking << "\n";
        saveFile.close();
        std::cout << "Progress saved successfully to " << saveFilePath << std::endl;
    } else {
        std::cerr << "Error: Could not open save file for writing: " << saveFilePath << std::endl;
    }
}

void loadProgress( int& dialogueIndex1, bool& isCharacter1Speaking ) {
    std::ifstream loadFile( "./saves/mysave.txt" ); // ��������� ���� ��� ������
    if ( loadFile.is_open() ) { // ���� ���� ������
        loadFile >> dialogueIndex1; // ������ ������ �������� �������
        loadFile >> isCharacter1Speaking; // ������ ���� ���������� ���������
        loadFile.close(); // ��������� ����
    }
}
// Skip to the choice section in the dialogues
void skipToChoices(int& currentDialogueIndex1, std::vector<std::string>& dialogues1, GameState& state, sf::Text& dialogue1) {
    currentDialogueIndex1 = dialogues1.size() - 1;
    dialogue1.setString(dialogues1[currentDialogueIndex1]);
    sf::FloatRect textRect1 = dialogue1.getLocalBounds();
    dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));  // Adjusted for screen resolution 1280x720
    state = GameState::Choice;
}

// Handle user input when in the Menu state
void handleMenuState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            state = GameState::Playing;
        } else if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            state = GameState::Settings;
        } else if (saveButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            state = GameState::SaveLoad;
        } else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            window.close();
        }
    }
}

// Handle user input when in the Playing state
void handlePlayingState(const sf::Event& event, GameState& state, int& currentDialogueIndex1, std::vector<std::string>& dialogues1, sf::Text& dialogue1, bool& isCharacter1Speaking) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            state = GameState::Menu;
        } else if (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl) {
            skipToChoices(currentDialogueIndex1, dialogues1, state, dialogue1);
        }
    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isCharacter1Speaking) {
            currentDialogueIndex1++;
            if (currentDialogueIndex1 < dialogues1.size()) {
                dialogue1.setString(dialogues1[currentDialogueIndex1]);
                sf::FloatRect textRect1 = dialogue1.getLocalBounds();
                dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
                dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));  // Adjusted for screen resolution 1280x720

                if (currentDialogueIndex1 == dialogues1.size() - 1) {
                    state = GameState::Choice;
                }
            }
        }
        isCharacter1Speaking = !isCharacter1Speaking;
    }
}

// Handle user input when in the Settings state
void handleSettingsState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Music& music, sf::RectangleShape& volumeSlider, sf::RectangleShape& brightnessSlider, sf::RectangleShape& volumeKnob, sf::RectangleShape& brightnessKnob, sf::Sprite& gameBackground) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (volumeSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            float volume = (mousePos.x - volumeSlider.getPosition().x) / 2.0f;
            volume = std::max(0.0f, std::min(100.0f, volume));
            music.setVolume(volume);
            volumeKnob.setPosition(volumeSlider.getPosition().x + volume * 2, volumeKnob.getPosition().y);
        } else if (brightnessSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            float brightness = (mousePos.x - brightnessSlider.getPosition().x);
            brightness = std::max(0.0f, std::min(200.0f, brightness));
            brightnessKnob.setPosition(brightnessSlider.getPosition().x + brightness, brightnessKnob.getPosition().y);

            sf::Color color = gameBackground.getColor();
            color.r = color.g = color.b = 255 * (brightness / 200.0f);
            gameBackground.setColor(color);
        }
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = GameState::Menu;
    }
}

// Handle user input when in the Choice state
void handleChoiceState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Text& choice1, sf::Text& choice2, std::vector<std::string>& dialogues1, std::vector<DialogueOption>& choices, int& currentDialogueIndex1, sf::Text& dialogue1, bool& isCharacter1Speaking) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (choice1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            dialogues1 = choices[0].nextDialogues;
            currentDialogueIndex1 = 0;
            dialogue1.setString(dialogues1[currentDialogueIndex1]);
            isCharacter1Speaking = true;
            state = GameState::Playing;
        } else if (choice2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            dialogues1 = choices[1].nextDialogues;
            currentDialogueIndex1 = 0;
            dialogue1.setString(dialogues1[currentDialogueIndex1]);
            isCharacter1Speaking = true;
            state = GameState::Playing;
        }
    }
}

// Handle user input when in the Save/Load state
void handleSaveLoadState(const sf::Event& event, GameState& state, sf::RenderWindow& window, sf::Text& saveProgressButton, sf::Text& loadProgressButton, int& currentDialogueIndex1, bool& isCharacter1Speaking, std::vector<std::string>& dialogues1, sf::Text& dialogue1) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (saveProgressButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            saveProgress(currentDialogueIndex1, isCharacter1Speaking);
        } else if (loadProgressButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            loadProgress(currentDialogueIndex1, isCharacter1Speaking);
            dialogue1.setString(dialogues1[currentDialogueIndex1]);
            state = GameState::Playing;
        }
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = GameState::Menu;
    }
}

// Draw elements for the Menu state
void drawMenuState(sf::RenderWindow& window, sf::Sprite& menuBackground, sf::RectangleShape& menuBox, sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton) {
    window.draw(menuBackground);
    window.draw(menuBox);
    window.draw(startButton);
    window.draw(settingsButton);
    window.draw(saveButton);
    window.draw(quitButton);
}

// Draw elements for the Playing state
void drawPlayingState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::Text& dialogue1) {
    window.draw(gameBackground);
    window.draw(dialogueBox);
    window.draw(dialogue1);
}

// Draw elements for the Settings state
void drawSettingsState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::RectangleShape& volumeSlider, sf::RectangleShape& volumeKnob, sf::RectangleShape& brightnessSlider, sf::RectangleShape& brightnessKnob) {
    window.draw(gameBackground);
    window.draw(dialogueBox);
    window.draw(volumeSlider);
    window.draw(volumeKnob);
    window.draw(brightnessSlider);
    window.draw(brightnessKnob);
}

// Draw elements for the Save/Load state
void drawSaveLoadState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::Text& saveProgressButton, sf::Text& loadProgressButton) {
    window.draw(gameBackground);
    window.draw(dialogueBox);
    window.draw(saveProgressButton);
    window.draw(loadProgressButton);
}

// Draw elements for the Choice state
void drawChoiceState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& choiceBox, sf::Text& choice1, sf::Text& choice2) {
    window.draw(gameBackground);
    window.draw(choiceBox);
    window.draw(choice1);
    window.draw(choice2);
}

// Initialize buttons with font, position, and text
void initButtons(sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton, sf::Font& font) {
    startButton.setFont(font);
    settingsButton.setFont(font);
    saveButton.setFont(font);
    quitButton.setFont(font);

    startButton.setString("START");
    settingsButton.setString("SETTINGS");
    saveButton.setString("SAVES");
    quitButton.setString("QUIT");

    startButton.setCharacterSize(24);
    settingsButton.setCharacterSize(24);
    saveButton.setCharacterSize(24);
    quitButton.setCharacterSize(24);

    startButton.setPosition(540, 300);     // Adjusted positions for screen resolution 1280x720
    settingsButton.setPosition(540, 350);
    saveButton.setPosition(540, 400);
    quitButton.setPosition(540, 450);
}

// Initialize sliders for settings like volume and brightness
void initSlider(sf::RectangleShape& slider, sf::Vector2f size, sf::Color color, sf::Vector2f position) {
    slider.setSize(size);
    slider.setFillColor(color);
    slider.setPosition(position);
}

// Initialize the choice box used in dialogues
void initChoiceBox(sf::RectangleShape& choiceBox) {
    choiceBox.setSize(sf::Vector2f(400, 150));
    choiceBox.setFillColor(sf::Color(0, 0, 0, 150));
    choiceBox.setPosition(440, 300);  // Adjusted for screen resolution 1280x720
}

// Play background music in the game
void playMusic(sf::Music& music) {
    if (!music.openFromFile("../assets/01.Hollywood.mp3")) {
        return;
    }
    music.setLoop(true);
    music.play();
}

// Function to handle credits state
void handleCreditsState(const sf::Event& event, GameState& state) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = GameState::Menu;
    }
}

// Function to draw credits screen
void drawCreditsState(sf::RenderWindow& window, sf::Text& creditsText) {
    window.clear(sf::Color::Black);
    window.draw(creditsText);
}

