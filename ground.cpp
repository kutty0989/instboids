#include "ground.h"
#include"CDirectInput.h"
#include<iostream>
#include"PlayerMgr.h"
#include"player.h"

//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f〜1.0f
template<typename T>
T LeapID(T _go, T _to, float _ratio)
{
	return _go * (1.0f - _ratio) + _to * (T)_ratio;
}

float sinC;
float cosC;

bool Ground::Init()
{
	g_heightmap = new CHeight_Map();
	g_heightmap->Init(XMFLOAT3(1.0f, 1.0f, 1.0f));
	g_heightmap->LoadTexture("assets/UI/ground1.jpg",0);//１枚目の地面画像　
	g_heightmap->LoadTexture("assets/UI/snow.jpeg", 1);//２枚目の高さによってブレンドする画像
	g_heightmap->LoadTexture("assets/UI/glow.jpg",2);//２枚目の高さによってブレンドする画像
	g_heightmap->LoadTexture("assets/UI/blood.png", 3);//２枚目の高さによってブレンドする画像
													 //m_WidthHeight = { 100.0f,100.0f };
	scaling = CHeight_Map::GetInstance()->ScaleMap;
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

float a;
void Ground::Update()
{
	
	scaling = CHeight_Map::GetInstance()->ScaleMap;
	m_scale.x = scaling;
	m_scale.y = scaling;
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

	if (CHeight_Map::GetInstance()->mapsave)
	{

		Save::GetInstance()->save1.fdata = 0.0f;
		Save::GetInstance()->save1.name = "test";
		Save::GetInstance()->save1.datavec[0] = 0;
		Save::GetInstance()->save1.datavec[1] = 0;
		Save::GetInstance()->save1.datavec[2] = 0;

		Save::GetInstance()->save1.dotto = CHeight_Map::GetInstance()->vData;



		Save::GetInstance()->Savevin("assets/assets.dat", Save::GetInstance()->save1);
		CHeight_Map::GetInstance()->mapsave = false;
	}
	if (CHeight_Map::GetInstance()->mapload)
	{
		Save::GetInstance()->save1 = Save::GetInstance()->Loadvin("assets/assets.dat");
		auto map = Save::GetInstance()->save1.dotto;
	
		g_heightmap->LoadMap(map);
		CHeight_Map::GetInstance()->mapload = false;
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
 

void Ground::GetPlayerHeight(Player& player)
{
	//高さを求める
	col = g_heightmap->GetHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling));//プレイヤーが画像のどこにいて、その足元のカラー情報

	//少し前の高さをだす
	gocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x/ scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z/ scaling),
		player.angley.x*10.0f, player.angley.y*10.0f);

	nowcol = gocol;

	//数フレームに一度、角度を変更
	if (player.groundcnt == 0)
	{
		//左前方の高さを出す
		lgocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
			player.lv_angle.x * 10.0f, player.lv_angle.y * 10.0f);
		//右前方の高さを出す
		rgocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
			player.rv_angle.x * 10.0f, player.rv_angle.y * 10.0f);
		
		bgocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
			player.rv_angle.x * 10.0f, player.rv_angle.y * 10.0f);


		if (gocol > lgocol)
		{
			nowcol = lgocol;//きたい方向の高さを設定しなおし
			player.angle.y += 1.0f;//角度を変更
			float rad = player.angle.y* (3.1415926535 / 180.0f);
			player.velocity.x = -sinf(rad);
			player.velocity.y = -cosf(rad);
			//ベクトル保存
			player.angley.x = player.velocity.x;
			player.angley.y = player.velocity.y;
		}
		if (gocol > rgocol)
		{
			nowcol = rgocol;
			player.angle.y -= 1.f;
			float rad = player.angle.y * (3.1415926535 / 180.0f);
			player.velocity.x = -sinf(rad);
			player.velocity.y = -cosf(rad);
			//ベクトル保存
			player.angley.x = player.velocity.x;
			player.angley.y = player.velocity.y;
		}
	}

	//100分の一だけ高さをずらす
	float cccol = LeapID<double>(gocol, nowcol, 0.01f);

	defcol = cccol - col;

	//高さによってスピードを変更する
	float time = (CHeight_Map::GetInstance()->g_hight) * 0.002f;
	if (time > 1.0f)time = 1.0f;
	defcol = LeapID<double>(0.0, defcol, time);//(CHeight_Map::GetInstance()->g_hight + 100) * 0.01f;


	//player.angley.x = player.velocity.x;
	//player.angley.y = player.velocity.y;
	
	/*player.velocity.x = player.angley.x;
	player.velocity.y = player.angley.y;*/

	//高さの差を出すための底辺を算出
	float teihen = sqrtf((player.velocity.x * 10.0f * player.velocity.x * 10.0f) + (player.velocity.y * 10.0f * player.velocity.y * 10.0f));

	//高さを元に角度を出す
	goangle = GetAtan(teihen, defcol*90.0f);

	{	
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::Begin("col");

	ImGui::SetNextWindowSize(ImVec2(300, 400));
	float cccol = col;
	float goocol = gocol;
	float posx = player.GetPos().x / scaling + (GetWidthHeight() / 2);
	float posy = GetWidthHeight() / 2 - player.GetPos().z / scaling;
	float posxx = player.GetPos().x / scaling + (GetWidthHeight() / 2) + player.angley.x * 10.0f;
	float posyy = GetWidthHeight() / 2 - player.GetPos().z / scaling - player.angley.y * 10.0f;
	ImGui::DragFloat("col", &cccol);
	ImGui::DragFloat("gocol", &goocol);
	ImGui::DragFloat("anglex", &player.angley.x);
	ImGui::DragFloat("angley", &player.angley.y);
	ImGui::DragFloat("posx", &posx);
	ImGui::DragFloat("posy", &posy);
	ImGui::DragFloat("posxx", &posxx);
	ImGui::DragFloat("posyy", &posyy);
	ImGui::DragFloat("goangle", &goangle);
	ImGui::DragFloat("accel", &player.boid_accel);

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	}

	if (player.groundcnt == 0)
	{
		if (goangle >= 0)
		{
			player.boid_accel *= cos(3.14 * goangle / 180);
			if (player.follow == Player::Follow::PLAYER)
			{
				player.boid_accel = TexSpeed(player.boid_accel);
			}
		}
		if (goangle < 0)
		{
			goangle = abs(goangle);
			player.boid_accel *= 1 + sin(3.14 * goangle / 180);
			if (player.follow == Player::Follow::PLAYER)
			{
				player.boid_accel = TexSpeed(player.boid_accel);
			}
		}
	}
	
	player.groundcnt++;
	if (player.groundcnt > 3)
	{
		player.groundcnt = 0;
	}

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

float Ground::TexSpeed(float boid_accel)
{


	int texcol = CHeight_Map::GetInstance()->g_col;
	int t_blendone = CHeight_Map::GetInstance()->blendone;
	int t_blendtwo = CHeight_Map::GetInstance()->blendtwo;

	float texoneblend = (1.0f - col) - (1.0f * t_blendone * 0.01f);
	float textwoblend = col - (1.0f * t_blendtwo * 0.01f);

	//float accel = 0.7 * (1 - texoneblend) + 1.8 * texoneblend;

	float onetexspeed = 1.0f;
	float twotexspeed = 1.0f;
	float theretexspeed =1.0f;

	
	if (texcol >= 1)
	{
		switch (CHeight_Map::GetInstance()->onetex)
		{
		case 1:
		{
			onetexspeed = 1.5f;
			break;
		}
		case 2:
		{
			onetexspeed = 0.9f;
			break;
		}
		case 3:
		{
			onetexspeed = 0.5f;
			break;
		}
		break;
		}
		
	}
	if (texcol >= 2)
	{

		switch (CHeight_Map::GetInstance()->twotex)
		{
		case 1:
		{
			twotexspeed = 1.5f;
			break;
		}
		case 2:
		{
			twotexspeed = 0.9f;
			break;
		}
		case 3:
		{
			twotexspeed = 0.5f;
			break;
		}
		break;
		}
		
	}
	if (texcol >= 3)
	{
		switch (CHeight_Map::GetInstance()->twotex)
		{
		case 1:
		{
			theretexspeed = 1.5f;
			break;
		}
		case 2:
		{
			theretexspeed = 0.9f;
			break;
		}
		case 3:
		{
			theretexspeed = 0.5f;
			break;
		}
		break;
		}
	}
	
	
	float accel = onetexspeed * (1 - texoneblend) + twotexspeed * texoneblend;
	accel = accel* (1 - textwoblend) + theretexspeed * textwoblend;

	////this->boid_accel

	return accel*boid_accel;

}
		

XMFLOAT3 Ground::GetPos()
{
	return m_pos;
}

float Ground::GetWidthHeight()
{
	return CHeight_Map::GetInstance()->iPixSize;
}

