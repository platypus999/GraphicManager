
#include "GraphicManager.h"

using namespace graph_man;

GraphicManager& grm = GraphicManager::getInstance();

int GraphicManager::group()
{
	return ++gr;
}

GraphicManager::GraphicManager() :gr(0),pass(""),extension(".png") {}

GraphicNode GraphicManager::load(std::string key, std::string filename)
{
	int gh = LoadGraph((pass + (filename.empty() ? key : (filename + extension))).c_str());
	data.emplace(key, std::make_shared<GraphicData>(gh, gr));
	return (*this)[key];
}

int GraphicManager::erase()
{
	for (auto itr = data.begin(); itr != data.end();)
	{
		if (itr->second->getgroup() == gr)
		{
			itr = data.erase(itr);
		}
		else 
		{
			++itr;
		}
	}
	return --gr;
}

void GraphicManager::setPass(std::string p_)
{
	pass = std::move(p_);
}

void GraphicManager::setExtension(std::string e_)
{
	extension = std::move(e_);
}


GraphicNode GraphicManager::operator[](std::string n)
{
	auto itr = data.find(n);
	if (itr != data.end())
	{
		return GraphicNode(itr->second);
	}
	return GraphicNode(std::weak_ptr<GraphicData>());
}