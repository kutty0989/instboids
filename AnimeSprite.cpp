//#include "animesprite.h"
//#include"scean.h"
//#include<fstream>
//#include<sstream>
//
//void Animesprite::animesprite(std::string _path)
//{
//
//	//mcamera = _camera;
//	ifstream file(_path);//file��csv���R�s�[
//	if (file.fail())//�t�@�C�����Ȃ�������G���[
//		throw;
//
//	map<string, vector<DirectX::XMINT2>> mapTest;//�������L�[
//
//
//	int count = 0;//���� y 
//	int tcount = 0;//�c�� x
//	int xMaxpath = 0;
//	int yMaxpath = 0;
//
//
//		//�A�j���[�V�����̃f�[�^�z��
//	vector<DirectX::XMINT2> frameData;//
//	string texturepath;//�p�X������p�̕ϐ�
//	//�L�[���A�j���V�����̖��O
//	//�v�f���A�j���[�V�����̃f�[�^�z���map
//
//
//	//map�Ƀf�[�^��ǉ�
//
//
//	 XMFLOAT4 color = { 1,1,1,0.4f };
//
//	string str;
//	while (getline(file, str))//��s���擾�@
//	{
//		if (count == 0)
//		{
//			count++;
//			continue;
//		}
//
//		if (count == 1)
//		{
//			//str�̕������ss�ɕϊ��R�s�[
//			stringstream ss(str);//������𕪊��@�����ɕϊ��@ss�@�ϐ��istr�j������
//
//			string buf;//�ꎞ�ۑ��p
//
//			while (getline(ss, buf, ','))//ss����J���}�܂ł̕������buf�Ƃ��Ď擾
//			{
//				stringstream aa(buf);//aa��buf�������l�Ƃ��ăR�s�[��n��
//				switch (tcount)
//				{
//				case 0:
//
//					texturepath = buf;
//
//					//mpTexture = Direct3D::LoadTexture(texturepath.data());
//					//Sprite *bufSprite = new Sprite(mcamera);
//					bufSprite = new CTex();
//					bufSprite->set
//					bufSprite->Start(texturepath);
//					bufSprite->position.x = 0;
//					bufSprite->position.y = 3000;
//					bufSprite->position.z = 14;
//					bufSprite->scale.x = 30;
//					bufSprite->scale.y = 30;
//
//					break;
//
//				case 1:
//
//					aa >> xMaxpath;
//
//					break;
//				case 2:
//					aa >> yMaxpath;
//					break;
//
//				default:
//					bufSprite->PartMax(xMaxpath, yMaxpath);
//
//					break;
//
//				}
//				tcount++;
//			}
//			count++;
//			continue;
//		}
//
//
//		//�摜�̃p�X�@������
//		stringstream ss(str);
//		//1�t���[���̃f�[�^
//
//		if (count % 2 == 0)
//		{
//			int xcount = 0;
//			string buf;
//			//���ڂ��̂Ł[��
//			while (getline(ss, buf, ','))//�J�E���g�ŋ�؂�ꂽ�P�v�f���擾))
//			{
//				if (xcount == 0)
//				{
//					animaName = buf;
//					++xcount;
//					continue;
//				}
//
//
//				//������𐔎��ɕϊ����邽�߂�strigstream
//				stringstream ss2(buf);
//				HewUtility::int2 frame = { 0,0 };
//				ss2 >> frame.x;//���̃f�[�^���擾
//
//				//�t���[���̃f�[�^�������
//				frameData.emplace_back(frame);
//
//				//	cout << frameData.at(xcount - 1).x << endl;
//				if (frame.x == -1)
//				{
//					//xcount = 1;
//					break;
//				}
//				++xcount;
//			}
//		}
//		else if (count % 2 == 1)
//		{
//			int ycount = 0;
//			string buf;
//			while (getline(ss, buf, ','))//�J�E���g�ŋ�؂�ꂽ�P�v�f���擾))
//			{
//				if (ycount == 0)
//				{
//					++ycount;
//					continue;
//				}
//
//				//������𐔎��ɕϊ����邽�߂�strigstream
//				stringstream ss2(buf);
//
//
//				//ss2 >> frame.y;//���̃f�[�^���擾
//				ss2 >> frameData.at(ycount - 1).y; //y�̃t���[���f�[�^
//				//frameData.push_back(frame);
//
//			//	cout << frameData.at(ycount - 1).y << endl;
//				if (frameData.at(ycount - 1).y == -1)
//				{
//					break;
//				}
//				++ycount;
//			}
//
//
//			//�}�b�v�Ƀf�[�^��ǉ�
//			bufSprite->mpmapTest.insert(make_pair(animaName, frameData));
//			frameData.clear();//�t���[���̃f�[�^���N���A
//		}
//		count++;
//	}
//
//
//}
//
//
//void Animesprite::Update()
//{
//	if (bufSprite->mpmapTest.at(animaName)[frame].x == -1)
//	{
//
//		frame = 0;
//	}
//	if (bufSprite->mpmapTest.at(animaName)[frame].x == -2)
//	{
//
//		frame = 7;
//	}
//
//	part.x = bufSprite->mpmapTest.at(animaName)[frame].x;
//	part.y = bufSprite->mpmapTest.at(animaName)[frame].y;
//
//	bufSprite->Part(part);
//
//	frame++;
//	//bufSprite->mapTest.at(animaName)[frame];
//}
//
//void Animesprite::SetAnimation(std::string _animation)
//{
//	if (_animation != animaName)
//	{
//		animaName = _animation;
//		frame = 0;
//		part.x = bufSprite->mpmapTest.at(animaName)[frame].x;
//		part.y = bufSprite->mpmapTest.at(animaName)[frame].y;
//
//		bufSprite->Part(part);
//	}
//}
