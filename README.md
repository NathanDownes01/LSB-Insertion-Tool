# LSB-Insertion-Tool

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
- To decrypt a file run:
```console 
$ ./decrypt filename.png secretWidth secretHeight [channels]
```
Where channels is optional with a default value of 3.
The input file is a png since `encrypt.c` outputs a png. 
