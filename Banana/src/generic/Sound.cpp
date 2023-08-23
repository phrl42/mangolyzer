#include "_Banana.h"
#include "Sound.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "generic/Application.hpp"

namespace Banana
{
  // make sound api something like input api
  Sound::Sound(const std::string& path_to_sound, bool loop)
  :sound_path(path_to_sound)
  {
    InitSound(path_to_sound, loop);
  }

  Sound::~Sound()
  {
    StopSound();
  }

  void Sound::ChangeSound(const std::string& path_to_sound, bool loop)
  {
    if(ma_sound_is_playing(&current_sound))
    {
      StopSound();
    }

    InitSound(path_to_sound, loop);
  }
    
  void Sound::InitSound(const std::string& path_to_sound, bool loop)
  {
    if(int success = ma_sound_init_from_file(&Application::GetInstance().soundhelper.GetEngine(), path_to_sound.c_str(), 0, NULL, NULL, &current_sound); success != MA_SUCCESS)
    {
      if(success == MA_DOES_NOT_EXIST)
      {
        LOG("Could not find " + path_to_sound);
        return;
      }
      LOG("Could not init sound with MINIAUDIO error: " + std::to_string(success));
    }
    
    if(loop)
    {
      ma_sound_set_looping(&current_sound, ma_sound_is_looping(&current_sound));
    }
  }

  void Sound::StartSound()
  {
    ma_sound_start(&current_sound);
  }

  void Sound::StopSound()
  {
    ma_sound_stop(&current_sound);
    //ma_sound_uninit(&current_sound);
  }

  void Sound::SetVolume(float vol)
  {
    ma_sound_set_volume(&current_sound, vol);
  }

  float Sound::GetVolume()
  {
    return ma_sound_get_volume(&current_sound);
  }

}
