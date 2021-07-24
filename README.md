# LSB-Insertion-Tool

## Purpose
This tool is used to essentially hide one image within another by altering the least signficant bit of each element of each pixel in the cover image.

## prerequisites
    
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
secret medium. 
- To decrypt a file run:
```console 
$ ./decrypt filename.png secretWidth secretHeight [channels]
```
Where channels is optional with a default value of 3.
The input file is a png since `encrypt.c` outputs a png. 

## Future plans

- Embed the dimensions of then secret image into the cover medium. This will mean we dont <br>
have to keep track of the dimensions manually 
- Allow text files to be used as secret medium 


