#include"IMgui/imgui.h"
#include"IMgui/imgui_impl_win32.h"
#include"IMgui/imgui_impl_dx11.h"
#include"player.h"
using namespace std;

class imgui {
public:
    static imgui* GetInstance() {
        static imgui instance;
        return &instance;
    }

    void setup();
  //  void mouseDown(MouseEvent event);
    void update();
    void draw();
};

void imgui::setup()
{
}

//void imgui_sampleApp::mouseDown(MouseEvent event)
//{
//}

void imgui::update()
{
}


void imgui::draw()
{
    
 //   ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
 //   ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
 // /*  ImGui::SetNextWindowPos(ImVec2(20, 20),ImGui::once ImGuiSetCond_Once);
 //   ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);*/
 ////   gl::clear(Color(0, 0, 0));

 //   ImGui::Begin("config 1");

 //   float pos[3] = { Player::GetInstance()->GetPos().x,Player::GetInstance()->GetPos().y,Player::GetInstance()->GetPos().z};
 //   ImGui::DragFloat3("Position",pos);

 //   ImGui::End();

 //   ImGui::PopStyleColor();
 //   ImGui::PopStyleColor();
}

//CINDER_APP(imgui_sampleApp, RendererGl)