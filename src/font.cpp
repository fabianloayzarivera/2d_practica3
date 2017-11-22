#include <font.h>
#include <iostream>
#include <vector>
//Font*  Font::load(const char* filename, float height) {
//	Font *resultFont;
//	FILE *ptr;
//
//	unsigned char ttf_buffer[1 << 20];
//	unsigned char temp_bitmap[512 * 512];
//	stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
//	ptr = fopen(filename, "r");
//	if (ptr == NULL) {
//		return nullptr;
//	}
//	else {
//		fread(ttf_buffer, 1, 1 << 20, ptr);
//		stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
//		
//		//lgfx_setcolor(1, 1, 1, 1);
//
//
//
//		fclose(ptr);
//		
//
//	}
//		return nullptr;
//}

Font*  Font::load(const char* filename, float height) {
	Font *resultFont;
	FILE *ptr;
	size_t size = 512;
	size_t sizeBuffer = 512;
	std::vector<unsigned char> ttf_buffer(sizeBuffer);
	std::vector<unsigned char> pixels(size * size);
	std::vector<unsigned char> colorBuffer(size * size);
	std::vector<stbtt_bakedchar> charData(128);
	ptr = fopen(filename, "r");
	if (ptr == NULL) {
		return nullptr;
	}
	else {
	
		while (fread(ttf_buffer.data(), 1, sizeBuffer, ptr) == 0) {
			sizeBuffer *= 2;

		}
		while (stbtt_BakeFontBitmap(ttf_buffer.data(), 0, 32.0, pixels.data(), 512, 512, 32, 96, charData.data()) == 0) {
			size *= 2;
			pixels.resize(size * size);
		}

		colorBuffer.resize(size * size * 4);


		
		fclose(ptr);

	}
		
	return nullptr;
}