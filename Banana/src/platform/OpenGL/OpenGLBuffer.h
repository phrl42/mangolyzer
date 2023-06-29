#include "renderer/Buffer.h"

namespace Banana
{
  class OpenGLVertexBuffer : public VertexBuffer
  {
  public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; }
    virtual const BufferLayout& GetLayout() override { return layout; }

  private:
    BufferLayout layout;
    uint32_t id;
  };


  class OpenGLIndexBuffer : public IndexBuffer
  {
  public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

    virtual ~OpenGLIndexBuffer() override;

    virtual void Bind() override;
    virtual void Unbind() override;
    
    virtual uint32_t GetCount() override { return count; }

  private:
    uint32_t id;
    uint32_t count;
  };
};