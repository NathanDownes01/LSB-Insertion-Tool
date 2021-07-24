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

/* convert n bit binary number into decimal */ 
int binToDec(unsigned char *bin, int start, int bits){
    int total = 0;
    int i = start;
    int x = 1 << (bits - 1);
    for(i;i<start+bits;i++){
        if (bin[i]){
            total += x;
        }
        x/=2;
    }
    return total;
}

/* Decrypts a stegano file */
int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Not enough arguments");
        exit(0);
    }

    int width, height, channels, steganoWidth, steganoHeight, steganoChannels;

    unsigned char *stegano = stbi_load(argv[1], &steganoWidth, &steganoHeight, &steganoChannels, 3);  //load image 
    if (stegano == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    int i;
    unsigned char *imageDimensionBin = (char *) calloc(secretDataBits, sizeof(char));
    for(i=0;i<secretDataBits;i++){
        imageDimensionBin[i] = stegano[i] % 2;
    }
    height = binToDec(imageDimensionBin,0,secretHeightBits);
    width = binToDec(imageDimensionBin,secretHeightBits,secretWidthBits);
    channels = binToDec(imageDimensionBin,secretHeightBits+secretWidthBits,secretChannelBits); 


    int length = width*height*channels;   // get length of array of pixels
    unsigned char *secretBin = (char *) calloc(length*8,sizeof(char)); 

    for (i; i< length*8;i++) {  // extract binary array of pixel data
        secretBin[i-secretDataBits] = stegano[i] % 2;
    }
    unsigned char *secret = (char *) calloc(length, sizeof(char));
    for (i=0;i<length;i++) {     // convert the binary array into array of intergers 
        secret[i] = binToDec(secretBin,i*8,8);
    }
    stbi_write_jpg("secretRetrived.jpg", width, height, channels, secret, 100); // output file

    free(stegano);
    free(secretBin);
    free(secret);
    return 0;
}