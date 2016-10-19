#pragma once

#include "DxLib.h"
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace graph_man
{
	class Uncopyable_Base{
	protected:
		Uncopyable_Base() {}
		~Uncopyable_Base() {}
	private:
		Uncopyable_Base(const Uncopyable_Base&);
		Uncopyable_Base& operator=(const Uncopyable_Base&);
	};

	//座標
	typedef std::pair<int, int> coordinate;


	//derivateやdivendしたものは子データとして管理される
	class GraphicData : Uncopyable_Base
	{
	public:
		GraphicData(int gh,int gr);
		void crush();
		int getdata();
		int getgroup();
		void pushch(int gh);
		GraphicData& operator [](int n);
		~GraphicData();
	private:
		GraphicData();
		int g_handle;
		int groupnum;
		std::vector<GraphicData> child;
	};

	//１つのグラフィックデータを管理するノード
	class GraphicNode
	{
	public:
		GraphicNode(std::weak_ptr<GraphicData>wk, coordinate siz = { -1,-1 });
		//画像の描画
		//position: 画像の位置
		//anchor: 左上を(0.0,0.0)、右下を(1.0,1.0)としたときのアンカー点の座標。アンカー点を中心に拡大・回転・描画が行われる。
		int draw(coordinate position, std::pair<double, double> anchor = { 0.0,0.0 }, std::pair<double, double> ext = { 1.0,1.0 }, double rot = 0.0, int trans = TRUE, int flip = TRUE);
		//画像の分譲データを作る。DxLibのDerivationGraphのように画像の指定位置をハンドルにし、GraphicNodeの子データとして管理する。
		//position:	画像の左上を(0,0)としたときの分譲データの左上の座標
		//size:		分譲データのサイズ
		int derivate(coordinate position, coordinate size);
		//画像の分譲データをLoadDivGraphのように升目に分けて作る。ただしLoadはしない。
		//divgrid:	LoadDivGraphのXNumとYNum
		//divnum:	LoadDivGraphのAllNum
		//size:		LoadDivGraphのXSizeとYSize
		int divend(coordinate divgrid, int divnum, coordinate size);
		//この画像データのみを解放する（分譲データは残したまま）
		void free();
	private:
		bool check();
		std::weak_ptr<GraphicData>ptr;
		coordinate size;
	};

	//グラフィックデータ管理クラス
	class GraphicManager : Uncopyable_Base
	{
	public:
		//グループ付けをする。詳細はGraphicManager::erase()関数を参照
		//戻り値：グループ固有値
		int group();
		//画像ファイルをロードし、GraphicNodeを作る。
		//key:		キーとなる文字列。普通はファイル名の拡張子をなくしたものを使う。
		//filename:	ファイル名が長い、汎用性に欠けるなどの理由でキーとして使いたくない場合にファイル名を明示的に指定できる。
		//			拡張子が必要。
		GraphicNode load(std::string key,std::string filename = std::string());
		//前回のgroup()関数呼び出しからロードされた画像のメモリ解放を行う。
		//再度参照は不可
		//戻り値：消去したグループ固有値
		int erase();

		GraphicNode operator [](std::string n);

		static GraphicManager &getInstance();
	private:
		GraphicManager();
		GraphicManager(const GraphicManager &other);
		GraphicManager &operator=(const GraphicManager &other) = delete;
		std::map<std::string, std::shared_ptr<GraphicData>> data;
		int gr;
	};

	//グラフィックデータの管理
	extern GraphicManager& grm;
}


using graph_man::grm;