#include <stdio.h>
#include <stdlib.h>
 
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

/* converts an 8 bit integer to its binary form */
char *intToBin(unsigned char x, unsigned char *bin){
    int i=128;
    for(i;i>0;i/=2){
        if(x>=i){
            *bin = 1;  //set binary digit 
            x-=i;
        }
        bin++;   //increment pointer 
    }
}

int main(int argc, char *argv[]) {
    if(argc < 3 ){
        printf("Not enough arguments");
        exit(0);
    }
    //load images
    int width1, height1, channels1;
    unsigned char *cover = stbi_load(argv[1], &width1, &height1, &channels1, 3);
    if (cover == NULL) {
        printf("Error in loading the first image\n");
        exit(1);
    }
    int width2, height2, channels2;
    unsigned char *secret = stbi_load(argv[2], &width2, &height2, &channels2, 3);
    if (secret == NULL) {
        printf("Error in loading the second image\n");
        exit(1);
    }

    //convert each pixel in secret to binary 
    int length = width2*height2*channels2;
    if (length*8>width1*height1*channels1){
        printf("secret medium is too large");
        exit(0);
    }

    unsigned char *secretBin = calloc(length*8,sizeof(char)); 
    int i=0;

    for(i=0;i<length;i++){
        unsigned char *tmp = calloc(9, sizeof(char)); //get binary of current pixel
        if(tmp==NULL){
            printf("ERROR");
            exit(1);
        }
        intToBin(secret[i],tmp);
        int j=0;
        for(j; j<8;j++){    //update binary 
            secretBin[i*8+j] = tmp[j];
        }
        free(tmp);
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
    stbi_write_png("stegano.png", width1, height1, channels1, cover, width1 * channels1);
    printf("Secret medium key details: \n Height: %d, Width: %d, Channels: %d ", height2, width2, channels2);
    free(cover);
    free(secret);
    free(secretBin);
    return 0;
}
