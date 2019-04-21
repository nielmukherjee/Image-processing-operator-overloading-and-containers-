#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "imageops.h"
namespace ANGDAN002{
TEST_CASE("ADDITION AND SUBRACTION","[ADDITION SUBRACTION]")
{
    unsigned char* buffer = new unsigned char[5]{255,2,3,12,2};
    unsigned char* buffer1= new unsigned char[5]{3,5,255,1,2};
    Image i1(5,5,nullptr);
    Image i2(5,5,nullptr);
    i1.getData().reset(buffer);
    i2.getData().reset(buffer1);

    SECTION("ADDITION"){
    Image iSum = i1+i2;

    REQUIRE(iSum.getData()[0]==255);
    REQUIRE(iSum.getData()[3]==13);
    REQUIRE(iSum.getData()[4]==4);
    REQUIRE(iSum.getData()[2]==255);
    }

    SECTION("SUBTRACTION"){
    Image iDif= i1-i2;
    REQUIRE(iDif.getData()[4]==0);
    REQUIRE(iDif.getData()[3]==11);
    REQUIRE(iDif.getData()[1]==0);
    REQUIRE(iDif.getData()[2]==0);
    }
}
}