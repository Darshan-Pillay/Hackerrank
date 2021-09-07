#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'whatFlavors' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY cost
 *  2. INTEGER money
 */

void whatFlavors(vector<int> cost, int money) {
   map<int,vector<int>> costIndiceMap;
   for(size_t costIndex = 0; costIndex < cost.size(); costIndex++){
       costIndiceMap[cost[costIndex]].push_back(costIndex + 1);
   }
   int flavourOneIndex = 0;
   int flavourTwoIndex = 0;
   for (auto iter = costIndiceMap.begin(); iter != costIndiceMap.end(); iter++) {
       auto searchIter = costIndiceMap.find(money - (iter -> first));
       if(searchIter != costIndiceMap.end()){
           if(searchIter -> first == iter -> first){
               if(iter -> second.size() >= 2){
                   flavourOneIndex = iter -> second[0];
                   flavourTwoIndex = iter -> second[1];
                   break;
               }
               else{
                   continue;
               }
           }
           else{
               flavourOneIndex = iter -> second[0];
               flavourTwoIndex = searchIter -> second[0];
               break;
           }
       }
   }
   cout << min(flavourOneIndex, flavourTwoIndex) << " " << max(flavourOneIndex, flavourTwoIndex) << endl;
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string money_temp;
        getline(cin, money_temp);

        int money = stoi(ltrim(rtrim(money_temp)));

        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string cost_temp_temp;
        getline(cin, cost_temp_temp);

        vector<string> cost_temp = split(rtrim(cost_temp_temp));

        vector<int> cost(n);

        for (int i = 0; i < n; i++) {
            int cost_item = stoi(cost_temp[i]);

            cost[i] = cost_item;
        }

        whatFlavors(cost, money);
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
