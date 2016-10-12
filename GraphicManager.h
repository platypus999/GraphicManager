#pragma once

#include "DxLib.h"
#include <utility>
#include <vector>
#include <map>
#include <string>

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

	//�P�̃O���t�B�b�N�f�[�^���Ǘ�����m�[�h
	//derivate��divend�������͎̂q�m�[�h�Ƃ��ĊǗ������
	class GraphicNode : Uncopyable_Base
	{
	public:
		//�摜�̕`��
		//position: �摜�̈ʒu
		//anchor: �����(0.0,0.0)�A�E����(1.0,1.0)�Ƃ����Ƃ��̃A���J�[�_�̍��W�B�A���J�[�_�𒆐S�Ɋg��E��]�E�`�悪�s����B
		int draw(coordinate position, std::pair<double, double> anchor = { 0.0,0.0 }, double ext = 1.0, double rot = 0.0);
		//�摜�̕����f�[�^�����BDxLib��DerivationGraph�̂悤�ɉ摜�̎w��ʒu���n���h���ɂ��AGraphicNode�̎q�f�[�^�Ƃ��ĊǗ�����B
		//position:	�摜�̍����(0,0)�Ƃ����Ƃ��̕����f�[�^�̍���̍��W
		//size:		�����f�[�^�̃T�C�Y
		int derivate(coordinate position, coordinate size);
		//�摜�̕����f�[�^��LoadDivGraph�̂悤�ɏ��ڂɕ����č��B������Load�͂��Ȃ��B
		//divgrid:	LoadDivGraph��XNum��YNum
		//divnum:	LoadDivGraph��AllNum
		//size:		LoadDivGraph��XSize��YSize
		int divend(coordinate divgrid, int divnum, coordinate size);

		GraphicNode& operator [](int n);
		~GraphicNode();
	private:
		int g_handle;
		std::vector<GraphicNode&> child;
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
		GraphicNode& load(std::string key,std::string filename = std::string());
		//�O���group()�֐��Ăяo�����烍�[�h���ꂽ�摜�̃�����������s���B
		//�ēx�Q�Ƃ͕s��
		//�߂�l�F���������O���[�v�ŗL�l
		int erase();

		GraphicNode& operator [](std::string n);
	private:
		std::map<std::pair<int, std::string>, GraphicNode> data;

	};
}