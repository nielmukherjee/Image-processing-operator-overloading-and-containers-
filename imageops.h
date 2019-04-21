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
#include <fstream>
#include <iostream>
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
    Image(int width, int height,std::unique_ptr<unsigned char[]> data); //Parametirized constructor
    Image(Image& image); //Copy constructor
    Image(Image&& other); //Move constructor
    Image& operator=(Image& other); //Assignment operator
    Image& operator=(Image&& other); //Move assignment operator
    //Accessors
    int getWidth() const;
    int getHeight() const;
    std::unique_ptr<unsigned char[]>& getData();
    //Mutators
    void setWidth(int width);
    void setHeight(int height);
    //overloaded operators
    Image operator+(Image& other);
    Image operator-(Image& other);
    Image operator!();
    Image operator/(Image& L1);
    Image operator*(int i);
    friend void operator >>(std::ifstream& stream, Image& other);
    friend void operator <<(std::ofstream& stream, Image& other);
    //other methods
    void copy(const Image& other);
    //load and save images
    Image load(std::string inputFileName);
    void save(std::string outputFileName);

    //start class iterator and make image the friend
    class iterator {
    private:
        unsigned char* ptr;
        // construct only via Image class (begin/end)
       
        iterator(u_char* p)
            : ptr(p)
        {
        }

    public: 
         friend class Image;
        //copy construct is public friend class Image;
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
            //std::cout<<"operator != called"<<std::endl;
            if (this->ptr != rhs.ptr) {
               // std::cout<<"operator != found true"<<std::endl;
                return true;
            }

            else {
               // std::cout<<"operator != found false"<<std::endl;
                return false;
            }
            //std::cout<<"operator != done"<<std::endl;
        }
    };
    // define begin()/end() to get iterator to start and
    iterator begin(void) const {
        return iterator(data.get());
    }
    iterator end(void) const {
        return (data.get()+((height)*(width)));
    }
};
}

#endif
