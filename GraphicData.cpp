
#include "GraphicManager.h"
#include <iostream>

using namespace graph_man;

GraphicData::GraphicData(int gh, int gr)
{
	g_handle = gh;
	groupnum = gr;
}

void GraphicData::crush()
{
	DeleteGraph(g_handle);
	g_handle = -1;
}

int GraphicData::getdata()
{
	return g_handle;
}

int GraphicData::getgroup()
{
	return groupnum;
}

void GraphicData::pushch(int gh)
{
	child.emplace_back(gh, groupnum);
}

GraphicData& GraphicData::operator [](int n)
{
	if (n < 0 || child.size() >= n)
	{
		return (*this);
	}
	else
	{
		return child.at(n);
	}
}

GraphicData::~GraphicData()
{
	if (g_handle >= 0)
	{
		DeleteGraph(g_handle);
	}
}

GraphicManager& GraphicManager::getInstance()
{
	static GraphicManager grm;
	return grm;
}