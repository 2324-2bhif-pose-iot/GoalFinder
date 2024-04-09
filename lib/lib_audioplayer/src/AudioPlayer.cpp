#include <AudioPlayer.h>
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMP3.h"
#include "sampleaac.h"

#define Bit_Clock_BCLK 23
#define Word_Select_WS 05
#define Serial_Data_SD 19

AudioFileSourcePROGMEM *file;

AudioGeneratorMP3 *wav;

AudioOutputI2S *out;

void AudioPlayer::Init() 
{
  Serial.begin(115200);
  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( music_mp3, music_mp3_len );
  out = new AudioOutputI2S();
  out -> SetPinout(Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD);
  wav = new AudioGeneratorMP3();
  wav->begin(file, out);
}

void AudioPlayer::TestAudio() 
{
    if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  } else {
    Serial.printf("WAV done\n");
    delay(1000);
  }
}