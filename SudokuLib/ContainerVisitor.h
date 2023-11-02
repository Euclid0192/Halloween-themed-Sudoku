/**
 * @file ContainerVisitor.h
 * @author Joanna Rodriguez Zamarron
 *
 * A concrete visitor to get the Container of the game
 */

#ifndef TARTARUS_SUDOKULIB_CONTAINERVISITOR_H
#define TARTARUS_SUDOKULIB_CONTAINERVISITOR_H

#include "ItemVisitor.h"
#include "Container.h"

/**
 * A concrete visitor to get the Container of the game
 */
class ContainerVisitor : public ItemVisitor
{
private:
	std::vector<Container*> mContainers;

public:
	std::vector<Container*> GetContainers() { return mContainers; }

	void VisitContainer(Container *container) override
	{
		mContainers.push_back(container);
	}

};

#endif //TARTARUS_SUDOKULIB_CONTAINERVISITOR_H
