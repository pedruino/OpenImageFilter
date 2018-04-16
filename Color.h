#pragma once
class Color
{
private:
	unsigned int _red, _green, _blue, _alpha;

public:
	Color()
		:_red(0), _green(0), _blue(0), _alpha(0xFF) {}
	Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 0xFF)
		:_red(red), _green(green), _blue(blue), _alpha(alpha) {}
	Color(float red, float green, float blue, float alpha = 1.0)
		:_red(red), _green(green), _blue(blue), _alpha(alpha) {}

	unsigned int& red() { return _red; }
	unsigned int& green() { return _green; }
	unsigned int& blue() { return _blue; }
	unsigned int& alpha() { return _alpha; }
	const unsigned char& red() const { return _red; }
	const unsigned char& green() const { return _green; }
	const unsigned char& blue() const { return _blue; }
	const unsigned char& alpha() const { return _alpha; }

	void set_f_red(float val) { _red = val * 255.0 + .5; }
	void set_f_green(float val) { _green = val * 255.0 + .5; }
	void set_f_blue(float val) { _blue = val * 255.0 + .5; }
	void set_f_alpha(float val) { _alpha = val * 255.0 + .5; }
	float get_f_red() const { return _red / 255.0; }
	float get_f_green() const { return _green / 255.0; }
	float get_f_blue() const { return _blue / 255.0; }
	float get_f_alpha() const { return _alpha / 255.0; }

	unsigned int rgba() { return (_red << 24) | (_green << 16) | (_blue << 8) | (_alpha << 0); }
};