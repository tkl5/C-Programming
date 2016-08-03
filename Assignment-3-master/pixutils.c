#include "pixutils.h"
#include "lodepng.h"

//private methods
static pixMap *pixMap_init(); //allocate memory for pixMap object, set variables to zero, and return a pointer to the object
static void pixMap_reset();  //free the allocated memoray and set to zero but do not free memory for pixMap
static void pixMap_copy(pixMap *dest,pixMap *source); //copy one pixmap to another
static int pixMap_read(pixMap *p,char *filename); //read in a pixmap from file

static pixMap* pixMap_init(){
 //allocate memory for pixMap object, set variables to zero, and return a pointer to the object
}	
pixMap* pixMap_init_filename(char *filename){
	//use pixMap_int to create the pixMap object
	//use pixMap read to fill the fields of the object
	//return the pointer to the new object
}
static int pixMap_read(pixMap *p,char *filename){
 //read and allocate image, read in width and height using using lodepng_decode32_file
 //example is in lodepng/examples - one liner
	//then allocate p->pixArray to hold p->height pointers
	//set p->pixArray[0] to p->image and p->pixArray[i]=p->pixArray[i-1]+p->width
	return 0;
}	
static void pixMap_copy(pixMap *dest,pixMap *source){
	//if source image is zero then reset dest and copy width and height
	//if source image is not zero
	  //if width or height are different
	    //if width*height is different then we need to allocate dest->image
	      //if dest->image is zero use malloc to allocate memory for dest->image
	      //else use realloc to allocate memory dest->image
	    //
	    //if dest->height is different
	      //malloc or realloc dest->pixArray depending on whether dest->pixArray is zero
	    //
	    //even if the height is the same set dest->pixArray[0] to dest->image and dest->pixArray[i]=dest->pixArray[i-1]+source->width 
	  //
	  //do a memcpy from source->image to dest->image
	  //set dest->width and dest->height to source values
	//
}

static void pixMap_reset(pixMap *p){
	//free all the memory in the fields and set everything to zero
}	


void pixMap_destroy(pixMap *p){
	//reset pixMap and free the object p
}


void pixMap_rotate (pixMap *p, float theta){
 //make a new temp blank pixMap structure
 //copy p to temp
 //set the values in the image to zero using memset - Note that the 3rd argument of memset is the size in BYTES

 //calculate the coordinates ox and oy of the middle of the png graphic
 //calculate the values of sine and cosine used by the rotation formula FOR -theta



	//for(int y=0;y<p->height;y++){   //two for loops to loop through each pixel in the new rotated image
	 //for(int x=0;x<p->width;x++){
	 
	    //calculate the old coordinates rotx roty by rotating by -theta and using the formula described here
	    //http://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
	    //use the answer from stackoverflowery
	    
	    //However this answer assumes that y is going from the bottom to the top (mathematical convention)
	    //but the pixmap starts at the upper left hand corner and height grows DOWN (scan order)
	    //so use this formula instead where c is cos(degreesToRadians(-theta)) and s is sin(degreeToRadians(-theta))
	    //    float rotx = c*(x-ox) - s * (oy-y) + ox;
     //    float roty = -(s*(x-ox) + c * (oy-y) - oy);
	    
 	   //round the coordinates to the nearest integer in your calculations (add 0.5 and cast to integer)	
	
	    //if old coordinates are within the height and width limits
	      //copy the pixel at the old coords to the pixel to the temporary copy using memcpy
	      //i.e. 	memcpy(temp->pixArray[y]+x,p->pixArray[roty]+rotx,sizeof(rgba))
	    //
	    
	  //
	//  
	//copy the temp pixMap to the original
	//destroy the temp;
}	

void pixMap_gray (pixMap *p){
	//for() loop through pixels using two for loops 
	  //for()
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
	return 0;
}	 
