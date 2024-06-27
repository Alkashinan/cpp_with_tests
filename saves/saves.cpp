#include <fstream>
#include <filesystem>

// ������� ���������� ���������
void saveProgress( int dialogueIndex1, bool isCharacter1Speaking ) {
    // std::filesystem::create_directory(
    //     "saves" ); // ������� ���������� ��� ����������
    std::ofstream saveFile( "mysave.txt" ); // ��������� ���� ��� ������
    if ( saveFile.is_open() ) {
        saveFile << dialogueIndex1 << "\n" << isCharacter1Speaking << "\n";
        saveFile.close(); // ��������� ����
    }
}

// ������� �������� ���������
void loadProgress( int& dialogueIndex1, bool& isCharacter1Speaking ) {
    std::ifstream loadFile( "mysave.txt" ); // ��������� ���� ��� ������
    if ( loadFile.is_open() ) { // ���� ���� ������
        loadFile >> dialogueIndex1; // ������ ������ �������� �������
        loadFile >> isCharacter1Speaking; // ������ ���� ���������� ���������
        loadFile.close(); // ��������� ����
    }
}