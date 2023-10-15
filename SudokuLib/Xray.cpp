/**
 * @file Xray.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of Xray
 */

#include "pch.h"
#include "Xray.h"

using namespace std;

/**
 * Constructor
 */
Xray::Xray(Game *game): Item(game)
{

}

/**
 * Override XmlLoadDeclaration in Item
 * @param node: node that we load attributes from
 */
void Xray::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    long capacity;
    node->GetAttribute(L"capacity", L"0").ToLong(&capacity);
    mCapacity = (int) capacity;
}