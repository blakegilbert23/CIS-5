/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 11, 2022, 5:00 PM
 * Purpose: Calculate the percentage of the national budget spent on military.
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
