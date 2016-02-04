#pragma once

#include <vector>
#include "SearchCell.h"
#include "MathCore.h"

class PathFinding
{
	PathFinding();
	~PathFinding();

	void FindPath(Vector2 curentPos, Vector2 targetPos);
	Vector2 NextPathPos();
	void ClearOpenList(){ m_openList.clear(); }
	void ClearVistedList() { m_vistedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	bool m_intializedStartGoal;
	bool m_foundGoal;

private:
	void setStartAndGoal(SearchCell start, SearchCell goal);
	void pathOpened(int x, int z, float newCost, SearchCell* parrent);
	SearchCell* getNextCell();
	void ContinuePath();

	SearchCell* m_startCell;
	SearchCell* m_goalCell;
	std::vector<SearchCell*> m_openList;
	std::vector<SearchCell*> m_vistedList;
	std::vector<Vector2*> m_pathToGoal;
};
