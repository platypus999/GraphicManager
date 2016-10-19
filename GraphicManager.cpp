
#include "GraphicManager.h"

using namespace graph_man;

GraphicManager& grm = GraphicManager::getInstance();

int GraphicManager::group()
{
	++gr;
}

GraphicManager::GraphicManager() :gr(0) {}

GraphicNode GraphicManager::load(std::string key, std::string filename)
{
	int gh = LoadGraph((filename.empty() ? key : filename).c_str());
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

GraphicNode GraphicManager::operator[](std::string n)
{
	auto itr = data.find(n);
	if (itr != data.end())
	{
		return GraphicNode(itr->second);
	}
	return GraphicNode(std::weak_ptr<GraphicData>());
}