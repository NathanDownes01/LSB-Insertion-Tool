# LSB-Insertion-Tool

## Purpose
This tool is used to essentially hide one image within another by altering the least signficant bit of each element of each pixel in the cover image.<br>
The dimensions and number of channels for the secret image is embedded in the cover image. This means we don't <br>
have to manually keep track of them to restore the secret image. <br>

When storing this, we use 11 bits for secret image width, 11 bits for secret image height and 2 bits for secret image <br>
colour channels. This means the maxium dimensions for a secret image are 2047px x 2047px.

## Dependencies
    
- stb_image library (https://github.com/nothings/stb)


## Using the tool

- Run 
```console 
$ git clone https://github.com/nothings/stb.git 
```
- The file directory should look as so:
``` 
project
├── README.md
├── decrypt.c
├── encrypt.c
└── stb
    └── [stuff]
```
- To compile run:
```console
 $ gcc -std=c17 -Wall -pedantic  encrypt.c -o encrypt -lm
 $ gcc -std=c17 -Wall -pedantic  decrypt.c -o decrypt -lm
```
- To encrypt a file run:
```console
$ ./encrypt coverMedium secretMedium
```
The cover file should have at least 8 times as many pixels as the 
secret medium + 8 pixels for the secret image dimensions to be held. 
- To decrypt a file run:
```console 
$ ./decrypt filename.png 
```
The input file is a png since `encrypt.c` outputs a png. 

## Future plans


- Allow text files to be used as secret medium 


