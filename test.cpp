/**
* Copyright (C) Dancan Matara Angwenyi
* Email: dancangwe@gmail.com
* Author : Dancan Angwenyi
* Date : 22nd April 2019
* Computer Science
* C++ Image processing (Using containers and operators)
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "imageops.h"
namespace ANGDAN002{
/**
 * Move and copy semantics
 */
TEST_CASE("MOVE & COPY SEMANTICS","[MOVE COPY]")
{
    unsigned char* buffer1 = new unsigned char[25]{
    255,2,3,12,2,255,2,3,12,2,
    255,2,3,12,2,255,2,3,12,2,255,2,3,12,2};
    int f = 128;
    Image image1(5,5,nullptr);
    Image image2(0,0,nullptr);
    image1.getData().reset(buffer1);
    SECTION("PRE CONDITION image1","[ReturnValue]"){
        REQUIRE(image1.getData()[0]==255);
        REQUIRE(image1.getData()[1]==2);
        REQUIRE(image1.getData()[2]==3);
        REQUIRE(image1.getData()[3]==12);
        REQUIRE(image1.getData()[4]==2);
    }
    SECTION("COPY CONSTRUCTOR","[Image image3 = image1]"){
        Image image3 = image1;
        REQUIRE(image1.getData()!=nullptr);
        REQUIRE(image3.getWidth()== image1.getWidth());
        REQUIRE(image3.getHeight()== image1.getHeight());
        REQUIRE(image3.getData()[0]==255);
        REQUIRE(image3.getData()[6]==2);
        REQUIRE(image3.getData()[22]==3);
        REQUIRE(image3.getData()[24]==2);
        REQUIRE(image3.getData()[10]==255);

    }
    SECTION("MOVE CONSTRUCTOR","[Image image3 = std::move(image1)]"){
        Image image3 = std::move(image1);
        REQUIRE(image1.getData()==nullptr);
        REQUIRE(image3.getWidth() != image1.getWidth());
        REQUIRE(image3.getHeight() != image1.getHeight());
        REQUIRE(image3.getData()[0]==255);
        REQUIRE(image3.getData()[6]==2);
        REQUIRE(image3.getData()[22]==3);
        REQUIRE(image3.getData()[24]==2);
        REQUIRE(image3.getData()[10]==255);

    }
    SECTION("COPY ASSIGNMENT","[image2 = image1]"){
        image2 = image1;
        REQUIRE(image1.getData()!=nullptr);
        REQUIRE(image2.getWidth()== image1.getWidth());
        REQUIRE(image2.getHeight()== image1.getHeight());
        REQUIRE(image2.getData()[0]==255);
        REQUIRE(image2.getData()[6]==2);
        REQUIRE(image2.getData()[22]==3);
        REQUIRE(image2.getData()[24]==2);
        REQUIRE(image2.getData()[10]==255);

    }
     SECTION("MOVE ASSIGNMENT","[image2 = std::move(image1)]"){
        image2 = std::move(image1);
        REQUIRE(image1.getData()==nullptr);
        REQUIRE(image2.getWidth() != image1.getWidth());
        REQUIRE(image2.getHeight() != image1.getHeight());
        REQUIRE(image2.getData()[0]==255);
        REQUIRE(image2.getData()[6]==2);
        REQUIRE(image2.getData()[22]==3);
        REQUIRE(image2.getData()[24]==2);
        REQUIRE(image2.getData()[10]==255);

    }
}
/**
 * Iterator and its operators (including boundary conditions)
 **/
TEST_CASE("ITERATOR AND ITS OPERATORS","[ITERATOR OPERATORS")
{
    unsigned char* buffer1 = new unsigned char[25]{
    255,2,3,12,2,255,2,3,12,2,
    255,2,3,12,2,255,2,3,12,2,255,2,3,12,2};
    unsigned char* buffer2= new unsigned char[25]{
    3,5,255,1,2,3,5,255,1,2,
    3,5,255,1,2,3,5,255,1,2,3,5,255,1,2};

    Image image1(5,5,nullptr);
    Image image2(5,5,nullptr);
    image1.getData().reset(buffer1);
    image2.getData().reset(buffer2);
    SECTION("* OPERATOR","[* OPERATOR]"){
        Image::iterator beg = image2.begin(), end = image2.end();
        Image::iterator inStart = image1.begin(), inEnd = image1.end();
        REQUIRE(*(beg)==3);
        REQUIRE(*(inStart)==255); 
        REQUIRE(*(end)!=2);
        REQUIRE(*(inEnd)!=2); 
    }
    SECTION("++ OPERATOR","[++ OPERATOR]"){
        Image::iterator beg = image2.begin(), end = image2.end();
        REQUIRE(*(beg)==3); ++beg;
        REQUIRE(*(beg)==5); ++beg;
        REQUIRE(*(beg)==255); ++beg;
        REQUIRE(*(beg)==1); ++beg;
        REQUIRE(*(beg)==2);
    }
    SECTION("-- OPERATOR","[-- OPERATOR]"){
        Image::iterator beg = image2.begin(), end = image2.end();
        --end;
        REQUIRE(*(end)==2); --end;
        REQUIRE(*(end)==1); --end;
        REQUIRE(*(end)==255);--end;
        REQUIRE(*(end)==5); --end;
        REQUIRE(*(end)==3);
    }
    SECTION("= OPERATOR","[= OPERATOR]"){
        Image::iterator beg = image1.begin(), end = image1.end();
        Image::iterator inStart = image2.begin(), inEnd = image2.end();
        *beg = *inStart;
        REQUIRE(*(beg)==3);
        REQUIRE(*(inStart)==3);
    }
}
/**
 * Testing Thresholding, inverting and masking operator overloads
 **/
TEST_CASE("THRESHOLDING","[THRESHOLDING]")
{
    unsigned char* buffer1 = new unsigned char[25]{
    255,2,3,12,2,255,2,3,12,2,
    255,2,3,12,2,255,2,3,12,2,255,2,3,12,2};
    int f = 128;
    Image image1(5,5,nullptr);
    image1.getData().reset(buffer1);
    SECTION("PRE CONDITION image1","[ReturnValue]"){
        REQUIRE(image1.getData()[0]==255);
        REQUIRE(image1.getData()[1]==2);
        REQUIRE(image1.getData()[2]==3);
        REQUIRE(image1.getData()[3]==12);
        REQUIRE(image1.getData()[4]==2);
    }
    SECTION("THRESHOLDING","[Image1*f]"){
        Image result = image1*f;
        REQUIRE(result.getData()[0]==255);
        REQUIRE(result.getData()[1]==0);
        REQUIRE(result.getData()[2]==0);
        REQUIRE(result.getData()[3]==0);
        REQUIRE(result.getData()[4]==0);
        REQUIRE(result.getData()[5]==255);
    }
    
}
TEST_CASE("INVERSE","[INVERSE]")
{
    unsigned char* buffer1 = new unsigned char[25]{
    255,2,3,12,2,255,2,3,12,2,
    255,2,3,12,2,255,2,3,12,2,255,2,3,12,2};
    Image image1(5,5,nullptr);
    image1.getData().reset(buffer1);
    SECTION("PRE CONDITION image1","[ReturnValue]"){
        REQUIRE(image1.getData()[0]==255);
        REQUIRE(image1.getData()[1]==2);
        REQUIRE(image1.getData()[2]==3);
        REQUIRE(image1.getData()[3]==12);
        REQUIRE(image1.getData()[4]==2);
    }
    SECTION("Inverse","[!Image1]"){
        !image1;
        REQUIRE(image1.getData()[0]==0);
        REQUIRE(image1.getData()[1]==253);
        REQUIRE(image1.getData()[2]==252);
        REQUIRE(image1.getData()[3]==243);
        REQUIRE(image1.getData()[4]==253);
    }
    
}

TEST_CASE("MASKING","[MASKING]")
{
    unsigned char* buffer1 = new unsigned char[25]{
    255,2,3,12,2,255,2,3,12,2,
    255,2,3,12,2,255,2,3,12,2,255,2,3,12,2};
    unsigned char* buffer2= new unsigned char[25]{
    255,255,255,255,255,0,0,0,0,0,
    0,0,0,0,0,0,0,255,255,255,255,255,255,255,255};

    Image image1(5,5,nullptr);
    Image image2(5,5,nullptr);
    image1.getData().reset(buffer1);
    image2.getData().reset(buffer2);

    SECTION("PRE CONDITION image1","[ReturnValue]"){
        REQUIRE(image1.getData()[0]==255);
        REQUIRE(image1.getData()[1]==2);
        REQUIRE(image1.getData()[2]==3);
        REQUIRE(image1.getData()[3]==12);
        REQUIRE(image1.getData()[4]==2);
    }
    SECTION("PRE CONDITION image2","[ReturnValue]"){
        REQUIRE(image2.getData()[0]==255);
        REQUIRE(image2.getData()[6]==0);
        REQUIRE(image2.getData()[22]==255);
        REQUIRE(image2.getData()[24]==255);
        REQUIRE(image2.getData()[10]==0);
    }
    SECTION("MASKING","[image1 / image2]"){
        Image result = image1/image2;
        REQUIRE(result.getData()[0]==255);
        REQUIRE(result.getData()[1]==2);
        REQUIRE(result.getData()[2]==3);
        REQUIRE(result.getData()[3]==12);
        REQUIRE(result.getData()[4]==2);
        REQUIRE(result.getData()[5]==0);
        REQUIRE(result.getData()[6]==0);
        REQUIRE(result.getData()[7]==0);
        REQUIRE(result.getData()[8]==0);
        REQUIRE(result.getData()[9]==0);
        REQUIRE(result.getData()[17]==3);
        REQUIRE(result.getData()[18]==12);
        REQUIRE(result.getData()[19]==2);
        REQUIRE(result.getData()[20]==255);
        REQUIRE(result.getData()[21]==2);
        REQUIRE(result.getData()[22]==3);
        REQUIRE(result.getData()[23]==12);
        REQUIRE(result.getData()[24]==2);
    }
}
/**-----------------------------------------------------------------*/
/*Addition and subtraction of images. Ensure that the pixels are clamped
 * appropriately
 * */
TEST_CASE("ADDITION AND SUBRACTION","[ADDITION SUBRACTION]")
{
    unsigned char* buffer1 = new unsigned char[25]{
    255,2,3,12,2,255,2,3,12,2,
    255,2,3,12,2,255,2,3,12,2,255,2,3,12,2};
    unsigned char* buffer2= new unsigned char[25]{
    3,5,255,1,2,3,5,255,1,2,
    3,5,255,1,2,3,5,255,1,2,3,5,255,1,2};

    Image image1(5,5,nullptr);
    Image image2(5,5,nullptr);
    image1.getData().reset(buffer1);
    image2.getData().reset(buffer2);

    SECTION("PRE CONDITION image1","[ReturnValue]"){
        REQUIRE(image1.getData()[0]==255);
        REQUIRE(image1.getData()[1]==2);
        REQUIRE(image1.getData()[2]==3);
        REQUIRE(image1.getData()[3]==12);
        REQUIRE(image1.getData()[4]==2);
    }
    SECTION("PRE CONDITION image2","[ReturnValue]"){
        REQUIRE(image2.getData()[0]==3);
        REQUIRE(image2.getData()[1]==5);
        REQUIRE(image2.getData()[2]==255);
        REQUIRE(image2.getData()[3]==1);
        REQUIRE(image2.getData()[4]==2);
    }
    SECTION("Addition","[image1 + image2]"){
        Image result = image1+image2;
        REQUIRE(result.getData()[0]==255);
        REQUIRE(result.getData()[1]==7);
        REQUIRE(result.getData()[2]==255);
        REQUIRE(result.getData()[3]==13);
        REQUIRE(result.getData()[4]==4);
    }
    SECTION("Subtraction","[image1 - image2]"){
        Image result = image1-image2;
        REQUIRE(result.getData()[0]==252);
        REQUIRE(result.getData()[1]==0);
        REQUIRE(result.getData()[2]==0);
        REQUIRE(result.getData()[3]==11);
        REQUIRE(result.getData()[4]==0);
    }
}
/**-----------------------------------------------------------------*/
}