#include <iostream>
#include <fstream>
#include <vector>

#define Width 80
#define Height 20

#define BLK "\x1b[" << "30m"
#define RED "\x1b[" << "31m"
#define GRN "\x1b[" << "32m"
#define YEL "\x1b[" << "33m"
#define BLU "\x1b[" << "34m"
#define MAG "\x1b[" << "35m"
#define CYN "\x1b[" << "36m"
#define WHT "\x1b[" << "37m"
#define RST "\x1b[" << "0m"

int main(){
    // RGBA!!
    std::ifstream filein("img.raw", std::ios::in | std::ios::binary);
    std::vector<unsigned char> pixels((std::istreambuf_iterator<char>(filein)), std::istreambuf_iterator<char>());

    char* pixel_list = "XX";
    for(int j = 0; j < Height; j++){
        for (int i = 0; i < Width; i++)
        {
            size_t ptr = (i + j * Width) * 4;
            char pixel = pixels[ptr] >> 7; //0xFF -> 1, 0 -> 0

            if(pixel == 1)
                std::cout << WHT;
            else
                std::cout << RED;
            
            std::cout << pixel_list[pixel] << RST;
        }
        std::cout << std::endl;
    }
    return 0;
}
