#include <stdint.h>

#define U32 uint32_t
#define U16 uint16_t

struct WavHeader{
  #pragma pack(push, 1) // Compiler directive -> no padding between the variables...
  /* RIFF CHUNK */
  U32 RIFF_ID = 0x46464952;  // "RIFF"
  U32 RIFF_SZ = 0x00000000;  // FileSize - 8
  U32 RIFF_TY = 0x45564157;  // "WAVE"
  /* FMT CHUNK*/
  U32 FMT_ID = 0x20746D66;   // "fmt"
  U32 FMT_SZ = 16;           // Chunk size
  U16 ComprCode = 1;         // Compression Code
  U16 NChans = 1;            // NChannels
  U32 SampleRate = 48000;    // Sample Rate
  U32 ByteRate = 96000;      // Byte Rate = SampleRate * BlockAlign
  U16 BlockAlign = 2;        // BlockAlign = NChannels * BitsDepth/8
  U16 BitDepth = 16;         // BitDepth
  /* DATA CHUNK */
  U32 DATA_ID = 0x61746164;  // "data"
  U32 DataSize = 0x00000000; // Data size
  /* PCM DATA */
  #pragma pack(pop)
};

int main(){
    return 0;
}
