#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


/* convert 8 bit binary number into decimal */ 
int binToDec(unsigned char *bin, int start){
    int total = 0;
    int i = start;
    int x = 128;
    for(i;i<start+8;i++){
        if (bin[i]){
            total += x;
        }
        x/=2;
    }
    return total;
}

/* Decrypts a stegano file:
    arguments are in format: filename, width, height, (channels - this is optional) */
int main(int argc, char *argv[]) {
    if(argc < 4){
        printf("Not enough arguments");
        exit(0);
    }

    int width, height, channels, width1, height1, channels1;
    if (argc == 4) {  // if 2 args are used, assume there are 3 channels in the image 
        channels = 3;
    } else {
        channels = atoi(argv[4]);
    }
    width = atoi(argv[2]);
    height = atoi(argv[3]);

    unsigned char *stegano = stbi_load(argv[1], &width1, &height1, &channels1, 3);  //load image 
    if (stegano == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    int length = width*height*channels;   // get length of array of pixels
    unsigned char *secretBin = (char *) calloc(length*8,sizeof(char)); 
    int i;

    for (i=0; i< length*8;i++) {  // extract binary array of pixel data
        secretBin[i] = stegano[i] % 2;
    }
    unsigned char *secret = (char *) calloc(length, sizeof(char));
    for (i=0;i<length;i++) {     // convert the binary array into array of intergers 
        secret[i] = binToDec(secretBin,i*8);
    }
    stbi_write_jpg("secretRetrived.jpg", width, height, channels, secret, 100); // output file

    free(stegano);
    free(secretBin);
    free(secret);
    return 0;
}