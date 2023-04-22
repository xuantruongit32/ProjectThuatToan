// INFLUENCE MAXIMIZATION WITH LIMITED BUDGET
#include<bits/stdc++.h>
#include <functional>
#include <iostream>
#include <unordered_map>
using namespace std;
struct KOL {
    string name;
    int numberFollowers;
    vector<int> followerSet;
    double money;
    KOL(string name, int numberFollowers, vector<int> followerSet, double money):name(name), numberFollowers(numberFollowers), followerSet(followerSet), money(money){} // Constructor
    KOL(){}
};

struct Input{
    double providedMoney;
    vector<KOL> listKOL;
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
            double money = stod(token); //So tien thue KOL
            iss >> token;
            int numberFollowers = stoi(token);
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
            listKOL.push_back(newKOL);
        }
    }

};

struct Solution{
    Input *data;
    double tienConLai;
    unordered_map<int,int> nguoiTiepCan; //int dau tien la ten nguoi theo doi, int sau la dem so KOL ma nguoi do theo doi
    int tongSoNguoiTiepCan;
    vector<KOL> KOLChuaThue;
    vector<KOL> KOLDaThue;

    Solution& operator=(const Solution& other){
        if(this != &other){
            this->data = other.data;
            this->tienConLai = other.tienConLai;
            this->nguoiTiepCan = other.nguoiTiepCan;
            this->tongSoNguoiTiepCan = other.tongSoNguoiTiepCan;
            this->KOLChuaThue = other.KOLChuaThue;
            this->KOLDaThue = other.KOLDaThue;
        }
        return *this;
    }
    Solution(const Solution& other){
            data = other.data;
            tienConLai = other.tienConLai;
            nguoiTiepCan = other.nguoiTiepCan;
            tongSoNguoiTiepCan = other.tongSoNguoiTiepCan;
            KOLChuaThue = other.KOLChuaThue;
            KOLDaThue = other.KOLDaThue;
    }

    void tongSoTienDeThueHet(){
         double i=0;
        for (auto c: data->listKOL){
            i+=c.money;
        }
        cout<<"Tong so tien de thue het KOL: "<<i<<endl;
    }
    void tongSoFollower(){
        long int i=0;
        for(auto c: data->listKOL){
            i+=c.followerSet.size();
        }
        cout<<"Tong so Follower: "<<i<<endl;
        
    }
    KOL getFirstKOL(){
        KOL firstKOL;
        float maxScore = 999999;
        for(int i=0; i<data->listKOL.size(); i++){
            int kolScore = data->listKOL[i].numberFollowers/data->listKOL[i].money;
            if (kolScore>maxScore)
                firstKOL = data->listKOL[i];
        }
        return firstKOL;
    }

//    void beginSolution(){
//        for(auto c: KOLChuaThue){
//            if(tienConLai<=0)
//                break;
//            if(c.second.money>tienConLai)
//                continue;
//            tienConLai -=c.second.money;
//            for(auto n: c.second.followerSet){
//                nguoiTiepCan[n]++;
//            }
//            KOLDaThue.push_back(c.second);
//            auto range = KOLChuaThue.equal_range(c.first);
//            bool found = false;
//            for (multimap<int,KOL>::iterator it = range.first; it!= range.second && !found;){
//                if(it->second.name == c.second.name){
//                    KOLChuaThue.erase(next(it));
//                    found=true;
//                }
//                else {
//                    ++it;
//            }
//        }
//        }
//        tongSoNguoiTiepCan = nguoiTiepCan.size();
//    }

    int getScore(){
        return tongSoNguoiTiepCan; 
    }

    Solution(){}

    Solution(Input &data){
        tongSoNguoiTiepCan=0;
        this->data = &data;
        tienConLai = data.providedMoney;
        KOLChuaThue = data.listKOL;
//        beginSolution();
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
    Input io("database/output2.txt");
    Solution solution(io);
//    solution.getBestNeighbor().printSolution();
//    solution.printSolution();
    cout<<solution.getFirstKOL().name<<endl;
    solution.tongSoTienDeThueHet();
    solution.tongSoFollower();
    }

