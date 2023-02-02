#include "ground.h"
#include"CDirectInput.h"
#include<iostream>
#include"PlayerMgr.h"
#include"player.h"
#include"Seiha.h"
//go 元の座標値
//to　行先の座標値
//ratio　現在の進行割合　0.0f～1.0f
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



std::vector<std::vector<double>> lmap;

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

	//if (CDirectInput::GetInstance().CheckKeyBufferTrigger(DIK_9))
	//{
	//	auto map = g_heightmap->GetMap();
	//	map[250].at(250) = 0.99f;
	//	g_heightmap->LoadMap(map);
	//	//g_heightmap->updateVertex(XMFLOAT3(1.0f, 0.5f, 1.0f));
	//	//g_heightmap->updateVbuffer();
	//	//g_heightmap->Draw();
	//}

	if (Seiha::pertime == 1.0f)
	{
		lmap = CHeight_Map::GetInstance()->CreateOnly();
		

	}
	if (Seiha::pertime >= 0.0f)
	{
		g_heightmap->BlendMap(lmap);
	}
}
 

void Ground::GetPlayerHeight(Player& player)
{
	//高さを求める
	col = g_heightmap->GetHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling));//プレイヤーが画像のどこにいて、その足元のカラー情報

	player.SetPos(XMFLOAT3(player.GetPos().x, col * CHeight_Map::GetInstance()->g_hight, player.GetPos().z));//プレイヤーのｙの高さを変えてる

}
Pvector Ground::DownBoid(Player& player)
{

	gocol = 0.0;

	//少し前の高さをだす
	gocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
		player.angley.x * 7.0f, player.angley.y * 7.0f);
	gocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
		player.angley.x * 14.0f, player.angley.y * 14.0f);
	gocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
		player.angley.x * 21.0f, player.angley.y * 21.0f);

	gocol /= 3.0f;

	nowcol = gocol;

	if (player.follow == Player::Follow::HYUMAN)
	{
		//数フレームに一度、角度を変更
		if (anglecnt == 0)
		{
			lgocol = 0.0;

			//左前方の高さを出す
			lgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.left_vec.x * 7.0f, player.left_vec.y * 7.0f);
			lgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.left_vec.x * 14.0f, player.left_vec.y * 14.0f);
			lgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.left_vec.x * 21.0f, player.left_vec.y * 21.0f);

			lgocol /= 3.0f;

			rgocol = 0.0;
			//右前方の高さを出す
			rgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.right_vec.x * 7.0f, player.right_vec.y * 7.0f);
			rgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.right_vec.x * 14.0f, player.right_vec.y * 14.0f);
			rgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.right_vec.x * 21.0f, player.right_vec.y * 21.0f);

			rgocol /= 3.0f;

			bgocol = 0.0;

			bgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.opposite_vec.x * 7.0f, player.opposite_vec.y * 7.0f);
			bgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.opposite_vec.x * 14.0f, player.opposite_vec.y * 14.0f);
			bgocol += CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
				player.opposite_vec.x * 21.0f, player.opposite_vec.y * 21.0f);

			bgocol /= 3.0;

			if (nowcol > rgocol)
			{
				angle_direction = Angle_Direction::Right;
			}
			else if (nowcol > lgocol)
			{
				angle_direction = Angle_Direction::Left;
			}


			if (nowcol > bgocol)
			{
				if (lgocol > rgocol)
				{
					angle_direction = Angle_Direction::Right;
				}
				else
				{
					angle_direction = Angle_Direction::Left;
				}

			}

		}

		if (anglechangecnt == 0)
		{
			if (angle_direction == Angle_Direction::Left)
			{
				nowcol = lgocol;//きたい方向の高さを設定しなおし
				float anglescale = CHeight_Map::GetInstance()->g_hight;
				anglescale /= 100;
				anglescale *= 0.4f;
				float angle = player.angle.y += anglescale;//角度を変更
				float rad = angle * (3.1415926535 / 180.0f);
				Pvector returnvec;
				returnvec.x = cosf(rad);
				returnvec.y = sinf(rad);
		
				return returnvec;
			}
			if (angle_direction == Angle_Direction::Right)
			{
				nowcol = rgocol;
				float anglescale = CHeight_Map::GetInstance()->g_hight;
				anglescale /= 100;
				anglescale *= 0.4f;
				float angle = player.angle.y -= anglescale;
				float rad = angle * (3.1415926535 / 180.0f);
				Pvector returnvec;
				returnvec.x = cosf(rad);
				returnvec.y = sinf(rad);

				return returnvec;
			}
		}
	}

	anglecnt++;
	//	if (anglecnt > 40)
	{
		anglecnt = 0;
	}
	anglechangecnt++;
	//	if (anglechangecnt >2)
	{
		anglechangecnt = 0;
	}

}
float Ground::AccelBoid(Player& player)
{
	col = g_heightmap->GetHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling));//プレイヤーが画像のどこにいて、その足元のカラー情報


	gocol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
		player.velocity.x * 10.0f, player.velocity.y * 10.0f);


	nowcol = gocol;

	//nowcol = CHeight_Map::GetInstance()->GetGoHeightColor(XMFLOAT2(player.GetPos().x / scaling + (GetWidthHeight() / 2), (GetWidthHeight() / 2) - player.GetPos().z / scaling),
	//	player.angley.x * 10.0f, player.angley.y * 10.0f);

	defcol = nowcol - col;

	//高さによってスピードを変更する
	float time = (CHeight_Map::GetInstance()->g_hight) * 0.002f;
	if (time > 1.0f)time = 1.0f;
	defcol = LeapID<double>(0.0, defcol, time);//(CHeight_Map::GetInstance()->g_hight + 100) * 0.01f;



	//高さの差を出すための底辺を算出
	float teihen = sqrtf((player.velocity.x * 10.0f * player.velocity.x * 10.0f) + (player.velocity.y * 10.0f * player.velocity.y * 10.0f));

	//高さを元に角度を出す
	goangle = GetAtan(teihen, defcol * 90.0f);


	float boid_accel = player.boid_accel;

	if (player.groundcnt == 0)
	{
		if (goangle >= 0)
		{
			boid_accel *= cos(3.14 * goangle / 180);
			if (player.follow == Player::Follow::HYUMAN)
			{
				if (Player::GetInstance()->texspeedflg)
				{
					boid_accel = TexSpeed(boid_accel);
				}
			}
		}
		if (goangle < 0)
		{
			goangle = abs(goangle);
			boid_accel *= 1 + sin(3.14 * goangle / 180);
			if (player.follow == Player::Follow::HYUMAN)
			{
				if (Player::GetInstance()->texspeedflg)
				{
					boid_accel = TexSpeed(boid_accel);
				}
			}
		}
	}

	player.groundcnt++;
	if (player.groundcnt > 5)
	{
		player.groundcnt = 0;
	}


	return boid_accel;
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

