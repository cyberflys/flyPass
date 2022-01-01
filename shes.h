#ifndef SHES_H
#define SHES_H
/*
*	**************************************************
*		fleon SHES Algorithm
*			Made for password manager
*				version 1.0
*				by Gavrilo Palalic
*		Date: Dec 22 21. , Dec 23 21. , Dec 24 21.
*	**************************************************
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <QDebug>

#include <stdlib.h>
#include <string.h>
#include <random>
#include <algorithm>
#include <string.h>
#include <cstring>

#include <sstream>

using namespace std;

class SHES{

    public:
        SHES();

        string convertback(string s){
            string converted;

            for(int i =0;i<s.length();i+=2){
                string part = s.substr(i,2);
                char ch = stoul(part,NULL,16);
                converted+=ch;
            }

            return converted;
        }
        string encrypt(string dat){
            //PLAN for encryption:
            //mixing all the random keys from vector on the certain position
            //reversing a string
            //adding random 3 values at the end
            fstream z("/passwords/key.key");
            string inp;
            string key1;
            while(z>>inp){
                key1+=inp;
            }

            string key = decrypt(key1);

            vector<char>hexes;

            stringstream ss;
            dat+=":";
            dat+=key;

            int i;
            for(i=0;i<dat.length();i++){
                ss<<hex<<(int)dat[i];
            }
            string omg = ss.str();


            vector<char>chunks;
            for(int i =0;i<omg.length();i++){
                chunks.push_back(omg[i]);
            }
            //Encryption starts here
            //reversing letters

            //LETTERS


            for(int i =1;i<chunks.size();i++){

                char temp = chunks[i];
                chunks[i] = chunks[i-1];
                chunks[i-1]= temp;



            }
            //finished reversing letters

            stringstream ssz;
            for(int i =0;i<chunks.size();i++){
                ssz<<chunks[i];
            }
            string chunked= ssz.str();
            //saved letters to string

            //chunk system
            vector<string>blocks;
            int spliz = 4;

            int j = chunked.length()/spliz;

            for(int i =0;i<j;i++){
                blocks.push_back(chunked.substr(i*spliz,spliz));
            }
            if(omg.length()% spliz !=0){
                blocks.push_back(chunked.substr(spliz*j));
            }

            //splitted all letters into chunks and then into string vector
            int nextel1 = blocks.size()-1;
            for(int i =0;i<blocks.size();i++){

                string temp = blocks[i];
                blocks[i] = blocks[nextel1];
                blocks[nextel1]= temp;

            }
            //jibberishing chunks


            stringstream ret;

            for(int i =0;i<chunks.size();i++){

                ret<<chunks[i];
            }
            string sen1 = ret.str();
            //decrypt here


            return sen1;


        }

        string decrypt(string data){

            //Plan for decryption
            //

            //breaking string into chunks 4 * 4
            vector<string>blocks;
            int spliz = 4;

            int j = data.length()/spliz;

            for(int i =0;i<j;i++){
                blocks.push_back(data.substr(i*spliz,spliz));
            }
            if(data.length()% spliz !=0){
                blocks.push_back(data.substr(spliz*j));
            }

            int nextel1 = blocks.size()-1;
            for(int i =0;i<blocks.size();i++){

                string temp = blocks[nextel1];
                blocks[nextel1] = blocks[i];
                blocks[i]= temp;

            }


            stringstream szy;
            for(int i=0;i<blocks.size();i++){
                szy<<blocks[i];
            }
            string ended= szy.str();
            vector<char>chunks;
            for(int i =0;i<ended.length();i++){
                chunks.push_back(ended[i]);
            }

            //LETTERS
            int nextel2 = chunks.size()-1;
            for(int i =1;i<chunks.size();i++){

                char temp = chunks[i];
                chunks[i] = chunks[i-1];
                chunks[i-1]= temp;

            }
            //printing it
            stringstream lolz;
            for(int i =0;i<chunks.size();i++){
                lolz<<chunks[i];
            }
            string om = lolz.str();



            string oz = convertback(om);
            qDebug()<<"DATA:"<<oz.c_str();
            return oz;
        }
        string encryptKey(string dat){
            //PLAN for encryption:
            //mixing all the random keys from vector on the certain position
            //reversing a string
            //adding random 3 values at the end

            vector<char>hexes;

            stringstream ss;

            int i;
            for(i=0;i<dat.length();i++){
                ss<<hex<<(int)dat[i];
            }
            string omg = ss.str();


            vector<char>chunks;
            for(int i =0;i<omg.length();i++){
                chunks.push_back(omg[i]);
            }
            //Encryption starts here
            //reversing letters

            //LETTERS


            for(int i =1;i<chunks.size();i++){

                char temp = chunks[i];
                chunks[i] = chunks[i-1];
                chunks[i-1]= temp;



            }
            //finished reversing letters

            stringstream ssz;
            for(int i =0;i<chunks.size();i++){
                ssz<<chunks[i];
            }
            string chunked= ssz.str();
            //saved letters to string

            //chunk system
            vector<string>blocks;
            int spliz = 4;

            int j = chunked.length()/spliz;

            for(int i =0;i<j;i++){
                blocks.push_back(chunked.substr(i*spliz,spliz));
            }
            if(omg.length()% spliz !=0){
                blocks.push_back(chunked.substr(spliz*j));
            }

            //splitted all letters into chunks and then into string vector
            int nextel1 = blocks.size()-1;
            for(int i =0;i<blocks.size();i++){

                string temp = blocks[i];
                blocks[i] = blocks[nextel1];
                blocks[nextel1]= temp;

            }
            //jibberishing chunks


            stringstream ret;

            for(int i =0;i<chunks.size();i++){

                ret<<chunks[i];
            }
            string sen1 = ret.str();
            //decrypt here


            return sen1;


        }



};


#endif // SHES_H
