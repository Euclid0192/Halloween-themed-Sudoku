/**
 * @file Container.cpp
 * @author yaxuan
 *
 * Class for containers
 *
 */


#include "pch.h"
#include "Container.h"
#include "Item.h"
#include "SudokuGame.h"
#include "GetDigitFromItem.h"
#include "GetSpartyVisitor.h"

using namespace std;

/**
 * Constructor
 * @param game: pointer to game
 */
Container::Container(SudokuGame *game) : Item(game)
{
	// Seed the random number generator
	std::random_device rd;
	mRandom.seed(rd());
}

/**
 * Override draw function
 * @param graphics : graphics context we use to draw
 */
void Container::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    auto wid = GetWidth(), hit = GetHeight();
    ///Get the bitmap and image of the background
    auto bitmap = GetBitmap();
    auto image = GetImage();

    ///Check if the bitmap is null
    if(bitmap.IsNull())
    {
        bitmap = graphics->CreateBitmapFromImage(*image);
    }

    ///Draw the back image
    graphics->DrawBitmap(bitmap,
                         GetX(),
                         GetY() - hit,
                         wid,
                         hit
    );
    if(mFrontBitmap.IsNull())
    {
        mFrontBitmap = graphics->CreateBitmapFromImage(*mFrontImage);
    }

    ///Draw the digits inside
    for (auto digit: mDigits)
    {
        digit->Draw(graphics);
    }

    //
    // Draw the front image
    //
    graphics->DrawBitmap(mFrontBitmap,
                         GetX(),
                         GetY() - hit,
                         wid,
                         hit);
}

/**
 * Override of loading declarations
 * @param node : node we are loading
 */
void Container::XmlLoadDeclaration(wxXmlNode *node)
{
    Item::XmlLoadDeclaration(node);
    auto frontPath = node->GetAttribute(L"front", L"").ToStdWstring();
    frontPath = GetImagesDirectory() + L"/" + frontPath;
    if (!frontPath.empty())
        mFrontImage = std::make_unique<wxImage>(frontPath, wxBITMAP_TYPE_ANY);
}

/**
 * Override of loading items
 * @param node : node we are loading
 */
void Container::XmlLoadItem(wxXmlNode *node)
{
    Item::XmlLoadItem(node);
    auto game = GetGame();
    ///Loading all the digits inside the container
    auto child = node->GetChildren();
    for ( ; child; child = child->GetNext())
    {
        auto id = child->GetAttribute(L"id", L"").ToStdWstring();
        auto declaration = game->GetDeclaration(id);
        auto item = declaration->Clone();
        item->XmlLoadItem(child);
        item->SetLocation(item->GetX(), item->GetY() - game->GetTileHeight());
        mDigits.push_back(item);
    }
}

/**
 * HitTest of Container items
 * @param x : x value
 * @param y : y value
 * @return bool : if we hit the Container
 */
bool Container::HitTest(double x, double y)
{
	// Container's coordinates and dimensions
	double containerX = GetX();
	double containerY = GetY() - GetHeight(); // Adjusting for the bottom-left origin
	double containerWidth = GetWidth();
	double containerHeight = GetHeight();

	GetSpartyVisitor GetSpartyVisitor;
	GetGame()->Accept(&GetSpartyVisitor);
	Sparty *sparty = GetSpartyVisitor.GetSparty();

	// Check if there is no overlap between Sparty and the Container
	if (x > containerX + containerWidth || // Sparty is to the right of the container
		x + sparty->GetWidth() < containerX ||    // Sparty is to the left of the container
		y > containerY + containerHeight || // Sparty is above the container
		y + sparty->GetHeight() < containerY)      // Sparty is below the container
	{
		return false; // No overlap detected
	}

	return true; // Overlap detected
}

/**
 * Empties the Container of its Digits
 */
void Container::Empty()
{
	double scatterDistanceX = 100.0; // maximum scatter distance in x direction
	double scatterDistanceY = 100.0; // maximum scatter distance in y direction

	// Uniform distributions for x and y offsets
	std::uniform_real_distribution<double> distributionX(-scatterDistanceX, scatterDistanceX);
	std::uniform_real_distribution<double> distributionY(0, scatterDistanceY);

	for(auto& digit : mDigits)
	{
		// Generate random offsets
		double offsetX = distributionX(mRandom);
		double offsetY = distributionY(mRandom);

		// Get the current location of the digit
		double digitX = digit->GetX();
		double digitY = digit->GetY();

		// Set the new location of the digit scattered above the container
		digit->SetLocation(digitX - offsetX, digitY - offsetY);

		GetGame()->AddItem(digit);
	}

	Clear();

}

/**
 * Clears the vector of Digits
 */
void Container::Clear()
{
	mDigits.clear();
}

