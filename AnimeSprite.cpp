//#include "animesprite.h"
//#include"scean.h"
//#include<fstream>
//#include<sstream>
//
//void Animesprite::animesprite(std::string _path)
//{
//
//	//mcamera = _camera;
//	ifstream file(_path);//fileにcsvをコピー
//	if (file.fail())//ファイルがなかったらエラー
//		throw;
//
//	map<string, vector<DirectX::XMINT2>> mapTest;//第一引数キー
//
//
//	int count = 0;//横列 y 
//	int tcount = 0;//縦列 x
//	int xMaxpath = 0;
//	int yMaxpath = 0;
//
//
//		//アニメーションのデータ配列
//	vector<DirectX::XMINT2> frameData;//
//	string texturepath;//パスを入れる用の変数
//	//キーがアニメションの名前
//	//要素がアニメーションのデータ配列のmap
//
//
//	//mapにデータを追加
//
//
//	 XMFLOAT4 color = { 1,1,1,0.4f };
//
//	string str;
//	while (getline(file, str))//一行ずつ取得　
//	{
//		if (count == 0)
//		{
//			count++;
//			continue;
//		}
//
//		if (count == 1)
//		{
//			//strの文字列をssに変換コピー
//			stringstream ss(str);//文字列を分割　数字に変換　ss　変数（str）初期化
//
//			string buf;//一時保存用
//
//			while (getline(ss, buf, ','))//ssからカンマまでの文字列をbufとして取得
//			{
//				stringstream aa(buf);//aaにbufを初期値としてコピーを渡す
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
//		//画像のパス　分割数
//		stringstream ss(str);
//		//1フレームのデータ
//
//		if (count % 2 == 0)
//		{
//			int xcount = 0;
//			string buf;
//			//一回目ｘのでーた
//			while (getline(ss, buf, ','))//カウントで区切られた１要素ずつ取得))
//			{
//				if (xcount == 0)
//				{
//					animaName = buf;
//					++xcount;
//					continue;
//				}
//
//
//				//文字列を数字に変換するためにstrigstream
//				stringstream ss2(buf);
//				HewUtility::int2 frame = { 0,0 };
//				ss2 >> frame.x;//ｘのデータを取得
//
//				//フレームのデータをいれる
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
//			while (getline(ss, buf, ','))//カウントで区切られた１要素ずつ取得))
//			{
//				if (ycount == 0)
//				{
//					++ycount;
//					continue;
//				}
//
//				//文字列を数字に変換するためにstrigstream
//				stringstream ss2(buf);
//
//
//				//ss2 >> frame.y;//ｘのデータを取得
//				ss2 >> frameData.at(ycount - 1).y; //yのフレームデータ
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
//			//マップにデータを追加
//			bufSprite->mpmapTest.insert(make_pair(animaName, frameData));
//			frameData.clear();//フレームのデータをクリア
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
