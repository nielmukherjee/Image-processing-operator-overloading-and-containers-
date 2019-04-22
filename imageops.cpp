/**
* Copyright (C) Dancan Matara Angwenyi
* Email: dancangwe@gmail.com
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
    : width(width)
    , height(height)
    , data(nullptr)
{
}
//default destructor
Image::~Image()
{
    cout << "destructor invoked" << endl;
    // this->width = 0;
    // this->height = 0;
    // cout<<"destructor done 1"<<endl;
    // this->data = nullptr;
    // cout<<"destructor done 2"<<endl;
}
//parametrized constructor
Image::Image(int width, int height, unique_ptr<unsigned char[]> data_in)
    : width(width)
    , height(height)
    , data(move(data_in))
{
}
//copy constructor
Image::Image(Image& other)
{
    cout << "copy constructor called" << endl;
    this->width = other.width;
    this->height = other.height;
    this->data.reset(new unsigned char[width * height]);
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while (beg != end) {
        *beg = *inStart;
        ++beg;
        ++inStart;
    }
    cout << "copy constructor done" << endl;
}
//Move constructor
Image::Image(Image&& other)
    : width(other.width)
    , height(other.height)
{
    cout << "move constructor called" << endl;
    this->data.reset(new unsigned char[width * height]);
    this->data = move(other.data);

    other.width = 0;
    other.height = 0;
    other.data.reset(nullptr);

    cout << "move constructor called" << endl;
}
//copy assignment operator
Image& Image::operator=(Image& other)
{
    if (this != &other) {
        //delete [] data.get();
        cout << "copy assignment operator invoked" << endl;
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        Image::iterator beg = this->begin(), end = this->end();
        Image::iterator inStart = other.begin(), inEnd = other.end();
        while (beg != end) {
            *beg = *inStart;
            ++beg;
            ++inStart;
        }
        cout << "copy assignment done" << endl;
    }
    return *this;
}
//move assignment operator
Image& Image::operator=(Image&& other)
{
    if (this != &other) {
        cout << "move constructor called" << endl;
        //delete [] data.get();
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        this->data = move(other.data);
        other.width = 0;
        other.height = 0;
        other.data.reset(nullptr);
        cout << "move constructor done" << endl;
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
std::unique_ptr<unsigned char[]>& Image::getData()
{
    return data;
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
Image& Image::operator+(Image& other)
{
    //std::cout<<"Data before plus"<<endl;
    //std::cout<<data.get()<<endl;
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while (beg != end) {
        if((*inStart + *beg) > 255){*beg=255;}
        else{*beg = *inStart + *beg;}
        if(*beg > 255){*beg=255;}
        ++beg;
        ++inStart;
    }
    //std::cout<<"Data after plus"<<endl;
    //std::cout << data.get() << endl;
    return (*this);
}
Image& Image::operator-(Image& other)
{
    //std::cout<<"Data before minus"<<endl;
    //std::cout<<data.get()<<endl;
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while (beg != end) {
       if((*beg - *inStart) < 0){*beg=0;}
       else{*beg = *beg - *inStart;}
        ++beg;
        ++inStart;
    }
    //std::cout<<"Data after minus"<<endl;
    //std::cout << data.get() << endl;
    return (*this);
}
Image& Image::operator!()
{
    //std::cout<<data.get()<<endl;
    Image::iterator beg = this->begin(), end = this->end();
    while (beg != end) {
        *beg = 255 - *beg;
        ++beg;
    }
    return (*this);
    //std::cout<<endl<<endl<<endl<<endl<<endl;
    //std::cout<<"Data after noting"<<endl;
    //std::cout<<data.get()<<endl;
}
Image& Image::operator/(Image& other)
{
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while (beg != end) {
        if (*inStart != 255) {
            *beg = 0;
        }
        ++beg;
        ++inStart;
    }
    return (*this);
}
Image& Image::operator*(int f)
{
    Image::iterator beg = this->begin(), end = this->end();
    while (beg != end) {
        if (*beg > f) {
            *beg = 255;
        }
        else {
            *beg = 0;
        }
        ++beg;
    }
    return (*this);
}
/*
* #Data Format of the file
* 
* P5
* #Comments if any
* Nrows Ncols
* 255
* binary_data_block
*/
void operator>>(ifstream& stream, Image& other)
{

    if (!stream) {
        cout << "Unable to open file" << endl;
    }
    else {
        cout << "File opened" << endl;
        string line;
        int height, width;
        int size;
        bool start = false;
        while (getline(stream, line)) {

            if (line != "P5" && line != "255" && line.at(0) != '#') {
                stringstream ss(line);
                if (start == false) {
                    ss >> height;
                    ss >> width;
                    cout << height << " is " << width << endl;
                    size = height * width;
                    start = true;
                    cout << "File size is: " << size << endl;
                }

                cout << "Start reading file data: " << endl;
                //cout << "File size is: " << size << endl;
                unique_ptr<unsigned char[]> buffer(new unsigned char[size]);
                stream.read((char*)buffer.get(), size);
                cout << "Successfully read " << endl;
                Image imagee(width, height, move(buffer));
                //cout << "imagee data :" << endl;
                //std::cout << imagee.data.get() << endl;
                //cout<<"Successfully created an instance of class image"<<endl;
                stream.close();
                other = imagee; //invokes copy assignment
                //std::cout<<"other copied data :"<<endl;
                //std::cout<<other.data.get()<<endl;
                cout << "input stream Successfully done" << endl;
                // }
            }
        }
    }
}
/*
* #Data Format for writing to the file
* 
* P5
* #Comments if any
* Nrows Ncols
* 255
* binary_data_block
*/
void operator<<(ofstream& stream, Image& other)
{
    cout << "start writing to out file" << endl;
    cout << "width: " << other.width << " height: " << other.height << endl;
    //cout<<"P5"<<endl<<"255"<<endl;
    //std::cout<<"other copied data :"<<endl;
    //std::cout<<other.data.get()<<endl;
    int size = other.width * other.height;
    //std::cout<<"other data :"<<endl;
    // std::cout<<other.data.get()<<endl;
    cout << "File size: " << size << endl;
    stream << "P5" << endl;
    stream << "#Dancan" << endl;
    stream << other.height << " " << other.width << endl;
    stream << 255 << endl;
    stream.write((char*)other.data.get(), size);
    stream.close();
    cout << "out file closed" << endl;
}
//
void Image::copy(const Image& other)
{
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while (beg != end) {
        *beg = *inStart;
        ++beg;
        ++inStart;
    }
}

//load and save images
Image Image::load(std::string inputFileName)
{
    ifstream file_stream(inputFileName, ios::in | ios::binary);
    Image imageFile(0, 0, std::move(nullptr));
    file_stream >> imageFile;
    cout << "image loaded successfully" << endl;
    //cout<<"image data :"<<endl;
    //std::cout<<imageFile.data.get()<<endl;
    return imageFile;
}
void Image::save(std::string outputFileName)
{

    //std::cout<<"Data to be saved :"<<endl;
    //std::cout<<data.get()<<endl;
    ofstream outstream(outputFileName, ios::out | ios::binary | ios::app);
    outstream << (*this);
    //Image imageFile(width,height,move(data));
    // outstream<<imageFile;
    //std::cout<<imageFile.data.get()<<endl;
    cout << "image saved successfully" << endl;
}
}