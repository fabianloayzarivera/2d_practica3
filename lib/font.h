#pragma once
#include <stb_truetype.h>
#include <Vec2.h>
#include <conio.h>

class Font {
private:
	float height;
public:
	static Font*  load(const char* filename, float height);
public:
	float         getHeight() const;
	Vec2          getTextSize(const char* text) const;
	void          draw(const char* text, const Vec2& pos) const;

};