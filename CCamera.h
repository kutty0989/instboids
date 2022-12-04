#include	<directxmath.h>
#include	"Memory.h"
#include<iostream>
#include"dx11mathutil.h"
#include"Application.h"
#define debuglog(a) std::cout<<a<<std::endl;


using namespace DirectX;

class CCamera{
	CCamera(){
	}
public:
	static bool blowflg;
	float max_camera = 0;
	float cameracnt = 0;

	CCamera(const CCamera&) = delete;
	CCamera& operator=(const CCamera&) = delete;
	CCamera(CCamera&&) = delete;
	CCamera& operator=(CCamera&&) = delete;

	static CCamera* GetInstance(){
		static CCamera instance;
		return &instance;
	}

	void Init(float nearclip, float farclip, float fov, 
		float width, float height,
		XMFLOAT3 eye, XMFLOAT3 lookat, XMFLOAT3 up){

		SetProjection(nearclip,farclip,fov,width,height);
		SetCamera(eye,lookat,up);
	}
	void Update(const XMFLOAT4X4 mtx)
	{
		XMFLOAT3 Position;
		XMFLOAT3 AxisY;
		XMFLOAT3 AxisZ;

		Position.x = mtx._41;
		Position.y = mtx._42;
		Position.z = mtx._43;



		AxisY.x = mtx._21;
		AxisY.y = mtx._22;
		AxisY.z = mtx._23;

		AxisZ.x = mtx._31;
		AxisZ.y = mtx._32;
		AxisZ.z = mtx._33;

		sts = CCamera::STATE::TPS_CAMERA;

		switch (sts)
		{
		case CCamera::STATE::FPS_CAMERA:
		{
			FPSCamera(Position,AxisY,AxisZ);
			break;
		}
		case CCamera::STATE::TPS_CAMERA:
		{
			TPSCamera(Position, AxisY, AxisZ);
			break;
		}
		//case CCamera::STATE::FIXED_CAMERA:
		//{
		//	FixedCamera();
		//	break;
		//}
		//case CCamera::STATE::DELAY_CAMERA:
		//{
		//	DelayCamera();
		//	break;
		//}
		case CCamera::STATE::TOP_CAMERA:
		{
			TopCamera(Position, AxisY, AxisZ);
			break;
		}
		}
	}

	void SetNear(float nearclip){
		m_near = nearclip;
	}

	void SetFar(float farclip){
		m_far = farclip;
	}

	void SetFov(float fov){
		m_Fov = fov;
	}

	void SetAspect(float width,float height){
		m_Aspect = width/height;
	}

	void SetProjection(float nearclip,float farclip,float fov,float width,float height){
		SetNear(nearclip);
		SetFar(farclip);
		m_far = farclip;
		m_near = nearclip;
		SetFov(fov);
		SetAspect(width,height);
		CreateProjectionMatrix();
	}
		
	void SetCamera(const XMFLOAT3& eye, const XMFLOAT3& lookat, const XMFLOAT3& up){

		SetEye(eye);
		SetLookat(lookat);
		SetUp(up);
		CreateCameraMatrix();
	}

	void SetEye(const XMFLOAT3& eye){
		m_Eye = eye;
	}

	void SetLookat(const XMFLOAT3& lookat){
		m_Lookat = lookat;
	}

	void SetUp(const XMFLOAT3& up){
		m_Up = up;
	}

	void SetEyeTargetPos(const XMFLOAT3& eye)
	{
		m_EyeTagetPos = eye;
	}

	void CreateCameraMatrix(){
		ALIGN16 XMVECTOR Eye = XMVectorSet(m_Eye.x, m_Eye.y, m_Eye.z, 0.0f);
		ALIGN16 XMVECTOR At = XMVectorSet(m_Lookat.x, m_Lookat.y, m_Lookat.z, 0.0f);
		ALIGN16 XMVECTOR Up = XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 0.0f);

		ALIGN16 XMMATRIX camera;
		camera = XMMatrixLookAtLH(Eye, At, Up);
		
		CreateViewMatrix();
		XMStoreFloat4x4(&m_Camera, camera);
	}

	void CreateProjectionMatrix(){

		ALIGN16 XMMATRIX projection;
	//	projection = XMMatrixOrthographicLH(Application::CLIENT_WIDTH,Application::CLIENT_HEIGHT, m_near, m_far);
		projection = XMMatrixPerspectiveFovLH(m_Fov, m_Aspect, m_near, m_far);
		XMStoreFloat4x4(&m_Projection, projection);
	}
	void CreateViewMatrix() {
		
	}

	const XMFLOAT4X4 GetCameraMatrix(){
		return m_Camera;
	}

	 XMFLOAT4X4& GetProjectionMatrix(){
		return m_Projection;
	}
	XMFLOAT4X4& GetViewMatrix() {
		return m_Camera;
	}


	float GetFov() const {
		return m_Fov;
	}

	const XMFLOAT3& GetEye() const {
		return m_Eye;
	}

	const XMFLOAT3& GetLookat() const {
		return m_Lookat;
	}

	const XMFLOAT3& GetUp() const {
		return m_Up;
	}
	const float& GetFar() const {
		return m_far;
	}
	const float& GetNear() const {
		return m_near;
	}
	const XMFLOAT3& GetRight() const {
		return  XMFLOAT3(m_Camera._11, m_Camera._21, m_Camera._31);
	}
	const XMFLOAT3& GetFoward() const {
		return XMFLOAT3(m_Camera._31, m_Camera._32, m_Camera._33);
	}


private:
	enum class STATE {
		TPS_CAMERA,
		FPS_CAMERA,
		DELAY_CAMERA,
		FIXED_CAMERA,
		TOP_CAMERA
	};

	STATE sts;



	XMFLOAT4X4		m_Projection;

	XMFLOAT4X4		m_Camera;
	XMFLOAT4X4		m_View;

	XMFLOAT3		m_Eye;				// カメラ位置
	XMFLOAT3		m_Lookat;			// 注視点
	XMFLOAT3		m_Up;				// 上向きベクトル

	float			m_near;
	float			m_Aspect;
	float			m_Fov;
	float			m_far;

	XMFLOAT3 m_EyeTagetPos = { 0.0f,0.0f,0.0f };



	void FPSCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy);
	void TPSCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy);
	void TopCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy);
	//void DelayCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy);
	void FixedCamera(XMFLOAT3 pos, XMFLOAT3 axisz, XMFLOAT3 axisy);

};


