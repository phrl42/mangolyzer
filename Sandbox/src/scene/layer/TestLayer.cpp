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
  
  std::string path_to_music = "assets/sounds/song.mp3";

  float samples[MAX_SIZE];
  volatile int sample_count = 0;

  void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
  {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) 
    {
      return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    memcpy((void*)samples, pOutput, sizeof(float) * frameCount * 2);
    sample_count = frameCount;

    // this loops better than the api
    if(samples[frameCount] == 0)
    {
      //ma_decoder_init_file(path_to_music.c_str(), NULL, pDecoder);
    }

    (void)pInput;
  }

  void TestLayer::OnAttach()
  {
    ma_result result = ma_decoder_init_file(path_to_music.c_str(), NULL, &decoder);
    if (result != MA_SUCCESS) {
      LOG("Could not load sound");
    }

    if(ma_result result = ma_data_source_set_looping(&decoder, 1); result != MA_SUCCESS)
    {
      LOG("Could not loop sound: " + std::to_string(result));
    }

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
    for(size_t i = 0; i < QUADS; i++)
    {
      ent[i].AddComponent(new Banana::QuadComponent());
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
    float one_width = 2.0f / QUADS;
    for(size_t i = 0; i < QUADS; i++)
    {
      ent[i].transform.proj = Banana::Projection::NONE;
      ent[i].transform.pos = {(i * one_width) - 1, 0, 0};
      ent[i].transform.size = {one_width, samples[i], 0};
      ent[i].transform.color = {samples[i] * 2, samples[i] + 0.6, samples[i] * 2, 1.0f};
      ent[i].Render(dt);
    }
  }
};
