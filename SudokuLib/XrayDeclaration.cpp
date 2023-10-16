/**
 * @file XrayDeclaration.cpp
 * @author Nam Hai Nguyen
 */

#include "pch.h"
#include "XrayDeclaration.h"

/**
 * Constructor
 */
XrayDeclaration::XrayDeclaration(Game *game): Declaration(game)
{

}

/**
 * Override XmlLoad in Declaration
 * @param node: node that we load attributes from
 */
void XrayDeclaration::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    long capacity;
    node->GetAttribute(L"capacity", L"0").ToLong(&capacity);
    mCapacity = (int) capacity;
}
