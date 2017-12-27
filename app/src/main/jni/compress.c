#include <stdio.h>
#include <jpeglib.h>
#include <malloc.h>
#include "compress.h"



void  read_jpeg(char *filename, unsigned char **data, int *width, int *height)
{
    FILE * infile = fopen(filename, "rb");
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    *width = cinfo.output_width;
    *height = cinfo.output_height;
    *data = (unsigned char *) malloc(cinfo.output_height * cinfo.output_width * cinfo.output_components);
    unsigned char *line_pointer;
    int i = 0;
    while (cinfo.output_scanline < cinfo.image_height) {
        line_pointer = *data + i * cinfo.output_width * cinfo.output_components;
        jpeg_read_scanlines(&cinfo, &line_pointer, 1); 
        i ++;
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);


    fclose(infile);
   //free(&cinfo);
    //free(&jerr);
//    free(line_pointer);
}

void write_jpeg(char *filename, unsigned char **data, int *width, int *height)
{
    FILE * outfile = fopen(filename, "wb");
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);
    cinfo.image_width = *width;
    cinfo.image_height = *height;
    cinfo.in_color_space = JCS_RGB;
    cinfo.input_components = 3;
    jpeg_set_defaults(&cinfo);
    jpeg_start_compress(&cinfo, TRUE);
    unsigned char *line_pointer;
    int i = 0;
    while (cinfo.next_scanline < cinfo.image_height) {
        line_pointer = *data + i * cinfo.image_width * cinfo.input_components;
        jpeg_write_scanlines(&cinfo, &line_pointer, 1); 
        i ++;
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

     fclose(outfile);

    //free(&cinfo);
    //free(&jerr);
    //free(line_pointer);
}

void get_pixel_of(int x, int y, unsigned char *dest, unsigned char **data, int *width, int *height)
{
    if ((x >= *width) || (x < 0) || (y >= *height) || (y < 0))
    {
        dest[0] = 0;
        dest[1] = 0;
        dest[2] = 0;
        return;
    }
    unsigned char *pos;
    pos = *data + (y * *width + x) * 3;
    dest[0] = pos[0];
    dest[1] = pos[1];
    dest[2] = pos[2];
}

void set_pixel_of(int x, int y, unsigned char *dest, unsigned char **data, int *width, int *height)
{
    if ((x >= *width) || (x < 0) || (y >= *height) || (y < 0))
    {
        return;
    }
    unsigned char *pos;
    pos = *data + (y * *width + x) * 3;
    pos[0] = dest[0];
    pos[1] = dest[1];
    pos[2] = dest[2];
}


int compress(char * in,char * out){
    int width, height = 0;
    unsigned char *data;

     read_jpeg(in, &data, &width, &height);
    unsigned char pixel[3] = {0, 0, 0};
    set_pixel_of(0, 0, pixel, &data, &width, &height);
    write_jpeg(out, &data, &width, &height);

    free(data);
    //free(width);
    //free(height);
    return 0;
}
//该片段来自于http://outofmemory.cn