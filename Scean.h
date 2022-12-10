#pragma once
#include<vector>
#include"ground.h"
#include"ModelMgr.h"
#include"XIController.h"
#include"CDirectInput.h"
#include"CTexMgr.h"

class Scean
{
public:
	Scean() = default;
	virtual ~Scean() = default;
	virtual void Initialize();
	virtual void Update(uint64_t dt);
	virtual void Release();
	virtual bool IsAbleChangeScean();
	virtual void Draw();
	static Scean* GetInstance() {
		static Scean instance;
		return &instance;
	}

	enum class CGID
	{
		NOTES,
		NOTES_TOP,
		NOTES_BOT,
		TITLE,
		CLEAR,
		SPACE,
		NOTES_MID,
		HEIGHT,
		NOTES_FRAME,
		NOTES_SHORT,
		NOTES_LONG,
		CIRCLE,
		MAX

	};
	enum class BCGID
	{
		HPBER,
		EXPLSION,
		BLOOD,
		MAX

	};

	bool animemodelflg = false;

	struct CgDataList {
		CGID id;
		const char* cgname;
		const char* vsfilename;
		const char* psfilename;
	};
	struct BCgDataList {
		BCGID id;
		const char* cgname;
		const char* vsfilename;
		const char* psfilename;
	};
	std::vector<CgDataList> g_texlist = {
		{CGID::NOTES,"assets/notes/Plain_Notes.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::NOTES_TOP,"assets/UI/Notes_long_A1.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::NOTES_BOT,"assets/UI/Notes_long_A2.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::TITLE,"assets/UI/Title.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::CLEAR,"assets/UI/Clear.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::SPACE,"assets/UI/Space.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::NOTES_MID,"assets/UI/Note_between.jpg","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::HEIGHT,"assets/UI/Height.jpg","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::NOTES_FRAME,"assets/notes/Flame_UnderCoat.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::NOTES_SHORT,"assets/notes/Short_Notes.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::NOTES_LONG,"assets/notes/long_notes.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{CGID::CIRCLE,"assets/UI/circle.png","shader/vs.hlsl","shader/pstexcol.hlsl"}

		//{CGID::TiTLE,"assets/UI/Notes.png","shader/vs.hlsl","shader/pstexcol.hlsl"}
	};

	std::vector<BCgDataList> g_btexlist = {
		{BCGID::HPBER,"assets/UI/hp.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{BCGID::EXPLSION,"assets/effect/explsion.png","shader/vs.hlsl","shader/pstexcol.hlsl"},
		{BCGID::BLOOD,"assets/effect/blood.png","shader/vs.hlsl","shader/pstexcol.hlsl"}

		//{CGID::TiTLE,"assets/UI/Notes.png","shader/vs.hlsl","shader/pstexcol.hlsl"}
	};

	enum  class MODELID
	{
		ONE,
		PLAYER,
		SKYDOME,
		ENEMY,
		MISSILE,
		BOX,
		HYUMAN,
		
		HUMAN,
	};



	struct ModelDataList {
		MODELID  id;
		std::string modelname;
		std::string vsfilenamename;
		std::string psfilename;
		std::string texfoldername;
	};


	std::vector<ModelDataList>  g_modellist = {
		{MODELID::ONE,zonbie,"shader/vsoneskin.fx", "shader/ps.hlsl","assets/3danime/"},
		{MODELID::PLAYER,"assets/f1/f1.x","shader/vs.hlsl","shader/ps.hlsl","assets/f1/"},
		{MODELID::SKYDOME,"assets/skydome/skydome.x","shader/vs.hlsl","shader/ps.hlsl","assets/skydome/"},
		{MODELID::ENEMY,"assets/f1/f1.x","shader/vs.hlsl","shader/ps.hlsl","assets/f1/"},
		{MODELID::MISSILE,"assets/starwars/Shot.x","shader/vs.hlsl","shader/ps.hlsl","assets/starwars/"},
		{MODELID::BOX,"assets/dice/PlayerBox.x","shader/vs.hlsl","shader/ps.hlsl","assets/dice/"},
		{MODELID::HYUMAN,"assets/3danime/Ch21_nonPBR (3).fbx","shader/vsoneskin.fx", "shader/ps.fx","assets/3danime/"},
		//{MODELID::ONE,zonbie, "shader/vsoneskin.fx", "shader/ps.fx","assets/"},
		//{MODELID::HUMAN,"assets/dice/PlayerBox.x","shader/vs.hlsl","shader/ps.hlsl","assets/dice/"},

		//{MODELID::HUMAN,human, "shader/vsoneskin.fx", "shader/ps.fx","assets/"},
//		{MODELID::ONE,"assets/dice/PlayerBox.x","shader/vs.hlsl","shader/ps.hlsl","assets/dice/"},
	
	};


	enum  class MODELIID
	{
		PLAYER,
		
	};



	struct ModelDataInstanceList {
		MODELIID  id;
		int num;
		std::string modelname;
		std::string vsfilenamename;
		std::string psfilename;
		std::string texfoldername;
	};


	std::vector<ModelDataInstanceList>  g_modelinstancelist = {
		//{MODELIID::PLAYER,100,"assets/f1.x.dat","shader/vs.hlsl","shader/ps.hlsl","assets/3danime/"},
		{MODELIID::PLAYER,100,"assets/3danime/Warzombie F Pedroso.fbx","shader/vsinstance.fx", "shader/ps.fx","assets/3danime/Ch21_1001_Diffuse.png"},
	//{MODELID::ONE,zonbie, "shader/vsoneskin.fx", "shader/ps.fx","assets/"},
		//{MODELID::HUMAN,"assets/dice/PlayerBox.x","shader/vs.hlsl","shader/ps.hlsl","assets/dice/"},

		//{MODELID::HUMAN,human, "shader/vsoneskin.fx", "shader/ps.fx","assets/"},
//		{MODELID::ONE,"assets/dice/PlayerBox.x","shader/vs.hlsl","shader/ps.hlsl","assets/dice/"},

	};




	Ground g_ground;//地形

	XMFLOAT4X4 g_mtxplayer;		// 主人公の行列
	
};