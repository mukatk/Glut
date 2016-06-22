#pragma once
#include <vector>

using namespace std;

class Face {
public:
	vector<int> refPoints;
	vector<int> textPoints;
	vector<int> normalPoints;

	Face(){}

	void addRefPoint(int point) {
		refPoints.push_back(point);
	}

	void addNormalPoint(int point) {
		normalPoints.push_back(point);
	}

	void addTextPoint(int point) {
		textPoints.push_back(point);
	}

	~Face()
	{
	}
};