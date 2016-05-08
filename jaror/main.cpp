#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h> // atoi

using namespace std;

struct Data{
    int hour;
    int minute;
    int second;
    string plate;
};
Data * dataArray = new Data[1000];
int lineNum=0;

void t2(){
    int wHours = dataArray[lineNum-1].hour - dataArray[0].hour +1;
    cout<<wHours<<" orat dolgoztak."<<endl;
}
void t3(){
    // Init
    int prevHour=dataArray[0].hour;
    cout<<prevHour<<" ora: "<<dataArray[0].plate<<endl;
    for(int i=0; i<lineNum; i++){
        if(dataArray[i].hour != prevHour){
            cout<<dataArray[i].hour<<" ora: "<<dataArray[i].plate<<endl;
            prevHour=dataArray[i].hour;
        }
    }
}
void t4(){
    int sumB=0; int sumK=0; int sumM=0;
    for(int i=0;i<lineNum;i++){
        if(dataArray[i].plate[0]=='B'){
            sumB++;
        }else if(dataArray[i].plate[0]=='K'){
            sumK++;
        }else if(dataArray[i].plate[0]=='M'){
            sumM++;
        }
    }
    int sumS = lineNum-(sumB+sumK+sumM);
    cout<<"Autobusz: "<<sumB<<", kamion: "<<sumK<<", motor: "<<sumM<<", szemelygepkocsi: "<<sumS<<endl;
}
void t5(){
    struct Data{
        int hour;
        int minute;
        int second;
        int from;
        int until;
    } maxRange;

    // Init
    maxRange.from = 0;
    maxRange.until = 1;
    maxRange.hour = dataArray[maxRange.until].hour - dataArray[maxRange.from].hour;
    maxRange.minute = dataArray[maxRange.until].minute - dataArray[maxRange.from].minute;
    maxRange.second = dataArray[maxRange.until].second - dataArray[maxRange.from].second;


    for(int i=0;i<lineNum;i++){
        int tempH = dataArray[i+1].hour-dataArray[i].hour;
        int tempM = dataArray[i+1].minute-dataArray[i].minute;
        int tempS = dataArray[i+1].second-dataArray[i].second;
        if(tempS>maxRange.second){
            if(tempM>maxRange.minute){
                if(tempH>maxRange.hour){
                        maxRange.hour = dataArray[i+1].hour-dataArray[i].hour;
                        maxRange.minute = dataArray[i+1].minute-dataArray[i].minute;
                        maxRange.second = dataArray[i+1].second-dataArray[i].second;
                        maxRange.from = i;
                        maxRange.until = i+1;
                }else{
                    maxRange.hour = dataArray[i+1].hour-dataArray[i].hour;
                    maxRange.minute = dataArray[i+1].minute-dataArray[i].minute;
                    maxRange.second = dataArray[i+1].second-dataArray[i].second;
                    maxRange.from = i;
                    maxRange.until = i+1;
                }
            }
        }
    }
    cout<<dataArray[maxRange.from].hour<<":"<<dataArray[maxRange.from].minute<<":"<<dataArray[maxRange.from].second<<" - "<<dataArray[maxRange.until].hour<<":"<<dataArray[maxRange.until].minute<<":"<<dataArray[maxRange.until].second<<endl;
}
void t6(){
    string userInput="";
    cout<<"Adja meg a rendszamot: ";
    cin>>userInput;

    // Should convert userInput to uppercase

    string result[lineNum];
    int index=0;
    for(int i=0;i<lineNum;i++){
        for(int c=0;c<7;c++){
            if(dataArray[i].plate[c]==userInput[c] || userInput[c]=='*'){
                //cout<<endl<<dataArray[i].plate[c]<<" "<<userInput[c];
                //cout<<" : "<<result<<endl;
            }else{ break; }
            if(c==6){
                result[index]=dataArray[i].plate;
                index++;
            }
        }
    }

    if(index==0){
        cout<<"404 - Nincs talalat."<<endl;
    }else{
        for(int i=0;i<index;i++){
            cout<<result[i]<<endl;
        }
    }
}
void t7(){
    ofstream fileOutput("vizsgalt.txt");
    // Init
    int prevChecked=dataArray[0].hour*10000+dataArray[0].minute*100+dataArray[0].second;

    fileOutput<<"0"<<dataArray[0].hour<<" ";fileOutput<<dataArray[0].minute<<" ";fileOutput<<dataArray[0].second<<" ";fileOutput<<dataArray[0].plate<<"\n";

    for(int i=0;i<lineNum;i++){
        int tempAdded=dataArray[i].hour*10000+dataArray[i].minute*100+dataArray[i].second;
        int temp=tempAdded-prevChecked;
       // cout<<temp<<endl;

        //
        // Ora valtasnal nem mukodik az osszehasonlitas
        if(temp>=500){ // 500 == 5min
            if(dataArray[i].hour<10){
                fileOutput<<"0"<<dataArray[i].hour<<" ";
            }else{
                fileOutput<<dataArray[i].hour<<" ";
            }
            if(dataArray[i].minute<10){
                fileOutput<<"0"<<dataArray[i].minute<<" ";
            }else{
                fileOutput<<dataArray[i].minute<<" ";
            }
            if(dataArray[i].second<10){
                fileOutput<<"0"<<dataArray[i].second<<" ";
            }else{
                fileOutput<<dataArray[i].second<<" ";
            }
            fileOutput<<dataArray[i].plate<<"\n";

            prevChecked=dataArray[i].hour*10000+dataArray[i].minute*100+dataArray[i].second;
        }
    }
}

int main(){
    ifstream fileCounter("jarmu.txt");
    ifstream fileInput("jarmu.txt");
    int index=0;
    if(fileInput.is_open() && fileCounter.is_open()){
        string line="";
        while(getline(fileCounter,line)){
            lineNum++;
        }
        fileCounter.close();

        while(index<lineNum){
            fileInput>>dataArray[index].hour;
            fileInput>>dataArray[index].minute;
            fileInput>>dataArray[index].second;
            fileInput>>dataArray[index].plate;
            index++;
        }
        fileInput.close();
    }else{ cout<<"Unable to open file."<<endl; }

    cout<<"1. Feladat"<<endl;
    cout<<"Fajl beolvasva."<<endl;
    cout<<endl;
    cout<<"2. Feladat"<<endl;
    t2();
    cout<<endl;
    cout<<"3. Feladat"<<endl;
    t3();
    cout<<endl;
    cout<<"4. Feladat"<<endl;
    t4();
    cout<<endl;
    cout<<"5. Feladat"<<endl;
    t5();
    cout<<endl;
    cout<<"6. Feladat"<<endl;
    t6();
    cout<<endl;
    cout<<"7. Feladat"<<endl;
    t7();
    cout<<"Fajl elmentve."<<endl;
    cout<<endl;
    return 0;
}
