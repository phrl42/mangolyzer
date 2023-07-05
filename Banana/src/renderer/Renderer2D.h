#pragma once
#include "_Banana.h"
#include "renderer/Texture.h"
#include "utility.h"
namespace Banana
{
  struct Texture2D;

  class Renderer2D
  {
  public:

    static void Init();
    static void Shutdown();


    static void BeginScene();    
    static void EndScene();

    static void StartBatch();
    static void NextBatch();

    static void Flush();

    static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const Shr<Texture2D>& texture);
  };
};