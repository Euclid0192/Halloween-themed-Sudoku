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
	/// holds the containers in the game
	std::vector<Container*> mContainers;

public:
	/**
	 * Grabs the Containers in the game
	 * @return mContainers: vector of the containers
	 */
	std::vector<Container*> GetContainers() { return mContainers; }

	/**
	 * visits the Container class
	 * @param container : pointer to Container object
	 */
	void VisitContainer(Container *container) override
	{
		mContainers.push_back(container);
	}

};

#endif //TARTARUS_SUDOKULIB_CONTAINERVISITOR_H
