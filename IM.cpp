// INFLUENCE MAXIMIZATION WITH LIMITED BUDGET
#include<bits/stdc++.h>
using namespace std;
struct KOL {
    string name;
    int numberFollowers;
    vector<int> followerSet;
    float money;
    KOL(string name, int numberFollowers, vector<int> followerSet, float money):name(name), numberFollowers(numberFollowers), followerSet(followerSet), money(money){} // Constructor
};

struct Input{
    float providedMoney;
    vector<KOL> listKOL;
    string path;
    Input(string path): path(path){};
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
            listKOL.push_back(newKOL);
        }
    }

};

int main (){
    Input io("database/output1.txt");
    io.readFile();
    float i =0;
    for(auto c: io.listKOL[0].followerSet){
        cout<<c << " ";
    }
}

