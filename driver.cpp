/*
* Author : Dancan Angwenyi
* Date : 8th April 2019
* Computer Science
* C++ Image processing (Using containers and operators)
*/
#include "imageops.h"
#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//int main(int argc, char *argv[])
int main(int argc,char* argv[]){
     string operation;
      string output;
      string l1;
      string l2;
      int f = 80;
    if (argc < 4 || argc > 5) {
      exit(EXIT_FAILURE);
    }
    if (argc == 4) {
        operation =string(argv[1]);
        cout<<"operation "<<operation<<endl;
        output = string(argv[argc-1]);
        cout<<"operation "<<argc<<endl;
        l1 = string(argv[2]);
    }
     if (argc == 5) {
        operation =string(argv[1]);
        cout<<"operation "<<operation<<endl;
        output= string(argv[argc-1]);
        l1 = string(argv[2]);
        l2 = string(argv[3]);
    }

    if(operation=="-i"){   
        ANGDAN002::Image image(0,0,std::move(nullptr));
        ANGDAN002::Image image1 =  image.load(l1);
        cout<<"start Noting operations"<<endl;
        !image1;
        cout<<"noted"<<endl;
        image1.save(output); 
    }
    if(operation=="-l"){
        ANGDAN002::Image image(0,0,std::move(nullptr));
        ANGDAN002::Image image1 =  image.load(l1);
        ANGDAN002::Image image2 =  image.load(l2);
        cout<<"start maskin operations"<<endl;
        image1/image2;
        cout<<"Done masking"<<endl;
        image1.save(output);
    }
    if(operation=="-a"){
        ANGDAN002::Image image(0,0,std::move(nullptr));
        ANGDAN002::Image image1 =  image.load(l1);
        ANGDAN002::Image image2 =  image.load(l2);
        cout<<"start adding operations"<<endl;
        image1+image2;
        cout<<"Done adding"<<endl;
        image1.save(output);
    }
    if(operation=="-s"){
        ANGDAN002::Image image(0,0,std::move(nullptr));
        ANGDAN002::Image image1 =  image.load(l1);
        ANGDAN002::Image image2 =  image.load(l2);
        cout<<"start sub operations"<<endl;
        image1-image2;
        cout<<"Done subtracting"<<endl;
        image1.save(output);
    }
    
    if(operation=="-t"){   
        ANGDAN002::Image image(0,0,std::move(nullptr));
        ANGDAN002::Image image1 =  image.load(l1);
        cout<<"start threshold operations"<<endl;
        image1*f;
        cout<<"threshold operation Done"<<endl;
        image1.save(output); 
    }
    return 0;
}