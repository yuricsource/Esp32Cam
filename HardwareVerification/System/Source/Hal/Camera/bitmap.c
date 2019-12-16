//https://stackoverflow.com/a/23303847
#include "bitmap.h"
#include <string.h>
#include <stdlib.h>


static bitmap_header_t *bmp_create_header(int w, int h)
{
	bitmap_header_t *pbitmap  = (bitmap_header_t*)calloc(1, sizeof(bitmap_header_t));
	int _pixelbytesize = w * h * _bitsperpixel/8;
	int _filesize = _pixelbytesize+sizeof(bitmap_header_t);
	memcpy((char*)pbitmap->fileheader.signature, "BM", 2);
	pbitmap->fileheader.filesize = _filesize;
	pbitmap->fileheader.fileoffset_to_pixelarray = sizeof(bitmap_header_t);
	pbitmap->bitmapinfoheader.dibheadersize = sizeof(Bitmapinfoheader);
	pbitmap->bitmapinfoheader.width = w;
	pbitmap->bitmapinfoheader.height = h;
	pbitmap->bitmapinfoheader.planes = _planes;
	pbitmap->bitmapinfoheader.bitsperpixel = _bitsperpixel;
	pbitmap->bitmapinfoheader.compression = _compression;
	pbitmap->bitmapinfoheader.imagesize = _pixelbytesize;
	pbitmap->bitmapinfoheader.ypixelpermeter = _ypixelpermeter ;
	pbitmap->bitmapinfoheader.xpixelpermeter = _xpixelpermeter ;
	pbitmap->bitmapinfoheader.numcolorspallette = 0;
	return pbitmap;
}
