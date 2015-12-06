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
void iniTen();
void dupeTen();
void finalTen();
void oneChange();
void calculate20Lengths();
void output20Lengths();
void sortByLength();
void selectSort( float arrg[], int n);
void sort20lengths();
void select10Paths(float arr[]);

float lArray[20];

int a_S; //array size

struct point {
    float x;
    float y;
    float clength;
    bool FULL;
} points [55], points2[55], points3[55], points4[55], points5[55], 
        points6 [55], points7[55], points8[55], points9[55], points10[55], 
        points11 [55], points12[55], points13[55], points14[55], points15[55],
        points16[55], points17[55], points18[55],
        points19[55],points20[55], temp, temp1[55], temp2[55], temp3[55],
        temp4[55],temp5[55], temp6[55],temp7[55],temp8[55],temp9[55],temp10[55];

void outputPoints(point pointargs[]);
void shufflePoints(point pointargs[]);
void shufflePoints2(point pointsargs[]);
float lengthOfPath(point pointargs[]);
float dBwPts(int first, int second, point pointsargs[]);
void store(point pointsargs[]);
void store2(point pointsargs[], point pointsargs2[]);

int main(int argc, char** argv) {
    readFile();
    srand (time(0));
    iniTen();
    for (int i=1; i<11; i++)
    {
        dupeTen();
        oneChange();
        calculate20Lengths();
        sort20lengths();
        //select10Paths();
        finalTen();
        cout << "\nEvaluations: "<< i*10<<endl;
    }
    cout<<"Points for the best path l="<<points[a_S-1].clength<<":"<< endl;
    for(int i =0; i<a_S; i++)
    {
        cout<< points[i].x <<" "<<points[i].y<<endl;
    }
    return 0;
}
//readFile asks which file you want to use
//it then initializes the points array to have the points in the file passed

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
            i++;
            a_S=i;
            
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    
}
/*
 shufflePoints shuffles all points in the passed points array
 */
void shufflePoints(point pointargs[])
{
    random_shuffle(&pointargs[0], &pointargs[a_S]);
}
//shufflePoints2 is from rmhc and swaps 2 points in an array
void shufflePoints2(point pointsargs[])
{
   
    int i = rand() % a_S;
    int j = rand() % a_S;
    
    temp = pointsargs[i];
    pointsargs[i] = pointsargs[j];
    pointsargs[j] = temp;
    
}
/*
 iniTen initializes 10 arrays with randomized point indices
 * This is useful to start the beam search
 */
void iniTen()
{
    for (int i=0; i<a_S; i++)
    {
        points2[i]=points[i];
        points3[i]=points[i];
        points4[i]=points[i];
        points5[i]=points[i];
        points6[i]=points[i];
        points7[i]=points[i];
        points8[i]=points[i];
        points9[i]=points[i];
        points10[i]=points[i];
    }
    shufflePoints(points);
    shufflePoints(points2);
    shufflePoints(points3);
    shufflePoints(points4);
    shufflePoints(points5);
    shufflePoints(points6);
    shufflePoints(points7);
    shufflePoints(points8);
    shufflePoints(points9);
    shufflePoints(points10);
    /*
    outputPoints(points);
    outputPoints(points2);
     */
}

void dupeTen()
{
    for (int i = 0; i< a_S; i++)
    {
        points11[i]=points[i];
        points12[i]=points2[i];
        points13[i]=points3[i];
        points14[i]=points4[i];
        points15[i]=points5[i];
        points16[i]=points6[i];
        points17[i]=points7[i];
        points18[i]=points8[i];
        points19[i]=points9[i]; 
        points20[i]=points10[i]; 
    }
    
}
//makes one change to the first 10 arrays by shuffling a point in their dupes
//20 total arrays after oneChange
void oneChange()
{
    shufflePoints2(points11);
    shufflePoints2(points12);
    shufflePoints2(points13);
    shufflePoints2(points14);
    shufflePoints2(points15);
    shufflePoints2(points16);
    shufflePoints2(points17);
    shufflePoints2(points18);
    shufflePoints2(points19);
    shufflePoints2(points20);
   
}
//outputPoints outputs the x and y values for a specified point struct
void outputPoints(point pointargs[])
{
    cout << "\nPoints are being output from: "<< pointargs<< "\n";
    for(int i = 0; i<a_S; i++)
    {
        cout << pointargs[i].x << " " << pointargs[i].y << endl;
    }
}

void calculate20Lengths()
{
    points[a_S-1].clength = lengthOfPath(points);
    points2[a_S-1].clength = lengthOfPath(points2);
    points3[a_S-1].clength = lengthOfPath(points3);
    points4[a_S-1].clength = lengthOfPath(points4);
    points5[a_S-1].clength = lengthOfPath(points5);
    points6[a_S-1].clength = lengthOfPath(points6);
    points7[a_S-1].clength = lengthOfPath(points7);
    points8[a_S-1].clength = lengthOfPath(points8);
    points9[a_S-1].clength = lengthOfPath(points9);
    points10[a_S-1].clength = lengthOfPath(points10);
    points11[a_S-1].clength = lengthOfPath(points11);
    points12[a_S-1].clength = lengthOfPath(points12);
    points13[a_S-1].clength = lengthOfPath(points13);
    points14[a_S-1].clength = lengthOfPath(points14);
    points15[a_S-1].clength = lengthOfPath(points15);
    points16[a_S-1].clength = lengthOfPath(points16);
    points17[a_S-1].clength = lengthOfPath(points17);
    points18[a_S-1].clength = lengthOfPath(points18);
    points19[a_S-1].clength = lengthOfPath(points19);
    points20[a_S-1].clength = lengthOfPath(points20);
    //output20Lengths();
}
//outputs the 20 lengths
void output20Lengths()
{
     cout << "length: " << points[a_S-1].clength << endl;
    cout << "length: " << points2[a_S-1].clength << endl; 
    cout << "length: " << points3[a_S-1].clength << endl; 
    cout << "length: " << points4[a_S-1].clength << endl; 
    cout << "length: " << points5[a_S-1].clength << endl; 
    cout << "length: " << points6[a_S-1].clength << endl; 
    cout << "length: " << points7[a_S-1].clength << endl; 
    cout << "length: " << points8[a_S-1].clength << endl; 
    cout << "length: " << points9[a_S-1].clength << endl; 
    cout << "length: " << points10[a_S-1].clength << endl; 
    cout << "length: " << points11[a_S-1].clength << endl; 
    cout << "length: " << points12[a_S-1].clength << endl; 
    cout << "length: " << points13[a_S-1].clength << endl; 
    cout << "length: " << points14[a_S-1].clength << endl; 
    cout << "length: " << points15[a_S-1].clength << endl; 
    cout << "length: " << points16[a_S-1].clength << endl; 
    cout << "length: " << points17[a_S-1].clength << endl; 
    cout << "length: " << points18[a_S-1].clength << endl; 
    cout << "length: " << points19[a_S-1].clength << endl; 
    cout << "length: " << points20[a_S-1].clength << endl; 
}

//sort from smallest to largest the 20 lengths
void sort20lengths()
{
    float lArray [] = { points[a_S-1].clength, points2[a_S-1].clength, 
    points3[a_S-1].clength , points4[a_S-1].clength , points5[a_S-1].clength, 
    points6[a_S-1].clength, points7[a_S-1].clength, points8[a_S-1].clength, 
    points9[a_S-1].clength, points10[a_S-1].clength, points11[a_S-1].clength
    , points12[a_S-1].clength, points13[a_S-1].clength, points14[a_S-1].clength
    , points15[a_S-1].clength, points16[a_S-1].clength, points17[a_S-1].clength
    , points18[a_S-1].clength, points19[a_S-1].clength, points20[a_S-1].clength
    };
    
    selectSort(lArray, 20);
    /*
    for(int i =0; i<20; i++)
        cout << "\n length: " << lArray[i];
    */
    select10Paths(lArray);
}

//selectSort taken from http://cforbeginners.com/ssort.html
void selectSort(float arrg[], int n)
{
   int pos_min;
   float temp;
   for (int i = 0; i < n-1; i++)
   {
       pos_min = i;
       for (int j=i+1; j<n; j++)
       {
           if(arrg[j] <arrg[pos_min])
               pos_min=j;
       }
       
       if(pos_min != i)
       {
           temp = arrg[i];
           arrg[i] = arrg[pos_min];
           arrg[pos_min] = temp;
       }
   }
   /*
    for(int i =0; i<20; i++)
        cout << "\n ss length: " << arrg[i];
    */

}

//gotta select 10 paths from the 20 distances
//aka worst code i've ever written
void select10Paths(float arr[])
{
    /*
    cout<<"\nBeginning of select10Paths"<<endl;
    cout<<"first argument in array"<<arr[1]<<endl;
     */
    int j = 0;
    while(j<10)
    {
        //change this for longest path
        //for (int i=10; i<20;i++)
        for(int i=0; i<10; i++)
        {
            if(points[a_S-1].clength == arr[i])
            {
                store(points);
                j++;
            }
            if(points2[a_S-1].clength == arr[i])
            {
                store(points2);
                j++;
            }
            if(points3[a_S-1].clength == arr[i])
            {
                store(points3);
                j++;
            }
            if(points4[a_S-1].clength == arr[i])
            {
                store(points4);
                j++;
            }
            if(points5[a_S-1].clength == arr[i])
            {
                store(points5);
                j++;
            }
            if(points6[a_S-1].clength == arr[i])
            {
                store(points6);
                j++;
            }
            if(points7[a_S-1].clength == arr[i])
            {
                store(points7);
                j++;
            }
            if(points8[a_S-1].clength == arr[i])
            {
                store(points8);
                j++;
            }
            if(points9[a_S-1].clength == arr[i])
            {
                store(points9);
                j++;
            }
            if(points10[a_S-1].clength == arr[i])
            {
                store(points10);
                j++;
            }
            if(points11[a_S-1].clength == arr[i])
            {
                store(points11);
                j++;
            }
            if(points12[a_S-1].clength == arr[i])
            {
                store(points12);
                j++;
            }
            if(points13[a_S-1].clength == arr[i])
            {
                store(points13);
                j++;
            }
            if(points14[a_S-1].clength == arr[i])
            {
                store(points14);
                j++;
            }
            if(points15[a_S-1].clength == arr[i])
            {
                store(points15);
                j++;
            }
            if(points16[a_S-1].clength == arr[i])
            {
                store(points16);
                j++;
            }
            if(points17[a_S-1].clength == arr[i])
            {
                store(points17);
                j++;
            }
            if(points18[a_S-1].clength == arr[i])
            {
                store(points18);
                j++;
            }
            if(points19[a_S-1].clength == arr[i])
            {
                store(points19);
                j++;
            }
            if(points20[a_S-1].clength == arr[i])
            {
                store(points20);
                j++;
            }
        }
    }
}

//store stores the 10 arrays I want into temp arrays
//these will be stored into points[]-points10[] on the next iteration
void store(point p[])
{
    /*
    cout<<"\nBeginning of a store"<<endl;
    cout<<"length of p"<<p[a_S].clength<<endl;
     */
    if(!temp1[0].FULL)
        store2(p, temp1);
    else if(!temp2[0].FULL)
        store2(p,temp2);
    else if(!temp3[0].FULL)
        store2(p,temp3);
    else if(!temp4[0].FULL)
        store2(p,temp4);
    else if(!temp5[0].FULL)
        store2(p,temp5);
    else if(!temp6[0].FULL)
        store2(p,temp6);
    else if(!temp7[0].FULL)
        store2(p,temp7);
    else if(!temp8[0].FULL)
        store2(p,temp8);
    else if(!temp9[0].FULL)
        store2(p,temp9);
    else if(!temp10[0].FULL)
        store2(p,temp10);
    //else
        //cout << "\n10 values already selected" << endl;
    
    //cout <<"\nEnd of a store" << endl;
        
}
//this actually stores it instead of just checking if its full
void store2(point p[], point t[])
{
    for (int i=0; i<a_S; i++)
    {
        t[i]=p[i];
    }
    t[0].FULL = true;
    /*
    cout <<"\nEnd of a store2" << endl;
    cout <<"length of t" << t[a_S].clength <<endl;
     */
}
//store the selected 10 arrays into points[]-points10[]
void finalTen()
{
    
    for (int i=0; i<a_S; i++)
    {
        points[i]=temp1[i];
        points2[i]=temp2[i];
        points3[i]=temp3[i];
        points4[i]=temp4[i];
        points5[i]=temp5[i];
        points6[i]=temp6[i];
        points7[i]=temp7[i];
        points8[i]=temp8[i];
        points9[i]=temp9[i];
        points10[i]=temp10[i];
    }
    
    temp1[0].FULL = false;
    temp2[0].FULL = false;
    temp3[0].FULL = false;
    temp4[0].FULL = false;
    temp5[0].FULL = false;
    temp6[0].FULL = false;
    temp7[0].FULL = false;
    temp8[0].FULL = false;
    temp9[0].FULL = false;
    temp10[0].FULL = false;
    cout<< "\n" <<points[a_S-1].clength<<endl<<points2[a_S-1].clength<<endl
    <<points3[a_S-1].clength<<endl<<points4[a_S-1].clength<<endl
            <<points5[a_S-1].clength<<endl
            <<points6[a_S-1].clength<<endl
            <<points7[a_S-1].clength<<endl
            <<points8[a_S-1].clength<<endl
            <<points9[a_S-1].clength<<endl
            <<points10[a_S-1].clength;
}
//lengthofPath finds the length of the shortest path of the given point struct
//it uses funct dBwPts and sums them to form a cohesive path based on min d

float lengthOfPath(point pointargs[])
{
    
    float pLength = 0;
    for (int i = 0; i < a_S-1; i++)
    {
       pLength += dBwPts(i, i+1, pointargs);
       
        
    }
    return pLength;
}

//dBwPts finds the distance between two points per the distance formula
float dBwPts(int first, int second, point pointargs[])
{
    float term1 = pointargs[second].x - pointargs[first].x;
    float term1sq= pow(term1, 2);
    float term2 = pointargs[second].y - pointargs[first].y;
    float term2sq = pow(term2, 2);
    float sqTerms = sqrt(term1sq+term2sq);
    float d = sqTerms;
    
    return d;
    
}

