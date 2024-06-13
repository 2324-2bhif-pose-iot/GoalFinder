#include <AudioPlayer.h>

AudioPlayer::AudioPlayer(FileSystem* fileSystem, int bclkPin, int wclkPin, int doutPin) 
{
    this->fileSystem = fileSystem;
    currentFile = new AudioFileSourceFS(*fileSystem->GetInternalFileSystem());
    mp3Generator = new AudioGeneratorMP3();
    audioOutput = new AudioOutputI2S();
    audioOutput->SetPinout(bclkPin, wclkPin, doutPin);
}

AudioPlayer::~AudioPlayer() 
{
    delete currentFile;
    delete mp3Generator;
    delete audioOutput;
}

void AudioPlayer::PlayMP3(const char* path)
{
    currentFile->open(path);
    mp3Generator->begin(currentFile, audioOutput);
}

void AudioPlayer::SetVolume(int percent) 
{
    audioOutput->SetGain((float)percent / 100.0f);
}

void AudioPlayer::Loop() 
{
    if(mp3Generator->isRunning()) 
    {
        if(!mp3Generator->loop()) 
        {
            mp3Generator->stop();
        }
    }
}

bool AudioPlayer::GetIsPlaying() 
{
    return mp3Generator->isRunning();
}