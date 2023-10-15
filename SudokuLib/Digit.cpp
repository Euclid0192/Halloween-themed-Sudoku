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
 * Override XmlLoadDeclaration in Item
 * @param node: node that we load attributes from
 */
void Digit::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    long value;
    node->GetAttribute(L"value", L"0").ToLong(&value);
    mValue = (int)value;
}

