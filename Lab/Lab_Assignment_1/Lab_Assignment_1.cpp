/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 4, 2022, 8:46 PM
 * Purpose: All projects start by using the CPP template. It shows where to place your project
 *
 */

//System Level Libraries
#include <iostream> //input-output Library
#include <iomanip>  //format library
using namespace std;

//User Defined Libraries go here

//Global CONSTANTS (not global VARIABLES) go here (constants from Physics, Chemistry, Engineering,  and Conversions between systems of units)
const unsigned char CNVPERC = 100;

//Function Prototypes go here

//Execution begins here
int main(int argc, char **argv)
{
    //Initialize Random Seed once here

    //Declare  Variables here
    float milBdgt, natBdgt; //miltray budget and national budget
    float ttlPrct;          //military's spending of total national budget

    //Initialize Variables here
    milBdgt = 7.529e11;
    natBdgt = 6.820e12;

    //Map inputs/knowns to the output
    ttlPrct = milBdgt / natBdgt;

    //Display Output
    cout << fixed << setprecision(2) << endl;
    cout << "The military uses " << ttlPrct * CNVPERC << "\% of the total national budget" << endl;

    //Exit the program
    return 0;
}
