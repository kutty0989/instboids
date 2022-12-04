//
//
////Global Declarations - Interfaces//
//IDXGISwapChain* SwapChain;
//ID3D11Device* d3d11Device;
//ID3D11DeviceContext* d3d11DevCon;
//ID3D11RenderTargetView* renderTargetView;
//ID3D11DepthStencilView* depthStencilView;
//ID3D11Texture2D* depthStencilBuffer;
//ID3D11VertexShader* VS;
//ID3D11PixelShader* PS;
//ID3D11PixelShader* D2D_PS;
//ID3D10Blob* D2D_PS_Buffer;
//ID3D10Blob* VS_Buffer;
//ID3D10Blob* PS_Buffer;
//ID3D11InputLayout* vertLayout;
//ID3D11Buffer* cbPerObjectBuffer;
//ID3D11BlendState* d2dTransparency;
//ID3D11RasterizerState* CCWcullMode;
//ID3D11RasterizerState* CWcullMode;
//ID3D11SamplerState* CubesTexSamplerState;
//ID3D11Buffer* cbPerFrameBuffer;
//
//ID3D10Device1* d3d101Device;
//IDXGIKeyedMutex* keyedMutex11;
//IDXGIKeyedMutex* keyedMutex10;
//ID2D1RenderTarget* D2DRenderTarget;
//ID2D1SolidColorBrush* Brush;
//ID3D11Texture2D* BackBuffer11;
//ID3D11Texture2D* sharedTex11;
//ID3D11Buffer* d2dVertBuffer;
//ID3D11Buffer* d2dIndexBuffer;
//ID3D11ShaderResourceView* d2dTexture;
//IDWriteFactory* DWriteFactory;
//IDWriteTextFormat* TextFormat;
//
//IDirectInputDevice8* DIKeyboard;
//IDirectInputDevice8* DIMouse;
//
//ID3D11Buffer* sphereIndexBuffer;
//ID3D11Buffer* sphereVertBuffer;
//
//ID3D11VertexShader* SKYMAP_VS;
//ID3D11PixelShader* SKYMAP_PS;
//ID3D10Blob* SKYMAP_VS_Buffer;
//ID3D10Blob* SKYMAP_PS_Buffer;
//
//ID3D11ShaderResourceView* smrv;
//
//ID3D11DepthStencilState* DSLessEqual;
//ID3D11RasterizerState* RSCullNone;
//
//ID3D11BlendState* Transparency;
//ID3D11BlendState* leafTransparency;
////Mesh variables. Each loaded mesh will need its own set of these
//ID3D11Buffer* meshVertBuff;
//ID3D11Buffer* meshIndexBuff;
//XMMATRIX meshWorld;
//int meshSubsets = 0;
//std::vector<int> meshSubsetIndexStart;
//std::vector<int> meshSubsetTexture;
//
////Textures and material variables, used for all mesh's loaded
//std::vector<ID3D11ShaderResourceView*> meshSRV;
//std::vector<std::wstring> textureNameArray;
//
//std::wstring printText;
//
////Global Declarations - Others//
//LPCTSTR WndClassName = L"firstwindow";
//HWND hwnd = NULL;
//HRESULT hr;
//
//int Width = 800;
//int Height = 600;
//
//DIMOUSESTATE mouseLastState;
//LPDIRECTINPUT8 DirectInput;
//
//float rotx = 0;
//float rotz = 0;
//float scaleX = 1.0f;
//float scaleY = 1.0f;
//
//XMMATRIX Rotationx;
//XMMATRIX Rotationz;
//XMMATRIX Rotationy;
//
//XMMATRIX WVP;
//XMMATRIX camView;
//XMMATRIX camProjection;
//XMMATRIX d2dWorld;
//
//XMVECTOR camPosition;
//XMVECTOR camTarget;
//XMVECTOR camUp;
//XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//
//XMVECTOR currCharDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//XMVECTOR oldCharDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//XMVECTOR charPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f); // Setting this global in case it can be used somewhere else in the app
//
//float charCamDist = 15.0f; // This is the distance between the camera and the character
//
//XMMATRIX camRotationMatrix;
//
//float moveLeftRight = 0.0f;
//float moveBackForward = 0.0f;
//
//float camYaw = 0.0f;
//float camPitch = 0.0f;
//
//int NumSphereVertices;
//int NumSphereFaces;
//
//XMMATRIX sphereWorld;
//
//XMMATRIX Rotation;
//XMMATRIX Scale;
//XMMATRIX Translation;
//
//float rot = 0.01f;
//
//double countsPerSecond = 0.0;
//__int64 CounterStart = 0;
//
//int frameCount = 0;
//int fps = 0;
//
//__int64 frameTimeOld = 0;
//double frameTime;
//
////Function Prototypes//
//bool InitializeDirect3d11App(HINSTANCE hInstance);
//void CleanUp();
//bool InitScene();
//void DrawScene();
//bool InitD2D_D3D101_DWrite(IDXGIAdapter1* Adapter);
//void InitD2DScreenTexture();
//void UpdateScene(double time);
//
//void UpdateCamera();
//
//void RenderText(std::wstring text, int inInt);
//
//void StartTimer();
//double GetTime();
//double GetFrameTime();
//
//bool InitializeWindow(HINSTANCE hInstance,
//    int ShowWnd,
//    int width, int height,
//    bool windowed);
//int messageloop();
//
//bool InitDirectInput(HINSTANCE hInstance);
//void DetectInput(double time);
//
//void CreateSphere(int LatLines, int LongLines);
//
//LRESULT CALLBACK WndProc(HWND hWnd,
//    UINT msg,
//    WPARAM wParam,
//    LPARAM lParam);
//
////Create effects constant buffer's structure//
//struct cbPerObject
//{
//    XMMATRIX  WVP;
//    XMMATRIX World;
//
//    //These will be used for the pixel shader
//    XMFLOAT4 difColor;
//    BOOL hasTexture;
//    //Because of HLSL structure packing, we will use windows BOOL
//    //instead of bool because HLSL packs things into 4 bytes, and
//    //bool is only one byte, where BOOL is 4 bytes
//    BOOL hasNormMap;
//
//    /************************************New Stuff****************************************************/
//    // Usually you will want to create a separate vertex shader for instanced geometry, however
//    // to keep things simple, i use the same vertex shader we have been using, but instead only
//    // apply the instance calculations if isInstance is set to true, and the leaf calculations
//    // if both isInstance and isLeaf are set to true
//    BOOL isInstance;
//    BOOL isLeaf;
//    /*************************************************************************************************/
//};
//cbPerObject cbPerObj;
//
///************************************New Stuff****************************************************/
//const int numLeavesPerTree = 1000;
//const int numTrees = 400;
//
//// This constant buffer is updated per scene. We will not be chaning the position of our leaves throughout
//// the scene, so we only need to send this to the gpu once, instead of every frame
//struct cbPerScene
//{
//    // Each tree gets 1000 leaves (numLeavesPerTree), so we create a matrix array of 1000 matrices that
//    // store the leaves position, orientation, and scale relative to the tree positions. All trees will
//    // have the same number of leaves, with the same position, orientation, and scale of each leaf.
//    XMMATRIX leafOnTree[numLeavesPerTree];
//};
//cbPerScene cbPerInst;
//ID3D11Buffer* cbPerInstanceBuffer;
//ID3D11InputLayout* leafVertLayout;
//
//// This is the data structure we will store in our instance buffer. It's very similar to the idea of
//// the vertex structure, where we create a layout for the vertex structure, we also need to create
//// the layout for the instance buffer (they are created together as a single layout). We will only
//// store the position of our trees in this instance structure, but this is where you would add
//// other things like color, rotations, matrices, whatever
//struct InstanceData
//{
//    XMFLOAT3 pos;
//};
//
//// leaf data (leaves are drawn as quads)
//ID3D11ShaderResourceView* leafTexture;
//ID3D11Buffer* quadVertBuffer;
//ID3D11Buffer* quadIndexBuffer;
//
//// Tree data (loaded from an obj file)
//ID3D11Buffer* treeInstanceBuff;
//ID3D11Buffer* treeVertBuff;
//ID3D11Buffer* treeIndexBuff;
//int treeSubsets = 0;
//std::vector<int> treeSubsetIndexStart;
//std::vector<int> treeSubsetTexture;
//XMMATRIX treeWorld; // Our trees are instanced and their positions will be calculated in the
//// vertex shader. This world matrix will define their starting (base) position
//// orientation, and scale AFTER they are moved to their individual positions
//// in the vertex buffer. So if you were to rotate the trees using this world matrix
//// The effect would not be that they rotate on their own axis, but instead rotate (orbit)
//// around the worlds origin (0,0,0) from their individual positions defined in the instance buffer
//// Same goes for scaling, they will appear stretched if you were to do scaling with this world matrix
//// However, we can use this world matrix to change the position of all the trees (translation). We
//// keep it an identity matrix though, so that the entire group of trees are centered around the world origin
///*************************************************************************************************/
//
////Create material structure
//struct SurfaceMaterial
//{
//    std::wstring matName;
//    XMFLOAT4 difColor;
//    int texArrayIndex;
//    int normMapTexArrayIndex;
//    bool hasNormMap;
//    bool hasTexture;
//    bool transparent;
//};
//
//std::vector<SurfaceMaterial> material;
//
////Define LoadObjModel function after we create surfaceMaterial structure
//bool LoadObjModel(std::wstring filename,            //.obj filename
//    ID3D11Buffer** vertBuff,                    //mesh vertex buffer
//    ID3D11Buffer** indexBuff,                    //mesh index buffer
//    std::vector<int>& subsetIndexStart,            //start index of each subset
//    std::vector<int>& subsetMaterialArray,        //index value of material for each subset
//    std::vector<SurfaceMaterial>& material,        //vector of material structures
//    int& subsetCount,                            //Number of subsets in mesh
//    bool isRHCoordSys,                            //true if model was created in right hand coord system
//    bool computeNormals);                        //true to compute the normals, false to use the files normals
//
//struct Light
//{
//    Light()
//    {
//        ZeroMemory(this, sizeof(Light));
//    }
//    XMFLOAT3 pos;
//    float range;
//    XMFLOAT3 dir;
//    float cone;
//    XMFLOAT3 att;
//    float pad2;
//    XMFLOAT4 ambient;
//    XMFLOAT4 diffuse;
//};
//
//Light light;
//
//struct cbPerFrame
//{
//    Light  light;
//};
//
//cbPerFrame constbuffPerFrame;
//
//struct Vertex    //Overloaded Vertex Structure
//{
//    Vertex() {}
//    Vertex(float x, float y, float z,
//        float u, float v,
//        float nx, float ny, float nz,
//        float tx, float ty, float tz)
//        : pos(x, y, z), texCoord(u, v), normal(nx, ny, nz),
//        tangent(tx, ty, tz) {}
//
//    XMFLOAT3 pos;
//    XMFLOAT2 texCoord;
//    XMFLOAT3 normal;
//    XMFLOAT3 tangent;
//    XMFLOAT3 biTangent;
//
//    // Will not be sent to shader
//    int StartWeight;
//    int WeightCount;
//};
//
//D3D11_INPUT_ELEMENT_DESC layout[] =
//{
//    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//    { "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
//    { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
//    /************************************New Stuff****************************************************/
//    // Instance elements
//    // last parameter (InstanceDataStepRate) is one because we will "step" to the next instance element (INSTANCEPOS) after drawing 1 instance (tree)
//    { "INSTANCEPOS", 0, DXGI_FORMAT_R32G32B32_FLOAT,    1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1}
//    /*************************************************************************************************/
//};
//UINT numElements = ARRAYSIZE(layout);
//
//
///*************************************************************************************************/
//
//struct Joint
//{
//    std::wstring name;
//    int parentID;
//
//    XMFLOAT3 pos;
//    XMFLOAT4 orientation;
//};
//
//
//struct BoundingBox
//{
//    XMFLOAT3 min;
//    XMFLOAT3 max;
//};
//
//struct FrameData
//{
//    int frameID;
//    std::vector<float> frameData;
//};
//struct AnimJointInfo
//{
//    std::wstring name;
//    int parentID;
//
//    int flags;
//    int startIndex;
//};
//
//struct ModelAnimation
//{
//    int numFrames;
//    int numJoints;
//    int frameRate;
//    int numAnimatedComponents;
//
//    float frameTime;
//    float totalAnimTime;
//    float currAnimTime;
//
//    std::vector<AnimJointInfo> jointInfo;
//    std::vector<BoundingBox> frameBounds;
//    std::vector<Joint>    baseFrameJoints;
//    std::vector<FrameData>    frameData;
//    std::vector<std::vector<Joint>> frameSkeleton;
//};
//
//
//struct Weight
//{
//    int jointID;
//    float bias;
//    XMFLOAT3 pos;
//
//    XMFLOAT3 normal;
//
//};
//
//struct ModelSubset
//{
//    int texArrayIndex;
//    int numTriangles;
//
//    std::vector<Vertex> vertices;
//    std::vector<XMFLOAT3> jointSpaceNormals;
//    std::vector<DWORD> indices;
//    std::vector<Weight> weights;
//
//    std::vector<XMFLOAT3> positions;
//
//    ID3D11Buffer* vertBuff;
//    ID3D11Buffer* indexBuff;
//};
//
//struct Model3D
//{
//    int numSubsets;
//    int numJoints;
//
//    std::vector<Joint> joints;
//    std::vector<ModelSubset> subsets;
//
//
//    std::vector<ModelAnimation> animations;
//
//};
//
//XMMATRIX playerCharWorld;
//Model3D NewMD5Model;
//
////LoadMD5Model() function prototype
//bool LoadMD5Model(std::wstring filename,
//    Model3D& MD5Model,
//    std::vector<ID3D11ShaderResourceView*>& shaderResourceViewArray,
//    std::vector<std::wstring> texFileNameArray);
//
//
//bool LoadMD5Anim(std::wstring filename, Model3D& MD5Model);
//
//void UpdateMD5Model(Model3D& MD5Model, float deltaTime, int animation);
//
//
//int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
//    HINSTANCE hPrevInstance,
//    LPSTR lpCmdLine,
//    int nShowCmd)
//{
//
//    if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
//    {
//        MessageBox(0, L"Window Initialization - Failed",
//            L"Error", MB_OK);
//        return 0;
//    }
//
//    if (!InitializeDirect3d11App(hInstance))    //Initialize Direct3D
//    {
//        MessageBox(0, L"Direct3D Initialization - Failed",
//            L"Error", MB_OK);
//        return 0;
//    }
//
//
//    if (!InitScene())    //Initialize our scene
//    {
//        MessageBox(0, L"Scene Initialization - Failed",
//            L"Error", MB_OK);
//        return 0;
//    }
//
//    if (!InitDirectInput(hInstance))
//    {
//        MessageBox(0, L"Direct Input Initialization - Failed",
//            L"Error", MB_OK);
//        return 0;
//    }
//
//    messageloop();
//
//    CleanUp();
//
//    return 0;
//}
//
//bool InitializeWindow(HINSTANCE hInstance,
//    int ShowWnd,
//    int width, int height,
//    bool windowed)
//{
//    typedef struct _WNDCLASS {
//        UINT cbSize;
//        UINT style;
//        WNDPROC lpfnWndProc;
//        int cbClsExtra;
//        int cbWndExtra;
//        HANDLE hInstance;
//        HICON hIcon;
//        HCURSOR hCursor;
//        HBRUSH hbrBackground;
//        LPCTSTR lpszMenuName;
//        LPCTSTR lpszClassName;
//    } WNDCLASS;
//
//    WNDCLASSEX wc;
//
//    wc.cbSize = sizeof(WNDCLASSEX);
//    wc.style = CS_HREDRAW | CS_VREDRAW;
//    wc.lpfnWndProc = WndProc;
//    wc.cbClsExtra = NULL;
//    wc.cbWndExtra = NULL;
//    wc.hInstance = hInstance;
//    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//    wc.lpszMenuName = NULL;
//    wc.lpszClassName = WndClassName;
//    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//    if (!RegisterClassEx(&wc))
//    {
//        MessageBox(NULL, L"Error registering class",
//            L"Error", MB_OK | MB_ICONERROR);
//        return 1;
//    }
//
//    hwnd = CreateWindowEx(
//        NULL,
//        WndClassName,
//        L"Lesson 32 - Instancing",
//        WS_OVERLAPPEDWINDOW,
//        CW_USEDEFAULT, CW_USEDEFAULT,
//        width, height,
//        NULL,
//        NULL,
//        hInstance,
//        NULL
//    );
//
//    if (!hwnd)
//    {
//        MessageBox(NULL, L"Error creating window",
//            L"Error", MB_OK | MB_ICONERROR);
//        return 1;
//    }
//
//    ShowWindow(hwnd, ShowWnd);
//    UpdateWindow(hwnd);
//
//    return true;
//}
//
//bool InitializeDirect3d11App(HINSTANCE hInstance)
//{
//    //Describe our SwapChain Buffer
//    DXGI_MODE_DESC bufferDesc;
//
//    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
//
//    bufferDesc.Width = Width;
//    bufferDesc.Height = Height;
//    bufferDesc.RefreshRate.Numerator = 60;
//    bufferDesc.RefreshRate.Denominator = 1;
//    bufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//
//    //Describe our SwapChain
//    DXGI_SWAP_CHAIN_DESC swapChainDesc;
//
//    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
//
//    swapChainDesc.BufferDesc = bufferDesc;
//    swapChainDesc.SampleDesc.Count = 1;
//    swapChainDesc.SampleDesc.Quality = 0;
//    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    swapChainDesc.BufferCount = 1;
//    swapChainDesc.OutputWindow = hwnd;
//    ///////////////**************Fullscreen/Windowed**************////////////////////
//    swapChainDesc.Windowed = true;
//    ///////////////**************Fullscreen/Windowed**************////////////////////
//    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//
//    // Create DXGI factory to enumerate adapters///////////////////////////////////////////////////////////////////////////
//    IDXGIFactory1* DXGIFactory;
//
//    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&DXGIFactory);
//
//    // Use the first adapter    
//    IDXGIAdapter1* Adapter;
//
//    hr = DXGIFactory->EnumAdapters1(0, &Adapter);
//
//    DXGIFactory->Release();
//
//    //Create our Direct3D 11 Device and SwapChain//////////////////////////////////////////////////////////////////////////
//    hr = D3D11CreateDeviceAndSwapChain(Adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
//        NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);
//
//    //Initialize Direct2D, Direct3D 10.1, DirectWrite
//    InitD2D_D3D101_DWrite(Adapter);
//
//    //Release the Adapter interface
//    Adapter->Release();
//
//    //Create our BackBuffer and Render Target
//    hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer11);
//    hr = d3d11Device->CreateRenderTargetView(BackBuffer11, NULL, &renderTargetView);
//
//    //Describe our Depth/Stencil Buffer
//    D3D11_TEXTURE2D_DESC depthStencilDesc;
//
//    depthStencilDesc.Width = Width;
//    depthStencilDesc.Height = Height;
//    depthStencilDesc.MipLevels = 1;
//    depthStencilDesc.ArraySize = 1;
//    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//    depthStencilDesc.SampleDesc.Count = 1;
//    depthStencilDesc.SampleDesc.Quality = 0;
//    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
//    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//    depthStencilDesc.CPUAccessFlags = 0;
//    depthStencilDesc.MiscFlags = 0;
//
//    //Create the Depth/Stencil View
//    d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
//    d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
//
//    return true;
//}
//
//bool InitD2D_D3D101_DWrite(IDXGIAdapter1* Adapter)
//{
//    //Create our Direc3D 10.1 Device///////////////////////////////////////////////////////////////////////////////////////
//    hr = D3D10CreateDevice1(Adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_BGRA_SUPPORT,
//        D3D10_FEATURE_LEVEL_9_3, D3D10_1_SDK_VERSION, &d3d101Device);
//
//    //Create Shared Texture that Direct3D 10.1 will render on//////////////////////////////////////////////////////////////
//    D3D11_TEXTURE2D_DESC sharedTexDesc;
//
//    ZeroMemory(&sharedTexDesc, sizeof(sharedTexDesc));
//
//    sharedTexDesc.Width = Width;
//    sharedTexDesc.Height = Height;
//    sharedTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//    sharedTexDesc.MipLevels = 1;
//    sharedTexDesc.ArraySize = 1;
//    sharedTexDesc.SampleDesc.Count = 1;
//    sharedTexDesc.Usage = D3D11_USAGE_DEFAULT;
//    sharedTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
//    sharedTexDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
//
//    hr = d3d11Device->CreateTexture2D(&sharedTexDesc, NULL, &sharedTex11);
//
//    // Get the keyed mutex for the shared texture (for D3D11)///////////////////////////////////////////////////////////////
//    hr = sharedTex11->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&keyedMutex11);
//
//    // Get the shared handle needed to open the shared texture in D3D10.1///////////////////////////////////////////////////
//    IDXGIResource* sharedResource10;
//    HANDLE sharedHandle10;
//
//    hr = sharedTex11->QueryInterface(__uuidof(IDXGIResource), (void**)&sharedResource10);
//
//    hr = sharedResource10->GetSharedHandle(&sharedHandle10);
//
//    sharedResource10->Release();
//
//    // Open the surface for the shared texture in D3D10.1///////////////////////////////////////////////////////////////////
//    IDXGISurface1* sharedSurface10;
//
//    hr = d3d101Device->OpenSharedResource(sharedHandle10, __uuidof(IDXGISurface1), (void**)(&sharedSurface10));
//
//    hr = sharedSurface10->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&keyedMutex10);
//
//    // Create D2D factory///////////////////////////////////////////////////////////////////////////////////////////////////
//    ID2D1Factory* D2DFactory;
//    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void**)&D2DFactory);
//
//    D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;
//
//    ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));
//
//    renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
//    renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
//
//    hr = D2DFactory->CreateDxgiSurfaceRenderTarget(sharedSurface10, &renderTargetProperties, &D2DRenderTarget);
//
//    sharedSurface10->Release();
//    D2DFactory->Release();
//
//    // Create a solid color brush to draw something with        
//    hr = D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &Brush);
//
//    //DirectWrite///////////////////////////////////////////////////////////////////////////////////////////////////////////
//    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
//        reinterpret_cast<IUnknown**>(&DWriteFactory));
//
//    hr = DWriteFactory->CreateTextFormat(
//        L"Script",
//        NULL,
//        DWRITE_FONT_WEIGHT_REGULAR,
//        DWRITE_FONT_STYLE_NORMAL,
//        DWRITE_FONT_STRETCH_NORMAL,
//        24.0f,
//        L"en-us",
//        &TextFormat
//    );
//
//    hr = TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
//    hr = TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
//
//    d3d101Device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
//    return true;
//}
//
//bool InitDirectInput(HINSTANCE hInstance)
//{
//    hr = DirectInput8Create(hInstance,
//        DIRECTINPUT_VERSION,
//        IID_IDirectInput8,
//        (void**)&DirectInput,
//        NULL);
//
//    hr = DirectInput->CreateDevice(GUID_SysKeyboard,
//        &DIKeyboard,
//        NULL);
//
//    hr = DirectInput->CreateDevice(GUID_SysMouse,
//        &DIMouse,
//        NULL);
//
//    hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
//    hr = DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//
//    hr = DIMouse->SetDataFormat(&c_dfDIMouse);
//    hr = DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
//
//    return true;
//}
//
//void MoveChar(double time, XMVECTOR& destinationDirection, XMMATRIX& worldMatrix)
//{
//    // Normalize our destinated direction vector
//    destinationDirection = XMVector3Normalize(destinationDirection);
//
//    // If character is currently facing the complete opposite direction as the desired direction
//    // they will turn around VERY slowly, so we want to make sure they turn around at a normal speed
//    // by making the old character direction not the exact opposite direction as the current character
//    // position. Try commenting out the next two lines to see what i'm talking about
//    if (XMVectorGetX(XMVector3Dot(destinationDirection, oldCharDirection)) == -1)
//        oldCharDirection += XMVectorSet(0.02f, 0.0f, -0.02f, 0.0f);
//
//    // Get our current characters position in the world, from it's world matrix
//    charPosition = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//    charPosition = XMVector3TransformCoord(charPosition, worldMatrix);
//
//    // Rotate our character smoothly when changing direction (from the GPG series)
//    float destDirLength = 10.0f * frameTime;        // Change to the speed you want your character to rotate. This uses the game timer from an earlier lesson
//    // The larget this value, the faster the character rotates
//    currCharDirection = (oldCharDirection)+(destinationDirection * destDirLength);    // Get the characters direction (based off time, old position, and desired
//    // direction), by adding together the current direction and the old direction
//    // to get vector that smoothly turns from oldCharDir to denstinationDirection
//    currCharDirection = XMVector3Normalize(currCharDirection);        // Normalize the characters current direction vector
//
//    // Here we find the angle of our character (angle between current direction and world's normal vector), used so that we can actually rotate
//    // our characters world matrix. The three lines below, together, find the angle between 0 PI and 2 PI (360 degrees, and technically, it returns
//    // the degrees in radians from -1 PI to 1 PI, but that has the same effect as 0 PI to 2 PI) between two vectors.
//    // XMVector3AngleBetweenNormals returns an angle between two vectors, but always a positive result between
//    // 0 and 1 PI. Which means, it doesn't tell us which half of the 2 PI degrees that are possible. So, we have the next if statement below,
//    // which crosses the current characters direction and the worlds forward (0,0,1), which should give us the y axis vector (assuming that our character
//    // rotates on the xz plane). We check to see if the y vector is positive ( > 0.0f), and if it is, we set the characters direction angle to be
//    // the opposite of what it currently is, giving us the result in -1 PI to 1 PI.
//    float charDirAngle = XMVectorGetX(XMVector3AngleBetweenNormals(XMVector3Normalize(currCharDirection), XMVector3Normalize(DefaultForward)));
//    if (XMVectorGetY(XMVector3Cross(currCharDirection, DefaultForward)) > 0.0f)
//        charDirAngle = -charDirAngle;
//
//    // Now we update our characters position based off the frame time, his old position, and the direction he is facing
//    float speed = 15.0f * frameTime;
//    charPosition = charPosition + (destinationDirection * speed);
//
//    // Update characters world matrix
//    XMMATRIX rotationMatrix;
//    Scale = XMMatrixScaling(0.25f, 0.25f, 0.25f);
//    Translation = XMMatrixTranslation(XMVectorGetX(charPosition), 0.0f, XMVectorGetZ(charPosition));
//    rotationMatrix = XMMatrixRotationY(charDirAngle - 3.14159265f);        // Subtract PI from angle so the character doesn't run backwards
//
//    worldMatrix = Scale * rotationMatrix * Translation;
//
//    // Set the characters old direction
//    oldCharDirection = currCharDirection;
//
//    // Update our animation
//    float timeFactor = 1.0f;    // You can speed up or slow down time by changing this
//    UpdateMD5Model(NewMD5Model, time * timeFactor, 0);
//}
//
//void UpdateCamera()
//{
//    // Rotate target around camera
//    /*camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
//    camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix );
//    camTarget = XMVector3Normalize(camTarget);*/
//
//    /*XMMATRIX RotateYTempMatrix;
//    RotateYTempMatrix = XMMatrixRotationY(camYaw);
//
//    // Walk
//    camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
//    camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);
//    camUp = XMVector3Cross(camForward, camRight);*/
//
//    /*// Free Cam
//    camRight = XMVector3TransformCoord(DefaultRight, camRotationMatrix);
//    camForward = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
//    camUp = XMVector3Cross(camForward, camRight);*/
//
//    /*camPosition += moveLeftRight*camRight;
//    camPosition += moveBackForward*camForward;
//
//    moveLeftRight = 0.0f;
//    moveBackForward = 0.0f;
//
//    camTarget = camPosition + camTarget;*/
//
//    // Third Person Camera
//    // Set the cameras target to be looking at the character.
//    camTarget = charPosition;
//
//    // This line is because this lessons model was set to stand on the point (0,0,0) (my bad), and we
//    // don't want to just be looking at the models feet, so we move the camera's target vector up 5 units
//    camTarget = XMVectorSetY(camTarget, XMVectorGetY(camTarget) + 5.0f);
//
//    // Unlike before, when we rotated the cameras target vector around the cameras position,
//    // we are now rotating the cameras position around it's target (which is the character)
//    // Rotate camera around target
//    camRotationMatrix = XMMatrixRotationRollPitchYaw(-camPitch, camYaw, 0);
//    camPosition = XMVector3TransformNormal(DefaultForward, camRotationMatrix);
//    camPosition = XMVector3Normalize(camPosition);
//
//    // Set our cameras position to rotate around the character. We need to add 5 to the characters
//    // position's y axis because i'm stupid and modeled the character in the 3d modeling program
//    // to be "standing" on (0,0,0), instead of centered around it ;) Well target her head here though
//    camPosition = (camPosition * charCamDist) + camTarget;
//
//    // We need to set our cameras forward and right vectors to lay
//    // in the worlds xz plane, since they are the vectors we will
//    // be using to determine the direction our character is running
//    camForward = XMVector3Normalize(camTarget - camPosition);    // Get forward vector based on target
//    camForward = XMVectorSetY(camForward, 0.0f);    // set forwards y component to 0 so it lays only on
//    // the xz plane
//    camForward = XMVector3Normalize(camForward);
//    // To get our camera's Right vector, we set it's x component to the negative z component from the
//    // camera's forward vector, and the z component to the camera forwards x component
//    camRight = XMVectorSet(-XMVectorGetZ(camForward), 0.0f, XMVectorGetX(camForward), 0.0f);
//
//    // Our camera does not "roll", so we can safely assume that the cameras right vector is always
//    // in the xz plane, so to get the up vector, we just get the normalized vector from the camera
//    // position to the cameras target, and cross it with the camera's Right vector
//    camUp = XMVector3Normalize(XMVector3Cross(XMVector3Normalize(camPosition - camTarget), camRight));
//
//    camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
//}
//
//void DetectInput(double time)
//{
//    DIMOUSESTATE mouseCurrState;
//
//    BYTE keyboardState[256];
//
//    DIKeyboard->Acquire();
//    DIMouse->Acquire();
//
//    DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
//
//    DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
//
//    if (keyboardState[DIK_ESCAPE] & 0x80)
//        PostMessage(hwnd, WM_DESTROY, 0, 0);
//
//    float speed = 10.0f * time;
//    bool moveChar = false;
//    XMVECTOR desiredCharDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//
//    if (keyboardState[DIK_A] & 0x80)
//    {
//        desiredCharDir += (camRight);
//        moveChar = true;
//    }
//    if (keyboardState[DIK_D] & 0x80)
//    {
//        desiredCharDir += -(camRight);
//        moveChar = true;
//    }
//    if (keyboardState[DIK_W] & 0x80)
//    {
//        desiredCharDir += (camForward);
//        moveChar = true;
//    }
//    if (keyboardState[DIK_S] & 0x80)
//    {
//        desiredCharDir += -(camForward);
//        moveChar = true;
//    }
//    if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
//    {
//        camYaw += mouseLastState.lX * 0.002f;
//
//        camPitch += mouseCurrState.lY * 0.002f;
//        // Check that the camera doesn't go over the top or under the player
//        if (camPitch > 0.85f)
//            camPitch = 0.85f;
//        if (camPitch < -0.85f)
//            camPitch = -0.85f;
//
//        mouseLastState = mouseCurrState;
//    }
//
//    if (moveChar == true)
//        MoveChar(time, desiredCharDir, playerCharWorld);
//
//    UpdateCamera();
//
//    return;
//}
//
//void CleanUp()
//{
//    SwapChain->SetFullscreenState(false, NULL);
//    PostMessage(hwnd, WM_DESTROY, 0, 0);
//
//    //Release the COM Objects we created
//    SwapChain->Release();
//    d3d11Device->Release();
//    d3d11DevCon->Release();
//    renderTargetView->Release();
//    VS->Release();
//    PS->Release();
//    VS_Buffer->Release();
//    PS_Buffer->Release();
//    vertLayout->Release();
//    depthStencilView->Release();
//    depthStencilBuffer->Release();
//    cbPerObjectBuffer->Release();
//    Transparency->Release();
//    CCWcullMode->Release();
//    CWcullMode->Release();
//
//    d3d101Device->Release();
//    keyedMutex11->Release();
//    keyedMutex10->Release();
//    D2DRenderTarget->Release();
//    Brush->Release();
//    BackBuffer11->Release();
//    sharedTex11->Release();
//    DWriteFactory->Release();
//    TextFormat->Release();
//    d2dTexture->Release();
//
//    cbPerFrameBuffer->Release();
//
//    DIKeyboard->Unacquire();
//    DIMouse->Unacquire();
//    DirectInput->Release();
//
//    sphereIndexBuffer->Release();
//    sphereVertBuffer->Release();
//
//    SKYMAP_VS->Release();
//    SKYMAP_PS->Release();
//    SKYMAP_VS_Buffer->Release();
//    SKYMAP_PS_Buffer->Release();
//
//    smrv->Release();
//
//    DSLessEqual->Release();
//    RSCullNone->Release();
//
//    meshVertBuff->Release();
//    meshIndexBuff->Release();
//
//    for (int i = 0; i < NewMD5Model.numSubsets; i++)
//    {
//        NewMD5Model.subsets[i].indexBuff->Release();
//        NewMD5Model.subsets[i].vertBuff->Release();
//    }
//}
//
//
//bool LoadMD5Anim(std::wstring filename, Model3D& MD5Model)
//{
//    ModelAnimation tempAnim;                        // Temp animation to later store in our model's animation array
//
//    std::wifstream fileIn(filename.c_str());        // Open file
//
//    std::wstring checkString;                        // Stores the next string from our file
//
//    if (fileIn)                                        // Check if the file was opened
//    {
//        while (fileIn)                                // Loop until the end of the file is reached
//        {
//            fileIn >> checkString;                    // Get next string from file
//
//            if (checkString == L"MD5Version")        // Get MD5 version (this function supports version 10)
//            {
//                fileIn >> checkString;
//                /*MessageBox(0, checkString.c_str(),    //display message
//                L"MD5Version", MB_OK);*/
//            }
//            else if (checkString == L"commandline")
//            {
//                std::getline(fileIn, checkString);    // Ignore the rest of this line
//            }
//            else if (checkString == L"numFrames")
//            {
//                fileIn >> tempAnim.numFrames;                // Store number of frames in this animation
//            }
//            else if (checkString == L"numJoints")
//            {
//                fileIn >> tempAnim.numJoints;                // Store number of joints (must match .md5mesh)
//            }
//            else if (checkString == L"frameRate")
//            {
//                fileIn >> tempAnim.frameRate;                // Store animation's frame rate (frames per second)
//            }
//            else if (checkString == L"numAnimatedComponents")
//            {
//                fileIn >> tempAnim.numAnimatedComponents;    // Number of components in each frame section
//            }
//            else if (checkString == L"hierarchy")
//            {
//                fileIn >> checkString;                // Skip opening bracket "{"
//
//                for (int i = 0; i < tempAnim.numJoints; i++)    // Load in each joint
//                {
//                    AnimJointInfo tempJoint;
//
//                    fileIn >> tempJoint.name;        // Get joints name
//                    // Sometimes the names might contain spaces. If that is the case, we need to continue
//                    // to read the name until we get to the closing " (quotation marks)
//                    if (tempJoint.name[tempJoint.name.size() - 1] != '"')
//                    {
//                        wchar_t checkChar;
//                        bool jointNameFound = false;
//                        while (!jointNameFound)
//                        {
//                            checkChar = fileIn.get();
//
//                            if (checkChar == '"')
//                                jointNameFound = true;
//
//                            tempJoint.name += checkChar;
//                        }
//                    }
//
//                    // Remove the quotation marks from joints name
//                    tempJoint.name.erase(0, 1);
//                    tempJoint.name.erase(tempJoint.name.size() - 1, 1);
//
//                    fileIn >> tempJoint.parentID;            // Get joints parent ID
//                    fileIn >> tempJoint.flags;                // Get flags
//                    fileIn >> tempJoint.startIndex;            // Get joints start index
//
//                    // Make sure the joint exists in the model, and the parent ID's match up
//                    // because the bind pose (md5mesh) joint hierarchy and the animations (md5anim)
//                    // joint hierarchy must match up
//                    bool jointMatchFound = false;
//                    for (int k = 0; k < MD5Model.numJoints; k++)
//                    {
//                        if (MD5Model.joints[k].name == tempJoint.name)
//                        {
//                            if (MD5Model.joints[k].parentID == tempJoint.parentID)
//                            {
//                                jointMatchFound = true;
//                                tempAnim.jointInfo.push_back(tempJoint);
//                            }
//                        }
//                    }
//                    if (!jointMatchFound)                    // If the skeleton system does not match up, return false
//                        return false;                        // You might want to add an error message here
//
//                    std::getline(fileIn, checkString);        // Skip rest of this line
//                }
//            }
//            else if (checkString == L"bounds")            // Load in the AABB for each animation
//            {
//                fileIn >> checkString;                        // Skip opening bracket "{"
//
//                for (int i = 0; i < tempAnim.numFrames; i++)
//                {
//                    BoundingBox tempBB;
//
//                    fileIn >> checkString;                    // Skip "("
//                    fileIn >> tempBB.min.x >> tempBB.min.z >> tempBB.min.y;
//                    fileIn >> checkString >> checkString;    // Skip ") ("
//                    fileIn >> tempBB.max.x >> tempBB.max.z >> tempBB.max.y;
//                    fileIn >> checkString;                    // Skip ")"
//
//                    tempAnim.frameBounds.push_back(tempBB);
//                }
//            }
//            else if (checkString == L"baseframe")            // This is the default position for the animation
//            {                                                // All frames will build their skeletons off this
//                fileIn >> checkString;                        // Skip opening bracket "{"
//
//                for (int i = 0; i < tempAnim.numJoints; i++)
//                {
//                    Joint tempBFJ;
//
//                    fileIn >> checkString;                        // Skip "("
//                    fileIn >> tempBFJ.pos.x >> tempBFJ.pos.z >> tempBFJ.pos.y;
//                    fileIn >> checkString >> checkString;        // Skip ") ("
//                    fileIn >> tempBFJ.orientation.x >> tempBFJ.orientation.z >> tempBFJ.orientation.y;
//                    fileIn >> checkString;                        // Skip ")"
//
//                    tempAnim.baseFrameJoints.push_back(tempBFJ);
//                }
//            }
//            else if (checkString == L"frame")        // Load in each frames skeleton (the parts of each joint that changed from the base frame)
//            {
//                FrameData tempFrame;
//
//                fileIn >> tempFrame.frameID;        // Get the frame ID
//
//                fileIn >> checkString;                // Skip opening bracket "{"
//
//                for (int i = 0; i < tempAnim.numAnimatedComponents; i++)
//                {
//                    float tempData;
//                    fileIn >> tempData;                // Get the data
//
//                    tempFrame.frameData.push_back(tempData);
//                }
//
//                tempAnim.frameData.push_back(tempFrame);
//
//                ///*** build the frame skeleton ***///
//                std::vector<Joint> tempSkeleton;
//
//                for (int i = 0; i < tempAnim.jointInfo.size(); i++)
//                {
//                    int k = 0;                        // Keep track of position in frameData array
//
//                    // Start the frames joint with the base frame's joint
//                    Joint tempFrameJoint = tempAnim.baseFrameJoints[i];
//
//                    tempFrameJoint.parentID = tempAnim.jointInfo[i].parentID;
//
//                    // Notice how I have been flipping y and z. this is because some modeling programs such as
//                    // 3ds max (which is what I use) use a right handed coordinate system. Because of this, we
//                    // need to flip the y and z axes. If your having problems loading some models, it's possible
//                    // the model was created in a left hand coordinate system. in that case, just reflip all the
//                    // y and z axes in our md5 mesh and anim loader.
//                    if (tempAnim.jointInfo[i].flags & 1)        // pos.x    ( 000001 )
//                        tempFrameJoint.pos.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];
//
//                    if (tempAnim.jointInfo[i].flags & 2)        // pos.y    ( 000010 )
//                        tempFrameJoint.pos.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];
//
//                    if (tempAnim.jointInfo[i].flags & 4)        // pos.z    ( 000100 )
//                        tempFrameJoint.pos.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];
//
//                    if (tempAnim.jointInfo[i].flags & 8)        // orientation.x    ( 001000 )
//                        tempFrameJoint.orientation.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];
//
//                    if (tempAnim.jointInfo[i].flags & 16)    // orientation.y    ( 010000 )
//                        tempFrameJoint.orientation.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];
//
//                    if (tempAnim.jointInfo[i].flags & 32)    // orientation.z    ( 100000 )
//                        tempFrameJoint.orientation.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];
//
//
//                    // Compute the quaternions w
//                    float t = 1.0f - (tempFrameJoint.orientation.x * tempFrameJoint.orientation.x)
//                        - (tempFrameJoint.orientation.y * tempFrameJoint.orientation.y)
//                        - (tempFrameJoint.orientation.z * tempFrameJoint.orientation.z);
//                    if (t < 0.0f)
//                    {
//                        tempFrameJoint.orientation.w = 0.0f;
//                    }
//                    else
//                    {
//                        tempFrameJoint.orientation.w = -sqrtf(t);
//                    }
//
//                    // Now, if the upper arm of your skeleton moves, you need to also move the lower part of your arm, and then the hands, and then finally the fingers (possibly weapon or tool too)
//                    // This is where joint hierarchy comes in. We start at the top of the hierarchy, and move down to each joints child, rotating and translating them based on their parents rotation
//                    // and translation. We can assume that by the time we get to the child, the parent has already been rotated and transformed based of it's parent. We can assume this because
//                    // the child should never come before the parent in the files we loaded in.
//                    if (tempFrameJoint.parentID >= 0)
//                    {
//                        Joint parentJoint = tempSkeleton[tempFrameJoint.parentID];
//
//                        // Turn the XMFLOAT3 and 4's into vectors for easier computation
//                        XMVECTOR parentJointOrientation = XMVectorSet(parentJoint.orientation.x, parentJoint.orientation.y, parentJoint.orientation.z, parentJoint.orientation.w);
//                        XMVECTOR tempJointPos = XMVectorSet(tempFrameJoint.pos.x, tempFrameJoint.pos.y, tempFrameJoint.pos.z, 0.0f);
//                        XMVECTOR parentOrientationConjugate = XMVectorSet(-parentJoint.orientation.x, -parentJoint.orientation.y, -parentJoint.orientation.z, parentJoint.orientation.w);
//
//                        // Calculate current joints position relative to its parents position
//                        XMFLOAT3 rotatedPos;
//                        XMStoreFloat3(&rotatedPos, XMQuaternionMultiply(XMQuaternionMultiply(parentJointOrientation, tempJointPos), parentOrientationConjugate));
//
//                        // Translate the joint to model space by adding the parent joint's pos to it
//                        tempFrameJoint.pos.x = rotatedPos.x + parentJoint.pos.x;
//                        tempFrameJoint.pos.y = rotatedPos.y + parentJoint.pos.y;
//                        tempFrameJoint.pos.z = rotatedPos.z + parentJoint.pos.z;
//
//                        // Currently the joint is oriented in its parent joints space, we now need to orient it in
//                        // model space by multiplying the two orientations together (parentOrientation * childOrientation) <- In that order
//                        XMVECTOR tempJointOrient = XMVectorSet(tempFrameJoint.orientation.x, tempFrameJoint.orientation.y, tempFrameJoint.orientation.z, tempFrameJoint.orientation.w);
//                        tempJointOrient = XMQuaternionMultiply(parentJointOrientation, tempJointOrient);
//
//                        // Normalize the orienation quaternion
//                        tempJointOrient = XMQuaternionNormalize(tempJointOrient);
//
//                        XMStoreFloat4(&tempFrameJoint.orientation, tempJointOrient);
//                    }
//
//                    // Store the joint into our temporary frame skeleton
//                    tempSkeleton.push_back(tempFrameJoint);
//                }
//
//                // Push back our newly created frame skeleton into the animation's frameSkeleton array
//                tempAnim.frameSkeleton.push_back(tempSkeleton);
//
//                fileIn >> checkString;                // Skip closing bracket "}"
//            }
//        }
//
//        // Calculate and store some usefull animation data
//        tempAnim.frameTime = 1.0f / tempAnim.frameRate;                        // Set the time per frame
//        tempAnim.totalAnimTime = tempAnim.numFrames * tempAnim.frameTime;    // Set the total time the animation takes
//        tempAnim.currAnimTime = 0.0f;                                        // Set the current time to zero
//
//        MD5Model.animations.push_back(tempAnim);                            // Push back the animation into our model object
//    }
//    else    // If the file was not loaded
//    {
//        SwapChain->SetFullscreenState(false, NULL);    // Make sure we are out of fullscreen
//
//        // create message
//        std::wstring message = L"Could not open: ";
//        message += filename;
//
//        MessageBox(0, message.c_str(),                // display message
//            L"Error", MB_OK);
//
//        return false;
//    }
//    return true;
//}
//
//void UpdateMD5Model(Model3D& MD5Model, float deltaTime, int animation)
//{
//    MD5Model.animations[animation].currAnimTime += deltaTime;            // Update the current animation time
//
//    if (MD5Model.animations[animation].currAnimTime > MD5Model.animations[animation].totalAnimTime)
//        MD5Model.animations[animation].currAnimTime = 0.0f;
//
//    // Which frame are we on
//    float currentFrame = MD5Model.animations[animation].currAnimTime * MD5Model.animations[animation].frameRate;
//    int frame0 = floorf(currentFrame);
//    int frame1 = frame0 + 1;
//
//    // Make sure we don't go over the number of frames    
//    if (frame0 == MD5Model.animations[animation].numFrames - 1)
//        frame1 = 0;
//
//    float interpolation = currentFrame - frame0;    // Get the remainder (in time) between frame0 and frame1 to use as interpolation factor
//
//    std::vector<Joint> interpolatedSkeleton;        // Create a frame skeleton to store the interpolated skeletons in
//
//    // Compute the interpolated skeleton
//    for (int i = 0; i < MD5Model.animations[animation].numJoints; i++)
//    {
//        Joint tempJoint;
//        Joint joint0 = MD5Model.animations[animation].frameSkeleton[frame0][i];        // Get the i'th joint of frame0's skeleton
//        Joint joint1 = MD5Model.animations[animation].frameSkeleton[frame1][i];        // Get the i'th joint of frame1's skeleton
//
//        tempJoint.parentID = joint0.parentID;                                            // Set the tempJoints parent id
//
//        // Turn the two quaternions into XMVECTORs for easy computations
//        XMVECTOR joint0Orient = XMVectorSet(joint0.orientation.x, joint0.orientation.y, joint0.orientation.z, joint0.orientation.w);
//        XMVECTOR joint1Orient = XMVectorSet(joint1.orientation.x, joint1.orientation.y, joint1.orientation.z, joint1.orientation.w);
//
//        // Interpolate positions
//        tempJoint.pos.x = joint0.pos.x + (interpolation * (joint1.pos.x - joint0.pos.x));
//        tempJoint.pos.y = joint0.pos.y + (interpolation * (joint1.pos.y - joint0.pos.y));
//        tempJoint.pos.z = joint0.pos.z + (interpolation * (joint1.pos.z - joint0.pos.z));
//
//        // Interpolate orientations using spherical interpolation (Slerp)
//        XMStoreFloat4(&tempJoint.orientation, XMQuaternionSlerp(joint0Orient, joint1Orient, interpolation));
//
//        interpolatedSkeleton.push_back(tempJoint);        // Push the joint back into our interpolated skeleton
//    }
//
//    for (int k = 0; k < MD5Model.numSubsets; k++)
//    {
//        for (int i = 0; i < MD5Model.subsets[k].vertices.size(); ++i)
//        {
//            Vertex tempVert = MD5Model.subsets[k].vertices[i];
//            tempVert.pos = XMFLOAT3(0, 0, 0);    // Make sure the vertex's pos is cleared first
//            tempVert.normal = XMFLOAT3(0, 0, 0);    // Clear vertices normal
//
//            // Sum up the joints and weights information to get vertex's position and normal
//            for (int j = 0; j < tempVert.WeightCount; ++j)
//            {
//                Weight tempWeight = MD5Model.subsets[k].weights[tempVert.StartWeight + j];
//                Joint tempJoint = interpolatedSkeleton[tempWeight.jointID];
//
//                // Convert joint orientation and weight pos to vectors for easier computation
//                XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
//                XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);
//
//                // We will need to use the conjugate of the joint orientation quaternion
//                XMVECTOR tempJointOrientationConjugate = XMQuaternionInverse(tempJointOrientation);
//
//                // Calculate vertex position (in joint space, eg. rotate the point around (0,0,0)) for this weight using the joint orientation quaternion and its conjugate
//                // We can rotate a point using a quaternion with the equation "rotatedPoint = quaternion * point * quaternionConjugate"
//                XMFLOAT3 rotatedPoint;
//                XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));
//
//                // Now move the verices position from joint space (0,0,0) to the joints position in world space, taking the weights bias into account
//                tempVert.pos.x += (tempJoint.pos.x + rotatedPoint.x) * tempWeight.bias;
//                tempVert.pos.y += (tempJoint.pos.y + rotatedPoint.y) * tempWeight.bias;
//                tempVert.pos.z += (tempJoint.pos.z + rotatedPoint.z) * tempWeight.bias;
//
//                // Compute the normals for this frames skeleton using the weight normals from before
//                // We can comput the normals the same way we compute the vertices position, only we don't have to translate them (just rotate)
//                XMVECTOR tempWeightNormal = XMVectorSet(tempWeight.normal.x, tempWeight.normal.y, tempWeight.normal.z, 0.0f);
//
//                // Rotate the normal
//                XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightNormal), tempJointOrientationConjugate));
//
//                // Add to vertices normal and ake weight bias into account
//                tempVert.normal.x -= rotatedPoint.x * tempWeight.bias;
//                tempVert.normal.y -= rotatedPoint.y * tempWeight.bias;
//                tempVert.normal.z -= rotatedPoint.z * tempWeight.bias;
//            }
//
//            MD5Model.subsets[k].positions[i] = tempVert.pos;                // Store the vertices position in the position vector instead of straight into the vertex vector
//            MD5Model.subsets[k].vertices[i].normal = tempVert.normal;        // Store the vertices normal
//            XMStoreFloat3(&MD5Model.subsets[k].vertices[i].normal, XMVector3Normalize(XMLoadFloat3(&MD5Model.subsets[k].vertices[i].normal)));
//        }
//
//        // Put the positions into the vertices for this subset
//        for (int i = 0; i < MD5Model.subsets[k].vertices.size(); i++)
//        {
//            MD5Model.subsets[k].vertices[i].pos = MD5Model.subsets[k].positions[i];
//        }
//
//        // Update the subsets vertex buffer
//        // First lock the buffer
//        D3D11_MAPPED_SUBRESOURCE mappedVertBuff;
//        hr = d3d11DevCon->Map(MD5Model.subsets[k].vertBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertBuff);
//
//        // Copy the data into the vertex buffer.
//        memcpy(mappedVertBuff.pData, &MD5Model.subsets[k].vertices[0], (sizeof(Vertex) * MD5Model.subsets[k].vertices.size()));
//
//        d3d11DevCon->Unmap(MD5Model.subsets[k].vertBuff, 0);
//
//        // The line below is another way to update a buffer. You will use this when you want to update a buffer less
//        // than once per frame, since the GPU reads will be faster (the buffer was created as a DEFAULT buffer instead
//        // of a DYNAMIC buffer), and the CPU writes will be slower. You can try both methods to find out which one is faster
//        // for you. if you want to use the line below, you will have to create the buffer with D3D11_USAGE_DEFAULT instead
//        // of D3D11_USAGE_DYNAMIC
//        //d3d11DevCon->UpdateSubresource( MD5Model.subsets[k].vertBuff, 0, NULL, &MD5Model.subsets[k].vertices[0], 0, 0 );
//    }
//}
//
//
//bool LoadMD5Model(std::wstring filename,
//    Model3D& MD5Model,
//    std::vector<ID3D11ShaderResourceView*>& shaderResourceViewArray,
//    std::vector<std::wstring> texFileNameArray)
//{
//    std::wifstream fileIn(filename.c_str());        // Open file
//
//    std::wstring checkString;                        // Stores the next string from our file
//
//    if (fileIn)                                        // Check if the file was opened
//    {
//        while (fileIn)                                // Loop until the end of the file is reached
//        {
//            fileIn >> checkString;                    // Get next string from file
//
//            if (checkString == L"MD5Version")        // Get MD5 version (this function supports version 10)
//            {
//                /*fileIn >> checkString;
//                MessageBox(0, checkString.c_str(),    //display message
//                L"MD5Version", MB_OK);*/
//            }
//            else if (checkString == L"commandline")
//            {
//                std::getline(fileIn, checkString);    // Ignore the rest of this line
//            }
//            else if (checkString == L"numJoints")
//            {
//                fileIn >> MD5Model.numJoints;        // Store number of joints
//            }
//            else if (checkString == L"numMeshes")
//            {
//                fileIn >> MD5Model.numSubsets;        // Store number of meshes or subsets which we will call them
//            }
//            else if (checkString == L"joints")
//            {
//                Joint tempJoint;
//
//                fileIn >> checkString;                // Skip the "{"
//
//                for (int i = 0; i < MD5Model.numJoints; i++)
//                {
//                    fileIn >> tempJoint.name;        // Store joints name
//                    // Sometimes the names might contain spaces. If that is the case, we need to continue
//                    // to read the name until we get to the closing " (quotation marks)
//                    if (tempJoint.name[tempJoint.name.size() - 1] != '"')
//                    {
//                        wchar_t checkChar;
//                        bool jointNameFound = false;
//                        while (!jointNameFound)
//                        {
//                            checkChar = fileIn.get();
//
//                            if (checkChar == '"')
//                                jointNameFound = true;
//
//                            tempJoint.name += checkChar;
//                        }
//                    }
//
//                    fileIn >> tempJoint.parentID;    // Store Parent joint's ID
//
//                    fileIn >> checkString;            // Skip the "("
//
//                    // Store position of this joint (swap y and z axis if model was made in RH Coord Sys)
//                    fileIn >> tempJoint.pos.x >> tempJoint.pos.z >> tempJoint.pos.y;
//
//                    fileIn >> checkString >> checkString;    // Skip the ")" and "("
//
//                    // Store orientation of this joint
//                    fileIn >> tempJoint.orientation.x >> tempJoint.orientation.z >> tempJoint.orientation.y;
//
//                    // Remove the quotation marks from joints name
//                    tempJoint.name.erase(0, 1);
//                    tempJoint.name.erase(tempJoint.name.size() - 1, 1);
//
//                    // Compute the w axis of the quaternion (The MD5 model uses a 3D vector to describe the
//                    // direction the bone is facing. However, we need to turn this into a quaternion, and the way
//                    // quaternions work, is the xyz values describe the axis of rotation, while the w is a value
//                    // between 0 and 1 which describes the angle of rotation)
//                    float t = 1.0f - (tempJoint.orientation.x * tempJoint.orientation.x)
//                        - (tempJoint.orientation.y * tempJoint.orientation.y)
//                        - (tempJoint.orientation.z * tempJoint.orientation.z);
//                    if (t < 0.0f)
//                    {
//                        tempJoint.orientation.w = 0.0f;
//                    }
//                    else
//                    {
//                        tempJoint.orientation.w = -sqrtf(t);
//                    }
//
//                    std::getline(fileIn, checkString);        // Skip rest of this line
//
//                    MD5Model.joints.push_back(tempJoint);    // Store the joint into this models joint vector
//                }
//
//                fileIn >> checkString;                    // Skip the "}"
//            }
//            else if (checkString == L"mesh")
//            {
//                ModelSubset subset;
//                int numVerts, numTris, numWeights;
//
//                fileIn >> checkString;                    // Skip the "{"
//
//                fileIn >> checkString;
//                while (checkString != L"}")            // Read until '}'
//                {
//                    // In this lesson, for the sake of simplicity, we will assume a textures filename is givin here.
//                    // Usually though, the name of a material (stored in a material library. Think back to the lesson on
//                    // loading .obj files, where the material library was contained in the file .mtl) is givin. Let this
//                    // be an exercise to load the material from a material library such as obj's .mtl file, instead of
//                    // just the texture like we will do here.
//                    if (checkString == L"shader")        // Load the texture or material
//                    {
//                        std::wstring fileNamePath;
//                        fileIn >> fileNamePath;            // Get texture's filename
//
//                        // Take spaces into account if filename or material name has a space in it
//                        if (fileNamePath[fileNamePath.size() - 1] != '"')
//                        {
//                            wchar_t checkChar;
//                            bool fileNameFound = false;
//                            while (!fileNameFound)
//                            {
//                                checkChar = fileIn.get();
//
//                                if (checkChar == '"')
//                                    fileNameFound = true;
//
//                                fileNamePath += checkChar;
//                            }
//                        }
//
//                        // Remove the quotation marks from texture path
//                        fileNamePath.erase(0, 1);
//                        fileNamePath.erase(fileNamePath.size() - 1, 1);
//
//                        //check if this texture has already been loaded
//                        bool alreadyLoaded = false;
//                        for (int i = 0; i < texFileNameArray.size(); ++i)
//                        {
//                            if (fileNamePath == texFileNameArray[i])
//                            {
//                                alreadyLoaded = true;
//                                subset.texArrayIndex = i;
//                            }
//                        }
//
//                        //if the texture is not already loaded, load it now
//                        if (!alreadyLoaded)
//                        {
//                            ID3D11ShaderResourceView* tempMeshSRV;
//                            hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, fileNamePath.c_str(),
//                                NULL, NULL, &tempMeshSRV, NULL);
//                            if (SUCCEEDED(hr))
//                            {
//                                texFileNameArray.push_back(fileNamePath.c_str());
//                                subset.texArrayIndex = shaderResourceViewArray.size();
//                                shaderResourceViewArray.push_back(tempMeshSRV);
//                            }
//                            else
//                            {
//                                MessageBox(0, fileNamePath.c_str(),        //display message
//                                    L"Could Not Open:", MB_OK);
//                                return false;
//                            }
//                        }
//
//                        std::getline(fileIn, checkString);                // Skip rest of this line
//                    }
//                    else if (checkString == L"numverts")
//                    {
//                        fileIn >> numVerts;                                // Store number of vertices
//
//                        std::getline(fileIn, checkString);                // Skip rest of this line
//
//                        for (int i = 0; i < numVerts; i++)
//                        {
//                            Vertex tempVert;
//
//                            fileIn >> checkString                        // Skip "vert # ("
//                                >> checkString
//                                >> checkString;
//
//                            fileIn >> tempVert.texCoord.x                // Store tex coords
//                                >> tempVert.texCoord.y;
//
//                            fileIn >> checkString;                        // Skip ")"
//
//                            fileIn >> tempVert.StartWeight;                // Index of first weight this vert will be weighted to
//
//                            fileIn >> tempVert.WeightCount;                // Number of weights for this vertex
//
//                            std::getline(fileIn, checkString);            // Skip rest of this line
//
//                            subset.vertices.push_back(tempVert);        // Push back this vertex into subsets vertex vector
//                        }
//                    }
//                    else if (checkString == L"numtris")
//                    {
//                        fileIn >> numTris;
//                        subset.numTriangles = numTris;
//
//                        std::getline(fileIn, checkString);                // Skip rest of this line
//
//                        for (int i = 0; i < numTris; i++)                // Loop through each triangle
//                        {
//                            DWORD tempIndex;
//                            fileIn >> checkString;                        // Skip "tri"
//                            fileIn >> checkString;                        // Skip tri counter
//
//                            for (int k = 0; k < 3; k++)                    // Store the 3 indices
//                            {
//                                fileIn >> tempIndex;
//                                subset.indices.push_back(tempIndex);
//                            }
//
//                            std::getline(fileIn, checkString);            // Skip rest of this line
//                        }
//                    }
//                    else if (checkString == L"numweights")
//                    {
//                        fileIn >> numWeights;
//
//                        std::getline(fileIn, checkString);                // Skip rest of this line
//
//                        for (int i = 0; i < numWeights; i++)
//                        {
//                            Weight tempWeight;
//                            fileIn >> checkString >> checkString;        // Skip "weight #"
//
//                            fileIn >> tempWeight.jointID;                // Store weight's joint ID
//
//                            fileIn >> tempWeight.bias;                    // Store weight's influence over a vertex
//
//                            fileIn >> checkString;                        // Skip "("
//
//                            fileIn >> tempWeight.pos.x                    // Store weight's pos in joint's local space
//                                >> tempWeight.pos.z
//                                >> tempWeight.pos.y;
//
//                            std::getline(fileIn, checkString);            // Skip rest of this line
//
//                            subset.weights.push_back(tempWeight);        // Push back tempWeight into subsets Weight array
//                        }
//
//                    }
//                    else
//                        std::getline(fileIn, checkString);                // Skip anything else
//
//                    fileIn >> checkString;                                // Skip "}"
//                }
//
//                //*** find each vertex's position using the joints and weights ***//
//                for (int i = 0; i < subset.vertices.size(); ++i)
//                {
//                    Vertex tempVert = subset.vertices[i];
//                    tempVert.pos = XMFLOAT3(0, 0, 0);    // Make sure the vertex's pos is cleared first
//
//                    // Sum up the joints and weights information to get vertex's position
//                    for (int j = 0; j < tempVert.WeightCount; ++j)
//                    {
//                        Weight tempWeight = subset.weights[tempVert.StartWeight + j];
//                        Joint tempJoint = MD5Model.joints[tempWeight.jointID];
//
//                        // Convert joint orientation and weight pos to vectors for easier computation
//                        // When converting a 3d vector to a quaternion, you should put 0 for "w", and
//                        // When converting a quaternion to a 3d vector, you can just ignore the "w"
//                        XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
//                        XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);
//
//                        // We will need to use the conjugate of the joint orientation quaternion
//                        // To get the conjugate of a quaternion, all you have to do is inverse the x, y, and z
//                        XMVECTOR tempJointOrientationConjugate = XMVectorSet(-tempJoint.orientation.x, -tempJoint.orientation.y, -tempJoint.orientation.z, tempJoint.orientation.w);
//
//                        // Calculate vertex position (in joint space, eg. rotate the point around (0,0,0)) for this weight using the joint orientation quaternion and its conjugate
//                        // We can rotate a point using a quaternion with the equation "rotatedPoint = quaternion * point * quaternionConjugate"
//                        XMFLOAT3 rotatedPoint;
//                        XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));
//
//                        // Now move the verices position from joint space (0,0,0) to the joints position in world space, taking the weights bias into account
//                        // The weight bias is used because multiple weights might have an effect on the vertices final position. Each weight is attached to one joint.
//                        tempVert.pos.x += (tempJoint.pos.x + rotatedPoint.x) * tempWeight.bias;
//                        tempVert.pos.y += (tempJoint.pos.y + rotatedPoint.y) * tempWeight.bias;
//                        tempVert.pos.z += (tempJoint.pos.z + rotatedPoint.z) * tempWeight.bias;
//
//                        // Basically what has happened above, is we have taken the weights position relative to the joints position
//                        // we then rotate the weights position (so that the weight is actually being rotated around (0, 0, 0) in world space) using
//                        // the quaternion describing the joints rotation. We have stored this rotated point in rotatedPoint, which we then add to
//                        // the joints position (because we rotated the weight's position around (0,0,0) in world space, and now need to translate it
//                        // so that it appears to have been rotated around the joints position). Finally we multiply the answer with the weights bias,
//                        // or how much control the weight has over the final vertices position. All weight's bias effecting a single vertex's position
//                        // must add up to 1.
//                    }
//
//                    subset.positions.push_back(tempVert.pos);            // Store the vertices position in the position vector instead of straight into the vertex vector
//                    // since we can use the positions vector for certain things like collision detection or picking
//                    // without having to work with the entire vertex structure.
//                }
//
//                // Put the positions into the vertices for this subset
//                for (int i = 0; i < subset.vertices.size(); i++)
//                {
//                    subset.vertices[i].pos = subset.positions[i];
//                }
//
//                //*** Calculate vertex normals using normal averaging ***///
//                std::vector<XMFLOAT3> tempNormal;
//
//                //normalized and unnormalized normals
//                XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);
//
//                //Used to get vectors (sides) from the position of the verts
//                float vecX, vecY, vecZ;
//
//                //Two edges of our triangle
//                XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//                XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//
//                //Compute face normals
//                for (int i = 0; i < subset.numTriangles; ++i)
//                {
//                    //Get the vector describing one edge of our triangle (edge 0,2)
//                    vecX = subset.vertices[subset.indices[(i * 3)]].pos.x - subset.vertices[subset.indices[(i * 3) + 2]].pos.x;
//                    vecY = subset.vertices[subset.indices[(i * 3)]].pos.y - subset.vertices[subset.indices[(i * 3) + 2]].pos.y;
//                    vecZ = subset.vertices[subset.indices[(i * 3)]].pos.z - subset.vertices[subset.indices[(i * 3) + 2]].pos.z;
//                    edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our first edge
//
//                    //Get the vector describing another edge of our triangle (edge 2,1)
//                    vecX = subset.vertices[subset.indices[(i * 3) + 2]].pos.x - subset.vertices[subset.indices[(i * 3) + 1]].pos.x;
//                    vecY = subset.vertices[subset.indices[(i * 3) + 2]].pos.y - subset.vertices[subset.indices[(i * 3) + 1]].pos.y;
//                    vecZ = subset.vertices[subset.indices[(i * 3) + 2]].pos.z - subset.vertices[subset.indices[(i * 3) + 1]].pos.z;
//                    edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our second edge
//
//                    //Cross multiply the two edge vectors to get the un-normalized face normal
//                    XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
//
//                    tempNormal.push_back(unnormalized);
//                }
//
//                //Compute vertex normals (normal Averaging)
//                XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//                int facesUsing = 0;
//                float tX, tY, tZ;    //temp axis variables
//
//                //Go through each vertex
//                for (int i = 0; i < subset.vertices.size(); ++i)
//                {
//                    //Check which triangles use this vertex
//                    for (int j = 0; j < subset.numTriangles; ++j)
//                    {
//                        if (subset.indices[j * 3] == i ||
//                            subset.indices[(j * 3) + 1] == i ||
//                            subset.indices[(j * 3) + 2] == i)
//                        {
//                            tX = XMVectorGetX(normalSum) + tempNormal[j].x;
//                            tY = XMVectorGetY(normalSum) + tempNormal[j].y;
//                            tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;
//
//                            normalSum = XMVectorSet(tX, tY, tZ, 0.0f);    //If a face is using the vertex, add the unormalized face normal to the normalSum
//
//                            facesUsing++;
//                        }
//                    }
//
//                    //Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
//                    normalSum = normalSum / facesUsing;
//
//                    //Normalize the normalSum vector
//                    normalSum = XMVector3Normalize(normalSum);
//
//                    //Store the normal and tangent in our current vertex
//                    subset.vertices[i].normal.x = -XMVectorGetX(normalSum);
//                    subset.vertices[i].normal.y = -XMVectorGetY(normalSum);
//                    subset.vertices[i].normal.z = -XMVectorGetZ(normalSum);
//
//
//                    // Create the joint space normal for easy normal calculations in animation
//                    Vertex tempVert = subset.vertices[i];                        // Get the current vertex
//                    subset.jointSpaceNormals.push_back(XMFLOAT3(0, 0, 0));        // Push back a blank normal
//                    XMVECTOR normal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);        // Clear normal
//
//                    for (int k = 0; k < tempVert.WeightCount; k++)                // Loop through each of the vertices weights
//                    {
//                        Joint tempJoint = MD5Model.joints[subset.weights[tempVert.StartWeight + k].jointID];    // Get the joints orientation
//                        XMVECTOR jointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
//
//                        // Calculate normal based off joints orientation (turn into joint space)
//                        normal = XMQuaternionMultiply(XMQuaternionMultiply(XMQuaternionInverse(jointOrientation), normalSum), jointOrientation);
//
//                        XMStoreFloat3(&subset.weights[tempVert.StartWeight + k].normal, XMVector3Normalize(normal));            // Store the normalized quaternion into our weights normal
//                    }
//
//                    //Clear normalSum, facesUsing for next vertex
//                    normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//                    facesUsing = 0;
//                }
//
//                // Create index buffer
//                D3D11_BUFFER_DESC indexBufferDesc;
//                ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
//
//                indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//                indexBufferDesc.ByteWidth = sizeof(DWORD) * subset.numTriangles * 3;
//                indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//                indexBufferDesc.CPUAccessFlags = 0;
//                indexBufferDesc.MiscFlags = 0;
//
//                D3D11_SUBRESOURCE_DATA iinitData;
//                iinitData.pSysMem = &subset.indices[0];
//                d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &subset.indexBuff);
//
//                //Create Vertex Buffer
//                D3D11_BUFFER_DESC vertexBufferDesc;
//                ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
//
//                vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                            // We will be updating this buffer, so we must set as dynamic
//                vertexBufferDesc.ByteWidth = sizeof(Vertex) * subset.vertices.size();
//                vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//                vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;                // Give CPU power to write to buffer
//                vertexBufferDesc.MiscFlags = 0;
//
//                D3D11_SUBRESOURCE_DATA vertexBufferData;
//                ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
//                vertexBufferData.pSysMem = &subset.vertices[0];
//                hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &subset.vertBuff);
//
//                // Push back the temp subset into the models subset vector
//                MD5Model.subsets.push_back(subset);
//            }
//        }
//    }
//    else
//    {
//        SwapChain->SetFullscreenState(false, NULL);    // Make sure we are out of fullscreen
//
//        // create message
//        std::wstring message = L"Could not open: ";
//        message += filename;
//
//        MessageBox(0, message.c_str(),    // display message
//            L"Error", MB_OK);
//
//        return false;
//    }
//
//    return true;
//}
//
//bool LoadObjModel(std::wstring filename,
//    ID3D11Buffer** vertBuff,
//    ID3D11Buffer** indexBuff,
//    std::vector<int>& subsetIndexStart,
//    std::vector<int>& subsetMaterialArray,
//    std::vector<SurfaceMaterial>& material,
//    int& subsetCount,
//    bool isRHCoordSys,
//    bool computeNormals)
//{
//    HRESULT hr = 0;
//
//    std::wifstream fileIn(filename.c_str());    //Open file
//    std::wstring meshMatLib;                    //String to hold our obj material library filename
//
//    //Arrays to store our model's information
//    std::vector<DWORD> indices;
//    std::vector<XMFLOAT3> vertPos;
//    std::vector<XMFLOAT3> vertNorm;
//    std::vector<XMFLOAT2> vertTexCoord;
//    std::vector<std::wstring> meshMaterials;
//
//    //Vertex definition indices
//    std::vector<int> vertPosIndex;
//    std::vector<int> vertNormIndex;
//    std::vector<int> vertTCIndex;
//
//    //Make sure we have a default if no tex coords or normals are defined
//    bool hasTexCoord = false;
//    bool hasNorm = false;
//
//    //Temp variables to store into vectors
//    std::wstring meshMaterialsTemp;
//    int vertPosIndexTemp;
//    int vertNormIndexTemp;
//    int vertTCIndexTemp;
//
//    wchar_t checkChar;        //The variable we will use to store one char from file at a time
//    std::wstring face;        //Holds the string containing our face vertices
//    int vIndex = 0;            //Keep track of our vertex index count
//    int triangleCount = 0;    //Total Triangles
//    int totalVerts = 0;
//    int meshTriangles = 0;
//
//    //Check to see if the file was opened
//    if (fileIn)
//    {
//        while (fileIn)
//        {
//            checkChar = fileIn.get();    //Get next char
//
//            switch (checkChar)
//            {
//            case '#':
//                checkChar = fileIn.get();
//                while (checkChar != '\n')
//                    checkChar = fileIn.get();
//                break;
//            case 'v':    //Get Vertex Descriptions
//                checkChar = fileIn.get();
//                if (checkChar == ' ')    //v - vert position
//                {
//                    float vz, vy, vx;
//                    fileIn >> vx >> vy >> vz;    //Store the next three types
//
//                    if (isRHCoordSys)    //If model is from an RH Coord System
//                        vertPos.push_back(XMFLOAT3(vx, vy, vz * -1.0f));    //Invert the Z axis
//                    else
//                        vertPos.push_back(XMFLOAT3(vx, vy, vz));
//                }
//                if (checkChar == 't')    //vt - vert tex coords
//                {
//                    float vtcu, vtcv;
//                    fileIn >> vtcu >> vtcv;        //Store next two types
//
//                    if (isRHCoordSys)    //If model is from an RH Coord System
//                        vertTexCoord.push_back(XMFLOAT2(vtcu, 1.0f - vtcv));    //Reverse the "v" axis
//                    else
//                        vertTexCoord.push_back(XMFLOAT2(vtcu, vtcv));
//
//                    hasTexCoord = true;    //We know the model uses texture coords
//                }
//                //Since we compute the normals later, we don't need to check for normals
//                //In the file, but i'll do it here anyway
//                if (checkChar == 'n')    //vn - vert normal
//                {
//                    float vnx, vny, vnz;
//                    fileIn >> vnx >> vny >> vnz;    //Store next three types
//
//                    if (isRHCoordSys)    //If model is from an RH Coord System
//                        vertNorm.push_back(XMFLOAT3(vnx, vny, vnz * -1.0f));    //Invert the Z axis
//                    else
//                        vertNorm.push_back(XMFLOAT3(vnx, vny, vnz));
//
//                    hasNorm = true;    //We know the model defines normals
//                }
//                break;
//
//                //New group (Subset)
//            case 'g':    //g - defines a group
//                checkChar = fileIn.get();
//                if (checkChar == ' ')
//                {
//                    subsetIndexStart.push_back(vIndex);        //Start index for this subset
//                    subsetCount++;
//                }
//                break;
//
//                //Get Face Index
//            case 'f':    //f - defines the faces
//                checkChar = fileIn.get();
//                if (checkChar == ' ')
//                {
//                    face = L"";
//                    std::wstring VertDef;    //Holds one vertex definition at a time
//                    triangleCount = 0;
//
//                    checkChar = fileIn.get();
//                    while (checkChar != '\n')
//                    {
//                        face += checkChar;            //Add the char to our face string
//                        checkChar = fileIn.get();    //Get the next Character
//                        if (checkChar == ' ')        //If its a space...
//                            triangleCount++;        //Increase our triangle count
//                    }
//
//                    //Check for space at the end of our face string
//                    if (face[face.length() - 1] == ' ')
//                        triangleCount--;    //Each space adds to our triangle count
//
//                    triangleCount -= 1;        //Ever vertex in the face AFTER the first two are new faces
//
//                    std::wstringstream ss(face);
//
//                    if (face.length() > 0)
//                    {
//                        int firstVIndex, lastVIndex;    //Holds the first and last vertice's index
//
//                        for (int i = 0; i < 3; ++i)        //First three vertices (first triangle)
//                        {
//                            ss >> VertDef;    //Get vertex definition (vPos/vTexCoord/vNorm)
//
//                            std::wstring vertPart;
//                            int whichPart = 0;        //(vPos, vTexCoord, or vNorm)
//
//                            //Parse this string
//                            for (int j = 0; j < VertDef.length(); ++j)
//                            {
//                                if (VertDef[j] != '/')    //If there is no divider "/", add a char to our vertPart
//                                    vertPart += VertDef[j];
//
//                                //If the current char is a divider "/", or its the last character in the string
//                                if (VertDef[j] == '/' || j == VertDef.length() - 1)
//                                {
//                                    std::wistringstream wstringToInt(vertPart);    //Used to convert wstring to int
//
//                                    if (whichPart == 0)    //If vPos
//                                    {
//                                        wstringToInt >> vertPosIndexTemp;
//                                        vertPosIndexTemp -= 1;        //subtract one since c++ arrays start with 0, and obj start with 1
//
//                                        //Check to see if the vert pos was the only thing specified
//                                        if (j == VertDef.length() - 1)
//                                        {
//                                            vertNormIndexTemp = 0;
//                                            vertTCIndexTemp = 0;
//                                        }
//                                    }
//
//                                    else if (whichPart == 1)    //If vTexCoord
//                                    {
//                                        if (vertPart != L"")    //Check to see if there even is a tex coord
//                                        {
//                                            wstringToInt >> vertTCIndexTemp;
//                                            vertTCIndexTemp -= 1;    //subtract one since c++ arrays start with 0, and obj start with 1
//                                        }
//                                        else    //If there is no tex coord, make a default
//                                            vertTCIndexTemp = 0;
//
//                                        //If the cur. char is the second to last in the string, then
//                                        //there must be no normal, so set a default normal
//                                        if (j == VertDef.length() - 1)
//                                            vertNormIndexTemp = 0;
//
//                                    }
//                                    else if (whichPart == 2)    //If vNorm
//                                    {
//                                        std::wistringstream wstringToInt(vertPart);
//
//                                        wstringToInt >> vertNormIndexTemp;
//                                        vertNormIndexTemp -= 1;        //subtract one since c++ arrays start with 0, and obj start with 1
//                                    }
//
//                                    vertPart = L"";    //Get ready for next vertex part
//                                    whichPart++;    //Move on to next vertex part                    
//                                }
//                            }
//
//                            //Check to make sure there is at least one subset
//                            if (subsetCount == 0)
//                            {
//                                subsetIndexStart.push_back(vIndex);        //Start index for this subset
//                                subsetCount++;
//                            }
//
//                            //Avoid duplicate vertices
//                            bool vertAlreadyExists = false;
//                            if (totalVerts >= 3)    //Make sure we at least have one triangle to check
//                            {
//                                //Loop through all the vertices
//                                for (int iCheck = 0; iCheck < totalVerts; ++iCheck)
//                                {
//                                    //If the vertex position and texture coordinate in memory are the same
//                                    //As the vertex position and texture coordinate we just now got out
//                                    //of the obj file, we will set this faces vertex index to the vertex's
//                                    //index value in memory. This makes sure we don't create duplicate vertices
//                                    if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
//                                    {
//                                        if (vertTCIndexTemp == vertTCIndex[iCheck])
//                                        {
//                                            indices.push_back(iCheck);        //Set index for this vertex
//                                            vertAlreadyExists = true;        //If we've made it here, the vertex already exists
//                                        }
//                                    }
//                                }
//                            }
//
//                            //If this vertex is not already in our vertex arrays, put it there
//                            if (!vertAlreadyExists)
//                            {
//                                vertPosIndex.push_back(vertPosIndexTemp);
//                                vertTCIndex.push_back(vertTCIndexTemp);
//                                vertNormIndex.push_back(vertNormIndexTemp);
//                                totalVerts++;    //We created a new vertex
//                                indices.push_back(totalVerts - 1);    //Set index for this vertex
//                            }
//
//                            //If this is the very first vertex in the face, we need to
//                            //make sure the rest of the triangles use this vertex
//                            if (i == 0)
//                            {
//                                firstVIndex = indices[vIndex];    //The first vertex index of this FACE
//
//                            }
//
//                            //If this was the last vertex in the first triangle, we will make sure
//                            //the next triangle uses this one (eg. tri1(1,2,3) tri2(1,3,4) tri3(1,4,5))
//                            if (i == 2)
//                            {
//                                lastVIndex = indices[vIndex];    //The last vertex index of this TRIANGLE
//                            }
//                            vIndex++;    //Increment index count
//                        }
//
//                        meshTriangles++;    //One triangle down
//
//                        //If there are more than three vertices in the face definition, we need to make sure
//                        //we convert the face to triangles. We created our first triangle above, now we will
//                        //create a new triangle for every new vertex in the face, using the very first vertex
//                        //of the face, and the last vertex from the triangle before the current triangle
//                        for (int l = 0; l < triangleCount - 1; ++l)    //Loop through the next vertices to create new triangles
//                        {
//                            //First vertex of this triangle (the very first vertex of the face too)
//                            indices.push_back(firstVIndex);            //Set index for this vertex
//                            vIndex++;
//
//                            //Second Vertex of this triangle (the last vertex used in the tri before this one)
//                            indices.push_back(lastVIndex);            //Set index for this vertex
//                            vIndex++;
//
//                            //Get the third vertex for this triangle
//                            ss >> VertDef;
//
//                            std::wstring vertPart;
//                            int whichPart = 0;
//
//                            //Parse this string (same as above)
//                            for (int j = 0; j < VertDef.length(); ++j)
//                            {
//                                if (VertDef[j] != '/')
//                                    vertPart += VertDef[j];
//                                if (VertDef[j] == '/' || j == VertDef.length() - 1)
//                                {
//                                    std::wistringstream wstringToInt(vertPart);
//
//                                    if (whichPart == 0)
//                                    {
//                                        wstringToInt >> vertPosIndexTemp;
//                                        vertPosIndexTemp -= 1;
//
//                                        //Check to see if the vert pos was the only thing specified
//                                        if (j == VertDef.length() - 1)
//                                        {
//                                            vertTCIndexTemp = 0;
//                                            vertNormIndexTemp = 0;
//                                        }
//                                    }
//                                    else if (whichPart == 1)
//                                    {
//                                        if (vertPart != L"")
//                                        {
//                                            wstringToInt >> vertTCIndexTemp;
//                                            vertTCIndexTemp -= 1;
//                                        }
//                                        else
//                                            vertTCIndexTemp = 0;
//                                        if (j == VertDef.length() - 1)
//                                            vertNormIndexTemp = 0;
//
//                                    }
//                                    else if (whichPart == 2)
//                                    {
//                                        std::wistringstream wstringToInt(vertPart);
//
//                                        wstringToInt >> vertNormIndexTemp;
//                                        vertNormIndexTemp -= 1;
//                                    }
//
//                                    vertPart = L"";
//                                    whichPart++;
//                                }
//                            }
//
//                            //Check for duplicate vertices
//                            bool vertAlreadyExists = false;
//                            if (totalVerts >= 3)    //Make sure we at least have one triangle to check
//                            {
//                                for (int iCheck = 0; iCheck < totalVerts; ++iCheck)
//                                {
//                                    if (vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
//                                    {
//                                        if (vertTCIndexTemp == vertTCIndex[iCheck])
//                                        {
//                                            indices.push_back(iCheck);            //Set index for this vertex
//                                            vertAlreadyExists = true;        //If we've made it here, the vertex already exists
//                                        }
//                                    }
//                                }
//                            }
//
//                            if (!vertAlreadyExists)
//                            {
//                                vertPosIndex.push_back(vertPosIndexTemp);
//                                vertTCIndex.push_back(vertTCIndexTemp);
//                                vertNormIndex.push_back(vertNormIndexTemp);
//                                totalVerts++;                    //New vertex created, add to total verts
//                                indices.push_back(totalVerts - 1);        //Set index for this vertex
//                            }
//
//                            //Set the second vertex for the next triangle to the last vertex we got        
//                            lastVIndex = indices[vIndex];    //The last vertex index of this TRIANGLE
//
//                            meshTriangles++;    //New triangle defined
//                            vIndex++;
//                        }
//                    }
//                }
//                break;
//
//            case 'm':    //mtllib - material library filename
//                checkChar = fileIn.get();
//                if (checkChar == 't')
//                {
//                    checkChar = fileIn.get();
//                    if (checkChar == 'l')
//                    {
//                        checkChar = fileIn.get();
//                        if (checkChar == 'l')
//                        {
//                            checkChar = fileIn.get();
//                            if (checkChar == 'i')
//                            {
//                                checkChar = fileIn.get();
//                                if (checkChar == 'b')
//                                {
//                                    checkChar = fileIn.get();
//                                    if (checkChar == ' ')
//                                    {
//                                        //Store the material libraries file name
//                                        fileIn >> meshMatLib;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//
//                break;
//
//            case 'u':    //usemtl - which material to use
//                checkChar = fileIn.get();
//                if (checkChar == 's')
//                {
//                    checkChar = fileIn.get();
//                    if (checkChar == 'e')
//                    {
//                        checkChar = fileIn.get();
//                        if (checkChar == 'm')
//                        {
//                            checkChar = fileIn.get();
//                            if (checkChar == 't')
//                            {
//                                checkChar = fileIn.get();
//                                if (checkChar == 'l')
//                                {
//                                    checkChar = fileIn.get();
//                                    if (checkChar == ' ')
//                                    {
//                                        meshMaterialsTemp = L"";    //Make sure this is cleared
//
//                                        fileIn >> meshMaterialsTemp; //Get next type (string)
//
//                                        meshMaterials.push_back(meshMaterialsTemp);
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                break;
//
//            default:
//                break;
//            }
//        }
//    }
//    else    //If we could not open the file
//    {
//        SwapChain->SetFullscreenState(false, NULL);    //Make sure we are out of fullscreen
//
//        //create message
//        std::wstring message = L"Could not open: ";
//        message += filename;
//
//        MessageBox(0, message.c_str(),    //display message
//            L"Error", MB_OK);
//
//        return false;
//    }
//
//    subsetIndexStart.push_back(vIndex); //There won't be another index start after our last subset, so set it here
//
//    //sometimes "g" is defined at the very top of the file, then again before the first group of faces.
//    //This makes sure the first subset does not conatain "0" indices.
//    if (subsetIndexStart[1] == 0)
//    {
//        subsetIndexStart.erase(subsetIndexStart.begin() + 1);
//        meshSubsets--;
//    }
//
//    //Make sure we have a default for the tex coord and normal
//    //if one or both are not specified
//    if (!hasNorm)
//        vertNorm.push_back(XMFLOAT3(0.0f, 0.0f, 0.0f));
//    if (!hasTexCoord)
//        vertTexCoord.push_back(XMFLOAT2(0.0f, 0.0f));
//
//    //Close the obj file, and open the mtl file
//    fileIn.close();
//    fileIn.open(meshMatLib.c_str());
//
//    std::wstring lastStringRead;
//    int matCount = material.size();    //total materials
//
//    //kdset - If our diffuse color was not set, we can use the ambient color (which is usually the same)
//    //If the diffuse color WAS set, then we don't need to set our diffuse color to ambient
//    bool kdset = false;
//
//    if (fileIn)
//    {
//        while (fileIn)
//        {
//            checkChar = fileIn.get();    //Get next char
//
//            switch (checkChar)
//            {
//                //Check for comment
//            case '#':
//                checkChar = fileIn.get();
//                while (checkChar != '\n')
//                    checkChar = fileIn.get();
//                break;
//
//                //Set diffuse color
//            case 'K':
//                checkChar = fileIn.get();
//                if (checkChar == 'd')    //Diffuse Color
//                {
//                    checkChar = fileIn.get();    //remove space
//
//                    fileIn >> material[matCount - 1].difColor.x;
//                    fileIn >> material[matCount - 1].difColor.y;
//                    fileIn >> material[matCount - 1].difColor.z;
//
//                    kdset = true;
//                }
//
//                //Ambient Color (We'll store it in diffuse if there isn't a diffuse already)
//                if (checkChar == 'a')
//                {
//                    checkChar = fileIn.get();    //remove space
//                    if (!kdset)
//                    {
//                        fileIn >> material[matCount - 1].difColor.x;
//                        fileIn >> material[matCount - 1].difColor.y;
//                        fileIn >> material[matCount - 1].difColor.z;
//                    }
//                }
//                break;
//
//                //Check for transparency
//            case 'T':
//                checkChar = fileIn.get();
//                if (checkChar == 'r')
//                {
//                    checkChar = fileIn.get();    //remove space
//                    float Transparency;
//                    fileIn >> Transparency;
//
//                    material[matCount - 1].difColor.w = Transparency;
//
//                    if (Transparency > 0.0f)
//                        material[matCount - 1].transparent = true;
//                }
//                break;
//
//                //Some obj files specify d for transparency
//            case 'd':
//                checkChar = fileIn.get();
//                if (checkChar == ' ')
//                {
//                    float Transparency;
//                    fileIn >> Transparency;
//
//                    //'d' - 0 being most transparent, and 1 being opaque, opposite of Tr
//                    Transparency = 1.0f - Transparency;
//
//                    material[matCount - 1].difColor.w = Transparency;
//
//                    if (Transparency > 0.0f)
//                        material[matCount - 1].transparent = true;
//                }
//                break;
//
//                //Get the diffuse map (texture)
//            case 'm':
//                checkChar = fileIn.get();
//                if (checkChar == 'a')
//                {
//                    checkChar = fileIn.get();
//                    if (checkChar == 'p')
//                    {
//                        checkChar = fileIn.get();
//                        if (checkChar == '_')
//                        {
//                            //map_Kd - Diffuse map
//                            checkChar = fileIn.get();
//                            if (checkChar == 'K')
//                            {
//                                checkChar = fileIn.get();
//                                if (checkChar == 'd')
//                                {
//                                    std::wstring fileNamePath;
//
//                                    fileIn.get();    //Remove whitespace between map_Kd and file
//
//                                    //Get the file path - We read the pathname char by char since
//                                    //pathnames can sometimes contain spaces, so we will read until
//                                    //we find the file extension
//                                    bool texFilePathEnd = false;
//                                    while (!texFilePathEnd)
//                                    {
//                                        checkChar = fileIn.get();
//
//                                        fileNamePath += checkChar;
//
//                                        if (checkChar == '.')
//                                        {
//                                            for (int i = 0; i < 3; ++i)
//                                                fileNamePath += fileIn.get();
//
//                                            texFilePathEnd = true;
//                                        }
//                                    }
//
//                                    //check if this texture has already been loaded
//                                    bool alreadyLoaded = false;
//                                    for (int i = 0; i < textureNameArray.size(); ++i)
//                                    {
//                                        if (fileNamePath == textureNameArray[i])
//                                        {
//                                            alreadyLoaded = true;
//                                            material[matCount - 1].texArrayIndex = i;
//                                            material[matCount - 1].hasTexture = true;
//                                        }
//                                    }
//
//                                    //if the texture is not already loaded, load it now
//                                    if (!alreadyLoaded)
//                                    {
//                                        ID3D11ShaderResourceView* tempMeshSRV;
//                                        hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, fileNamePath.c_str(),
//                                            NULL, NULL, &tempMeshSRV, NULL);
//                                        if (SUCCEEDED(hr))
//                                        {
//                                            textureNameArray.push_back(fileNamePath.c_str());
//                                            material[matCount - 1].texArrayIndex = meshSRV.size();
//                                            meshSRV.push_back(tempMeshSRV);
//                                            material[matCount - 1].hasTexture = true;
//                                        }
//                                    }
//                                }
//                            }
//                            //map_d - alpha map
//                            else if (checkChar == 'd')
//                            {
//                                //Alpha maps are usually the same as the diffuse map
//                                //So we will assume that for now by only enabling
//                                //transparency for this material, as we will already
//                                //be using the alpha channel in the diffuse map
//                                material[matCount - 1].transparent = true;
//                            }
//
//                            //map_bump - bump map (we're usinga normal map though)
//                            else if (checkChar == 'b')
//                            {
//                                checkChar = fileIn.get();
//                                if (checkChar == 'u')
//                                {
//                                    checkChar = fileIn.get();
//                                    if (checkChar == 'm')
//                                    {
//                                        checkChar = fileIn.get();
//                                        if (checkChar == 'p')
//                                        {
//                                            std::wstring fileNamePath;
//
//                                            fileIn.get();    //Remove whitespace between map_bump and file
//
//                                            //Get the file path - We read the pathname char by char since
//                                            //pathnames can sometimes contain spaces, so we will read until
//                                            //we find the file extension
//                                            bool texFilePathEnd = false;
//                                            while (!texFilePathEnd)
//                                            {
//                                                checkChar = fileIn.get();
//
//                                                fileNamePath += checkChar;
//
//                                                if (checkChar == '.')
//                                                {
//                                                    for (int i = 0; i < 3; ++i)
//                                                        fileNamePath += fileIn.get();
//
//                                                    texFilePathEnd = true;
//                                                }
//                                            }
//
//                                            //check if this texture has already been loaded
//                                            bool alreadyLoaded = false;
//                                            for (int i = 0; i < textureNameArray.size(); ++i)
//                                            {
//                                                if (fileNamePath == textureNameArray[i])
//                                                {
//                                                    alreadyLoaded = true;
//                                                    material[matCount - 1].normMapTexArrayIndex = i;
//                                                    material[matCount - 1].hasNormMap = true;
//                                                }
//                                            }
//
//                                            //if the texture is not already loaded, load it now
//                                            if (!alreadyLoaded)
//                                            {
//                                                ID3D11ShaderResourceView* tempMeshSRV;
//                                                hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, fileNamePath.c_str(),
//                                                    NULL, NULL, &tempMeshSRV, NULL);
//                                                if (SUCCEEDED(hr))
//                                                {
//                                                    textureNameArray.push_back(fileNamePath.c_str());
//                                                    material[matCount - 1].normMapTexArrayIndex = meshSRV.size();
//                                                    meshSRV.push_back(tempMeshSRV);
//                                                    material[matCount - 1].hasNormMap = true;
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                break;
//
//            case 'n':    //newmtl - Declare new material
//                checkChar = fileIn.get();
//                if (checkChar == 'e')
//                {
//                    checkChar = fileIn.get();
//                    if (checkChar == 'w')
//                    {
//                        checkChar = fileIn.get();
//                        if (checkChar == 'm')
//                        {
//                            checkChar = fileIn.get();
//                            if (checkChar == 't')
//                            {
//                                checkChar = fileIn.get();
//                                if (checkChar == 'l')
//                                {
//                                    checkChar = fileIn.get();
//                                    if (checkChar == ' ')
//                                    {
//                                        //New material, set its defaults
//                                        SurfaceMaterial tempMat;
//                                        material.push_back(tempMat);
//                                        fileIn >> material[matCount].matName;
//                                        material[matCount].transparent = false;
//                                        material[matCount].hasTexture = false;
//                                        material[matCount].hasNormMap = false;
//                                        material[matCount].normMapTexArrayIndex = 0;
//                                        material[matCount].texArrayIndex = 0;
//                                        matCount++;
//                                        kdset = false;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                break;
//
//            default:
//                break;
//            }
//        }
//    }
//    else
//    {
//        SwapChain->SetFullscreenState(false, NULL);    //Make sure we are out of fullscreen
//
//        std::wstring message = L"Could not open: ";
//        message += meshMatLib;
//
//        MessageBox(0, message.c_str(),
//            L"Error", MB_OK);
//
//        return false;
//    }
//
//    //Set the subsets material to the index value
//    //of the its material in our material array
//    for (int i = 0; i < meshSubsets; ++i)
//    {
//        bool hasMat = false;
//        for (int j = 0; j < material.size(); ++j)
//        {
//            if (meshMaterials[i] == material[j].matName)
//            {
//                subsetMaterialArray.push_back(j);
//                hasMat = true;
//            }
//        }
//        if (!hasMat)
//            subsetMaterialArray.push_back(0); //Use first material in array
//    }
//
//    std::vector<Vertex> vertices;
//    Vertex tempVert;
//
//    //Create our vertices using the information we got 
//    //from the file and store them in a vector
//    for (int j = 0; j < totalVerts; ++j)
//    {
//        tempVert.pos = vertPos[vertPosIndex[j]];
//        tempVert.normal = vertNorm[vertNormIndex[j]];
//        tempVert.texCoord = vertTexCoord[vertTCIndex[j]];
//
//        vertices.push_back(tempVert);
//    }
//
//    //////////////////////Compute Normals///////////////////////////
//    //If computeNormals was set to true then we will create our own
//    //normals, if it was set to false we will use the obj files normals
//    if (computeNormals)
//    {
//        std::vector<XMFLOAT3> tempNormal;
//
//        //normalized and unnormalized normals
//        XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);
//
//        //tangent stuff
//        std::vector<XMFLOAT3> tempTangent;
//        XMFLOAT3 tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
//        float tcU1, tcV1, tcU2, tcV2;
//
//        //Used to get vectors (sides) from the position of the verts
//        float vecX, vecY, vecZ;
//
//        //Two edges of our triangle
//        XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//        XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//
//        //Compute face normals
//        //And Tangents
//        for (int i = 0; i < meshTriangles; ++i)
//        {
//            //Get the vector describing one edge of our triangle (edge 0,2)
//            vecX = vertices[indices[(i * 3)]].pos.x - vertices[indices[(i * 3) + 2]].pos.x;
//            vecY = vertices[indices[(i * 3)]].pos.y - vertices[indices[(i * 3) + 2]].pos.y;
//            vecZ = vertices[indices[(i * 3)]].pos.z - vertices[indices[(i * 3) + 2]].pos.z;
//            edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our first edge
//
//            //Get the vector describing another edge of our triangle (edge 2,1)
//            vecX = vertices[indices[(i * 3) + 2]].pos.x - vertices[indices[(i * 3) + 1]].pos.x;
//            vecY = vertices[indices[(i * 3) + 2]].pos.y - vertices[indices[(i * 3) + 1]].pos.y;
//            vecZ = vertices[indices[(i * 3) + 2]].pos.z - vertices[indices[(i * 3) + 1]].pos.z;
//            edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our second edge
//
//            //Cross multiply the two edge vectors to get the un-normalized face normal
//            XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));
//
//            tempNormal.push_back(unnormalized);
//
//            //Find first texture coordinate edge 2d vector
//            tcU1 = vertices[indices[(i * 3)]].texCoord.x - vertices[indices[(i * 3) + 2]].texCoord.x;
//            tcV1 = vertices[indices[(i * 3)]].texCoord.y - vertices[indices[(i * 3) + 2]].texCoord.y;
//
//            //Find second texture coordinate edge 2d vector
//            tcU2 = vertices[indices[(i * 3) + 2]].texCoord.x - vertices[indices[(i * 3) + 1]].texCoord.x;
//            tcV2 = vertices[indices[(i * 3) + 2]].texCoord.y - vertices[indices[(i * 3) + 1]].texCoord.y;
//
//            //Find tangent using both tex coord edges and position edges
//            tangent.x = (tcV1 * XMVectorGetX(edge1) - tcV2 * XMVectorGetX(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
//            tangent.y = (tcV1 * XMVectorGetY(edge1) - tcV2 * XMVectorGetY(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
//            tangent.z = (tcV1 * XMVectorGetZ(edge1) - tcV2 * XMVectorGetZ(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
//
//            tempTangent.push_back(tangent);
//        }
//
//        //Compute vertex normals (normal Averaging)
//        XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//        XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//        int facesUsing = 0;
//        float tX, tY, tZ;    //temp axis variables
//
//        //Go through each vertex
//        for (int i = 0; i < totalVerts; ++i)
//        {
//            //Check which triangles use this vertex
//            for (int j = 0; j < meshTriangles; ++j)
//            {
//                if (indices[j * 3] == i ||
//                    indices[(j * 3) + 1] == i ||
//                    indices[(j * 3) + 2] == i)
//                {
//                    tX = XMVectorGetX(normalSum) + tempNormal[j].x;
//                    tY = XMVectorGetY(normalSum) + tempNormal[j].y;
//                    tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;
//
//                    normalSum = XMVectorSet(tX, tY, tZ, 0.0f);    //If a face is using the vertex, add the unormalized face normal to the normalSum
//
//                    //We can reuse tX, tY, tZ to sum up tangents
//                    tX = XMVectorGetX(tangentSum) + tempTangent[j].x;
//                    tY = XMVectorGetY(tangentSum) + tempTangent[j].y;
//                    tZ = XMVectorGetZ(tangentSum) + tempTangent[j].z;
//
//                    tangentSum = XMVectorSet(tX, tY, tZ, 0.0f); //sum up face tangents using this vertex
//
//                    facesUsing++;
//                }
//            }
//
//            //Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
//            normalSum = normalSum / facesUsing;
//            tangentSum = tangentSum / facesUsing;
//
//            //Normalize the normalSum vector and tangent
//            normalSum = XMVector3Normalize(normalSum);
//            tangentSum = XMVector3Normalize(tangentSum);
//
//            //Store the normal and tangent in our current vertex
//            vertices[i].normal.x = XMVectorGetX(normalSum);
//            vertices[i].normal.y = XMVectorGetY(normalSum);
//            vertices[i].normal.z = XMVectorGetZ(normalSum);
//
//            vertices[i].tangent.x = XMVectorGetX(tangentSum);
//            vertices[i].tangent.y = XMVectorGetY(tangentSum);
//            vertices[i].tangent.z = XMVectorGetZ(tangentSum);
//
//            //Clear normalSum, tangentSum and facesUsing for next vertex
//            normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//            tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//            facesUsing = 0;
//
//        }
//    }
//
//    //Create index buffer
//    D3D11_BUFFER_DESC indexBufferDesc;
//    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
//
//    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    indexBufferDesc.ByteWidth = sizeof(DWORD) * meshTriangles * 3;
//    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//    indexBufferDesc.CPUAccessFlags = 0;
//    indexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA iinitData;
//
//    iinitData.pSysMem = &indices[0];
//    d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, indexBuff);
//
//    //Create Vertex Buffer
//    D3D11_BUFFER_DESC vertexBufferDesc;
//    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
//
//    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    vertexBufferDesc.ByteWidth = sizeof(Vertex) * totalVerts;
//    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//    vertexBufferDesc.CPUAccessFlags = 0;
//    vertexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA vertexBufferData;
//
//    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
//    vertexBufferData.pSysMem = &vertices[0];
//    hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, vertBuff);
//
//    return true;
//}
//
//void CreateSphere(int LatLines, int LongLines)
//{
//    NumSphereVertices = ((LatLines - 2) * LongLines) + 2;
//    NumSphereFaces = ((LatLines - 3) * (LongLines) * 2) + (LongLines * 2);
//
//    float sphereYaw = 0.0f;
//    float spherePitch = 0.0f;
//
//    std::vector<Vertex> vertices(NumSphereVertices);
//
//    XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//
//    vertices[0].pos.x = 0.0f;
//    vertices[0].pos.y = 0.0f;
//    vertices[0].pos.z = 1.0f;
//
//    for (DWORD i = 0; i < LatLines - 2; ++i)
//    {
//        spherePitch = (i + 1) * (3.14f / (LatLines - 1));
//        Rotationx = XMMatrixRotationX(spherePitch);
//        for (DWORD j = 0; j < LongLines; ++j)
//        {
//            sphereYaw = j * (6.28f / (LongLines));
//            Rotationy = XMMatrixRotationZ(sphereYaw);
//            currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (Rotationx * Rotationy));
//            currVertPos = XMVector3Normalize(currVertPos);
//            vertices[i * LongLines + j + 1].pos.x = XMVectorGetX(currVertPos);
//            vertices[i * LongLines + j + 1].pos.y = XMVectorGetY(currVertPos);
//            vertices[i * LongLines + j + 1].pos.z = XMVectorGetZ(currVertPos);
//        }
//    }
//
//    vertices[NumSphereVertices - 1].pos.x = 0.0f;
//    vertices[NumSphereVertices - 1].pos.y = 0.0f;
//    vertices[NumSphereVertices - 1].pos.z = -1.0f;
//
//
//    D3D11_BUFFER_DESC vertexBufferDesc;
//    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
//
//    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    vertexBufferDesc.ByteWidth = sizeof(Vertex) * NumSphereVertices;
//    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//    vertexBufferDesc.CPUAccessFlags = 0;
//    vertexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA vertexBufferData;
//
//    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
//    vertexBufferData.pSysMem = &vertices[0];
//    hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &sphereVertBuffer);
//
//
//    std::vector<DWORD> indices(NumSphereFaces * 3);
//
//    int k = 0;
//    for (DWORD l = 0; l < LongLines - 1; ++l)
//    {
//        indices[k] = 0;
//        indices[k + 1] = l + 1;
//        indices[k + 2] = l + 2;
//        k += 3;
//    }
//
//    indices[k] = 0;
//    indices[k + 1] = LongLines;
//    indices[k + 2] = 1;
//    k += 3;
//
//    for (DWORD i = 0; i < LatLines - 3; ++i)
//    {
//        for (DWORD j = 0; j < LongLines - 1; ++j)
//        {
//            indices[k] = i * LongLines + j + 1;
//            indices[k + 1] = i * LongLines + j + 2;
//            indices[k + 2] = (i + 1) * LongLines + j + 1;
//
//            indices[k + 3] = (i + 1) * LongLines + j + 1;
//            indices[k + 4] = i * LongLines + j + 2;
//            indices[k + 5] = (i + 1) * LongLines + j + 2;
//
//            k += 6; // next quad
//        }
//
//        indices[k] = (i * LongLines) + LongLines;
//        indices[k + 1] = (i * LongLines) + 1;
//        indices[k + 2] = ((i + 1) * LongLines) + LongLines;
//
//        indices[k + 3] = ((i + 1) * LongLines) + LongLines;
//        indices[k + 4] = (i * LongLines) + 1;
//        indices[k + 5] = ((i + 1) * LongLines) + 1;
//
//        k += 6;
//    }
//
//    for (DWORD l = 0; l < LongLines - 1; ++l)
//    {
//        indices[k] = NumSphereVertices - 1;
//        indices[k + 1] = (NumSphereVertices - 1) - (l + 1);
//        indices[k + 2] = (NumSphereVertices - 1) - (l + 2);
//        k += 3;
//    }
//
//    indices[k] = NumSphereVertices - 1;
//    indices[k + 1] = (NumSphereVertices - 1) - LongLines;
//    indices[k + 2] = NumSphereVertices - 2;
//
//    D3D11_BUFFER_DESC indexBufferDesc;
//    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
//
//    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    indexBufferDesc.ByteWidth = sizeof(DWORD) * NumSphereFaces * 3;
//    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//    indexBufferDesc.CPUAccessFlags = 0;
//    indexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA iinitData;
//
//    iinitData.pSysMem = &indices[0];
//    d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &sphereIndexBuffer);
//
//}
//
//void InitD2DScreenTexture()
//{
//    //Create the vertex buffer
//    Vertex v[] =
//    {
//        // Front Face
//        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//        Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//        Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//    };
//
//    DWORD indices[] = {
//        // Front Face
//        0,  1,  2,
//        0,  2,  3,
//    };
//
//    D3D11_BUFFER_DESC indexBufferDesc;
//    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
//
//    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
//    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//    indexBufferDesc.CPUAccessFlags = 0;
//    indexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA iinitData;
//
//    iinitData.pSysMem = indices;
//    d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &d2dIndexBuffer);
//
//
//    D3D11_BUFFER_DESC vertexBufferDesc;
//    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
//
//    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
//    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//    vertexBufferDesc.CPUAccessFlags = 0;
//    vertexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA vertexBufferData;
//
//    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
//    vertexBufferData.pSysMem = v;
//    hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &d2dVertBuffer);
//
//    //Create A shader resource view from the texture D2D will render to,
//    //So we can use it to texture a square which overlays our scene
//    d3d11Device->CreateShaderResourceView(sharedTex11, NULL, &d2dTexture);
//}
//
//bool InitScene()
//{
//    InitD2DScreenTexture();
//
//    CreateSphere(10, 10);
//
//    if (!LoadObjModel(L"ground.obj", &meshVertBuff, &meshIndexBuff, meshSubsetIndexStart, meshSubsetTexture, material, meshSubsets, true, true))
//        return false;
//
//    /************************************New Stuff****************************************************/
//    // Load in our tree model
//    if (!LoadObjModel(L"tree.obj", &treeVertBuff, &treeIndexBuff, treeSubsetIndexStart, treeSubsetTexture, material, treeSubsets, true, true))
//        return false;
//
//    // Set up the tree positions then instance buffer
//    std::vector<InstanceData> inst(numTrees);
//    XMVECTOR tempPos;
//    srand(100);
//    // We are just creating random positions for the trees, between the positions of (-100, 0, -100) to (100, 0, 100)
//    // then storing the position in our instanceData array
//    for (int i = 0; i < numTrees; i++)
//    {
//        float randX = ((float)(rand() % 2000) / 10) - 100;
//        float randZ = ((float)(rand() % 2000) / 10) - 100;
//        tempPos = XMVectorSet(randX, 0.0f, randZ, 0.0f);
//
//        XMStoreFloat3(&inst[i].pos, tempPos);
//    }
//
//    // Create our trees instance buffer
//    // Pretty much the same thing as a regular vertex buffer, except that this buffers data
//    // will be used per "instance" instead of per "vertex". Each instance of the geometry
//    // gets it's own instanceData data, similar to how each vertex of the geometry gets its own
//    // Vertex data
//    D3D11_BUFFER_DESC instBuffDesc;
//    ZeroMemory(&instBuffDesc, sizeof(instBuffDesc));
//
//    instBuffDesc.Usage = D3D11_USAGE_DEFAULT;
//    instBuffDesc.ByteWidth = sizeof(InstanceData) * numTrees;
//    instBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//    instBuffDesc.CPUAccessFlags = 0;
//    instBuffDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA instData;
//    ZeroMemory(&instData, sizeof(instData));
//
//    instData.pSysMem = &inst[0];
//    hr = d3d11Device->CreateBuffer(&instBuffDesc, &instData, &treeInstanceBuff);
//
//    // The tree's world matrix (We will keep it an identity matrix, but we could change their positions without
//    // unrealistic effects, since remember that all transformations are done around the point (0,0,0), and we will
//    // be applying this world matrix to our trees AFTER they have been individually positioned depending on the
//    // instance buffer, which means they will not be centered at the point (0,0,0))
//    treeWorld = XMMatrixIdentity();
//    /*************************************************************************************************/
//
//    if (!LoadMD5Model(L"Female.md5mesh", NewMD5Model, meshSRV, textureNameArray))
//        return false;
//    if (!LoadMD5Anim(L"Female.md5anim", NewMD5Model))
//        return false;
//
//
//    /************************************New Stuff****************************************************/
//    // Create Leaf geometry (quad)
//    Vertex v[] =
//    {
//        // Front Face
//        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//        Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//        Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
//    };
//
//    DWORD indices[] = {
//        // Front Face
//        0,  1,  2,
//        0,  2,  3,
//    };
//
//    D3D11_BUFFER_DESC indexBufferDesc;
//    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
//
//    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
//    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//    indexBufferDesc.CPUAccessFlags = 0;
//    indexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA iinitData;
//
//    iinitData.pSysMem = indices;
//    d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &quadIndexBuffer);
//
//
//    D3D11_BUFFER_DESC vertexBufferDesc;
//    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
//
//    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
//    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//    vertexBufferDesc.CPUAccessFlags = 0;
//    vertexBufferDesc.MiscFlags = 0;
//
//    D3D11_SUBRESOURCE_DATA vertexBufferData;
//
//    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
//    vertexBufferData.pSysMem = v;
//    hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &quadVertBuffer);
//
//    // Now we load in the leaf texture
//    hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, L"leaf.png",
//        NULL, NULL, &leafTexture, NULL);
//
//    // Here we create the leaf world matrices, that will be the leafs
//    // position and orientation on the tree each individual tree. We will create an array of matrices
//    // for the leaves that we will send to the shaders in the cbPerInstance constant buffer
//    // This matrix array is used "per tree", so that each tree gets the exact same number of leaves,
//    // with the same orientation, position, and scale as all of the other trees
//    // Start by initializing the matrix array
//    srand(100);
//    XMFLOAT3 fTPos;
//    XMMATRIX rotationMatrix;
//    XMMATRIX tempMatrix;
//    for (int i = 0; i < numLeavesPerTree; i++)
//    {
//        float rotX = (rand() % 2000) / 500.0f; // Value between 0 and 4 PI (two circles, makes it slightly more mixed)
//        float rotY = (rand() % 2000) / 500.0f;
//        float rotZ = (rand() % 2000) / 500.0f;
//
//        // the rand() function is slightly more biased towards lower numbers, which would make the center of
//        // the leaf "mass" be more dense with leaves than the outside of the "sphere" of leaves we are making.
//        // We want the outside of the "sphere" of leaves to be more dense than the inside, so the way we do this
//        // is getting a distance value between 0 and 4, we then subtract that value from 6, so that the very center
//        // does not have any leaves. then below you can see we are checking to see if the distance is greater than 4
//        // (because the tree branches are approximately 4 units radius from the center of the tree). If the distance
//        // is greater than 4, then we set it at 4, which will make the edge of the "sphere" of leaves more densly
//        // populated than the center of the leaf mass
//        float distFromCenter = 6.0f - ((rand() % 1000) / 250.0f);
//
//        if (distFromCenter > 4.0f)
//            distFromCenter = 4.0f;
//
//        // Now we create a vector with the length of distFromCenter, by simply setting it's x component as distFromCenter.
//        // We will now rotate the vector, which will give us the "sphere" of leaves after we have rotated all the leaves.
//        // We do not want a perfect sphere, more like a half sphere to cover the branches, so we check to see if the y
//        // value is less than -1.0f (giving us slightly more than half a sphere), and if it is, negate it so it is reflected
//        // across the xz plane
//        tempPos = XMVectorSet(distFromCenter, 0.0f, 0.0f, 0.0f);
//        rotationMatrix = XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ);
//        tempPos = XMVector3TransformCoord(tempPos, rotationMatrix);
//
//        if (XMVectorGetY(tempPos) < -1.0f)
//            tempPos = XMVectorSetY(tempPos, -XMVectorGetY(tempPos));
//
//        // Now we create our leaves "tree" matrix (this is not the leaves "world matrix", because we are not
//        // defining the leaves position, orientation, and scale in world space, but instead in "tree" space
//        XMStoreFloat3(&fTPos, tempPos);
//
//        Scale = XMMatrixScaling(0.25f, 0.25f, 0.25f);
//        Translation = XMMatrixTranslation(fTPos.x, fTPos.y + 8.0f, fTPos.z);
//        tempMatrix = Scale * rotationMatrix * Translation;
//
//        // To make things simple, we just store the matrix directly into our cbPerInst structure
//        cbPerInst.leafOnTree[i] = XMMatrixTranspose(tempMatrix);
//    }
//    /*************************************************************************************************/
//
//    //Compile Shaders from shader file
//    hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "VS", "vs_4_0", 0, 0, 0, &VS_Buffer, 0, 0);
//    hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "PS", "ps_4_0", 0, 0, 0, &PS_Buffer, 0, 0);
//    hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "D2D_PS", "ps_4_0", 0, 0, 0, &D2D_PS_Buffer, 0, 0);
//    hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_VS", "vs_4_0", 0, 0, 0, &SKYMAP_VS_Buffer, 0, 0);
//    hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_PS", "ps_4_0", 0, 0, 0, &SKYMAP_PS_Buffer, 0, 0);
//
//    //Create the Shader Objects
//    hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
//    hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
//
//    hr = d3d11Device->CreatePixelShader(D2D_PS_Buffer->GetBufferPointer(), D2D_PS_Buffer->GetBufferSize(), NULL, &D2D_PS);
//    hr = d3d11Device->CreateVertexShader(SKYMAP_VS_Buffer->GetBufferPointer(), SKYMAP_VS_Buffer->GetBufferSize(), NULL, &SKYMAP_VS);
//    hr = d3d11Device->CreatePixelShader(SKYMAP_PS_Buffer->GetBufferPointer(), SKYMAP_PS_Buffer->GetBufferSize(), NULL, &SKYMAP_PS);
//
//
//    //Set Vertex and Pixel Shaders
//    d3d11DevCon->VSSetShader(VS, 0, 0);
//    d3d11DevCon->PSSetShader(PS, 0, 0);
//
//    light.pos = XMFLOAT3(0.0f, 7.0f, 0.0f);
//    light.dir = XMFLOAT3(-0.5f, 0.75f, -0.5f);
//    light.range = 1000.0f;
//    light.cone = 12.0f;
//    light.att = XMFLOAT3(0.4f, 0.02f, 0.000f);
//    light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
//    light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//
//    //Create the Input Layout
//    hr = d3d11Device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
//        VS_Buffer->GetBufferSize(), &vertLayout);
//
//    /************************************New Stuff****************************************************/
//    // Create the leaf Input Layout. We create a second layout for the leaves because the instance
//    // element used for the positions is different than the instance element used for the positions
//    // when drawing the trees. We want to only move to the next element in the instance buffer
//    // AFTER we have drawn ALL the leaves for the current tree
//    hr = d3d11Device->CreateInputLayout(leafLayout, numLeafElements, VS_Buffer->GetBufferPointer(),
//        VS_Buffer->GetBufferSize(), &leafVertLayout);
//    /*************************************************************************************************/
//
//    //Set the Input Layout
//    d3d11DevCon->IASetInputLayout(vertLayout);
//
//    //Set Primitive Topology
//    d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//    //Create the Viewport
//    D3D11_VIEWPORT viewport;
//    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
//
//    viewport.TopLeftX = 0;
//    viewport.TopLeftY = 0;
//    viewport.Width = Width;
//    viewport.Height = Height;
//    viewport.MinDepth = 0.0f;
//    viewport.MaxDepth = 1.0f;
//
//    //Set the Viewport
//    d3d11DevCon->RSSetViewports(1, &viewport);
//
//    //Create the buffer to send to the cbuffer in effect file
//    D3D11_BUFFER_DESC cbbd;
//    ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
//
//    cbbd.Usage = D3D11_USAGE_DEFAULT;
//    cbbd.ByteWidth = sizeof(cbPerObject);
//    cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//    cbbd.CPUAccessFlags = 0;
//    cbbd.MiscFlags = 0;
//
//    hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);
//
//    //Create the buffer to send to the cbuffer per frame in effect file
//    ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
//
//    cbbd.Usage = D3D11_USAGE_DEFAULT;
//    cbbd.ByteWidth = sizeof(cbPerFrame);
//    cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//    cbbd.CPUAccessFlags = 0;
//    cbbd.MiscFlags = 0;
//
//    hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerFrameBuffer);
//
//    /************************************New Stuff****************************************************/
//    //Create the buffer to send to the cbuffer per instance in effect file
//    ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
//
//    cbbd.Usage = D3D11_USAGE_DEFAULT;
//    // We have already defined how many elements are in our leaf matrix array inside the cbPerScene structure,
//    // so we only need the size of the entire structure here, because the number of leaves per tree will not
//    // change throughout the scene.
//    cbbd.ByteWidth = sizeof(cbPerScene);
//    cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//    cbbd.CPUAccessFlags = 0;
//    cbbd.MiscFlags = 0;
//
//    hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerInstanceBuffer);
//
//    // Now we set the constant buffer per instance (used only for the leaves in this lesson)
//    // We are sending this buffer to the GPU now, because it will not be updated throughout the scene,
//    // so it would be a waste of time to be sending this to the GPU every frame, when we only have to
//    // send it once per scene. This is why constant buffers should be separated depending on how often
//    // they are updated, so that you do not send data to the GPU more often than you have to. It's a
//    // performance thing ;)
//    d3d11DevCon->UpdateSubresource(cbPerInstanceBuffer, 0, NULL, &cbPerInst, 0, 0);
//    /*************************************************************************************************/
//
//    Scale = XMMatrixScaling(0.25f, 0.25f, 0.25f);            // The model is a bit too large for our scene, so make it smaller
//    Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
//    playerCharWorld = Scale * Translation;
//
//    //Camera information
//    camPosition = XMVectorSet(0.0f, 10.0f, 8.0f, 0.0f);
//    camTarget = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
//    camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//    //Set the View matrix
//    camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
//
//    //Set the Projection matrix
//    camProjection = XMMatrixPerspectiveFovLH(3.14f / 4.0f, (float)Width / Height, 1.0f, 1000.0f);
//
//    D3D11_BLEND_DESC blendDesc;
//    ZeroMemory(&blendDesc, sizeof(blendDesc));
//
//    D3D11_RENDER_TARGET_BLEND_DESC rtbd;
//    ZeroMemory(&rtbd, sizeof(rtbd));
//
//    rtbd.BlendEnable = true;
//    rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
//    rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
//    rtbd.BlendOp = D3D11_BLEND_OP_ADD;
//    rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
//    rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
//    rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
//    rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;
//
//    blendDesc.AlphaToCoverageEnable = false;
//    blendDesc.RenderTarget[0] = rtbd;
//
//    d3d11Device->CreateBlendState(&blendDesc, &d2dTransparency);
//
//    ZeroMemory(&rtbd, sizeof(rtbd));
//
//    rtbd.BlendEnable = true;
//    rtbd.SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
//    rtbd.DestBlend = D3D11_BLEND_SRC_ALPHA;
//    rtbd.BlendOp = D3D11_BLEND_OP_ADD;
//    rtbd.SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
//    rtbd.DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
//    rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
//    rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;
//
//    blendDesc.AlphaToCoverageEnable = false;
//    blendDesc.RenderTarget[0] = rtbd;
//
//    d3d11Device->CreateBlendState(&blendDesc, &Transparency);
//
//    ZeroMemory(&rtbd, sizeof(rtbd));
//
//    rtbd.BlendEnable = true;
//    rtbd.SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
//    rtbd.DestBlend = D3D11_BLEND_SRC_ALPHA;
//    rtbd.BlendOp = D3D11_BLEND_OP_ADD;
//    rtbd.SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
//    rtbd.DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
//    rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
//    rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;
//
//    blendDesc.AlphaToCoverageEnable = true;
//    blendDesc.RenderTarget[0] = rtbd;
//
//    d3d11Device->CreateBlendState(&blendDesc, &leafTransparency);
//
//    ///Load Skymap's cube texture///
//    D3DX11_IMAGE_LOAD_INFO loadSMInfo;
//    loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
//
//    ID3D11Texture2D* SMTexture = 0;
//    hr = D3DX11CreateTextureFromFile(d3d11Device, L"skymap.dds",
//        &loadSMInfo, 0, (ID3D11Resource**)&SMTexture, 0);
//
//    D3D11_TEXTURE2D_DESC SMTextureDesc;
//    SMTexture->GetDesc(&SMTextureDesc);
//
//    D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
//    SMViewDesc.Format = SMTextureDesc.Format;
//    SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
//    SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
//    SMViewDesc.TextureCube.MostDetailedMip = 0;
//
//    hr = d3d11Device->CreateShaderResourceView(SMTexture, &SMViewDesc, &smrv);
//
//    // Describe the Sample State
//    D3D11_SAMPLER_DESC sampDesc;
//    ZeroMemory(&sampDesc, sizeof(sampDesc));
//    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
//    sampDesc.MinLOD = 0;
//    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
//
//    //Create the Sample State
//    hr = d3d11Device->CreateSamplerState(&sampDesc, &CubesTexSamplerState);
//
//    D3D11_RASTERIZER_DESC cmdesc;
//
//    ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
//    cmdesc.FillMode = D3D11_FILL_SOLID;
//    cmdesc.CullMode = D3D11_CULL_BACK;
//    cmdesc.FrontCounterClockwise = true;
//    hr = d3d11Device->CreateRasterizerState(&cmdesc, &CCWcullMode);
//
//    cmdesc.FrontCounterClockwise = false;
//
//    hr = d3d11Device->CreateRasterizerState(&cmdesc, &CWcullMode);
//
//    cmdesc.CullMode = D3D11_CULL_NONE;
//    //cmdesc.FillMode = D3D11_FILL_WIREFRAME;
//    hr = d3d11Device->CreateRasterizerState(&cmdesc, &RSCullNone);
//
//    D3D11_DEPTH_STENCIL_DESC dssDesc;
//    ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
//    dssDesc.DepthEnable = true;
//    dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//    dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
//
//    d3d11Device->CreateDepthStencilState(&dssDesc, &DSLessEqual);
//
//    return true;
//}
//
//void StartTimer()
//{
//    LARGE_INTEGER frequencyCount;
//    QueryPerformanceFrequency(&frequencyCount);
//
//    countsPerSecond = double(frequencyCount.QuadPart);
//
//    QueryPerformanceCounter(&frequencyCount);
//    CounterStart = frequencyCount.QuadPart;
//}
//
//double GetTime()
//{
//    LARGE_INTEGER currentTime;
//    QueryPerformanceCounter(&currentTime);
//    return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
//}
//
//double GetFrameTime()
//{
//    LARGE_INTEGER currentTime;
//    __int64 tickCount;
//    QueryPerformanceCounter(&currentTime);
//
//    tickCount = currentTime.QuadPart - frameTimeOld;
//    frameTimeOld = currentTime.QuadPart;
//
//    if (tickCount < 0.0f)
//        tickCount = 0.0f;
//
//    return float(tickCount) / countsPerSecond;
//}
//
//void UpdateScene(double time)
//{
//    //Reset sphereWorld
//    sphereWorld = XMMatrixIdentity();
//
//    //Define sphereWorld's world space matrix
//    Scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
//    //Make sure the sphere is always centered around camera
//    Translation = XMMatrixTranslation(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));
//
//    //Set sphereWorld's world space using the transformations
//    sphereWorld = Scale * Translation;
//
//    //the loaded models world space
//    meshWorld = XMMatrixIdentity();
//
//    Rotation = XMMatrixRotationY(3.14f);
//    Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
//    Translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
//
//    meshWorld = Rotation * Scale * Translation;
//}
//
//void RenderText(std::wstring text, int inInt)
//{
//
//    d3d11DevCon->PSSetShader(D2D_PS, 0, 0);
//
//    //Release the D3D 11 Device
//    keyedMutex11->ReleaseSync(0);
//
//    //Use D3D10.1 device
//    keyedMutex10->AcquireSync(0, 5);
//
//    //Draw D2D content        
//    D2DRenderTarget->BeginDraw();
//
//    //Clear D2D Background
//    D2DRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
//
//    //Create our string
//    std::wostringstream printString;
//    printString << text << inInt;
//    printText = printString.str();
//
//    //Set the Font Color
//    D2D1_COLOR_F FontColor = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
//
//    //Set the brush color D2D will use to draw with
//    Brush->SetColor(FontColor);
//
//    //Create the D2D Render Area
//    D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, Width, Height);
//
//    //Draw the Text
//    D2DRenderTarget->DrawText(
//        printText.c_str(),
//        wcslen(printText.c_str()),
//        TextFormat,
//        layoutRect,
//        Brush
//    );
//
//    D2DRenderTarget->EndDraw();
//
//    //Release the D3D10.1 Device
//    keyedMutex10->ReleaseSync(1);
//
//    //Use the D3D11 Device
//    keyedMutex11->AcquireSync(1, 5);
//
//    //Use the shader resource representing the direct2d render target
//    //to texture a square which is rendered in screen space so it
//    //overlays on top of our entire scene. We use alpha blending so
//    //that the entire background of the D2D render target is "invisible",
//    //And only the stuff we draw with D2D will be visible (the text)
//
//    //Set the blend state for D2D render target texture objects
//    d3d11DevCon->OMSetBlendState(d2dTransparency, NULL, 0xffffffff);
//
//    //Set the d2d Index buffer
//    d3d11DevCon->IASetIndexBuffer(d2dIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//    //Set the d2d vertex buffer
//    UINT stride = sizeof(Vertex);
//    UINT offset = 0;
//    d3d11DevCon->IASetVertexBuffers(0, 1, &d2dVertBuffer, &stride, &offset);
//
//    WVP = XMMatrixIdentity();
//    cbPerObj.WVP = XMMatrixTranspose(WVP);
//    d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//    d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//    d3d11DevCon->PSSetShaderResources(0, 1, &d2dTexture);
//    d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//    d3d11DevCon->RSSetState(CWcullMode);
//    d3d11DevCon->DrawIndexed(6, 0, 0);
//}
//
//void DrawScene()
//{
//    //Clear our render target and depth/stencil view
//    float bgColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
//    d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);
//    d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//
//    constbuffPerFrame.light = light;
//    d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
//    d3d11DevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);
//
//    //Set our Render Target
//    d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
//
//    //Set the default blend state (no blending) for opaque objects
//    d3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
//
//    // Set vertex buffer and pixel shader
//    d3d11DevCon->VSSetShader(VS, 0, 0);
//    d3d11DevCon->PSSetShader(PS, 0, 0);
//
//    /************************************New Stuff****************************************************/
//    ///***Draw INSTANCED Leaf Models***///
//    // We are now binding two buffers to the input assembler, one for the vertex data,
//    // and one for the instance data, so we will have to create a strides array, offsets array
//    // and buffer array.
//    UINT strides[2] = { sizeof(Vertex), sizeof(InstanceData) };
//    UINT offsets[2] = { 0, 0 };
//
//    // Store the vertex and instance buffers into an array
//    // The leaves will use the same instance buffer as the trees, because we need each leaf
//    // to go to a certain tree
//    ID3D11Buffer* vertInstBuffers[2] = { quadVertBuffer, treeInstanceBuff };
//
//    // Set the leaf input layout. This is where we will set our special input layout for our leaves
//    d3d11DevCon->IASetInputLayout(leafVertLayout);
//
//    //Set the models index buffer (same as before)
//    d3d11DevCon->IASetIndexBuffer(quadIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//
//    //Set the models vertex and isntance buffer using the arrays created above
//    d3d11DevCon->IASetVertexBuffers(0, 2, vertInstBuffers, strides, offsets);
//
//    //Set the WVP matrix and send it to the constant buffer in effect file
//    WVP = treeWorld * camView * camProjection;
//    cbPerObj.WVP = XMMatrixTranspose(WVP);
//    cbPerObj.World = XMMatrixTranspose(treeWorld);
//    cbPerObj.hasTexture = true;        // We'll assume all md5 subsets have textures
//    cbPerObj.hasNormMap = false;    // We'll also assume md5 models have no normal map (easy to change later though)
//    cbPerObj.isInstance = true;        // Tell shaders if this is instanced data so it will know to use instance data or not
//    cbPerObj.isLeaf = true;        // Tell shaders if this is the leaf instance so it will know to the cbPerInstance data or not
//    d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//
//    // We are sending two constant buffers to the vertex shader now, wo we will create an array of them
//    ID3D11Buffer* vsConstBuffers[2] = { cbPerObjectBuffer, cbPerInstanceBuffer };
//    d3d11DevCon->VSSetConstantBuffers(0, 2, vsConstBuffers);
//    d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
//    d3d11DevCon->PSSetShaderResources(0, 1, &leafTexture);
//    d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//    d3d11DevCon->RSSetState(RSCullNone);
//    d3d11DevCon->DrawIndexedInstanced(6, numLeavesPerTree * numTrees, 0, 0, 0);
//
//    // Reset the default Input Layout
//    d3d11DevCon->IASetInputLayout(vertLayout);
//
//    /////Draw our tree instances/////
//    for (int i = 0; i < treeSubsets; ++i)
//    {
//        // Store the vertex and instance buffers into an array
//        ID3D11Buffer* vertInstBuffers[2] = { treeVertBuff, treeInstanceBuff };
//
//        //Set the models index buffer (same as before)
//        d3d11DevCon->IASetIndexBuffer(treeIndexBuff, DXGI_FORMAT_R32_UINT, 0);
//        //Set the models vertex buffer
//        d3d11DevCon->IASetVertexBuffers(0, 2, vertInstBuffers, strides, offsets);
//
//        //Set the WVP matrix and send it to the constant buffer in effect file
//        WVP = treeWorld * camView * camProjection;
//        cbPerObj.WVP = XMMatrixTranspose(WVP);
//        cbPerObj.World = XMMatrixTranspose(treeWorld);
//        cbPerObj.difColor = material[treeSubsetTexture[i]].difColor;
//        cbPerObj.hasTexture = material[treeSubsetTexture[i]].hasTexture;
//        cbPerObj.hasNormMap = material[treeSubsetTexture[i]].hasNormMap;
//        cbPerObj.isInstance = true;        // Tell shaders if this is instanced data so it will know to use instance data or not
//        cbPerObj.isLeaf = false;        // Tell shaders if this is the leaf instance so it will know to the cbPerInstance data or not
//        d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//        d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//        d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
//        if (material[treeSubsetTexture[i]].hasTexture)
//            d3d11DevCon->PSSetShaderResources(0, 1, &meshSRV[material[treeSubsetTexture[i]].texArrayIndex]);
//        if (material[treeSubsetTexture[i]].hasNormMap)
//            d3d11DevCon->PSSetShaderResources(1, 1, &meshSRV[material[treeSubsetTexture[i]].normMapTexArrayIndex]);
//        d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//        d3d11DevCon->RSSetState(RSCullNone);
//        int indexStart = treeSubsetIndexStart[i];
//        int indexDrawAmount = treeSubsetIndexStart[i + 1] - treeSubsetIndexStart[i];
//        if (!material[meshSubsetTexture[i]].transparent)
//            d3d11DevCon->DrawIndexedInstanced(indexDrawAmount, numTrees, indexStart, 0, 0);
//    }
//    /*************************************************************************************************/
//
//    //Set Vertex and Pixel Shaders
//    d3d11DevCon->VSSetShader(VS, 0, 0);
//    d3d11DevCon->PSSetShader(PS, 0, 0);
//
//    UINT stride = sizeof(Vertex);
//    UINT offset = 0;
//
//    ///***Draw MD5 Model***///
//    for (int i = 0; i < NewMD5Model.numSubsets; i++)
//    {
//        //Set the grounds index buffer
//        d3d11DevCon->IASetIndexBuffer(NewMD5Model.subsets[i].indexBuff, DXGI_FORMAT_R32_UINT, 0);
//        //Set the grounds vertex buffer
//        d3d11DevCon->IASetVertexBuffers(0, 1, &NewMD5Model.subsets[i].vertBuff, &stride, &offset);
//
//        //Set the WVP matrix and send it to the constant buffer in effect file
//        WVP = playerCharWorld * camView * camProjection;
//        cbPerObj.WVP = XMMatrixTranspose(WVP);
//        cbPerObj.World = XMMatrixTranspose(playerCharWorld);
//        cbPerObj.hasTexture = true;        // We'll assume all md5 subsets have textures
//        cbPerObj.hasNormMap = false;    // We'll also assume md5 models have no normal map (easy to change later though)
//        cbPerObj.isInstance = false;        // Tell shaders if this is instanced data so it will know to use instance data or not
//        cbPerObj.isLeaf = false;        // Tell shaders if this is the leaf instance so it will know to the cbPerInstance data or not
//        d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//        d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//        d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
//        d3d11DevCon->PSSetShaderResources(0, 1, &meshSRV[NewMD5Model.subsets[i].texArrayIndex]);
//        d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//        d3d11DevCon->RSSetState(RSCullNone);
//        d3d11DevCon->DrawIndexed(NewMD5Model.subsets[i].indices.size(), 0, 0);
//    }
//
//    /////Draw our model's NON-transparent subsets/////
//    for (int i = 0; i < meshSubsets; ++i)
//    {
//        //Set the grounds index buffer
//        d3d11DevCon->IASetIndexBuffer(meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
//        //Set the grounds vertex buffer
//        d3d11DevCon->IASetVertexBuffers(0, 1, &meshVertBuff, &stride, &offset);
//
//        //Set the WVP matrix and send it to the constant buffer in effect file
//        WVP = meshWorld * camView * camProjection;
//        cbPerObj.WVP = XMMatrixTranspose(WVP);
//        cbPerObj.World = XMMatrixTranspose(meshWorld);
//        cbPerObj.difColor = material[meshSubsetTexture[i]].difColor;
//        cbPerObj.hasTexture = material[meshSubsetTexture[i]].hasTexture;
//        cbPerObj.hasNormMap = material[meshSubsetTexture[i]].hasNormMap;
//        cbPerObj.isInstance = false;        // Tell shaders if this is instanced data so it will know to use instance data or not
//        cbPerObj.isLeaf = false;        // Tell shaders if this is the leaf instance so it will know to the cbPerInstance data or not
//        d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//        d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//        d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
//        if (material[meshSubsetTexture[i]].hasTexture)
//            d3d11DevCon->PSSetShaderResources(0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex]);
//        if (material[meshSubsetTexture[i]].hasNormMap)
//            d3d11DevCon->PSSetShaderResources(1, 1, &meshSRV[material[meshSubsetTexture[i]].normMapTexArrayIndex]);
//        d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//        d3d11DevCon->RSSetState(RSCullNone);
//        int indexStart = meshSubsetIndexStart[i];
//        int indexDrawAmount = meshSubsetIndexStart[i + 1] - meshSubsetIndexStart[i];
//        if (!material[meshSubsetTexture[i]].transparent)
//            d3d11DevCon->DrawIndexed(indexDrawAmount, indexStart, 0);
//    }
//
//    /////Draw the Sky's Sphere//////
//    //Set the spheres index buffer
//    d3d11DevCon->IASetIndexBuffer(sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//    //Set the spheres vertex buffer
//    d3d11DevCon->IASetVertexBuffers(0, 1, &sphereVertBuffer, &stride, &offset);
//
//    //Set the WVP matrix and send it to the constant buffer in effect file
//    WVP = sphereWorld * camView * camProjection;
//    cbPerObj.WVP = XMMatrixTranspose(WVP);
//    cbPerObj.World = XMMatrixTranspose(sphereWorld);
//    cbPerObj.isInstance = false;        // Tell shaders if this is instanced data so it will know to use instance data or not    
//    cbPerObj.isLeaf = false;        // Tell shaders if this is the leaf instance so it will know to the cbPerInstance data or not
//    d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//    d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//    //Send our skymap resource view to pixel shader
//    d3d11DevCon->PSSetShaderResources(0, 1, &smrv);
//    d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//    //Set the new VS and PS shaders
//    d3d11DevCon->VSSetShader(SKYMAP_VS, 0, 0);
//    d3d11DevCon->PSSetShader(SKYMAP_PS, 0, 0);
//    //Set the new depth/stencil and RS states
//    d3d11DevCon->OMSetDepthStencilState(DSLessEqual, 0);
//    d3d11DevCon->RSSetState(RSCullNone);
//    d3d11DevCon->DrawIndexed(NumSphereFaces * 3, 0, 0);
//
//    //Set the default VS, PS shaders and depth/stencil state
//    d3d11DevCon->VSSetShader(VS, 0, 0);
//    d3d11DevCon->PSSetShader(PS, 0, 0);
//    d3d11DevCon->OMSetDepthStencilState(NULL, 0);
//
//    /////Draw our model's TRANSPARENT subsets now/////
//    //Set our blend state
//    d3d11DevCon->OMSetBlendState(Transparency, NULL, 0xffffffff);
//
//    for (int i = 0; i < meshSubsets; ++i)
//    {
//        //Set the grounds index buffer
//        d3d11DevCon->IASetIndexBuffer(meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
//        //Set the grounds vertex buffer
//        d3d11DevCon->IASetVertexBuffers(0, 1, &meshVertBuff, &stride, &offset);
//
//        //Set the WVP matrix and send it to the constant buffer in effect file
//        WVP = meshWorld * camView * camProjection;
//        cbPerObj.WVP = XMMatrixTranspose(WVP);
//        cbPerObj.World = XMMatrixTranspose(meshWorld);
//        cbPerObj.difColor = material[meshSubsetTexture[i]].difColor;
//        cbPerObj.hasTexture = material[meshSubsetTexture[i]].hasTexture;
//        cbPerObj.hasNormMap = material[meshSubsetTexture[i]].hasNormMap;
//        cbPerObj.isInstance = false;        // Tell shaders if this is instanced data so it will know to use instance data or not
//        cbPerObj.isLeaf = false;        // Tell shaders if this is the leaf instance so it will know to the cbPerInstance data or not
//        d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
//        d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
//        d3d11DevCon->PSSetConstantBuffers(1, 1, &cbPerObjectBuffer);
//        if (material[meshSubsetTexture[i]].hasTexture)
//            d3d11DevCon->PSSetShaderResources(0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex]);
//        if (material[meshSubsetTexture[i]].hasNormMap)
//            d3d11DevCon->PSSetShaderResources(1, 1, &meshSRV[material[meshSubsetTexture[i]].normMapTexArrayIndex]);
//        d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);
//
//        d3d11DevCon->RSSetState(RSCullNone);
//        int indexStart = meshSubsetIndexStart[i];
//        int indexDrawAmount = meshSubsetIndexStart[i + 1] - meshSubsetIndexStart[i];
//
//        if (material[meshSubsetTexture[i]].transparent)
//            d3d11DevCon->DrawIndexed(indexDrawAmount, indexStart, 0);
//    }
//
//    RenderText(L"FPS: ", fps);
//
//    //Present the backbuffer to the screen
//    SwapChain->Present(0, 0);
//}
//
//int messageloop() {
//    MSG msg;
//    ZeroMemory(&msg, sizeof(MSG));
//    while (true)
//    {
//        BOOL PeekMessageL(
//            LPMSG lpMsg,
//            HWND hWnd,
//            UINT wMsgFilterMin,
//            UINT wMsgFilterMax,
//            UINT wRemoveMsg
//        );
//
//        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//        {
//            if (msg.message == WM_QUIT)
//                break;
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//        else {
//            // run game code    
//            frameCount++;
//            if (GetTime() > 1.0f)
//            {
//                fps = frameCount;
//                frameCount = 0;
//                StartTimer();
//            }
//
//            frameTime = GetFrameTime();
//
//            DetectInput(frameTime);
//            UpdateScene(frameTime);
//            DrawScene();
//        }
//    }
//    return msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd,
//    UINT msg,
//    WPARAM wParam,
//    LPARAM lParam)
//{
//    switch (msg)
//    {
//    case WM_KEYDOWN:
//        if (wParam == VK_ESCAPE) {
//            DestroyWindow(hwnd);
//        }
//        return 0;
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        return 0;
//    }
//    return DefWindowProc(hwnd,
//        msg,
//        wParam,
//        lParam);
//}