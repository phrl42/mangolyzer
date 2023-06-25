#include "imgui/IMGUILayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Application.hpp"

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
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable some options

    ImGui_ImplOpenGL3_Init("#version 460");
  }

  void IMGUILayer::OnDetach()
  {

  }

  void IMGUILayer::OnUpdate()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();

    float time = (float)glfwGetTime();
    
    Application& app = Application::GetInstance();


    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    io.DeltaTime = l_time > 0.0 ? (time - l_time) : (1.0f / 60.0f);
    l_time = time;

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui::EndFrame();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void IMGUILayer::OnEvent(Event& event)
  {

  }

};