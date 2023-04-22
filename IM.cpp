// INFLUENCE MAXIMIZATION WITH LIMITED BUDGET
#include <algorithm>
#include<bits/stdc++.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_map>
using namespace std;
struct KOL {
    string name;
    int numberFollowers;
    vector<int> followerSet;
    double money;
    KOL(string name, int numberFollowers, vector<int> followerSet, double money):name(name), numberFollowers(numberFollowers), followerSet(followerSet), money(money){} // Constructor
    KOL(){}
    KOL& operator=(const KOL& other){
        if(this != &other){
            this->name = other.name;
            this->numberFollowers = other.numberFollowers;
            this->followerSet = other.followerSet;
            this->money = other.money;
        }
        return *this;
    }
    bool operator==(const KOL& other){
        return (name == other.name && numberFollowers == other.numberFollowers && followerSet == other.followerSet && money == other.money);
    }
    bool operator<(const KOL& other){
        return numberFollowers/money < other.numberFollowers/other.money;
    }

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
    unordered_set<int> nguoiTiepCan; //int dau tien la ten nguoi theo doi, int sau la dem so KOL ma nguoi do theo doi
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
    void tongSoTienDeThueHet(){
         double i=0;
        for (auto c: data->listKOL){
            i+=c.money;
        }
        cout<<"Tong so tien de thue het KOL cua data: "<<i<<endl;
    }
    void tongSoFollower(){
        long int i=0;
        for(auto c: data->listKOL){
            i+=c.followerSet.size();
        }
        cout<<"Tong so Follower cua data: "<<i<<endl;
        
    }
    void thueKOL(KOL kol, int i){
        tienConLai -= kol.money;
        cout<<tienConLai<<endl;
        for(auto n: kol.followerSet){
            nguoiTiepCan.insert(n);
        }
        tongSoNguoiTiepCan = nguoiTiepCan.size();
        KOLChuaThue.erase(KOLChuaThue.begin()+i);
        KOLDaThue.push_back(kol);

    }
    void thueFirstKOL(){
        auto firstIT = max_element(KOLChuaThue.begin(), KOLChuaThue.end());
        KOL firstKOL = *firstIT;
        int index = distance(KOLChuaThue.begin(), firstIT);
        thueKOL(firstKOL,index);
    }
    float getScore(KOL kol){
        unordered_set<int> nguoiTiepCanTest = nguoiTiepCan;
        for(auto n: kol.followerSet){
            nguoiTiepCanTest.insert(n);
        }
        int tongSoNguoiTiepCanTest = nguoiTiepCanTest.size();
        float score = tongSoNguoiTiepCanTest/kol.money;
        return score;

    }

    void greedySolution(){
        thueFirstKOL();
        KOL nextKOL;
        while(!KOLChuaThue.empty()){
            float maxScore=-1;
            float maxIndex=-1;
            for(int i=0;i<KOLChuaThue.size();i++){
                if(tienConLai<KOLChuaThue[i].money)
                    // Neu tien khong du thue KOL nay, bo qua va tiep tuc voi KOL khac
                    continue;
                if(getScore(KOLChuaThue[i])>maxScore){
                    nextKOL = KOLChuaThue[i];
                    maxScore=getScore(KOLChuaThue[i]);
                    maxIndex=i;
                }
            }
            if(maxIndex == -1){
                break;
            }
            thueKOL(nextKOL,maxIndex);
        }

    }

    Solution(){}

    Solution(Input &data){
        tongSoNguoiTiepCan=0;
        this->data = &data;
        tienConLai = data.providedMoney;
        KOLChuaThue = data.listKOL;
        greedySolution();
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
//    solution.tongSoTienDeThueHet();
//    solution.tongSoFollower();
    }

