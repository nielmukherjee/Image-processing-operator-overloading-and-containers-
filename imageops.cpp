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
    : width(width = 0)
    , height(height = 0)
    , data(nullptr)
{
}
//default destructor
Image::~Image()
{
    cout << "destructor invoked" << endl;
    this->width = 0;
    this->height = 0;
    if(data){
         this->data = nullptr;
    }
    cout << "destructor done" << endl;
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
    : width(other.width)
    , height(other.height)
{
    cout << "copy constructor called" << endl;
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
    , data(move(other.data))
{
    cout << "move constructor called" << endl;

    other.width = 0;
    other.height = 0;
    other.data.reset(nullptr);

    cout << "move constructor called" << endl;
}
//copy assignment operator
Image& Image::operator=(Image& other)
{
    if (this != &other) {
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
        cout << "copy assignment operator done" << endl;
    }
    return *this;
}
//move assignment operator
Image& Image::operator=(Image&& other)
{
    if (this != &other) {
        cout << "move assignment operator called" << endl;
        //delete [] data.get();
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        this->data = move(other.data);
        other.width = 0;
        other.height = 0;
        other.data.reset(nullptr);
        cout << "move assignment operator done" << endl;
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
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    if ((this->width * this->height) != (other.width * other.height)) {
        cout << "!!!!!!!!!!!!!Images are not of the same size!!!!!!!!!!" << endl;
        cout << "Exiting from the program" << endl;
        exit(0);
    }
    while (beg != end) {
        if ((*inStart + *beg) > 255) {
            *beg = 255;
        }
        else {
            *beg = *inStart + *beg;
        }
        if (*beg > 255) {
            *beg = 255;
        }
        ++beg;
        ++inStart;
    }
    return (*this);
}
Image& Image::operator-(Image& other)
{
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    if ((this->width * this->height) != (other.width * other.height)) {
        cout << "!!!!!!!!!!!!!Images are not of the same size!!!!!!!!!!" << endl;
        cout << "Exiting from the program" << endl;
        exit(0);
    }
    while (beg != end) {
        if ((*beg - *inStart) < 0) {
            *beg = 0;
        }
        else {
            *beg = *beg - *inStart;
        }
        ++beg;
        ++inStart;
    }
    return (*this);
}
Image& Image::operator!()
{
    Image::iterator beg = this->begin(), end = this->end();
    while (beg != end) {
        *beg = 255 - *beg;
        ++beg;
    }
    return (*this);
}
Image& Image::operator/(Image& other)
{
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    if ((this->width * this->height) != (other.width * other.height)) {
        cout << "!!!!!!!!!!!!!Images are not of the same size!!!!!!!!!!" << endl;
        cout << "Exiting from the program" << endl;
        exit(0);
    }
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
Image& Image::operator%(Filter & g){
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = this->begin(), inEnd = this->end();
    float unfiltered[height][width];
    for(int i = 0; i<height ;++i){
        for (int j=0; j<width ;++j){
            while(beg!=end){
                float pixel = float(*beg);
                unfiltered[i][j]= pixel;
                ++beg;
            }
        }
    }
    for(int i = 0; i<height ;++i){
        for (int j=0; j<width ;++j){
            int median = g.N / 2;
            int x_val = 0;
            int y_val = 0;
            float fir[g.N][g.N];
            for (int x = i + median ; x >= i - median ; x--) {
                for (int y = j - median ; y <= j + median ; y++) {
                    int val1 = reflect(height, x);
                    int val2 = reflect(width, y);
                    fir[x_val][y_val] = unfiltered[val1][val2];
                    y_val += 1;
                }
               x_val += 1;
            }
            float sum = 0.0;
            for (int n = 0; n < g.N; n++) {
                for (int c = 0; c < g.N; c++) { 
                    sum += fir[n][c] * g.fir[n][c];
                }
            }
            if (sum > 255) {
                *beg = 255;
            }else {
                *beg = sum;
            }
            ++beg;
        }
    }
    return *this;
}

int Image::reflect(int measure, int value)
{
    int result = value;
    if (value < 0) {
         result= (value*-1) - 1;
        return result;
    }
    if (value >= measure) {
        result = (2 * measure) - (value)-1;
        return result;
    }
    return result;
}
/*
* Data Format of the file
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
                unique_ptr<unsigned char[]> buffer(new unsigned char[size]);
                stream.read((char*)buffer.get(), size);
                cout << "Successfully read " << endl;
                Image imagee(width, height, move(buffer));
                stream.close();
                other = imagee; //invokes copy assignment
                cout << "input stream Successfully done" << endl;
            }
        }
    }
}
/*
* Data Format for writing to the file
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
    int size = other.width * other.height;
    cout << "File size: " << size << endl;
    stream << "P5" << endl;
    stream << "#Dancan" << endl;
    stream << other.height << " " << other.width << endl;
    stream << 255 << endl;
    stream.write((char*)other.data.get(), size);
    stream.close();
    cout << "out file closed" << endl;
}
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

//load images
Image Image::load(std::string inputFileName)
{
    ifstream file_stream(inputFileName, ios::in | ios::binary);
    Image imageFile(0, 0, std::move(nullptr));
    file_stream >> imageFile;
    cout << "image loaded successfully" << endl;
    return imageFile;
}
// Save images
void Image::save(std::string outputFileName)
{

    ofstream outstream(outputFileName, ios::out | ios::binary | ios::app);
    outstream << (*this);
    cout << "image saved successfully" << endl;
}
}