/*
* Author : Dancan Angwenyi
* Date : 8th April 2019
* Computer Science
* C++ Image processing (Using containers and operators)
*/
#ifndef IMAGEOPS_H_
#define IMAGEOPS_H_
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <algorithm>
#include <memory>

namespace ANGDAN002 {
class Image {
private:
    int width, height;
    std::unique_ptr<unsigned char[]> data;

public:
    Image(); //default constructor
    ~Image(); //default destructor
    Image(int width, int height); //Parametirized constructor
    Image(Image& image); //Copy constructor
    Image(Image&& other); //Move constructor
    Image& operator=(Image& other); //Assignment operator
    Image& operator=(Image&& other); //Move assignment operator
    //Accessors
    int getWidth() const;
    int getHeight() const;
    //Mutators
    void setWidth(int width);
    void setHeight(int height);
    //overloaded operators
    Image operator+(Image& other);
    Image operator-(Image& other);
    Image operator!();
    Image operator/(Image& L1);
    Image operator*(int i);
    //load and save images
    void load(std::string inputFileName);
    void save(std::string outputFileName);

    //start class iterator and make image the friend
    class iterator {
    private:
        unsigned char* ptr;
        // construct only via Image class (begin/end)
        friend class Image;
        iterator(u_char* p)
            : ptr(p)
        {
        }

    public: //copy construct is public
        iterator(const iterator& rhs)
            : ptr(rhs.ptr)
        {
        }
        // define overloaded ops: *, ++, --, =
        iterator& operator=(const iterator& rhs)
        {
            if (this != &rhs) {
                this->ptr = rhs.ptr;
            }
            return *this;
        }
        // other methods for iterator
        unsigned char& operator*()
        {
            return *ptr;
        }
        iterator& operator++()
        {
            ++ptr;
            return (*this);
        }
        iterator& operator--()
        {
            --ptr;
            return (*this);
        }
        bool operator!=(const iterator& rhs)
        {
            if (this->ptr != rhs.ptr) {
                return true;
            }

            else {
                return false;
            }
        }
    };
    // define begin()/end() to get iterator to start and
    iterator begin(void)
    {
        return iterator(data.get());
    }
    iterator end(void)
    {
        return iterator(data.get() + (width * height));
    }
};
}

#endif