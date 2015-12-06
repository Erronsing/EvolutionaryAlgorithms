/* 
 * File:   main.cpp
 * Author: Garth
 *
 * Created on December 4, 2014, 2:34 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

void parse(const char* filename); //parses file into items
void parse2(const char* filename);
void outputItemList(); //displays the items in the file
void inquiry(); //basically anything user input
void randomizeBuild(); //randomize a build to initialize array
void buildFitness(); //calculate the fitness of each item/build
void selectionSort(); //sort from largest fitness to smallest
void evolution(); //alter population in some way
void enhancedEvo(); //new method
void outputWeights(); //display weights
int itemcount;
int itemsneeded = 0;

//define constants
 //maximum values for an item slot
//min values are all 0 except cost
const double maxcost=3800;
const double leastcost=180;
const double maxhp=1000;
const double maxmana=500;
const double maxarmor=100;
const double maxMR=55;
const double maxAD=80;
const double maxAP=120;

//need weights for stats, these can be changed with input later
//should do that through a gui, for now
int hpWeight;
int manaWeight;
int armorWeight;
int mrWeight;
int adWeight;
int apWeight;
int goldWeight = -5;

struct item
{
    string name;
    int gold;
    int hp;
    int mana;
    int armor;
    int mr;
    int ad;
    int ap;
    bool unique;
    double fitness;
} items[50], build[40][6], buildTotal;
//20 builds, 6 items max each
//50 max items

int main(int argc, char** argv) {
    srand (time(NULL)); //init random seed
    int lpn=0; //loop number
    int evaluations=0; //evaluation count
    int buildCost=0; //build cost
    double bestFit=0.0; //used to keep track of when best fitness changes
    inquiry();
    parse("items.txt");
    parse2("priorities.txt");
    if(goldWeight==1)
        goldWeight = 
            -1*(hpWeight+manaWeight+armorWeight+mrWeight+adWeight+apWeight-4);
    else
        goldWeight = 0;
    outputWeights();
    randomizeBuild();
    buildFitness();
    selectionSort();
    evaluations=40;
    bestFit=build[0][0].fitness;
    cout <<"\n\nTop 5 builds found:"<<endl;
    for(int a=0; a<5;a++)
    {
        cout<<"\nBuild "<<a+1<<":";
        for(int b=0; b<itemsneeded;b++)
        {
            cout<<"\n"<<build[a][b].name;
        }
    }
    cout<<"\nEvaluations: "<<evaluations;
    cout<<"\nFitness: "<<build[0][0].fitness<<endl;
    while(lpn<50000)
    {
        enhancedEvo();
        buildFitness();
        selectionSort();
        evaluations = evaluations+40;
        if(bestFit!=build[0][0].fitness)
        {
            lpn=0;
            bestFit=build[0][0].fitness;
            if(evaluations>100)
            cout<<"\nFitness: "<<build[0][0].fitness<<" at evaluation: "
        <<evaluations<<endl;
            
        }
        else
        {
            lpn++;
        }
        if(evaluations<=100)
            cout<<"\nFitness: "<<build[0][0].fitness<<" at evaluation: "
        <<evaluations<<endl;
        if(evaluations==100000)
            cout<<"\nFitness: "<<build[0][0].fitness<<" at evaluation: "
        <<evaluations<<endl;
        if(evaluations%250000==0)
            cout<<"\nFitness: "<<build[0][0].fitness<<" at evaluation: "
        <<evaluations<<endl;
    }
    cout <<"\n\nFinal top 5 builds found:"<<endl;
    for(int a=0; a<5;a++)
    {
        buildTotal.gold=0;
        buildTotal.hp=0;
        cout<<"\nBuild "<<a+1<<":";
        for(int b=0; b<itemsneeded;b++)
        {
            cout<<"\n"<<build[a][b].name;
            buildTotal.gold+=build[a][b].gold;
            buildTotal.hp+=build[a][b].hp;
            if(b==(itemsneeded-1))
            {
                cout<<"\nBuild cost: "<<buildTotal.gold<<endl;
                cout<<"Build hp: "<<buildTotal.hp<<endl;
                
            }
        }
    }
    cout<<"\nEvaluations: "<<evaluations<<endl;
    
    return 0;
}

void parse(const char* filename)
{
    string line;
    ifstream myfile(filename);
    string data;
    int val;
    itemcount = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream linestream(line);
            getline(linestream, data, ','); //read up to the first comma
            items[itemcount].name = data;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].gold=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].hp=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].mana=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].armor=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].mr=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].ad=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            items[itemcount].ap=val;
            getline(linestream,data, ',');
            val = atoi(data.c_str());
            if(val=1)
                items[itemcount].unique = true;
            else
                items[itemcount].unique = false;
            itemcount++;
            
        }
        myfile.close();
    }
    
  
}

void parse2(const char* filename)
{
    string line;
    ifstream statFile(filename);
    string data;
    int val;
    if (statFile.is_open())
    {
        while (getline(statFile, line))
        {
            stringstream linestream(line);
            getline(linestream, data, ','); //read up to the first comma
            goldWeight = atoi(data.c_str());
            getline(linestream,data, ',');
            hpWeight = atoi(data.c_str());
            getline(linestream,data, ',');
            manaWeight = atoi(data.c_str());
            getline(linestream,data, ',');
            armorWeight = atoi(data.c_str());
            getline(linestream,data, ',');
            mrWeight = atoi(data.c_str());
            getline(linestream,data, ',');
            adWeight = atoi(data.c_str());
            getline(linestream,data, ',');
            apWeight = atoi(data.c_str());   
        }
    }
    statFile.close();
}

void outputItemList()
{
    cout << "\nPrinting Item List..."<<endl;
    cout << "Name\t\t\t|Cost\t|HP\t|Mana\t|Armor\t|Magic Resist\t|"<<
            "Attack Damage\t|Ability Power\t|Uniqueness"<<endl;
    
    for(int i=0; i<itemcount; i++)
    {
        cout<<items[i].name<<"\t\t|"<<items[i].gold<<"\t|"<<items[i].hp<<"\t|"
                <<items[i].mana<<"\t|"
                <<items[i].armor<<"\t|"<<items[i].mr<<"\t\t|"
                <<items[i].ad<<"\t\t|"
                <<items[i].ap<<"\t\t|"<<items[i].unique<<endl;
    }
     
        
}

void outputWeights()
{
    cout << "\nWeights\n";
    cout << goldWeight<<endl;
    cout << hpWeight<<endl;
    cout << manaWeight<<endl;
    cout << armorWeight<<endl;
    cout << mrWeight<<endl;
    cout << adWeight << endl;
    cout << apWeight << endl;
}

void inquiry()
{
    int input;
    while(itemsneeded<1 || itemsneeded>6)
    {
    cout <<"\nHow many items do you need?" <<endl;
    cin >> input;
    if (input>0 && input<7)
    {
        itemsneeded=input;
        cout << "\nYou need "<<itemsneeded<<" items.";
    }
    else
        cout<< "\nInvalid input!";
    }
}

void randomizeBuild()
{
    int j;
    for (int k=0; k<40; k++)
    {
        for (int i=0; i<itemsneeded; i++)
        {
            j= rand() %itemcount;
            build[k][i]=items[j];
        }
    }

}

//efficiency problem, make new buildfitness for only calcuating last 10 that
//changed? Is this better than just calculating memory+cpu wise?
void buildFitness()
{
   //feature scaling?
    double buildFitness;
    
    for (int k=0; k<40; k++)
    {
        buildFitness = 0.0;
        for (int i=0; i<itemsneeded; i++)
        {
            double itemvector = 
            (goldWeight*(build[k][i].gold-leastcost)/(maxcost-leastcost))+
            hpWeight*build[k][i].hp/maxhp 
            + manaWeight*build[k][i].mana/maxmana + 
            armorWeight*build[k][i].armor/maxarmor + 
            mrWeight*build[k][i].mr/maxMR 
            + adWeight*build[k][i].ad/maxAD
            + apWeight*build[k][i].ap/maxAP;
            buildFitness+=itemvector;
        }
        build[k][0].fitness = buildFitness;
    }

}
//http://www.learncpp.com/cpp-tutorial/64-sorting-an-array-using-selection-sort/
//most efficient sort for small datasets like this?
void selectionSort()
{

    int first;
    int wait;
    item temp[1][itemsneeded];
    int numLength = 40;
    for (int nStartIndex=0; nStartIndex<numLength; nStartIndex++)
    {
        //nLargestIndex is the index of the largest element encountered so far
        int nLargestIndex = nStartIndex;
        
        for(int nCurrentIndex = nStartIndex+1; nCurrentIndex<numLength; 
                nCurrentIndex++)
        {
            //if current element is larger than previously found largest
            if(build[nCurrentIndex][0].fitness>build[nLargestIndex][0].fitness)
                //store index in nLargestIndex
                nLargestIndex = nCurrentIndex;
        }
        //swap start element with largest element
        for(int k=0; k<itemsneeded;k++)
        {
            temp[0][k]=build[nStartIndex][k];
            build[nStartIndex][k]=build[nLargestIndex][k];
            build[nLargestIndex][k]=temp[0][k];
        }
    }

}

void evolution()
{
    //thinking I should take half the items from top 10 builds
    //put them in slots of index 10-19
    for(int i=0; i<10; i++)
    {
        for(int k=0; k<itemsneeded; k++)
        {
            if(k%2==0)
            {
                build[i+10][k]=build[i][k];
            }
        }
    }
    
    //randomize last 10 builds
    int j = 0;
    for(int i=30; i<40; i++)
    {
        for(int k=0; k<itemsneeded; k++)
        {
            j= rand() %itemcount;
            build[i][k]=items[j];
            
        }
    }
}

void enhancedEvo()
{
    //top 10 builds cross with next 10 builds 
    //place those crosses in next 10 builds
    //randomize last 10 builds
    //[0-9]x[10-19]->[20-29]    rnd([30-39])
    for(int i=0; i<10; i++)
    {
        for(int k=0; k<itemsneeded; k++)
        {
            if(k%2==0)
            {
                build[i+20][k]=build[i][k];
            }
            else
                build[i+20][k]=build[i+10][k];
                
        }
    }
    
    int j=0;
    for(int i=30; i<40; i++)
    {
        for(int k=0; k<itemsneeded; k++)
        {
            j= rand() %itemcount;
            build[i][k]=items[j];
            
        }
    }
}

