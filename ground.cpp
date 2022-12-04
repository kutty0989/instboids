#include "ground.h"
#include"CDirectInput.h"
#include<iostream>
#include"PlayerMgr.h"
#include"player.h"
#include"Save.h"


float sinC;
float cosC;

bool Ground::Init()
{
	g_heightmap = new CHeight_Map();
	g_heightmap->Init(XMFLOAT3(1.0f, 1.0f, 1.0f));
	g_heightmap->LoadTexture("assets/UI/ground1.jpg",0);//１枚目の地面画像　
	g_heightmap->LoadTexture("assets/UI/glow.jpg",1);//２枚目の高さによってブレンドする画像
	g_heightmap->LoadTexture("assets/UI/snow.jpeg",2);//２枚目の高さによってブレンドする画像
	g_heightmap->LoadTexture("assets/UI/blood.png",3);//２枚目の高さによってブレンドする画像
	//m_WidthHeight = { 100.0f,100.0f };

	m_scale.x = scaling;
	m_scale.y = scaling;
	return true;
}



void Ground::Draw()
{
	//ディスプレイトメントマッピングをしたい画像の描画
	g_heightmap->SetUV(CHeight_Map::GetInstance()->c_uv);
	g_heightmap->SetScale(m_scale);
	g_heightmap->SetPosition(m_pos);
	g_heightmap->SetRotation(90.0f, 0.0f, 0.0f);//カメラの正面に向くように
	g_heightmap->updateVertex(XMFLOAT3(1.0f, 0.5f, 1.0f));
	g_heightmap->updateVbuffer();
	g_heightmap->Draw();
	
}
SaveData save1;
float a;
void Ground::Update()
{
	

	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_8))
	{
	//	/*std::vector<std::vector<double>> loadmap ={};
	//	
	//	g_heightmap->gData[25][250] = 0.8f;
	//	loadmap[251][250] = 1.8f;
	//	loadmap[252][250] = 1.8f;
	//	loadmap[253][250] = 1.8f;
	//	loadmap[254][250] = 1.8f;
	//	loadmap[255][250] = 1.8f;*/
		/*auto map = g_heightmap->GetMap();
	
		g_heightmap->LoadMap(map);*/

	
		for (int x = 0; x < 50; x++)
		{
			for (int y = 0; y < 50; y++)
			{

				g_heightmap->gData[x][y] = 0.5f;


			}
		}
	
		g_heightmap->ChangeMap();
		//g_heightmap->LoadMap(loadmap);
	}

	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_T))
	{

		save1.fdata = 0.0f;
		save1.name = "test";
		save1.datavec[0] = 0;
		save1.datavec[1] = 0;
		save1.datavec[2] = 0;

		save1.dotto = CHeight_Map::GetInstance()->vData;



		Savevin("assets/assets.dat", save1);
	}
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_Y))
	{
		save1 = Loadvin("assets/assets.dat");
		auto map = save1.dotto;
	
		g_heightmap->LoadMap(map);

	}
	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_U))
	{
		g_heightmap->NoiseCreate();//自動地形生成
	}
	//if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_7))
	//{
	//	g_heightmap->LoadMap(save1.dotto);
	//}

	if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_9))
	{
		auto map = g_heightmap->GetMap();
		map[250].at(250) = 0.99f;
		g_heightmap->LoadMap(map);
		//g_heightmap->updateVertex(XMFLOAT3(1.0f, 0.5f, 1.0f));
		//g_heightmap->updateVbuffer();
		//g_heightmap->Draw();
	}

}
static int cnt = 0;

void Ground::GetPlayerHeight(Player& player)
{
	col = g_heightmap->GetHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling));//プレイヤーが画像のどこにいて、その足元のカラー情報


		//debuglog(player.GetPos().x + GetWidthHeight() / 2);
		//debuglog(player.Getpad_rig().x);
	gocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
		PlayerMgr::GetInstance()->Getpad_rig().x, PlayerMgr::GetInstance()->Getpad_rig().y);

	defcol = gocol - col;
	if (cnt == 0)
	{
		//player.SetAPower(cosvalues[(int)goangle]);
		if (goangle >= 0)
		{
			player.SetAPower(cosC);
		}
		if (goangle < 0)
		{
			sinC = sinC + 1.0f;
			//float value = abs(goangle);
			//value = sinvalues[(int)value] + 1;*/
			player.SetAPower(sinC);
		}
	}
	else
	{
		player.SetAPower(1.0f);
	}

	float teihen = sqrtf((PlayerMgr::GetInstance()->Getpad_rig().x * PlayerMgr::GetInstance()->Getpad_rig().x) + (PlayerMgr::GetInstance()->Getpad_rig().y * PlayerMgr::GetInstance()->Getpad_rig().y));
	goangle = GetAtan(teihen * 0.05f, defcol * CHeight_Map::GetInstance()->g_hight);
	defcol *= 0.2f;
	if (abs(defcol) > 1.0f)
	{
		defcol = 1.0f;
	}
	cosC = GetcosC(teihen * 0.05f, defcol * CHeight_Map::GetInstance()->g_hight);
	sinC = GetsinC(teihen * 0.05f, defcol * CHeight_Map::GetInstance()->g_hight);

	player.SetPos(XMFLOAT3(player.GetPos().x, col * CHeight_Map::GetInstance()->g_hight, player.GetPos().z));//プレイヤーのｙの高さを変えてる

}
//
//void Ground::DefangleAccel(Player& player)
//{
//	col = g_heightmap->GetHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling));
//
//	if (PlayerMgr::GetInstance()->Getpad_rig_flg())
//	{
//		//debuglog(player.GetPos().x + GetWidthHeight() / 2);
//		//debuglog(player.Getpad_rig().x);
//		gocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
//		PlayerMgr::GetInstance()->Getpad_rig().x, PlayerMgr::GetInstance()->Getpad_rig().y);
//		
//		defcol = gocol - col;
//		
//		if (cnt == 0)
//		{
//			//player.SetAPower(cosvalues[(int)goangle]);
//			if (goangle >= 0)
//			{
//				accel* cosC;
//				//player.SetAPower(cosC);
//			}
//			if (goangle < 0)
//			{
//				sinC = sinC + 1.0f;
//				//float value = abs(goangle);
//				//value = sinvalues[(int)value] + 1;*/
//			//	player.SetAPower(sinC);
//				accel* sinC;
//			}
//		}
//		else
//		{
//			player.SetAPower(1.0f);
//		}
//	}
//	//float teihen = sqrtf((PlayerMgr::GetInstance()->Getpad_rig().x * PlayerMgr::GetInstance()->Getpad_rig().x) + (PlayerMgr::GetInstance()->Getpad_rig().y * PlayerMgr::GetInstance()->Getpad_rig().y));
//	//goangle = GetAtan(teihen * 0.05f, defcol * CHeight_Map::GetInstance()->g_hight);
//	//
//	//
//	//cosC = GetcosC(teihen * 0.05f, defcol * CHeight_Map::GetInstance()->g_hight);
//	//sinC = GetsinC(teihen * 0.05f, defcol * CHeight_Map::GetInstance()->g_hight);
//
//	player.SetPos(XMFLOAT3(player.GetPos().x, col * CHeight_Map::GetInstance()->g_hight, player.GetPos().z));
//
//
//	cnt++;
//	if (cnt > 1005)
//	{
//		cnt = 0;
//	}
//}

void Ground::Finalize()
{
	g_heightmap->UnInit();
}

XMFLOAT3 Ground::GetPos()
{
	return m_pos;
}

float Ground::GetWidthHeight()
{
	return CHeight_Map::GetInstance()->iPixSize;
}

