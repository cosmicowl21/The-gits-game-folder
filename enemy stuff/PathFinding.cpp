
#include "Pathfinding.h"
#include "MathCore.h"
/*
PathFinding::PathFinding(void)
{
	m_intializedStartGoal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding()
{

}
void PathFinding::FindPath(Vector2 currentPos, Vector2 targetPos)
{
	if (!m_intializedStartGoal)
	{
		for (int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for (int i = 0; i < m_vistedList.size(); i++)
		{
			delete m_vistedList[i];
		}
		m_openList.clear();
		for (int i = 0; m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		//init start
		SearchCell start;
		//start.m_xcoord = currentPos._x;
		//start.m_zcoord = currentPos._z;
		//init goal
		SearchCell goal;
		//goal.m_xcoord = targetPos._x;
		//goal.m_zcoord = targetPos._z;

		setStartAndGoal(start, goal);
		m_intializedStartGoal = true;
	}
	if (m_intializedStartGoal)
	{
		ContinuePath();
	}
}

void PathFinding::setStartAndGoal(SearchCell start, SearchCell goal)
{
	m_startCell = new SearchCell(start.m_xcoord, start.m_zcoord, NULL);
	m_goalCell = new SearchCell(goal.m_xcoord, goal.m_zcoord, &goal);

	m_startCell->G = 0;
	m_startCell->H - m_startCell->ManHattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

SearchCell* PathFinding::getNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	SearchCell* nextCell = NULL;

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->getF() < bestF)
		{
			bestF = m_openList[i]->getF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_vistedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}
	return nextCell;
}
void PathFinding::pathOpened(int x, int z, float newCost, SearchCell* parrent)
{
	/*if (CELL_BLOCKED
	return
	}  */
/*
	int id = z* WOLRD_SIZE + x;
	for (int i = 0; i < m_vistedList.size(); i++)
	{
		if (id == m_vistedList[i]->m_id)
		{
			return;
		}
	}
	SearchCell* newChild = new SearchCell(x, z, parrent);
	newChild->G = newCost;
	newChild->H = parrent->ManHattanDistance(m_goalCell);

	for (int i; i < m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;

			if (m_openList[i]->getF() > newF)
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;

			}
			else //if the F is not better
			{
				delete newChild;
				return;
			}
		}
	}
	m_openList.push_back(newChild);
}

void PathFinding::ContinuePath()
{
	if (m_openList.empty())
	{
		return;
	}
	SearchCell* currentCell = getNextCell();

	if (currentCell->m_id == m_goalCell->m_id)
	{
		m_goalCell->parent = currentCell->parent;
		SearchCell* getPath;
		
		/*
		for (getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
		{
			m_pathToGoal.push_back(new Vector2(getPath->m_xcoord, 0, getPath->m_zcoord));
		}
		m_foundGoal = true;
		return;
	}
	else
	{
		//rigthside
		pathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
		//leftside
		pathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord, currentCell->G + 1, currentCell);
		//up
		pathOpened(currentCell->m_xcoord , currentCell->m_zcoord + 1, currentCell->G + 1, currentCell);
		//down
		pathOpened(currentCell->m_xcoord, currentCell->m_zcoord - 1, currentCell->G + 1, currentCell);
		//left-up diagonal
		pathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord +1, currentCell->G + 1.414f, currentCell);
		//rigth-up diagonal
		pathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord+1, currentCell->G + 1.414f, currentCell);
		//left-down diagonal
		pathOpened(currentCell->m_xcoord - 1, currentCell->m_zcoord -1, currentCell->G + 1.414f, currentCell);
		//right-down diagonal
		pathOpened(currentCell->m_xcoord + 1, currentCell->m_zcoord -1, currentCell->G + 1.414f, currentCell);

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentCell->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + i);
			}
		}
	}
}

Vector2 PathFinding::NextPathPos()
{
	int index = 1;
	Vector2 NextPos;
	NextPos._x = m_pathToGoal[m_pathToGoal.size() - index]-> _x;
	NextPos._z = m_pathToGoal[m_pathToGoal.size() - index]-> _z;

	Vector2 distance = NextPos - pos;

	if (index < m_pathToGoal.size())
	{
		if (distance.Length() < radius)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}
	return NextPos;
}
*/