
#include "GraphicManager.h"

using namespace graph_man;

GraphicNode::GraphicNode(std::weak_ptr<GraphicData>wk, coordinate siz)
{
	ptr = wk;
	if (!check())return;
	if (siz.first != -1)
	{
		size = siz;
	}
	else
	{
		GetGraphSize(ptr.lock()->getdata(), &size.first, &size.second);
	}
}

//#error ‰Ê‚½‚µ‚Ärot=1.0‚Ìê‡‚Íˆ—‚ªŒyŒ¸‰»‚³‚ê‚é‚Ì‚¾‚ë‚¤‚©H
int GraphicNode::draw(coordinate position, std::pair<double, double> anchor, std::pair<double, double> ext, double rot, int trans, int flip)
{
	if (!check())return -2;
	return DrawRotaGraph3(position.first, position.second, size.first * anchor.first, size.second*anchor.second, ext.first, ext.second, rot, ptr.lock()->getdata(), trans, flip);
}

int GraphicNode::derivate(coordinate position, coordinate size)
{
	if (!check())return -2;
	int handle = DerivationGraph(position.first, position.second, size.first, size.second, ptr.lock()->getdata());
	if (handle < 0)return -1;
	ptr.lock()->pushch(handle);
	return 0;
}

int GraphicNode::divend(coordinate divgrid, int divnum, coordinate size)
{
	if (!check())return -2;
	int r = 0;
	for (int x = 0; x < divnum; ++x)
	{
		r &= derivate({ size.first * (x % divgrid.first),size.second * (x / divgrid.second) }, size);
	}
	return r;
}

void GraphicNode::free()
{
	if (!check())return;
	ptr.lock()->crush();
}

bool GraphicNode::check()
{
	if (ptr.expired() || ptr.lock()->getdata() < 0)
	{
		size = { -1,-1 };
		return false;
	}
	return true;
}

