	#ifndef pbm_rw_pbm_h
	#define pbm_rw_pbm_h
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>
	
	struct image_header{
	
	char format[3];
	int rows, cols, levels;
	};
	char *readImage(const char *file_name, unsigned long *length, 
	struct image_header *ih);
	void writeImage(const char *filename, const char *image_data,
	const struct image_header ih);
	unsigned char * RGB2YCbCr(const char *filename ,const unsigned char *rgb_data, 
	const struct image_header ih);
	unsigned char * YCbCr2YUV444const unsigned char *ycbcr_data, 
	const struct image_header ih);
	unsigned char * YUV4442YCbCr(const unsigned char *ycbcr_data, 
	const struct image_header ih);
	void * YCbCr2RGB(const char *filename, const unsigned char *ycbcr_data, 
	const struct image_header ih);
	
	#endif
