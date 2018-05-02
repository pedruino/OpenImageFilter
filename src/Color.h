//
// Created by pedruino on 4/30/18.
//

#ifndef OPENIMAGEFILTER_COLOR_H
#define OPENIMAGEFILTER_COLOR_H

class Color {
private:
    unsigned char _red, _green, _blue, _alpha;

public:
    Color()
            :_red(0), _green(0), _blue(0), _alpha(0xFF) {}
    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 0xFF)
            :_red(red), _green(green), _blue(blue), _alpha(alpha) {}
    Color(unsigned int red, unsigned int  green, unsigned int  blue, unsigned int  alpha = 1)
            :_red(red), _green(green), _blue(blue), _alpha(alpha) {}
    Color(int red, int  green, int  blue, int  alpha = 1)
            :_red(red), _green(green), _blue(blue), _alpha(alpha) {}
    Color(float red, float green, float blue, float alpha = 1.0)
            :_red(red), _green(green), _blue(blue), _alpha(alpha) {}

    const unsigned char red() const { return _red; }
    const unsigned char green() const { return _green; }
    const unsigned char blue() const { return _blue; }
    const unsigned char alpha() const { return _alpha; }

    const unsigned int rgba() { return (_red << 24) | (_green << 16) | (_blue << 8) | (_alpha << 0); }
};


#endif //OPENIMAGEFILTER_COLOR_H
