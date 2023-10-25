/**
 * @file LevelTest.cpp
 * @author Lewi Anamo
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

#include <SudokuGame.h>
#include <Level.h>

using namespace std;

class LevelTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files0
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/actionSudoku";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
   * Read a file into a wstring and return it.
   * @param filename Name of the file to read
   * @return File contents
   */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to see the a level was loaded properly
     */
     void TestLevel(wxString filename){
         cout << "Temp file: " << filename << endl;

         auto xml = ReadFile(filename);
         cout << xml << endl;

         //Ensure declarations, game and items are there
//        ASSERT_TRUE(regex_search(xml, wregex(L"<level.*<declarations.*<game.*<items.*</level>")));

//        ASSERT_TRUE(regex_search(xml, wregex(L"<game col=\"4\" row=\"3\">7 3 1 4 6 5 8 0 2 2 6 5 0 7 8 1 3 4 8 4 0 3 2 1 7 5 6 3 0 2 1 4 7 5 6 8 4 1 8 6 5 3 0 2 7 5 7 6 8 0 2 3 4 1 1 5 7 2 3 4 6 8 0 0 8 4 5 1 6 2 7 3 6 2 3 7 8 0 4 1 5</game>")));

    }
};

TEST_F(LevelTest, Construct){
    Level level;
}

TEST_F(LevelTest, Save){
    auto path = TempPath();

    //create the level class
    SudokuGame game;
    Level level;

    level.SetGame(&game);
    level.Load(L"../levels/level1.xml");

    auto file1 = path + L"/test.xml";
    //save the level

    level.Save(file1);

    TestLevel(file1);
}

TEST_F(LevelTest, Load){
    // Create a path to temporary files
    auto path = TempPath();

    //create the level class
    SudokuGame game;
    SudokuGame game2;
    Level level;

    level.SetGame(&game);
    level.Load(L"../levels/level1.xml");

    auto file1 = path + L"/test.xml";
    //save the level

    level.Save(file1);

    //Change the game a different one
    level.SetGame(&game2);

    // Load and save into file1
    level.Load(file1);
    level.Save(file1);


    TestLevel(file1);
}

