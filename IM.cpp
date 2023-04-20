// INFLUENCE MAXIMIZATION WITH LIMITED BUDGET
#include<bits/stdc++.h>
#include <functional>
#include <iostream>
using namespace std;
struct KOL {
    string name;
    int numberFollowers;
    vector<int> followerSet;
    float money;
    KOL(string name, int numberFollowers, vector<int> followerSet, float money):name(name), numberFollowers(numberFollowers), followerSet(followerSet), money(money){} // Constructor
    KOL(){}
    bool operator==(const KOL &kol) const {
        return (name == kol.name && numberFollowers ==kol.numberFollowers && followerSet == kol.followerSet && money == kol.money);
    }
};

struct Input{
    float providedMoney;
    multimap<int,KOL,greater<int>> listKOL;
    string path;
    Input(string path): path(path){
        readFile();
    };
    void readFile(){
        ifstream ifile(path); //Read file data
        string line;
        getline(ifile,line); //Lay dong dau tien
        istringstream iss(line);
        string token;
        iss >> token;
        iss >> token;
        iss >> token;
        providedMoney = stof(token); //Vi providedMoney la tu thu 3 nen getline 3 lan, va phai doi tu string -> float
        getline(ifile,line); //Bo dong thu 2
        while(getline(ifile,line)){
            istringstream iss(line);
            string name;
            iss >> token;
            name = token;
            iss >> token;
            float money = stof(token); //So tien thue KOL
            iss >> token;
            float numberFollowers = stof(token);
            iss >> token;
            string newToken = token.substr(1, token.length()-2); //Bo dau {} o dau va cuoi
            istringstream iss1(newToken);
            string token2;
            vector<int> followerSet;
            // Cho tat ca cac follwer vao vector<int> followerSet
            while(getline(iss1,token2, ',')){
               followerSet.push_back(stoi(token2)); 
            }
            KOL newKOL(name, numberFollowers, followerSet, money);
            listKOL.insert({numberFollowers,newKOL});
        }
    }

};

struct Solution{
    Input *data;
    float tienConLai;
    set<int> nguoiTiepCan;
    int tongSoNguoiTiepCan;
    multimap<int,KOL,greater<int>> KOLChuaThue;
    vector<KOL> KOLDaThue;

    void beginSolution(){
        for(auto c: data->listKOL){
            if(tienConLai<=0)
                break;
            if(c.second.money>tienConLai)
                continue;
            tienConLai -=c.second.money;
            for(auto n: c.second.followerSet){
                nguoiTiepCan.insert(n);
            }
            KOLDaThue.push_back(c.second);
        }
        tongSoNguoiTiepCan = nguoiTiepCan.size();
    }

    Solution(Input &data){
        tongSoNguoiTiepCan=0;
        this->data = &data;
        tienConLai = data.providedMoney;
        KOLChuaThue = data.listKOL;
        beginSolution();
    }

    void printSolution(){
        cout<<"Tong tien thue: "<<data->providedMoney-tienConLai<<endl;
        cout<<"So nguoi tiep can: "<<tongSoNguoiTiepCan<<endl;
        cout<<"KOL: "<<endl;
        for(auto c: KOLDaThue){
            cout<<c.name<<endl;
        }

    }


};

int main (){
    Input io("database/output1.txt");
    Solution solution(io);
    solution.printSolution();
    }

