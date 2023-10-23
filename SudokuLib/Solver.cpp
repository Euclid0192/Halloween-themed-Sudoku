/**
 * @file Solver.cpp
 * @author Lewi Anamo
 */

#include "pch.h"
#include "Solver.h"
#include <sstream>

/**
 * Load the game tag from the XML file
 * @param node of the game tag
 */
void Solver::XmlLoad(wxXmlNode *node) {

    node->GetAttribute(L"col").ToInt(&mCol);
    node->GetAttribute(L"row").ToInt(&mRow);

    auto content = node->GetNodeContent().ToStdString();

    std::istringstream iss(content);
    int number;
    std::vector<int> tempRow;
    int ipos = 0;
    while (iss >> number) {
        tempRow.push_back(number);
        ipos++;

        if(ipos == 9)
        {
            ipos = 0;
            mSolution.push_back(tempRow);

            tempRow.clear();
        }
    }
}

/**
 * Save the content of the Solver class into the XML file
 * @param node of the game tag
 */
void Solver::XmlSave(wxXmlNode *node){
    node->AddAttribute(L"col", wxString::FromDouble(mCol));
    node->AddAttribute(L"row", wxString::FromDouble(mRow));

    std::ostringstream out;
    /// Loop through the vector that holds the solutions and add it to a ostringstream
    for (auto i = mSolution.begin(); i != mSolution.end(); i++)
    {
        for (int j = 0; j < 9; j++){
                out << i->at(j) << " ";
        }
    }

    const auto str = out.str();
    ///Cut the space at the end off
    auto str1 = str.substr(0, str.size() - 1);

    new wxXmlNode(node, wxXML_TEXT_NODE, wxT("game"), str1);
}
