#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "saves/saves.h"

// Define different states of the game
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
    std::ofstream saveFile("saves/mysave.txt");
    if (saveFile.is_open()) {
        saveFile << dialogueIndex1 << "\n" << isCharacter1Speaking << "\n";
        saveFile.close();
    }
}

// Load the game progress from a file
void loadProgress(int& dialogueIndex1, bool& isCharacter1Speaking) {
    std::ifstream loadFile("saves/mysave.txt");
    if (loadFile.is_open()) {
        loadFile >> dialogueIndex1;
        loadFile >> isCharacter1Speaking;
        loadFile.close();
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
    if (!music.openFromFile("assets/01.Hollywood.mp3")) {
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

// Main function to run the game
int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Menu Example");  // Adjusted screen resolution to 1280x720

    sf::Font font;
    if (!font.loadFromFile("assets/Arial.ttf")) {
        return -1;
    }

    sf::Text startButton, settingsButton, saveButton, quitButton;
    initButtons(startButton, settingsButton, saveButton, quitButton, font);

    sf::RectangleShape menuBox(sf::Vector2f(400, 300));
    menuBox.setFillColor(sf::Color(0, 0, 0, 150));
    menuBox.setPosition(440, 250);  // Adjusted for screen resolution 1280x720

    sf::Text saveProgressButton("SAVE PROGRESS", font, 24);
    sf::Text loadProgressButton("LOAD PROGRESS", font, 24);

    saveProgressButton.setPosition(540, 300);  // Adjusted for screen resolution 1280x720
    loadProgressButton.setPosition(540, 350);

    // Change font color to black in the Save/Load state
    saveProgressButton.setFillColor(sf::Color::Black);
    loadProgressButton.setFillColor(sf::Color::Black);

    GameState state = GameState::Menu;

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("assets/night.jpg")) {
        return -1;
    }
    sf::Sprite menuBackground(menuBackgroundTexture);

    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("assets/map2.png")) {
        return -1;
    }
    sf::Sprite gameBackground(gameBackgroundTexture);

    std::vector<std::string> dialogues1 = {
        "Zvvvv, Zvvvvv",
        "GG: �What?...�",
        "The alarm clock woke me up on a hot spring day",
        "GG: �Aah, shut up�",
        "I rejected the call, thinking it was an alarm clock",
        "Zvvvv, Zvvvvv",
        "I sat up and picked up the ringing phone.",
        "GG: the headman?",
        "I swiped the green handset to the right and held the phone to my ear.",
        "GG: `Hello?..''",
        "The headman: �where the hell are you, today is the last day of retaking the matanalysis, or do you want to fly out of the HSE like a cork out of a bottle?!�",
        "Masha is as usual in her repertoire.",
        "Almost screams, why is she so worried about the whole group?",
        "Her voice was so high and loud that my ears curled up into a tube.",
        "GG: �I'll come, I just prepared all night, I almost overslept because of it.�",
        "It's good that I hardly communicate with my classmates and no one will turn me in, saying that I played Dota all night.",
        "Headman Masha: �it's good that I was preparing, otherwise I'm already ashamed of our group, 8 people at the retake, this is wrong.�",
        "Her words make sense ... But I'd rather keep silent about her transfer in English",
        "GG: �Come on, I'm getting dressed and going out.",
        "I started to get dressed quickly, but my stomach rumbled.",
        "GG: �Damn, I need to have breakfast, although I may be late�"
    };

    sf::Text dialogue1(dialogues1[0], font, 24);
    dialogue1.setPosition(640, 660);  // Adjusted for screen resolution 1280x720

    sf::FloatRect textRect1 = dialogue1.getLocalBounds();
    dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));  // Adjusted for screen resolution 1280x720

    int currentDialogueIndex1 = 0;
    bool isCharacter1Speaking = true;

    sf::RectangleShape dialogueBox(sf::Vector2f(1280, 100));  // Adjusted for screen resolution 1280x720
    dialogueBox.setFillColor(sf::Color(0, 0, 0, 150));
    dialogueBox.setPosition(0, 620);  // Adjusted for screen resolution 1280x720

    sf::Music music;
    playMusic(music);

    sf::RectangleShape volumeSlider, brightnessSlider, volumeKnob, brightnessKnob;
    initSlider(volumeSlider, sf::Vector2f(200, 10), sf::Color::White, sf::Vector2f(540, 400));  // Adjusted for screen resolution 1280x720
    initSlider(brightnessSlider, sf::Vector2f(200, 10), sf::Color::White, sf::Vector2f(540, 450));
    initSlider(volumeKnob, sf::Vector2f(10, 30), sf::Color::Red, sf::Vector2f(540 + music.getVolume() * 2, 385));  // Adjusted for screen resolution 1280x720
    initSlider(brightnessKnob, sf::Vector2f(10, 30), sf::Color::Red, sf::Vector2f(540 + 100, 435));

    sf::Text choice1("Take a Breakfast?", font, 24);
    sf::Text choice2("Don't breakfast.", font, 24);
    choice1.setPosition(540, 300);  // Adjusted for screen resolution 1280x720
    choice2.setPosition(540, 350);

    sf::RectangleShape choiceBox;
    initChoiceBox(choiceBox);

    std::vector<DialogueOption> choices = {
        {"Take a Breakfast?", {"I made myself 2 sandwiches with sausage and cheese, quickly made them and washed them down with water.", "I got dressed quickly and ran to the streets.", "Opening the entrance door, the sun began to shine in my eyes.", "It is so bright that I would gladly go to the beach right now.", "I open my phone to look at the bus and commuter train schedules"}},
        {"Don't breakfast.", {"GG: �no, I won't eat, otherwise I'll be late�", "I got dressed quickly and ran to the streets.", "I opened the entrance door", "The sun is shining brightly in my eyes.", "It's so bright that I would love to go to the beach right now.", "I open my phone to look at the bus and commuter train schedules"}}
    };

    // Credits text initialization
    sf::Text creditsText("Game developed by XYZ Team\nSpecial thanks to the OpenAI community for support.", font, 30);
    creditsText.setPosition(400, 350);  // Adjusted for screen resolution 1280x720

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (state == GameState::Menu) {
                handleMenuState(event, state, window, startButton, settingsButton, saveButton, quitButton);
            } else if (state == GameState::Playing) {
                handlePlayingState(event, state, currentDialogueIndex1, dialogues1, dialogue1, isCharacter1Speaking);
            } else if (state == GameState::Settings) {
                handleSettingsState(event, state, window, music, volumeSlider, brightnessSlider, volumeKnob, brightnessKnob, gameBackground);
            } else if (state == GameState::Choice) {
                handleChoiceState(event, state, window, choice1, choice2, dialogues1, choices, currentDialogueIndex1, dialogue1, isCharacter1Speaking);
            } else if (state == GameState::SaveLoad) {
                handleSaveLoadState(event, state, window, saveProgressButton, loadProgressButton, currentDialogueIndex1, isCharacter1Speaking, dialogues1, dialogue1);
            } else if (state == GameState::Credits) {
                handleCreditsState(event, state);
            }
        }

        window.clear();

        if (state == GameState::Menu) {
            drawMenuState(window, menuBackground, menuBox, startButton, settingsButton, saveButton, quitButton);
        } else if (state == GameState::Playing) {
            drawPlayingState(window, gameBackground, dialogueBox, dialogue1);
        } else if (state == GameState::Settings) {
            drawSettingsState(window, gameBackground, dialogueBox, volumeSlider, volumeKnob, brightnessSlider, brightnessKnob);
        } else if (state == GameState::SaveLoad) {
            drawSaveLoadState(window, gameBackground, dialogueBox, saveProgressButton, loadProgressButton);
        } else if (state == GameState::Choice) {
            drawChoiceState(window, gameBackground, choiceBox, choice1, choice2);
        } else if (state == GameState::Credits) {
            drawCreditsState(window, creditsText);
        }

        window.display();
    }

    return 0;
}
