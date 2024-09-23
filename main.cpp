#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "functions/func.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Menu Example");  

    sf::Font font;
    if (!font.loadFromFile("../assets/Arial.ttf")) {
        return -1;
    }

    sf::Text startButton, settingsButton, saveButton, quitButton;
    initButtons(startButton, settingsButton, saveButton, quitButton, font);

    sf::RectangleShape menuBox(sf::Vector2f(400, 300));
    menuBox.setFillColor(sf::Color(0, 0, 0, 150));
    menuBox.setPosition(440, 250);  

    sf::Text saveProgressButton("SAVE PROGRESS", font, 24);
    sf::Text loadProgressButton("LOAD PROGRESS", font, 24);

    saveProgressButton.setPosition(540, 300);  
    loadProgressButton.setPosition(540, 350);

    saveProgressButton.setFillColor(sf::Color::Black);
    loadProgressButton.setFillColor(sf::Color::Black);

    GameState state = GameState::Menu;

    sf::Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("../assets/night.jpg")) {
        return -1;
    }
    sf::Sprite menuBackground(menuBackgroundTexture);

    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("../assets/map2.png")) {
        return -1;
    }
    sf::Sprite gameBackground(gameBackgroundTexture);

    std::vector<std::string> dialogues1 = {
        "Zvvvv, Zvvvvv",
        "GG: What?...",
        "The alarm clock woke me up on a hot spring day",
        "GG: ~Aah, shut up~",
        "I rejected the call, thinking it was an alarm clock",
        "Zvvvv, Zvvvvv",
        "I sat up and picked up the ringing phone.",
        "GG: the headman?",
        "I swiped the green handset to the right and held the phone to my ear.",
        "GG: `Hello?..''",
        "The headman: ~Where the hell are you, today is the last day of retaking the matanalysis, or do you want to fly out of the HSE like a cork out of a bottle?!�",
        "Masha is as usual in her repertoire.",
        "Almost screams, why is she so worried about the whole group?",
        "Her voice was so high and loud that my ears curled up into a tube.",
        "GG: I'll come, I just prepared all night, I almost overslept because of it.",
        "It's good that I hardly communicate with my classmates and no one will turn me in, saying that I played Dota all night.",
        "Headman Masha: it's good that I was preparing, otherwise I'm already ashamed of our group, 8 people at the retake, this is wrong.�",
        "Her words make sense ... But I'd rather keep silent about her transfer in English",
        "GG: Come on, I'm getting dressed and going out.",
        "I started to get dressed quickly, but my stomach rumbled.",
        "GG: Damn, I need to have breakfast, although I may be late�"
    };

    sf::Text dialogue1(dialogues1[0], font, 24);
    dialogue1.setPosition(640, 660); 

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
    sf::Text creditsText("Game developed by Danya Team\nSpecial thanks to Misha for support.", font, 30);
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
