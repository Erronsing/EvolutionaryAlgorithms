/* 
 * File:   main.cpp
 * Author: Garth
 *
 * Created on September 27, 2014, 10:49 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <time.h>
#include <string.h>

using namespace std;

void readFile();
void copyXVals();
void outputPts();
void equationCreation();
void eqR(); //equationRandomization
void evalEquation(float f, int p);
void calcError(int p);
void equationSurgery();
void selectSort(float arrg[],int n);
void reorderArray(float arrg[]);
void initErrArray(float arrg[]);




struct pts {
    float x;
    float y;
    
}readPts[60];

struct eqhp {
    string sym;
    float val;
    string exp;
    float err;
};


pts calcPts[20][50];
int a_S;
int fxc = 10;
eqhp fx[20][11];
eqhp tmpfx[20][11];




int main(int argc, char** argv) {
    string blank;
    //make a float array of all the errors
    float errArr[20];
    int evaluations = 0;
    int lpn = 0; //this counts the loops without change to error
    float lastErr;
    srand (time(NULL)); //init random seed
    readFile();
    copyXVals();
    equationCreation();
   //evaluate the equations and errors for the given points
    for(int i = 0; i < a_S; i++){
        evalEquation(calcPts[0][i].x, i);
        calcError(i);
    }
  
    initErrArray(errArr);
    selectSort(errArr, 20);
    reorderArray(errArr);
    evaluations = 20;
    lastErr = fx[0][0].err;
    cout << "\n New best fit expression found!"<<endl;
    cout << fx[0][0].exp <<endl;
    cout << "Error: " << lastErr<<endl;
    cout << "Evaluations: 20"<<endl;
    
    while (lpn<50000)
    {
        equationSurgery();
        for(int i = 0; i < a_S; i++){
            evalEquation(calcPts[0][i].x, i);
            calcError(i);
        }
        initErrArray(errArr);
        selectSort(errArr, 20);
        reorderArray(errArr);
        evaluations+=20;
        if (lastErr == fx[0][0].err)
        {
            lpn++;
            //if(evaluations%100000==0)
                //cout<<"\nEvals: "<<evaluations<<endl;
        }
        else
        {
            lpn=0;
            lastErr = fx[0][0].err;
            cout << "\n New best fit expression found!"<<endl;
            cout << fx[0][0].exp <<endl;
            cout << "Error: " << lastErr<<endl;
            cout << "Evaluations: "<< evaluations<<endl;
        }
        
    }
    
    cout << "\n Final expression:"<<endl;
    cout << fx[0][0].exp << endl;
    cout << "Error: " << lastErr << endl;
    cout << "Evaluations: " << evaluations << endl;
    return 0;
}

void readFile()
{
    char filepath[80];
    cout << "\nWhich file would you like to open?";
    cin >> filepath;
    ifstream myfile(filepath);
    
    if(myfile.is_open())
    {
        int i=0;
        
         while(!myfile.eof())
        {
       
                 
            myfile >> readPts[i].x;
            myfile >> readPts[i].y;
            //cout<<"\n"<<readPts[i].x << " " << readPts[i].y << endl;
            i++;
            a_S=i;
           
             
            
        }
        //printf("\n%i\n", a_S);
        myfile.close();
        
    }
    else cout << "Unable to open file.";
    
}

void copyXVals()
{
    
    //calcPts = new pts [20][a_S];
    
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < a_S; i++) {

            calcPts[j][i].x = readPts[i].x;
        }
    }
}

void outputPts()
{
    /*
    for (int i =0; i<a_S; i++)
    {
        cout << "\nX: "<< readPts[i].x <<" Y: " << readPts[i].y << endl;
        cout << "\nCopied X: " << calcPts[i].x << endl;
    }
     */
    
}

void equationCreation()
{
    string blank;
    int opOrNum, watOp;
    //upon returning, added x here
    string ops[6] = {"+", "-", "/", "*", "cos", "sin"};
    
    for (int j = 0; j < 20; j++) {
        //initialize first value

        fx[j][0].val = 0;
        fx[j][0].sym = "y";

        for (int i = 1; i < fxc + 1; i++) {
            /*1 for op 2 for number*/
            opOrNum = rand() % 3 + 1;
            //cout << "opornum " << opOrNum<<endl;
            if (opOrNum == 1) {
                watOp = rand() % 6;
                //cout << "watOp" << watOp<<endl;
                fx[j][i].val = 0;
                fx[j][i].sym = ops[watOp];
                fx[j][i].exp = ops[watOp];
            } else if(opOrNum==2){
                fx[j][i].val=0;
                fx[j][i].sym="x";
                fx[j][i].exp="x";
            }
            else {
                float c =
                        -10 + static_cast<float> (rand()) /
                        (static_cast<float> (RAND_MAX / (20)));
                //cout << "c" << c << endl;
                //std::string s = std::to_string(42);
                ostringstream ostr;
                ostr << c;
                fx[j][i].val = c;
                fx[j][i].sym = ostr.str();
                fx[j][i].exp = ostr.str();
            }
        }
    }
   
}

//this randomizes the last equation
void eqR() {
    string blank;
    int opOrNum, watOp;
    //upon returning, added x here
    string ops[6] = {"+", "-", "/", "*", "cos", "sin"};


    //initialize first value

    fx[19][0].val = 0;
    fx[19][0].sym = "y";

    for (int i = 1; i < fxc + 1; i++) {
        /*1 for op 2 for number*/
        opOrNum = rand() % 3 + 1;
        //cout << "opornum " << opOrNum<<endl;
        if (opOrNum == 1) {
            watOp = rand() % 6;
            //cout << "watOp" << watOp<<endl;
            fx[19][i].val = 0;
            fx[19][i].sym = ops[watOp];
            fx[19][i].exp = ops[watOp];
        } else if (opOrNum == 2) {
            fx[19][i].val = 0;
            fx[19][i].sym = "x";
            fx[19][i].exp = "x";
        } else {
            float c =
                    -10 + static_cast<float> (rand()) /
                    (static_cast<float> (RAND_MAX / (20)));
            //cout << "c" << c << endl;
            //std::string s = std::to_string(42);
            ostringstream ostr;
            ostr << c;
            fx[19][i].val = c;
            fx[19][i].sym = ostr.str();
            fx[19][i].exp = ostr.str();
        }
    }
}
void evalEquation(float f, int p)
{
    //f is x value, p is position of x value among data points
    //changing this to evaluate 20 points at a time because of whatever
    for(int h=0; h<20; h++)
    {
        float n, m;

        int z = fxc;


        while (z != 0) {
            int k = z;
            
            //if no children
            if ((2 * k + 1) > fxc && (2 * k) > fxc) {
                if (fx[h][k].sym == "x") {
                    n = f;
                    fx[h][k].val = n;
                    fx[h][k].exp = "x";
                } else if (fx[h][k].sym == "+" || fx[h][k].sym == "-" ||
                        fx[h][k].sym == "*" || fx[h][k].sym == "/" ||
                        fx[h][k].sym == "sin" || fx[h][k].sym == "cos") {
                    n = 1;
                    fx[h][k].val = n;
                    fx[h][k].sym="1";
                    fx[h][k].exp="1";
                    //fx[k].sym=1;
                } else {
                    n = atof((fx[h][k].sym).c_str());
                    fx[h][k].val = n;
                }
            }                //if only one child
            else if ((2 * k + 1) > fxc && (2 * k) <= fxc) {
                if (fx[h][k].sym == "x") {
                    n = f;
                    fx[h][k].val = n;
                    fx[h][k].exp = "x";
                } else if (fx[h][k].sym == "sin") {
                    fx[h][k].val = sin(fx[h][2 * k].val);
                    fx[h][k].exp = "sin(" + fx[h][2 * k].exp + ")";

                } else if (fx[h][k].sym == "cos") {
                    fx[h][k].val = cos(fx[h][2 * k].val);
                    fx[h][k].exp = "cos(" + fx[h][2 * k].exp + ")";
                } else if (fx[h][k].sym == "-") {
                    fx[h][k].val = -(fx[h][2 * k].val);
                    fx[h][k].exp ="-"+fx[h][2*k].exp;
                } else if (fx[h][k].sym == "+") {
                    fx[h][k].val = fx[h][2 * k].val;
                    fx[h][k].exp=fx[h][2*k].exp;
                } else {
                    fx[h][k].val = fx[h][2 * k].val;
                }

            }                //both children
            else {
                if (fx[h][k].sym == "x") {
                    n = f;
                    fx[h][k].val = fx[h][2 * k].val * n * fx[h][2 * k + 1].val;
                    fx[h][k].exp = fx[h][2 * k].sym + "*x*" + fx[h][2 * k + 1].sym;
                } else if (fx[h][k].sym == "sin") {
                    fx[h][k].val = sin(fx[h][2 * k].val);
                    fx[h][k].exp = "sin(" + fx[h][2 * k].exp + ")";
                } else if (fx[h][k].sym == "cos") {
                    fx[h][k].val = cos(fx[h][2 * k].val);
                    fx[h][k].exp = "cos(" + fx[h][2 * k].exp + ")";
                } else if (fx[h][k].sym == "+") {
                    //cout << "\n + eval" << fx[2*k].val << fx[2*k+1].val;
                    fx[h][k].val = fx[h][2 * k].val + fx[h][2 * k + 1].val;
                    fx[h][k].exp = "(" + fx[h][2 * k].exp + "+" + fx[h][2 * k + 1].exp + ")";
                } else if (fx[h][k].sym == "-") {
                    fx[h][k].val = fx[h][2 * k].val - fx[h][2 * k + 1].val;
                    fx[h][k].exp = "(" + fx[h][2 * k].exp+ "-" + fx[h][2 * k + 1].exp + ")";
                } else if (fx[h][k].sym == "*") {
                    fx[h][k].val = fx[h][2 * k].val * fx[h][2 * k + 1].val;
                    fx[h][k].exp = "(" + fx[h][2 * k].exp + "*" + fx[h][2 * k + 1].exp + ")";
                } else if (fx[h][k].sym == "/") {
                    fx[h][k].val = fx[h][2 * k].val / fx[h][2 * k + 1].val;
                    fx[h][k].exp = "(" + fx[h][2 * k].exp + "/" + fx[h][2 * k + 1].exp + ")";
                }

            }


            //cout << "\n k: " << k << " val: " << fx[k].val << " sym: " <<
            //fx[k].sym << " exp: " << fx[k].exp<< " z: " << z << endl;
            z--;
        }
        fx[h][0].val = fx[h][1].val;
        fx[h][0].exp = fx[h][1].exp;
        //need to look at calcpts
        calcPts[h][p].y = fx[h][0].val;
        //cout << "\n final equation: " << fx[0].exp<<endl;
        //cout << "final value: " << fx[h][0].val << endl;
    }
}

void calcError(int p)
{
    for(int j=0; j<20; j++) {
        float relativeError;
        float intermed = calcPts[j][p].y - readPts[p].y;
        relativeError = abs((abs(intermed)) / readPts[p].y);
        fx[j][0].err += relativeError;
    }
    
}

//selectSort taken from http://cforbeginners.com/ssort.html
void selectSort(float arrg[], int n)
{
    int pos_min;
    float temp;
    for (int i=0; i< n-1; i++)
    {
        pos_min=i;
        for(int j=i+1; j<n; j++)
        {
            if(arrg[j] <arrg[pos_min])
                pos_min=j;
        }
        
        if(pos_min!=i)
        {
            temp = arrg[i];
            arrg[i] = arrg[pos_min];
            arrg[pos_min]=temp;
        }
    }
}

//this copies the first 10 equation's upper half and splices it with
//second 10 equations' lower half to create the last 10 new equations
//that idea didn't work
//take left half of better tree and make it the left half of the worse tree
//randomize last equation
void equationSurgery()
{
    for (int i = 10; i<20; i++)
    {
         
            fx[i][2]=fx[i-10][2];
            fx[i][4]=fx[i-10][4];
            fx[i][5]=fx[i-10][5];
            fx[i][10]=fx[i-10][10];
            
        
    }
    eqR();
    //reset errors
    for (int i=0; i<20; i++)
    {
        fx[i][0].err=0;
    }
        
}

//i had this in main originally but this makes it easier to loop
void reorderArray(float arrg[])
{
     //make a temp version of the fx array that is in order of smallest to
    //largest error
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<20; j++)
        {
            if (fx[i][0].err == arrg[j] )
            {
                for (int k=0;k<11;k++)
                {
                    tmpfx[j][k]=fx[i][k];
                }
            }
                
        }
    }
   
    //make the real array the temp array
    for (int i=0; i<20; i++){
        for (int j=0; j<11; j++){
            fx[i][j]=tmpfx[i][j];
        }
    }
}

//initializes error array
void initErrArray(float arrg[])
{
      for (int i=0; i<20; i++)
    {
        arrg[i]=fx[i][0].err;
       
    }
}


