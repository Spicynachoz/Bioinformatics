/*Analysis & RNA Protein Translation Program
Created by David Ye on 5/3/13
Title : Hwk1 Programming Project 3
Description : Read the contents of a file or string, and analyze the data
Purpose : This program allows you to find the gc content, CpG islands, Number of Poly T sequences and complement DNA
from a DNA strand. It also allows you to transcribe an RNA into a protein.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;
string ComplementDna (string& dnastringP);
double gc (string dnastringP);
void CpG(string dnastringP, ofstream& myfile);
int PolyT (string dnastringP);
void RNAprotein(string rnastring,map<string,string>& M, bool& rnacheck, bool& start);

int main()
{
    // initializing strings for manipulation and file i/o
    string rnastring, substring, dnastring, infilename, outfilename;
    bool rnacheck = true;
    bool start = false;
    // initializing map for RNA codons
   map<string, string> M;
    M["UAA"]="STOP";  M["UAG"]="STOP";  M["UGA"]="STOP"; M["UGC"]="C";
    M["UUU"]="F"; M["UUC"]="F"; M["UUA"]="L"; M["UUG"]="L"; M["GAA"]="E"; M["GAG"]="E";
    M["UCU"]="S"; M["UCC"]="S"; M["UCA"]="S"; M["UCG"]="S"; M["AGU"]="S"; M["AGC"]="S";
    M["UAU"]="Y"; M["UGG"]="W"; M["CUU"]="L"; M["CUA"]="L"; M["CUG"]="L"; M["CGU"]="P";
    M["CCC"]="P"; M["CCA"]="P"; M["CCG"]="P"; M["CAU"]="H"; M["CAC"]="H"; M["CAA"]="Q";
    M["CGU"]="R"; M["CGC"]="R"; M["CGA"]="R"; M["CGG"]="R"; M["AGA"]="R"; M["AGG"]="R";
    M["GGU"]="G"; M["GGC"]="G"; M["GGG"]="G"; M["GGA"]="G"; M["GAU"]="D"; M["GAC"]="D";
    M["GUU"]="V"; M["GUG"]="V"; M["GUC"]="V"; M["GUA"]= "V";M["ACU"]="T"; M["ACA"]="T";
    M["GCU"]="A"; M["GCG"]="A"; M["GCA"]="A"; M["GCC"]="A"; M["ACC"]="T"; M["ACG"]="T";
    M["AUU"]="I"; M["AUC"]="I"; M["AUA"]="M"; M["AUG"]="M"; M["UAC"]="Y"; M["CUC"]= "L";
    M["AAU"]="N"; M["AAC"]="N"; M["AAA"]="K"; M["AAG"]="K"; M["CAG"]="Q"; M["UGU"]="C";
    // Printing out menu for user
    cout << "Welcome to the Bioinformatics Program..... " << endl;
    cout << " Please select an option from the menu"<< endl;
    cout << " 1. DNA Sequence Analysis" << endl << " 2. Protein Sequence Prediction" << endl;
    int selection;
    cin >> selection;
    // allows user to enter a selection from the menu
    if ( selection == 1)
    {
        cout << " Please enter a file name to open" << endl;
        cin >> infilename;
        ifstream dnafile;
        dnafile.open (infilename.c_str(),ios::in | ios::binary);
        if(!dnafile)
        //Test file open
    {
                cout<<"Error opening output file"<<endl;

    }

            int filecount = 1;
            stringstream convert;
            string outfilename;

        while (!dnafile.eof())
        {
            // converting integer to string for ofstream usage since ofstream only opens strings
              convert << filecount;
            outfilename=convert.str();
            ofstream myfile(outfilename.c_str());

            getline(dnafile,dnastring); // get single line from file and do functions.everything repeats until end of file.
            myfile<< "gc content = " <<  gc(dnastring) << endl;
            CpG(dnastring, myfile);
           myfile<< "Number of Poly T Sequences = " << PolyT(dnastring)<< endl;;
           myfile<< ComplementDna (dnastring)<< endl;
            convert.str("");
            filecount++;
        }



        }

    if ( selection == 2)
    {
        cout << " please enter an RNA string " << endl;
        cin >> rnastring;
        RNAprotein(rnastring,M,rnacheck,start);
    }


 return 0;
   }

// functions for DNA strings and RNA strings

double gc (string dnastringP)
{
    double stringLength=0, cgContent=0, gcRatio;
    // determine if a letter is equal to c or g

    while (stringLength < dnastringP.length())
    {
        if (dnastringP[stringLength] == 'c' || dnastringP[stringLength] == 'g')
        {
            cgContent++;
        }
        stringLength++;
    }

    gcRatio = (cgContent/stringLength);
    return gcRatio;
}
void CpG (string dnastringP,ofstream& myfile )
{
    //check if current letter is c and next letter is g. if this is true,print out the index of c.
    for ( int i = 0; i < dnastringP.length(); i++)
    {
        if( dnastringP[i]== 'c' && dnastringP[i+1]== 'g')
        {
            myfile << "CpG Island located at position " << i << endl;
        }
    }

}

int PolyT(string dnastringP)
{
    int NumberOfTs = 0;
    int SequenceT = 0;
   for ( int i = 0; i < dnastringP.length(); i++)
   {
       if (dnastringP[i]=='t')
       {
               NumberOfTs++;    // reads through dnastring and counts the number of T's
       }
        if (dnastringP[i]!='t' && NumberOfTs>=4)
            {
                SequenceT++;     // when both conditions are met, Sequence increases.
            }
        if ( dnastringP[i]!= 't')
            {
                 NumberOfTs=0;     // If the current letter is no longer a t, reset t count

            }
       }
       return SequenceT;
}
string ComplementDna (string& dnastringP)
{
    // read through the dnastring and convert each letter (a,c,g,t) to its complement
    for (int i =0 ; i < dnastringP.length(); i++)
    {
        if (dnastringP[i] == 'a')
        {
            dnastringP[i] = 't';
        }
        else if (dnastringP[i] == 'c')
        {
            dnastringP[i] = 'g';
        }
        else if (dnastringP[i] == 'g')
        {
            dnastringP[i] = 'c';
        }
        else if (dnastringP[i] == 't')
        {
            dnastringP[i] = 'a';
        }

    }
    // reverse dnastring and return
     dnastringP == string( dnastringP.rbegin(), dnastringP.rend() );
                return dnastringP;

   cout << endl;
}

void RNAprotein(string rnastringP,map<string,string>& M, bool& rnacheck, bool& start )
{
        string substring;
        // check if rnastring is valid string : length is multiple of 3 and characters are acceptable
    if (rnastringP.length()%3 ==0)
    {
    for(int i = 0; i<rnastringP.length(); i++)
    {
        if (rnastringP[i]!='A'&&rnastringP[i]!='G'&&rnastringP[i]!='C'&&rnastringP[i]!='U')
        {
        cout <<"invalid string " ;
         rnacheck = false;
        }
    }
        // if string is valid, rnacheck becomes true
    if ( rnacheck== true)
        {
    for( int x=0; x <rnastringP.length(); x+=3)
            {
        substring = rnastringP.substr(x,3);
        /* if the substring is equal to "AUG", start becomes true.
        If substring is equal to stop codon, start = false.
        Print out the substring when start is true. */
            if ( substring == "AUG")
                {
                start= true;
                }
            if ((substring=="UAA")||(substring=="UAG")||(substring=="UGA"))
                {
                start=false;
                }
            if (start==true)
                {
                cout <<M[substring];
                }
            }
        }
    }
}
