
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

namespace ANGDAN002 {
class Image {
private:
    int width, height;
    std::unique_ptr<unsigned char[]> data;

public:
    Image(); //default constructor
    ~Image(); //default destructor
    //Parametirized constructor
    Image(int width, int height ,std::unique_ptr<unsigned char[]> data);
    Image (const Image& image); //Copy constructor
    Image (Image&& other); //Move constructor
    Image& operator=(const Image& other); //Assignment operator
    Image& operator=(Image&& other); //Move assignment operator
    /***************************Mutators******************/
    void setWidth(int width);
    void setHeight(int height);
    void setData(std::unique_ptr<unsigned char[]> data);
    /*********************************************************/
    /***********************Accessors*************************/
    int getWidth() const;
    int getHeight() const;
    std::unique_ptr<unsigned char[]> getData() const;
    /*********************************************************/
    class iterator {
    private:
        unsigned char* ptr;
        // construct only via Image class (begin/end)
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
        }
        // other methods for iterator
    };
    // define begin()/end() to get iterator to start and
    // "one-past" end.
    iterator begin(void) { return iterator(data.get()) } // etc
};
}
}

#endif