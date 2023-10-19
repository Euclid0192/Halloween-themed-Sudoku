/**
 * @file Digit.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Digit class
 */

#include "pch.h"
#include "Digit.h"

using namespace std;

/**
 * Constructor
 */
Digit::Digit(Game *game): Item(game)
{

}

/**
 * Copy constructor
 */
Digit::Digit(const Digit &digit) : Item(digit)
{
    mValue = digit.mValue;
    mGiven = digit.mGiven;
}

void Digit::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    long value;
    node->GetAttribute(L"value", L"0").ToLong(&value);
    mValue = (int)value;
    auto name = node->GetName();
    if (name == L"given")
        mGiven = true;
    else
        mGiven = false;
};

shared_ptr<Item> Digit::Clone()
{
    return make_shared<Digit>(*this);
}


