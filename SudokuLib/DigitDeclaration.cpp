/**
 * @file DigitDeclaration.cpp
 * @author Nam Hai Nguyen
 *
 * Implementation of DigitDeclaration
 */

#include "pch.h"
#include "DigitDeclaration.h"

#include "pch.h"
#include "Digit.h"

using namespace std;

/**
 * Constructor
 */
DigitDeclaration::DigitDeclaration(Game *game): Declaration(game)
{

}

/**
 * Override XmlLoadDeclaration in Item
 * @param node: node that we load attributes from
 */
void DigitDeclaration::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    long value;
    node->GetAttribute(L"value", L"0").ToLong(&value);
    mValue = (int)value;
}