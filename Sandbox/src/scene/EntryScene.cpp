#include "scene/EntryScene.h"
#include "scene/layer/SampleLayer.h"
#include "scene/layer/FreqLayer.h"
#include "layer/Layer.h"

#include "renderer/Renderer2D.h"

#include "imgui/IMGUILayer.h"

#include <cstring>

namespace SANDBOX
{
  EntryScene::EntryScene(const std::string& name)
  :name(name)
  {
    layer_stack.PushLayer(new SampleLayer("SampleLayer"));
    layer_stack.PushLayer(new FreqLayer("FreqLayer"));
  }

  float EntryScene::samples[MAX_SIZE];

  int EntryScene::sample_count;
  
  // miniaudio stuff
  std::string path_to_music = "assets/sounds/song.mp3";

  /*void data_callback_output(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
  {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) 
    {
      return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    memcpy((void*)EntryScene::samples, pInput, sizeof(float) * frameCount * 2);
    EntryScene::sample_count = frameCount;

    // this loops better than the api
    if(EntryScene::samples[frameCount] == 0)
    {
      //ma_decoder_init_file(path_to_music.c_str(), NULL, pDecoder);
    }

    (void)pInput;
   }*/

  void data_callback_input(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
  {
    ma_encoder* pEncoder = (ma_encoder*)pDevice->pUserData;

    //ma_encoder_write_pcm_frames(pEncoder, pInput, frameCount, NULL);
    memcpy((void*)EntryScene::samples, pInput, sizeof(float) * frameCount * 2);
    EntryScene::sample_count = frameCount; 
    (void)pOutput; 
  }

  
  void EntryScene::OnAttach()
  {
    AttachLayer();
#if 0
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
#else
    ma_result result;
    ma_encoder_config encoderConfig;
    ma_device_config deviceConfig;

    encoderConfig = ma_encoder_config_init(ma_encoding_format_wav, ma_format_f32, 2, 44100);
    if (ma_encoder_init_file("assets/sounds/nothing.mp3", &encoderConfig, &encoder) != MA_SUCCESS) {
      printf("Failed to initialize output file.\n");
    }

    deviceConfig = ma_device_config_init(ma_device_type_capture);
    deviceConfig.capture.format   = encoder.config.format;
    deviceConfig.capture.channels = encoder.config.channels;
    deviceConfig.sampleRate       = encoder.config.sampleRate;
    deviceConfig.dataCallback     = data_callback_input;
    deviceConfig.pUserData        = &encoder;

    result = ma_device_init(NULL, &deviceConfig, &device);
    
    if (result != MA_SUCCESS) {
      printf("Failed to initialize capture device.\n");
    }

    result = ma_device_start(&device);
    if (result != MA_SUCCESS) {
      ma_device_uninit(&device);
      printf("Failed to start device.\n");
    }
#endif

  }

  void EntryScene::OnUpdate(float dt)
  {
    static float x = 14.3;
    static float y = 12.8;
    static float z = 15.1;

    if(Banana::Input::IsKeyPressed(KEY_S))
    {
      y -= 10 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_W))
    {
      y += 10 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_A))
    {
      x -= 10 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_D))
    {
      x += 10 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_T))
    {
      z += 10 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_G))
    {
      z -= 10 * dt;
    }

    cam.SetPosition({x, y, z});

    if(Banana::IMGUILayer::active_layer == 0)
    {
      RenderLayer(dt, "SampleLayer");
    }
    else if(Banana::IMGUILayer::active_layer == 1)
    {
      RenderLayer(dt, "FreqLayer");
    }
  }

  void EntryScene::OnDetach()
  {
    DetachLayer();
    ma_device_uninit(&device);
#if 0
    ma_decoder_uninit(&decoder);
#else
    ma_encoder_uninit(&encoder);
#endif
 
  }
};
