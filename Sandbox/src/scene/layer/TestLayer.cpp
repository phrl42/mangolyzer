#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

#include <cstring>

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
    : name(name)
  {

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
    //memcpy(samples, pOutput, sizeof(float) * frameCount);
    if(((float*)pOutput)[0] > 0)
    {
      for(size_t i = 0; i < frameCount; ++i)
      {
        LOG(((float*)pOutput)[i]);
      }
    }
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
  }

  void TestLayer::OnAttach()
  {
    ma_result result = ma_decoder_init_file("assets/sounds/menu.wav", NULL, &decoder);
    if (result != MA_SUCCESS) {
      LOG("Could not load sound");
    }

    ma_data_source_set_looping(&decoder, MA_TRUE);

    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate        = decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &decoder;

    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
      LOG("Failed to open playback device.\n");
      ma_decoder_uninit(&decoder);
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
      LOG("Failed to start playback device.\n");
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
