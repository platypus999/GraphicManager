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

	//���W
	typedef std::pair<int, int> coordinate;


	//derivate��divend�������͎̂q�f�[�^�Ƃ��ĊǗ������
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

	//�P�̃O���t�B�b�N�f�[�^���Ǘ�����m�[�h
	class GraphicNode
	{
	public:
		GraphicNode(std::weak_ptr<GraphicData>wk, coordinate siz = { -1,-1 });
		//�摜�̕`��
		//position: �摜�̈ʒu
		//anchor: �����(0.0,0.0)�A�E����(1.0,1.0)�Ƃ����Ƃ��̃A���J�[�_�̍��W�B�A���J�[�_�𒆐S�Ɋg��E��]�E�`�悪�s����B
		int draw(coordinate position, std::pair<double, double> anchor = { 0.0,0.0 }, std::pair<double, double> ext = { 1.0,1.0 }, double rot = 0.0, int trans = TRUE, int flip = TRUE);
		//�摜�̕����f�[�^�����BDxLib��DerivationGraph�̂悤�ɉ摜�̎w��ʒu���n���h���ɂ��AGraphicNode�̎q�f�[�^�Ƃ��ĊǗ�����B
		//position:	�摜�̍����(0,0)�Ƃ����Ƃ��̕����f�[�^�̍���̍��W
		//size:		�����f�[�^�̃T�C�Y
		int derivate(coordinate position, coordinate size);
		//�摜�̕����f�[�^��LoadDivGraph�̂悤�ɏ��ڂɕ����č��B������Load�͂��Ȃ��B
		//divgrid:	LoadDivGraph��XNum��YNum
		//divnum:	LoadDivGraph��AllNum
		//size:		LoadDivGraph��XSize��YSize
		int divend(coordinate divgrid, int divnum, coordinate size);
		//���̉摜�f�[�^�݂̂��������i�����f�[�^�͎c�����܂܁j
		void free();
	private:
		bool check();
		std::weak_ptr<GraphicData>ptr;
		coordinate size;
	};

	//�O���t�B�b�N�f�[�^�Ǘ��N���X
	class GraphicManager : Uncopyable_Base
	{
	public:
		//�O���[�v�t��������B�ڍׂ�GraphicManager::erase()�֐����Q��
		//�߂�l�F�O���[�v�ŗL�l
		int group();
		//�摜�t�@�C�������[�h���AGraphicNode�����B
		//key:		�L�[�ƂȂ镶����B���ʂ̓t�@�C�����̊g���q���Ȃ��������̂��g���B
		//filename:	�t�@�C�����������A�ėp���Ɍ�����Ȃǂ̗��R�ŃL�[�Ƃ��Ďg�������Ȃ��ꍇ�Ƀt�@�C�����𖾎��I�Ɏw��ł���B
		//			�g���q���K�v�B
		GraphicNode load(std::string key,std::string filename = std::string());
		//�O���group()�֐��Ăяo�����烍�[�h���ꂽ�摜�̃�����������s���B
		//�ēx�Q�Ƃ͕s��
		//�߂�l�F���������O���[�v�ŗL�l
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

	//�O���t�B�b�N�f�[�^�̊Ǘ�
	extern GraphicManager& grm;
}


using graph_man::grm;