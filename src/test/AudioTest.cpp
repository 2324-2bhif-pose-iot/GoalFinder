#pragma once
#include <AudioPlayer.h>

#define Bit_Clock_BCLK 23
#define Word_Select_WS 05
#define Serial_Data_SD 19

class AudioTest 
{
    public:
        AudioTest(FileSystem* fs) : audio(fs, Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD) 
        {

        }

        void Setup() 
        {
            audio.PlayMP3("/start.mp3");
            audio.SetVolume(100);
        }  

        void Loop() 
        {
            audio.Loop();
        }
    private:
        AudioPlayer audio;
        //variables
};