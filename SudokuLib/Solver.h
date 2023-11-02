/**
 * @file Solver.h
 * @author yaxuan
 * @author nam nguyen
 *
 * Class that holds the solutions
 */

#ifndef TARTARUS_SUDOKULIB_SOLVER_H
#define TARTARUS_SUDOKULIB_SOLVER_H

#include<string>
#include<vector>

/**
* Class that holds the solutions
*/
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

    /**
     * Get the column of the first top left board square
     * @return int mCol
     */
    int GetCol() { return mCol; }
    /**
    * Get the row of the first top left board square
    * @return int mRow
    */
    int GetRow() { return mRow; }
    /**
     * Gets the solution vector value at the given positions
     * @param opos index of vector of vector
     * @param ipos index of inner vector
     * @return in value at solution[opos][ipos]
     */
    int GetVectorValue(int opos, int ipos) { return mSolution.at(opos).at(ipos); }
    /**
     * Clears our solution vector
     */
    void Clear() { mSolution.clear();}
};

#endif //TARTARUS_SUDOKULIB_SOLVER_H
