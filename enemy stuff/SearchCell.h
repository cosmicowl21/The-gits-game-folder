#pragma once
#include <math.h>
#define WOLRD_SIZE 64

struct SearchCell
{
public:
	int m_xcoord, m_zcoord;
	int m_id;
	SearchCell* parent;
	float G;
	float H;

	SearchCell() : parent(0) {}
	SearchCell(int x, int z, SearchCell* _parrent = 0) : m_xcoord(x), m_zcoord(z),
		parent(_parrent) , m_id(z* WOLRD_SIZE + z), G(0), H(0) {};
	float getF() { return G + H;  }
	float ManHattanDistance(SearchCell* nodeEnd)
	{
		float x = (float)(fabsf(this->m_xcoord - nodeEnd->m_xcoord));
		float z = (float)(fabsf(this->m_zcoord - nodeEnd->m_zcoord));
		return x + z;
	}
};