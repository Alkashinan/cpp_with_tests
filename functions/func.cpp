
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class GameState { Menu, Playing, Settings, SaveLoad, Choice, Credits };

<<<<<<< HEAD
=======

>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
struct DialogueOption {
  std::string text;
  std::vector<std::string> nextDialogues;
};

<<<<<<< HEAD
/// \brief saveProgress - функция для сохранения состояния игры
/// \param dialogueIndex1 - int, номер диалога, на котором находится игра
/// \param isCharacter1Speaking - bool, говорит ли главный герой в момент
/// сохранения?
=======

>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
void saveProgress(int dialogueIndex1, bool isCharacter1Speaking) {
  std::string saveDirectory = "saves";
  std::string saveFilePath = saveDirectory + "/mysave.txt";

<<<<<<< HEAD
  if (!std::filesystem::exists(saveDirectory)) {
    if (!std::filesystem::create_directories(saveDirectory)) {
      std::cerr << "Error: Failed to create directory " << saveDirectory
                << std::endl;
      return;
=======
  
    if (!std::filesystem::exists(saveDirectory)) {
        if (!std::filesystem::create_directories(saveDirectory)) {
            std::cerr << "Error: Failed to create directory " << saveDirectory << std::endl;
            return;
        } else {
            std::cout << "Directory " << saveDirectory << " created successfully.\n";
        }
    }

    
    if (std::filesystem::exists(saveDirectory)) {
        std::cout << "Directory exists: " << saveDirectory << std::endl;
>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
    } else {
      std::cout << "Directory " << saveDirectory << " created successfully.\n";
    }
  }

<<<<<<< HEAD
  if (std::filesystem::exists(saveDirectory)) {
    std::cout << "Directory exists: " << saveDirectory << std::endl;
  } else {
    std::cerr << "Error: Directory does not exist: " << saveDirectory
              << std::endl;
    return;
  }

  std::ofstream saveFile(saveFilePath);
  if (saveFile.is_open()) {
    saveFile << dialogueIndex1 << "\n" << isCharacter1Speaking << "\n";
    saveFile.close();
    std::cout << "Progress saved successfully to " << saveFilePath << std::endl;
  } else {
    std::cerr << "Error: Could not open save file for writing: " << saveFilePath
              << std::endl;
  }
}

/// \brief loadProgress - функция для прогружения состояния игры
/// \param dialogueIndex1 - int, номер диалога, на котором находится игра
/// \param isCharacter1Speaking - bool, говорит ли главный герой в момент
/// сохранения?
void loadProgress(int &dialogueIndex1, bool &isCharacter1Speaking) {
  std::ifstream loadFile("./saves/mysave.txt");
  if (loadFile.is_open()) {
    loadFile >> dialogueIndex1;
    loadFile >> isCharacter1Speaking;
    loadFile.close();
  }
}

/// \brief skipToChoices - функция для пропуска диалога до стадии выбора
/// \param currentDialogueIndex1 - int, номер диалога, на котором находится игра
/// в данный момент времени \param dialogues1 - bool, говорит ли главный герой в
/// момент сохранения? \param state - GameState (наш класс для хранения
/// состояния игры), state - нынешнее состояние игры \param dialogue1 -
/// sf::Text(элемент namespace sf для хранения текста), dialogue1 - выводимый на
/// экран текст
void skipToChoices(int &currentDialogueIndex1,
                   std::vector<std::string> &dialogues1, GameState &state,
                   sf::Text &dialogue1) {
  currentDialogueIndex1 = dialogues1.size() - 1;
  dialogue1.setString(dialogues1[currentDialogueIndex1]);
  sf::FloatRect textRect1 = dialogue1.getLocalBounds();
  dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f,
                      textRect1.top + textRect1.height / 2.0f);
  dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));
  state = GameState::Choice;
}

/// \brief handleMenuState - функция для отображения меню
/// \param event - мониторинг действий пользователя
/// \param state - GameState (наш класс для хранения состояния игры), state -нынешнее состояние игры 
/// \param window - окно с игрой \param  startButton -
/// текст кнопки старта \param  settingsButton - текст кнопки настроек \param
/// saveButton - текст кнопки сохранений \param  quitButton - текст кнопки выйти
void handleMenuState(const sf::Event &event, GameState &state,
                     sf::RenderWindow &window, sf::Text &startButton,
                     sf::Text &settingsButton, sf::Text &saveButton,
                     sf::Text &quitButton) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      state = GameState::Playing;
    } else if (settingsButton.getGlobalBounds().contains(mousePos.x,
                                                         mousePos.y)) {
      state = GameState::Settings;
    } else if (saveButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      state = GameState::SaveLoad;
    } else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      window.close();
    }
  }
}

/// \brief handlePlayingState - функция для отображения игры
/// \param event - мониторинг действий пользователя
/// \param state - GameState (наш класс для хранения состояния игры), state -нынешнее состояние игры 
/// \param currentDialogueIndex1 - номер диалога на котором игра находится в данный момент
/// \param dialogues1 - вектор из строк, список всех реплик в игре
/// \param dialogue1 - текущий текст на экране
/// \param isCharacter1Speaking - bool, говорит ли сейчас персонаж?
void handlePlayingState(const sf::Event &event, GameState &state,
                        int &currentDialogueIndex1,
                        std::vector<std::string> &dialogues1,
                        sf::Text &dialogue1, bool &isCharacter1Speaking) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape) {
      state = GameState::Menu;
    } else if (event.key.code == sf::Keyboard::LControl ||
               event.key.code == sf::Keyboard::RControl) {
      skipToChoices(currentDialogueIndex1, dialogues1, state, dialogue1);
    }
  } else if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
    if (isCharacter1Speaking) {
      currentDialogueIndex1++;
      if (currentDialogueIndex1 < dialogues1.size()) {
        dialogue1.setString(dialogues1[currentDialogueIndex1]);
        sf::FloatRect textRect1 = dialogue1.getLocalBounds();
        dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f,
                            textRect1.top + textRect1.height / 2.0f);
        dialogue1.setPosition(sf::Vector2f(
            1280 / 2.0f, 660));

        if (currentDialogueIndex1 == dialogues1.size() - 1) {
          state = GameState::Choice;
=======
   
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
    std::ifstream loadFile( "./saves/mysave.txt" ); // 
    if ( loadFile.is_open() ) {
        loadFile >> dialogueIndex1; 
        loadFile >> isCharacter1Speaking; 
        loadFile.close(); 
    }
}

void skipToChoices(int& currentDialogueIndex1, std::vector<std::string>& dialogues1, GameState& state, sf::Text& dialogue1) {
    currentDialogueIndex1 = dialogues1.size() - 1;
    dialogue1.setString(dialogues1[currentDialogueIndex1]);
    sf::FloatRect textRect1 = dialogue1.getLocalBounds();
    dialogue1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
    dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));  
    state = GameState::Choice;
}


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
>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
        }
      }
    }
    isCharacter1Speaking = !isCharacter1Speaking;
  }
}

<<<<<<< HEAD
/// \brief handleSettingsState - функция для отображения настроек
/// \param event - мониторинг действий пользователя
/// \param state - GameState (наш класс для хранения состояния игры), state -нынешнее состояние игры 
/// \param window - текущее окно
/// \param music - музыка
/// \param volumeSlider - полоска изменения громкости
/// \param brightnessSlider - полоска изменения яркости
/// \param volumeKnob - слайдер изменения громкости
/// \param volumeKnob - слайдер изменения яркости
/// \param gameBackground - фон
void handleSettingsState(const sf::Event &event, GameState &state,
                         sf::RenderWindow &window, sf::Music &music,
                         sf::RectangleShape &volumeSlider,
                         sf::RectangleShape &brightnessSlider,
                         sf::RectangleShape &volumeKnob,
                         sf::RectangleShape &brightnessKnob,
                         sf::Sprite &gameBackground) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (volumeSlider.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      float volume = (mousePos.x - volumeSlider.getPosition().x) / 2.0f;
      volume = std::max(0.0f, std::min(100.0f, volume));
      music.setVolume(volume);
      volumeKnob.setPosition(volumeSlider.getPosition().x + volume * 2,
                             volumeKnob.getPosition().y);
    } else if (brightnessSlider.getGlobalBounds().contains(mousePos.x,
                                                           mousePos.y)) {
      float brightness = (mousePos.x - brightnessSlider.getPosition().x);
      brightness = std::max(0.0f, std::min(200.0f, brightness));
      brightnessKnob.setPosition(brightnessSlider.getPosition().x + brightness,
                                 brightnessKnob.getPosition().y);
=======

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
                dialogue1.setPosition(sf::Vector2f(1280 / 2.0f, 660));  
>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6

      sf::Color color = gameBackground.getColor();
      color.r = color.g = color.b = 255 * (brightness / 200.0f);
      gameBackground.setColor(color);
    }
  } else if (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) {
    state = GameState::Menu;
  }
}

<<<<<<< HEAD
/// \brief handleChoiceState - функция для отображения выбора
/// \param event - мониторинг действий пользователя
/// \param state - GameState (наш класс для хранения состояния игры), state -нынешнее состояние игры 
/// \param window - текущее окно
/// \param choice1 - текст первого выбора
/// \param choice2 - текст второго выбора
/// \param dialogues1 - вектор строк всех диалогов
/// \param choices - выбор
/// \param currentDialogueIndex1 - номер текущего диалога
/// \param dialogue1 - текст на эране текущего диалога
/// \param isCharacter1Speaking - bool, говорит ли сейчас персонаж?
void handleChoiceState(const sf::Event &event, GameState &state,
                       sf::RenderWindow &window, sf::Text &choice1,
                       sf::Text &choice2, std::vector<std::string> &dialogues1,
                       std::vector<DialogueOption> &choices,
                       int &currentDialogueIndex1, sf::Text &dialogue1,
                       bool &isCharacter1Speaking) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
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
=======

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
>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
    }
  }
}

<<<<<<< HEAD
/// \brief handleSaveLoadState - функция для отображения меню сохранений
/// \param event - мониторинг действий пользователя
/// \param state - GameState (наш класс для хранения состояния игры), state -нынешнее состояние игры 
/// \param window - текущее окно
/// \param saveProgressButton - текст кнопки сохраниться
/// \param loadProgressButton - текст кнопки загрузить прогресс
/// \param currentDialogueIndex1 - номер текущего диалога
/// \param isCharacter1Speaking - bool, говорит ли сейчас персонаж?
/// \param dialogues1 - вектор строк всех диалогов
/// \param dialogue1 - текст на эране текущего диалога
void handleSaveLoadState(const sf::Event &event, GameState &state,
                         sf::RenderWindow &window, sf::Text &saveProgressButton,
                         sf::Text &loadProgressButton,
                         int &currentDialogueIndex1, bool &isCharacter1Speaking,
                         std::vector<std::string> &dialogues1,
                         sf::Text &dialogue1) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (saveProgressButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      saveProgress(currentDialogueIndex1, isCharacter1Speaking);
    } else if (loadProgressButton.getGlobalBounds().contains(mousePos.x,
                                                             mousePos.y)) {
      loadProgress(currentDialogueIndex1, isCharacter1Speaking);
      dialogue1.setString(dialogues1[currentDialogueIndex1]);
      state = GameState::Playing;
=======

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
>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
    }
  } else if (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) {
    state = GameState::Menu;
  }
}

<<<<<<< HEAD
void drawMenuState(sf::RenderWindow &window, sf::Sprite &menuBackground,
                   sf::RectangleShape &menuBox, sf::Text &startButton,
                   sf::Text &settingsButton, sf::Text &saveButton,
                   sf::Text &quitButton) {
  window.draw(menuBackground);
  window.draw(menuBox);
  window.draw(startButton);
  window.draw(settingsButton);
  window.draw(saveButton);
  window.draw(quitButton);
}

void drawPlayingState(sf::RenderWindow &window, sf::Sprite &gameBackground,
                      sf::RectangleShape &dialogueBox, sf::Text &dialogue1) {
  window.draw(gameBackground);
  window.draw(dialogueBox);
  window.draw(dialogue1);
}

void drawSettingsState(sf::RenderWindow &window, sf::Sprite &gameBackground,
                       sf::RectangleShape &dialogueBox,
                       sf::RectangleShape &volumeSlider,
                       sf::RectangleShape &volumeKnob,
                       sf::RectangleShape &brightnessSlider,
                       sf::RectangleShape &brightnessKnob) {
  window.draw(gameBackground);
  window.draw(dialogueBox);
  window.draw(volumeSlider);
  window.draw(volumeKnob);
  window.draw(brightnessSlider);
  window.draw(brightnessKnob);
}

void drawSaveLoadState(sf::RenderWindow &window, sf::Sprite &gameBackground,
                       sf::RectangleShape &dialogueBox,
                       sf::Text &saveProgressButton,
                       sf::Text &loadProgressButton) {
  window.draw(gameBackground);
  window.draw(dialogueBox);
  window.draw(saveProgressButton);
  window.draw(loadProgressButton);
}

void drawChoiceState(sf::RenderWindow &window, sf::Sprite &gameBackground,
                     sf::RectangleShape &choiceBox, sf::Text &choice1,
                     sf::Text &choice2) {
  window.draw(gameBackground);
  window.draw(choiceBox);
  window.draw(choice1);
  window.draw(choice2);
}

void initButtons(sf::Text &startButton, sf::Text &settingsButton,
                 sf::Text &saveButton, sf::Text &quitButton, sf::Font &font) {
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

  startButton.setPosition(
      540, 300); // Adjusted positions for screen resolution 1280x720
  settingsButton.setPosition(540, 350);
  saveButton.setPosition(540, 400);
  quitButton.setPosition(540, 450);
}

void initSlider(sf::RectangleShape &slider, sf::Vector2f size, sf::Color color,
                sf::Vector2f position) {
  slider.setSize(size);
  slider.setFillColor(color);
  slider.setPosition(position);
}

void initChoiceBox(sf::RectangleShape &choiceBox) {
  choiceBox.setSize(sf::Vector2f(400, 150));
  choiceBox.setFillColor(sf::Color(0, 0, 0, 150));
  choiceBox.setPosition(440, 275); // Adjusted for screen resolution 1280x720
}

void playMusic(sf::Music &music) {
  if (!music.openFromFile("../assets/01.Hollywood.mp3")) {
    return;
  }
  music.setLoop(true);
  music.play();
}

void handleCreditsState(const sf::Event &event, GameState &state) {
  if (event.type == sf::Event::KeyPressed &&
      event.key.code == sf::Keyboard::Escape) {
    state = GameState::Menu;
  }
}

void drawCreditsState(sf::RenderWindow &window, sf::Text &creditsText) {
  window.clear(sf::Color::Black);
  window.draw(creditsText);
}
=======

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


void drawMenuState(sf::RenderWindow& window, sf::Sprite& menuBackground, sf::RectangleShape& menuBox, sf::Text& startButton, sf::Text& settingsButton, sf::Text& saveButton, sf::Text& quitButton) {
    window.draw(menuBackground);
    window.draw(menuBox);
    window.draw(startButton);
    window.draw(settingsButton);
    window.draw(saveButton);
    window.draw(quitButton);
}


void drawPlayingState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::Text& dialogue1) {
    window.draw(gameBackground);
    window.draw(dialogueBox);
    window.draw(dialogue1);
}


void drawSettingsState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::RectangleShape& volumeSlider, sf::RectangleShape& volumeKnob, sf::RectangleShape& brightnessSlider, sf::RectangleShape& brightnessKnob) {
    window.draw(gameBackground);
    window.draw(dialogueBox);
    window.draw(volumeSlider);
    window.draw(volumeKnob);
    window.draw(brightnessSlider);
    window.draw(brightnessKnob);
}


void drawSaveLoadState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& dialogueBox, sf::Text& saveProgressButton, sf::Text& loadProgressButton) {
    window.draw(gameBackground);
    window.draw(dialogueBox);
    window.draw(saveProgressButton);
    window.draw(loadProgressButton);
}


void drawChoiceState(sf::RenderWindow& window, sf::Sprite& gameBackground, sf::RectangleShape& choiceBox, sf::Text& choice1, sf::Text& choice2) {
    window.draw(gameBackground);
    window.draw(choiceBox);
    window.draw(choice1);
    window.draw(choice2);
}


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

    startButton.setPosition(540, 300);    
    settingsButton.setPosition(540, 350);
    saveButton.setPosition(540, 400);
    quitButton.setPosition(540, 450);
}


void initSlider(sf::RectangleShape& slider, sf::Vector2f size, sf::Color color, sf::Vector2f position) {
    slider.setSize(size);
    slider.setFillColor(color);
    slider.setPosition(position);
}


void initChoiceBox(sf::RectangleShape& choiceBox) {
    choiceBox.setSize(sf::Vector2f(400, 150));
    choiceBox.setFillColor(sf::Color(0, 0, 0, 150));
    choiceBox.setPosition(440, 300);  
}


void playMusic(sf::Music& music) {
    if (!music.openFromFile("../assets/01.Hollywood.mp3")) {
        return;
    }
    music.setLoop(true);
    music.play();
}


void handleCreditsState(const sf::Event& event, GameState& state) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = GameState::Menu;
    }
}


void drawCreditsState(sf::RenderWindow& window, sf::Text& creditsText) {
    window.clear(sf::Color::Black);
    window.draw(creditsText);
}

>>>>>>> 5515ae12d6d6f33a76d20d2a40bda14437236fe6
