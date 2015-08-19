
#pragma once

#include "Utils.h"

class WayPoints
{
public:
	struct Way_Point
	{
		Vec2F pt = { 0.0f, 0.0f };
		bool  reached = false;
		float value = 0.0f;
		int mapIndex = -1;
		Way_Point(){}
		Way_Point(Vec2F p,bool reach,float val,int map_index)
			:
			pt(p),
			reached(reach),
			value(val),
			mapIndex(map_index)
		{}
	};
protected:
	std::vector<Way_Point>points;
	UINT pointCount;
public:
	WayPoints(UINT numbPoints)
		:
		pointCount(numbPoints)
	{
		points.resize(pointCount);
	}
	void AddPoint(const Way_Point pt)
	{
		if (points.size() == pointCount)
			return;

		points.push_back(pt);
	}
	Way_Point GetPoint(const UINT index)
	{ 
		if (index >= pointCount)
			return Way_Point({-1.0f,-1.0f},false,-1.0f,-1);

		return points[index];
	}
};