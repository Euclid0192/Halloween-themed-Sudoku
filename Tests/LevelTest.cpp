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

#include "Game.h"
#include "Level.h"

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
        ASSERT_TRUE(regex_search(xml, wregex(L"<level.*<declarations.*<game.*<items.*</level>")));
     }
};

TEST_F(LevelTest, Construct){
    Level leve;
}

TEST_F(LevelTest, Save){
    auto path = TempPath();

    //create the level class
    Game game;
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
    Game game;
    Game game2;
    Level level;

    level.SetGame(&game);
    level.Load(L"../levels/level1.xml");

    auto file1 = path + L"/test.xml";
    //save the level

    level.Save(file1);

    level.SetGame(&game2);
    level.Load(file1);
    level.Save(file1);
    TestLevel(file1);
}