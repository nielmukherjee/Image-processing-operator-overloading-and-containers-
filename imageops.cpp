/*
* Author : Dancan Angwenyi
* Date : 8th April 2019
* Computer Science
* C++ Image processing (Using containers and operators)
*/
#include "imageops.h"
using namespace std;

namespace ANGDAN002 {

//default constructor
Image::Image()
{
    this->width = 0;
    this->height = 0;
}
//default destructor
Image::~Image()
{
    this->width = -1;
    this->height = -1;
    data.reset(nullptr);
}
//parametrized constructor
Image::Image(int width, int height)
    : width(width)
    , height(height){};
//copy constructor
Image::Image(Image& other)
{
    this->width = other.width;
    this->height = other.height;
    this->data.reset(new unsigned char[width * height]);
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while ( beg != end) { *beg = *inStart; ++beg; ++inStart; } 
}
//Move constructor
Image::Image(Image&& other)
    : width(other.width)
    , height(other.height)
{
    this->data.reset(new unsigned char[width * height]);
    this->data = std::move(other.data);
}
//copy assignment operator
Image::Image& Image::operator=(Image& other)
{
    if (this != &other) {
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        Image::iterator beg = this->begin(), end = this->end();
        Image::iterator inStart = other.begin(), inEnd = other.end();
        while ( beg != end) { *beg = *inStart; ++beg; ++inStart; } 
    }
    return *this;
}
//move assignment operator
Image::Image& Image::operator=(Image&& other)
{
    if (this != &other) {
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        this->data = std::move(other.data);
        other.width = -1;
        other.height = -1;
    }
    return *this;
}
//Accessors
int Image::getWidth() const
{
    return width;
}
int Image::getHeight() const
{
    return height;
}
//Mutators
void Image::setWidth(int width)
{
    this->width = width;
}
void Image::setHeight(int height)
{
    this->height = height;
}
//overloaded operators
Image Image::operator+(Image& other){}
Image Image::operator-(Image& other){}
Image Image::operator!(){}
Image Image::operator/(Image& others){}
Image Image::operator*(int f){}

//load and save images
void Image::load(std::string inputFileName) {}
void Image::save(std::string outputFileName) {}
}