/**
 * @file Solver.h
 * @author yaxuan
 * @author nam nguyen
 *
 */

#ifndef TARTARUS_SUDOKULIB_SOLVER_H
#define TARTARUS_SUDOKULIB_SOLVER_H

#include<string>
#include<vector>

class Solver
{
private:
    /// Vector that holds the solution
    //std::vector<std::vector<std::wstring>> mSolution;
    std::vector<std::vector<int>> mSolution;
    /// Holds the col in tiles
    int mCol;
    /// Holds the row in tiles
    int mRow;
public:
    void XmlLoad(wxXmlNode *node);
    void XmlSave(wxXmlNode *node);
};

#endif //TARTARUS_SUDOKULIB_SOLVER_H
