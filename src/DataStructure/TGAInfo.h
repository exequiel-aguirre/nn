#ifndef TGAInfoH
#define TGAInfoH

struct TGAInfo {
	const char* status;
	unsigned char type;
	unsigned char pixelDepth;
	short int w;
	short int h;
	unsigned char *pixels;
};

#endif