#pragma once

#include "DxLib.h"
#include <utility>

namespace graph_man
{
	class GraphicNode
	{
	public:
		int draw(std::pair<int,int>position, std::pair<int, int>anchor,double ext = 1.0,double turn = 0.0);
	private:
		int g_handle;
	};

	class GraphicManager
	{
	public:

	private:

	};
}