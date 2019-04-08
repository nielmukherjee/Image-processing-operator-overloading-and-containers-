#include "imageops.h"
using namespace std;

namespace ANGDAN002{
    
    //default constructor
    Image::Image(){}
    //default destructor
    Image::~Image(){}
    //parametrized constructor
    Image::Image(int width, int height ,std::unique_ptr<unsigned char[]> data)
        :width(width)
        ,height(height)
        ,data(data.get())
    {};
    //copy constructor
    Image::Image (const Image& image)
        :width(image.width)
        ,height(image.height)
        ,data(image.data.get())
    {};
    //Move constructor
    Image::Image (Image&& other)
        :width(other.width)
        ,height(other.height)
        ,data(move(other.data.get()))
    {};
    Image::Image& Image::operator=(const Image& other)
    {
        if (this != &other) {
        this->width = other.width;
        this->height = other.height;
       //s data.getData() = other.data.get();  
        }
         
    return *this;
    }
    Image::Image& Image::operator=(Image&& other){
        if (this != &other) {
        this->width = other.width;
        this->height = other.height;
        //this->getData() = move(other.data.get());
        other.setWidth(0);
        other.setHeight(0);
        other.setData(nullptr);
        }
        return *this;
   
    }





}