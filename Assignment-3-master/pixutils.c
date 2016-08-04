#include "pixutils.h"
#include "lodepng.h"

//private methods
static pixMap *pixMap_init(); //allocate memory for pixMap object, set variables to zero, and return a pointer to the object
static void pixMap_reset();  //free the allocated memoray and set to zero but do not free memory for pixMap
static void pixMap_copy(pixMap *dest,pixMap *source); //copy one pixmap to another
static int pixMap_read(pixMap *p,char *filename); //read in a pixmap from file

static pixMap* pixMap_init(){
	//allocate memory for pixMap object, set variables to zero, and return a pointer to the object
 	pixMap *p = malloc(sizeof(pixMap));
	p -> width = 0;
	p -> pixArray = 0;
	p -> height = 0;
	p -> image = 0;

	return p;
}	
pixMap* pixMap_init_filename(char *filename){
	//use pixMap_int to create the pixMap object
	//use pixMap read to fill the fields of the object
	//return the pointer to the new object
	pixMap *p = pixMap_init();
	pixMap_read(p, filename);
	return p;
}
static int pixMap_read(pixMap *p,char *filename){
 //read and allocate image, read in width and height using using lodepng_decode32_file
 //example is in lodepng/examples - one liner
	//then allocate p->pixArray to hold p->height pointers
	//set p->pixArray[0] to p->image and p->pixArray[i]=p->pixArray[i-1]+p->width
	lodepng_decode32_file(&(p->image), &(p->width), &(p->height), filename);
	p -> pixArray[0] = (rgba*) p -> image;
	int i;
	for (i = 1; i < p->height; i++) {
		p -> pixArray[i] = (p->pixArray[i-1] + (p->width));
	}
	return 0;
}	
static void pixMap_copy(pixMap *dest,pixMap *source){
	//if source image is zero then reset dest and copy width and height
	if (!source) {
		dest -> height = 0;
		dest -> width = 0;
		dest -> image = 0;
		dest -> pixArray = 0;
	}
	//if source image is not zero
	else {
	  //if width or height are different
		if (dest->height != source -> height || dest-> width != source ->width) {

	    //if width*height is different then we need to allocate dest->image
			if ((dest->height) * (dest->width) != (source ->height) * (source->width)) {
	      //if dest->image is zero use malloc to allocate memory for dest->image
				if (dest -> image == 0) {
					dest -> image = malloc((source->height) * (source->width)*4);
				}
	      //else use realloc to allocate memory dest->image
				else { dest ->image = realloc(source -> image, (source-> height) * (source->width)*4);
				}
			    //if dest->height is different
				if (dest->height != source->height) {
					if (!dest ->height != source->height) {
					    //malloc or realloc dest->pixArray depending on whether dest->pixArray is zero
						dest -> pixArray = malloc(sizeof(source->pixArray));
					    //even if the height is the same set dest->pixArray[0] to dest->image and dest->pixArray[i]=dest->pixArray[i-1]+source->width
						dest -> pixArray[0] = (rgba*) dest -> image;
						int i;
						for (i = 1; i < source -> height; i++) {
							dest ->pixArray[i] = dest -> pixArray[i-1] + dest -> width;
						}
					}
				}
			}
		}

	  //
	  //do a memcpy from source->image to dest->image
	  //set dest->width and dest->height to source values
		memcpy(dest -> image, source -> image, ((source -> height) * (source -> width) * 4));
		dest -> width = source -> width;
		dest -> height = source -> height;
	}
}

static void pixMap_reset(pixMap *p){
	//free all the memory in the fields and set everything to zero
	free(p -> pixArray);
	free(p ->image);
	p -> width = 0;
	p -> height = 0;
	p -> pixArray = 0;
	p -> image = 0;
}	


void pixMap_destroy(pixMap *p){
	//reset pixMap and free the object p
	if (p) {
		free(p->pixArray);
		free(p->image);
		free(p);
	}
}


void pixMap_rotate (pixMap *p, float theta){
 //make a new temp blank pixMap structure
	pixMap temp;
 //copy p to temp
	p = temp;
 //set the values in the image to zero using memset - Note that the 3rd argument of memset is the size in BYTES
	memset(p, 0, sizeof(p));
 //calculate the coordinates ox and oy of the middle of the png graphic
 //calculate the values of sine and cosine used by the rotation formula 
	int x, y;
	for(y = 0; y < p->height; y++){   //two for loops to loop through each pixel in the original
		for(x = 0; x < p->width; x++){
	 
	    //calculate the new rotated coordinates rotx roty using the formula from 
	    //http://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
	    //use the answer from stackoverflowery

	    //However this answer assumes that y is going from the bottom to the top (mathematical convention)
	    //but the pixmap starts at the upper left hand corner and height grows DOWN (scan order)
	    //so use this formula instead where c is cos(degreesToRadians(theta)) and s is sin(degreeToRadians(theta))
	    //    float rotx = c*(x-ox) - s * (oy-y) + ox;
        //    float roty = -(s*(x-ox) + c * (oy-y) - oy);
			float rotx = cos(degreesToRadians(theta)) * (x - p->width) - sin(degreesToRadians(theta)) *  (y - p->height) + p->width;
			float roty = -(sin(degreesToRadians(theta))* (x - p->width) + cos(degreesToRadians(theta)) * (y - p->height) - p->height);
	    
		   //round the coordinates to the nearest integer in your calculations (add 0.5 and cast to integer)
			rotx = rotx + 0.5;
			rotx = (int) rotx;
			roty = roty + 0.5;
			roty = (int) roty;

	    //if rotated coordinates are within the height and width limits
			if (rotx <= p->width && roty <= p->height) {
	      //copy the pixel at the old coords to the pixel to the temporary copy using memcpy
				temp = p;
				memcpy(temp->pixArray[roty]+rotx,p->pixArray[y]+x,sizeof(rgba));
			}
		}
	}
	    
	  //
	//  
	//copy the temp pixMap to the original
	temp = p;
	//destroy the temp;
	destroy(temp);
}	

void pixMap_gray (pixMap *p){
	int i, j;
	float red, green, blue, pixelCount = 0;
	//for() loop through pixels using two for loops 
		for(i = 0; i < p->height; i++) {
			for(j = 0; j < p->width; j++) {
				red = red + p->pixArray[i][j].r;
				green = green + p->pixArray[i][j].g;
				blue = blue + p->pixArray[i][j].b;
				pixelCount++;
			}
		}
		float avR = red / pixelCount + 0.5;
		float avB = blue / pixelCount + 0.5;
		float avG = green / pixelCount + 0.5;
		p->pixArray.r = (int) avR;
		p->pixArray.b = (int) avB;
		p->pixArray.g = (int) avG;
	    //calculate average value of r and g and b values (assign to a float variable)
	    //for example the red value of for the pixel at height i, width j would be p->pixel[i][j].r
	    //round float variable to integer (add 0.5 before casting to integer)
	    //assign the rounded value to r,g and b values
	  //
	//   
}
int pixMap_write(pixMap *p,char *filename){
 //write out to filename using lodepng_encode32_file
 //example is in lodepng/examples - one liner
 	lodepng_encode32_file(filename, &(p->image), &(p->width), &(p->height));
	return 0;
}	 
