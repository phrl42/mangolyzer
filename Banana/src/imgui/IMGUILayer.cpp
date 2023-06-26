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
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
  }

  void IMGUILayer::OnDetach()
  {

  }

  void IMGUILayer::OnUpdate()
  {
    static bool show = false;
    static bool show_another_window = true;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(&show);

    // Rendering
    ImGui::Render();
    
    int display_w, display_h;
    glfwGetFramebufferSize((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void IMGUILayer::OnEvent(Event& event)
  {

  }

};