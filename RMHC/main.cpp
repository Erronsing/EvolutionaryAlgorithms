/* 
 * File:   main.cpp
 * Author: Garth
 *
 * Created on September 11, 2014, 12:43 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream> // file stream
#include <sstream>
#include <algorithm> //random shuffle
#include <iterator>
#include <vector> 
#include <cmath> // for sqrt


using namespace std;

void readFile();
void shufflePoints();
void outputPoints();
float lengthOfPath();
float dBwPts(int first, int second);
int a_S; //array size

struct point {
    float x;
    float y;
} points [55], temp;


int main(int argc, char** argv) {
    readFile();
    srand (time(0));
    
    float minLength = lengthOfPath();
    cout << "length of path: "<<minLength << " evaluations 0" << endl;
    int k = 0;
    int evaluations = 1;
    while (k < 50) //50 run throughs since last change - changed this to 65 for
        //graphs
    {
        shufflePoints();
        float newLength = lengthOfPath();
        //change this for longest path
        //if (newLength> minLength)
         if (newLength < minLength)
          {
          minLength = newLength;
          k=0;
          }
          else
          k++;
          
          
          cout << "length of path: "<<minLength << " evaluations " << evaluations << endl;
          evaluations++;
         
    }
    outputPoints();
    return 0;
}

void readFile()
{
    char filepath[80];
    cout << "\nWhich file would you like to open?";
    cin >> filepath;
    ifstream myfile (filepath);
    
    
    if (myfile.is_open())
    {
        int i=0;
        while(!myfile.eof())
        {
            
            myfile >> points[i].x;
            myfile >> points[i].y;
            //cout << points[i].x << " " << points[i].y << endl;
            
            i++;
            a_S=i;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    
    //cout<< "\n"<<a_S<<endl;
}

void shufflePoints()
{
    //random_shuffle(&points[0], &points[a_S]);
    
    int i = rand()%a_S;
    int j = rand()%a_S;
    //cout << i <<" "<< j << endl;
    temp = points[i];
    points[i] = points[j];
    points[j] = temp;
    
}

void outputPoints()
{
    cout << "\nPoints are being output:\n";
    for(int i = 0; i<a_S; i++)
    {
        cout << points[i].x << " " << points[i].y << endl;
    }
}

float lengthOfPath()
{
    float pLength = 0;
    for (int i = 0; i < a_S-1; i++)
    {
       pLength += dBwPts(i, i+1);
       
        
    }
    return pLength;
}

float dBwPts(int first, int second)
{
    float term1 = points[second].x - points[first].x;
    float term1sq= pow(term1, 2);
    float term2 = points[second].y - points[first].y;
    float term2sq = pow(term2, 2);
    float sqTerms = sqrt(term1sq+term2sq);
    float d = sqTerms;
    
    return d;
    
}

