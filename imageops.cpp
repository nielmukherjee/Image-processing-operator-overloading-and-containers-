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
    cout<<"destructor invoked"<<endl;
    this->width = -1;
    this->height = -1;
    data.reset(nullptr);
    cout<<"destructor done"<<endl;
}
//parametrized constructor
Image::Image(int width, int height,unique_ptr<unsigned char[]> data_in)
    : width(width)
    , height(height)
    ,data(move(data_in)){};
//copy constructor
Image::Image(Image& other)
{
    cout<<"copy constructor called"<<endl;
    this->width = other.width;
    this->height = other.height;
    this->data.reset(new unsigned char[width * height]);
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while ( beg != end) { *beg = *inStart; ++beg; ++inStart; }
    cout<<"copy constructor done"<<endl;
}
//Move constructor
Image::Image(Image&& other)
    : width(other.width)
    , height(other.height)
{
    cout<<"move constructor called"<<endl;
    this->data.reset(new unsigned char[width * height]);
    this->data = move(other.data);
    cout<<"move constructor called"<<endl;
}
//copy assignment operator
Image& Image::operator=(Image& other)
{
    if (this != &other) {
        //delete [] data.get();
        cout<<"copy assignment operator invoked"<<endl;
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        Image::iterator beg = this->begin(), end = this->end();
        Image::iterator inStart = other.begin(), inEnd = other.end();
        while ( beg != end) { *beg = *inStart; ++beg; ++inStart; }
        cout<<"copy assignment done"<<endl;
    }
    return *this;
}
//move assignment operator
Image& Image::operator=(Image&& other)
{
    if (this != &other) {
        cout<<"move constructor called"<<endl;
        delete [] data.get();
        this->width = other.width;
        this->height = other.height;
        this->data.reset(new unsigned char[width * height]);
        this->data = std::move(other.data);
        other.width = -1;
        other.height = -1;
        other.data.reset(nullptr);
        cout<<"move constructor done"<<endl;
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
std::unique_ptr<unsigned char[]>& Image::getData(){
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
Image Image::operator+(Image& other){
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while ( beg != end) {
        *beg = *inStart+*beg;
        ++beg; 
        ++inStart; 
    }
}
Image Image::operator-(Image& other){
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while ( beg != end) {
        *beg = *inStart-*beg;
        ++beg; 
        ++inStart; 
    }
}
Image Image::operator!(){
    Image::iterator beg = this->begin(), end = this->end();
    cout<<"line one okay"<<endl;
    cout<<"line one okay"<<*end<<endl;
    while ( beg != end) { 
        //cout<<"loop okay"<<endl;
        *beg = 255-*beg; ++beg; 
    }
}
Image Image::operator/(Image& other){
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while ( beg != end) {
        if(*beg==255){
            *beg = *inStart;
        }
        else{
            *beg  =0;
        }
        ++beg; 
        ++inStart; 
    }
}
Image Image::operator*(int f){
    Image::iterator beg = this->begin(), end = this->end();
    while ( beg != end) { 
        if(*beg >f ){
            *beg = 255;
        }
        else{
            *beg =0;
        }
       ++beg; 
    }
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
void operator >>(ifstream& stream, Image& other){

    if(!stream){
        cout<<"Unable to open file"<<endl;
    }
    else{
        cout<<"File opened"<<endl;
        string line;
        int height, width;
        int size ;
        bool start = false;
        while(getline(stream,line)){
            
            if(line != "P5" && line != "255" && line.at(0) != '#'){
                stringstream ss(line);
                if(start==false){
                    ss >> height;
                    ss >> width;
                    cout<<height<<" is "<<width<<endl;
                    size = height*width;
                    start = true;
                    cout<<"File size is: "<<size<<endl;
                }
                else if (start==true){
                    cout<<"Start reading file data: "<<endl;
                    unique_ptr<unsigned char[]> data(new unsigned char[size]);
                    ss.read((char *)data.get(),size);
                    cout<<"Successfully read "<<endl;
                    Image imagee(width,height,move(data));
                    cout<<"Successfully created an instance of class image"<<endl;
                    stream.close();
                    other = imagee; //invokes copy assignment
                    cout<<"Successfully done"<<endl; 
                }   
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
void operator <<(ofstream& stream, Image& other){
    cout<<"start writing to out file"<<endl;
    int size = other.width*other.height;
    stream<<"P5"<<endl;
    stream<<other.height<<" "<<other.width<<endl;
    stream<<"255"<<endl;
    stream.write((char*)other.data.get(),size);
    stream.close();
    cout<<"out file closed"<<endl;
}
//
void Image::copy(const Image& other) {
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = other.begin(), inEnd = other.end();
    while ( beg != end) { *beg = *inStart; ++beg; ++inStart; }
}

//load and save images
Image Image::load(std::string inputFileName) {
    ifstream file_stream(inputFileName, ios::in | ios::binary);
    Image imageFile(0,0,std::move(nullptr));
   
    file_stream>>imageFile;
    cout<<"image loaded successfully"<<endl;
    cout<<"image data :"<<endl;
    std::cout<<imageFile.data.get()<<endl;
    cout<<"image data :"<<endl;
    return imageFile;
}
void Image::save(std::string outputFileName) {
    ofstream outstream(outputFileName, ios::out | ios::binary | ios::app);
    Image imageFile(width,height,move(data));
    outstream<<imageFile;
    std::cout<<imageFile.data.get()<<endl;
    cout<<"image saved successfully"<<endl;
}
}