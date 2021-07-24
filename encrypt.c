#include <stdio.h>
#include <stdlib.h>
 
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

const int secretHeightBits = 11;
const int secretWidthBits = 11;
const int secretChannelBits = 2;
const int secretDataBits = secretChannelBits + secretHeightBits + secretWidthBits; //24 bits are used to store secret image data (width, height and channels)

/* converts an 8 bit integer to its binary form */
void intToBin(int x, unsigned char *bin, int bits){
    int i = 1 << (bits-1);
    for(;i>0;i/=2){
        if(x>=i){
            *bin = 1;  //set binary digit 
            x-=i;
        }
        bin++;   //increment pointer 
    }
}

/* Insert data into the binary array.
    decValue: The value to be converted to binary
    binArr: The binary array to be added to
    start: The starting index of the array
    bits: The bits needed to store decValue  */
void insertBinaryData(int decValue, unsigned char *binArr, int start, int bits ){
    unsigned char *tmp = (unsigned char *)calloc(bits + 1, sizeof(char));
    if (tmp == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    intToBin(decValue, tmp, bits);
    int i = start;
    for (; i < start+bits; i++) {
        binArr[i] = tmp[i-start];
    }
    free(tmp);
}



/* hide the secret image in the LSBs of the cover image */
int main(int argc, char *argv[]) {
    if(argc < 3 ){
        printf("Not enough arguments");
        exit(0);
    }
    //load images
    int coverWidth, coverHeight, coverChannels, secretWidth, secretHeight, secretChannels;
    unsigned char *cover = stbi_load(argv[1], &coverWidth, &coverHeight, &coverChannels, 0);
    if (cover == NULL) {
        printf("Error in loading the first image\n");
        exit(1);
    }
    unsigned char *secret = stbi_load(argv[2], &secretWidth, &secretHeight, &secretChannels, 0);
    if (secret == NULL) {
        printf("Error in loading the second image\n");
        exit(1);
    }

    /*
        TODO
        ensure secret dimensions and channels are less than 11,11,2 bits
    */

    int length = secretWidth*secretHeight*secretChannels;
    if (length*8 + secretDataBits >coverWidth*coverHeight*coverChannels) {  //ensure secret image will fit in cover image
        printf("secret medium is too large");
        exit(0);
    }


    unsigned char *secretBin = (unsigned char *) calloc(secretDataBits + length*8,sizeof(char)); //get binary of secret pixels 
    int i;

    // inserting image dimension data
    insertBinaryData(secretHeight, secretBin, 0, secretHeightBits);
    insertBinaryData(secretWidth, secretBin, secretHeightBits, secretWidthBits);
    insertBinaryData(secretChannels, secretBin, secretHeightBits + secretWidthBits, secretChannelBits);

    for(i = secretDataBits; i<length + secretDataBits; i++){
        insertBinaryData(secret[i-secretDataBits], secretBin, i + (i-24)*7,8);
    }

    // put each element of secretBin into lsb of cover medium
    for(i=0 ;i<length*8;i++){
        if ((cover[i] ^ secretBin[i]) % 2 == 1 ){
            if (secretBin[i]==1){
                cover[i]++; 
            } else {
                cover[i]--;
            }
        } 
    }
    stbi_write_png("stegano.png", coverWidth, coverHeight, coverChannels, cover, coverWidth * coverChannels);
    free(cover);
    free(secret);
    free(secretBin);
    return 0;
}
