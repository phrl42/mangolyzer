#include "../include/mixer.h"
// maybe use miniaudio...
Mix_Chunk *testWAV;

int mixerOpenAudio(int frequency, int channels)
{
  // the defaults are fine

  if(Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, 2048) == -1)
  {
    errorHandling("Failed to open audio device: ", 2);
    return -1;
  }
  // in order to play sounds simultaneously
  // see https://wiki.libsdl.org/SDL_mixer/Mix_AllocateChannels
  if(Mix_AllocateChannels(8) != 8)
  {
    errorHandling("Failed to allocate 8 channels: ", 2);
    return -1;
  }
  // lower volume
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
  return 0;
}

void mixerchangeVolume(int volume)
{
  // set between 0 and MIX_MAX_VOLUME (128)
  Mix_VolumeMusic(volume);
}

Mix_Chunk* mixerLoadAudio(const char *file)
{
  // using wav files are mandatory for playing audio simultaneously, as playing mp3 files will stop 
  // every other sound being played as Mix_LoadMusic does not work with manual channel choosing
  testWAV = Mix_LoadWAV(file);
  if(!testWAV)
  {
    errorHandling("Could not load WAV file: ", 2);
  }
  Mix_FreeChunk(testWAV);
  return Mix_LoadWAV(file); // also returns on error, so the program (hopefully) crashes
}

int mixerPlayAudio(int channel, Mix_Chunk *sound, int loop)
{
  // use loop = -1 for infinite loop (65000 times lol)
  // use channel = -1 to use the next free channel to play desired sound
  if(Mix_PlayChannel(channel, sound, loop) == -1)
  {
    errorHandling("Could not play desired sound: ", 2);
    return -1;
  }
  return 0;
}

void mixerFreeChunk(Mix_Chunk* chunk)
{
  Mix_FreeChunk(chunk);
}
