/**
 * @file Container.h
 * @author yaxuan
 *
 * The class for containers
 */

#ifndef TARTARUS_SUDOKULIB_CONTAINER_H
#define TARTARUS_SUDOKULIB_CONTAINER_H

#include "Item.h"

class Container : public Item
{
private:

    ///Default constructor (disabled)
    Container() = delete;

    /// Copy constructor (disabled)
    Container(const Container &) = delete;

    /// Assignment operator
    void operator=(const Container &) = delete;

public:

};

#endif //TARTARUS_SUDOKULIB_CONTAINER_H
