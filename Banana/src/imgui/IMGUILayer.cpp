#include "imgui/IMGUILayer.h"
#include "imgui.h"

namespace Banana
{

  IMGUILayer::IMGUILayer(const std::string& name)
  : name(name)
  {

  }

  void IMGUILayer::OnAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();


  }

  void IMGUILayer::OnDetach()
  {

  }

  void IMGUILayer::OnUpdate()
  {
    ImGui::Render();
  }

  void IMGUILayer::OnEvent(Event& event)
  {

  }

};