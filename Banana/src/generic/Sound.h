#pragma once

#include "_Banana.h"

#include "miniaudio.h"

namespace Banana
{

  struct SoundHelper
  {
    public:
      SoundHelper()
      {
        if(int success = ma_engine_init(NULL, &engine); success != MA_SUCCESS)
        {
          LOG("Could not init engine: " + std::to_string(success));
        }

        if(int success = ma_engine_start(&engine); success != MA_SUCCESS)
        {
          LOG("Could not start engine: " + std::to_string(success));
        }
      }

      ~SoundHelper()
      {
        LOG("Deleting sound engine");
        ma_engine_stop(&engine);
        ma_engine_uninit(&engine);
      }

      ma_engine& GetEngine()
      {
        return engine;
      }

    private:

      ma_engine engine;
  };

  class Sound
  {
    public:
      Sound(const std::string& path_to_sound, bool loop = false);
      void ChangeSound(const std::string& path_to_sound, bool loop = false);

      void StartSound();
      void StopSound();

      void SetVolume(float vol);
      float GetVolume();

      ~Sound();

    private:
      void InitSound(const std::string& path_to_sound, bool loop);
      ma_sound current_sound;
  };
};
