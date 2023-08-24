#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

#include <cstring>

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name), b_sound(Banana::Sound("assets/sounds/menu.wav", true))
  {
    b_sound.Start();
  }

  TestLayer::~TestLayer()
  {

  }

#define MAX_SIZE 5000

  float samples[MAX_SIZE];
  void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
  {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) 
    {
      return;
    }
    memcpy(samples, pOutput, sizeof(float) * frameCount);

    for(size_t i = 0; i < frameCount; ++i)
    {
      LOG(std::to_string(samples[i]));
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
  }

  void TestLayer::OnAttach()
  {
    ma_device_config deviceConfig;

    if (ma_result result = ma_decoder_init_file("assets/sounds/menu.wav", NULL, &decoder); result != MA_SUCCESS) 
    {
      LOG("Could not load file");
    }

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) 
    {
      LOG("Failed to open playback device.");
      ma_decoder_uninit(&decoder);
    }

    if (ma_device_start(&device) != MA_SUCCESS) 
    {
      LOG("Failed to start playback device.");
      ma_device_uninit(&device);
      ma_decoder_uninit(&decoder);
    }
  }

  void TestLayer::OnDetach()
  {
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
  }

  void TestLayer::OnEvent(Banana::Event& event)
  {

  }

  void TestLayer::OnUpdate(float dt)
  {

  }
};
