#include <iostream>
#include <list>
#include <vector>

#include "C:/new_danya_cpp/saves/saves.h"

#include <gtest/gtest.h>

TEST(SavingTests, Testsaved)
{
    int dialogueIndex_in = 2;
    bool isCharacter1Speaking_in = 0;
    int dialogueIndex_out = 0;
    bool isCharacter1Speaking_out = 1;
    saveProgress(dialogueIndex_in, isCharacter1Speaking_in);
    loadProgress(dialogueIndex_out, isCharacter1Speaking_out);
    
    
    ASSERT_EQ(dialogueIndex_in, dialogueIndex_out);
    
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
