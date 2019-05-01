
#ifndef FILTER_H
#define FILTER_H
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>

namespace ANGDAN002{
        class Filter{
          private:
          friend class Image;
            int N;   //must be odd
            float fir[100][100]; //default size
            std::string filename;     
          public:
            Filter(std::string filename)
            {
                std::ifstream file(filename);
                if (!file) {
                    std::cerr << "Unable to open file datafile.txt";
                    exit(1); 
                }
                int n;
                float x;
                file >> n;
                this->N = n;
                while (file >> x) {
                    for(int i = 0; i< N;++i){
                        for(int j = 0; j<N ;++j){
                            fir[i][j] = x;
                        }
                    }
                }
                file.close();
            }
        };      
   
}
#endif
