#include <iostream>
#include <cmath>
#include "tgaimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <utility>
#include <cstddef>
#include <cstdio>


using namespace std;


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

//Algorithme de Brensenham
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1-x0;
    int dy = y1-y0;
    int derror = std::abs(dy)*2;
    int error = 0;
    int y = y0;

    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error += derror;
        if (error > dx) {
            y += (y1>y0?1:-1);
            error -= dx*2;
        }
    }
}





void read(){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
    vector<float> v;
    vector<float> f;

    fp = fopen("african_head.obj", "r"); //deuxième arg : Droit
    if (fp == NULL)
        exit(EXIT_FAILURE);
	while ((read = getline(&line, &len, fp)) != -1) {
        if(strchr(line, 'v') && !strchr(line, 'vt') && !strchr(line, 'vn') && !strchr(line, '#')){  
            v.push_back(atof(strtok(line+2, " ")));
            char *res = NULL;
            int cnt = 1;
            while (res = strtok(NULL, " ")) {                
                  v.push_back(atof(res));
            }

        }
        if(strchr(line, 'f') && !strchr(line, '#')){
            f.push_back(atof(strtok(line+2, "/")));
            char *res = NULL;
			int cnt = 1;
			while (res = strtok(NULL, "/ ")) {
                if (0==cnt%3){                   
                   f.push_back(atof(res));
                }
				cnt++;
			}           

        }
    }

    fclose(fp);
    if (line)
        free(line);

   exit(EXIT_SUCCESS);
}




int main(int argc, char** argv) {


    TGAImage image(1000, 1000, TGAImage::RGB);
	image.set(34,34,white);
	line(48, 20, 580, 680, image, white);
    read();
    write(image);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("wireframe.tga");
    
	return 0;
}
