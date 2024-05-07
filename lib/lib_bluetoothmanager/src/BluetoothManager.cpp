#include <BluetoothManager.h>
#include <FileSystem.h>

const char* BLUETOOTH_SPEAKER_NAME = "DEFAULT"; 

char BT_SINK_NAME[]   = "DESKTOP-L6GA9OQ"; // sink devicename
char BT_SINK_PIN[]    = "1234";             // sink pincode
char BT_DEVICE_NAME[] = "ESP_A2DP_SRC";     // source devicename

File            audiofile;    // @suppress("Abstract class cannot be instantiated")
uint32_t        sampleRate;
uint32_t        bitRate;
uint8_t         channels;
uint8_t         bitsPerSample=16;
uint32_t        posDataSection;

bool parseWAV(fs::FS &fs, String path){
    char chbuf[256];
    audiofile=fs.open(path.c_str());
    String afn = (String)audiofile.name();  //audioFileName

    if(afn.endsWith(".wav")) {
        audiofile.readBytes(chbuf, 4); // read RIFF tag
        if ((chbuf[0] != 'R') || (chbuf[1] != 'I') || (chbuf[2] != 'F') || (chbuf[3] != 'F')){
            Serial.println("file has no RIFF tag");
            audiofile.seek(0);
            return false;
        }

        audiofile.readBytes(chbuf, 4); // read chunkSize (datalen)
        uint32_t cs = (uint32_t)(chbuf[0] + (chbuf[1] <<8) + (chbuf[2] <<16) + (chbuf[3] <<24) - 8);

        audiofile.readBytes(chbuf, 4); /* read wav-format */ chbuf[5] = 0;
        if ((chbuf[0] != 'W') || (chbuf[1] != 'A') || (chbuf[2] != 'V') || (chbuf[3] != 'E')){
            Serial.println("format tag is not WAVE");
            audiofile.seek(0);
            return false;
        }

        while(true){ // skip wave chunks, seek for fmt element
            audiofile.readBytes(chbuf, 4); /* read wav-format */
            if ((chbuf[0] == 'f') && (chbuf[1] == 'm') && (chbuf[2] == 't')){
                //if(audio_info) audio_info("format tag found");
                break;
            }
        }

        audiofile.readBytes(chbuf, 4); // fmt chunksize
        cs = (uint32_t) (chbuf[0] + (chbuf[1] <<8));
        if(cs>40) return false; //something is wrong
        uint8_t bts=cs-16; // bytes to skip if fmt chunk is >16
        audiofile.readBytes(chbuf, 16);
        uint16_t fc  = (uint16_t)(chbuf[0]  + (chbuf[1] <<8));  // Format code
        uint16_t nic = (uint16_t)(chbuf[2]  + (chbuf[3] <<8));  // Number of interleaved channels
        uint32_t sr  = (uint32_t)(chbuf[4]  + (chbuf[5] <<8) + (chbuf[6]  <<16) + (chbuf[7]  <<24)); // Smpling rate
        uint32_t dr  = (uint32_t)(chbuf[8]  + (chbuf[9] <<8) + (chbuf[10] <<16) + (chbuf[11] <<24)); // Data rate
        uint16_t dbs = (uint16_t)(chbuf[12] + (chbuf[13] <<8));  // Data block size
        uint16_t bps = (uint16_t)(chbuf[14] + (chbuf[15] <<8));  // Bits per sample
        Serial.printf("FormatCode=%u\n", fc);
        Serial.printf("Channel=%u\n", nic);
        Serial.printf("SampleRate=%u\n", sr);
        Serial.printf("DataRate=%u\n", dr);
        Serial.printf("DataBlockSize=%u\n", dbs);
        Serial.printf("BitsPerSample=%u\n", bps);


        if(fc != 1){
            Serial.println("format code is not 1 (PCM)");
            return false;
        }

        if(nic != 1 && nic != 2){
            Serial.print("number of channels must be 1 or 2");
            return false;
        }

        if(bps != 8 && bps !=16){
            Serial.println("bits per sample must be 8 or 16");
            return false;
        }
        bitsPerSample=bps;
        channels = nic;
        sampleRate = sr;
        bitRate = nic * sr * bps;
        Serial.printf("BitRate=%u\n", bitRate);

        audiofile.readBytes(chbuf, bts); // skip to data
        uint32_t s = audiofile.position();
        //here can be extra info, seek for data;
        while(true){
            audiofile.seek(s);
            audiofile.readBytes(chbuf, 4); /* read header signature */
            if ((chbuf[0] == 'd') && (chbuf[1] == 'a') && (chbuf[2] == 't') && (chbuf[3] == 'a')) break;
            s++;
        }

        audiofile.readBytes(chbuf, 4); // read chunkSize (datalen)
        cs = chbuf[0] + (chbuf[1] <<8) + (chbuf[2] <<16) + (chbuf[3] <<24) - 44;
        sprintf(chbuf, "DataLength=%u\n", cs);
        Serial.print(chbuf);
        posDataSection = audiofile.position();
        return true;
    }
    return false;
}

void BluetoothManager::Init() 
{
    //parseWAV(LittleFS, "/cola.wav");
    //a2dp_source_init(BT_SINK_NAME, BT_SINK_PIN);
}

void BluetoothManager::Test() 
{
    bt_loop();
}

int32_t bt_data(uint8_t *data, int32_t len, uint32_t* sr){
    *sr = sampleRate;
    if (len < 0 || data == NULL) {
        return 0;
    }
    len = audiofile.read(data, len);
    if(len == 0) audiofile.seek(posDataSection); // EOF? enless loop
    return len;
}
void bt_info(const char* info){
    Serial.printf("bt_info: %s\n", info);
}