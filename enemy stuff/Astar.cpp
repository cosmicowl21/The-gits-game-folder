
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>

using std::unordered_map;
using std::unordered_set;
using std::array;
using std::vector;
using std::queue;
using std::priority_queue;
using std::pair;
using std::tuple;
using std::tie;
using std::string;





int main() {
	inline int heuristic(SquareGrid::Location a, SquareGrid::Location b) {
		int x1, y1, x2, y2;
		tie(x1, y1) = a;
		tie(x2, y2) = b;
		return abs(x1 - x2) + abs(y1 - y2);
	}

	template<typename Graph>
	void a_star_search
		(Graph graph,
		typename Graph::Location start,
		typename Graph::Location goal,
		unordered_map<typename Graph::Location, typename Graph::Location>& came_from,
		unordered_map<typename Graph::Location, int>& cost_so_far)
	{
		typedef typename Graph::Location Location;
		PriorityQueue<Location> frontier;
		frontier.put(start, 0);

		came_from[start] = start;
		cost_so_far[start] = 0;

		while (!frontier.empty()) {
			auto current = frontier.get();

			if (current == goal) {
				break;
			}

			for (auto next : graph.neighbors(current)) {
				int new_cost = cost_so_far[current] + graph.cost(current, next);
				if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
					cost_so_far[next] = new_cost;
					int priority = new_cost + heuristic(next, goal);
					frontier.put(next, priority);
					came_from[next] = current;
				}
			}
		}
	}
	return 0;
}

