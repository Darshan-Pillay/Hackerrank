#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

static unordered_map<char, int> alphabet =
{
  {'a' , 0},
  {'b' , 1},
  {'c' , 2},
  {'d' , 3},
  {'e' , 4},
  {'f' , 5},
  {'g' , 6},
  {'h' , 7},
  {'i' , 8},
  {'j' , 9},
  {'k' , 10},
  {'l' , 11},
  {'m' , 12},
  {'n' , 13},
  {'o' , 14},
  {'p' , 15},
  {'q' , 16},
  {'r' , 17},
  {'s' , 18},
  {'t' , 19},
  {'u' , 20},
  {'v' , 21},
  {'w' , 22},
  {'x' , 23},
  {'y' , 24},
  {'z' , 25}
 
};
inline int asciiCharToInteger(char c){
    return int(c);
}

vector<int> getSignature(string s){
    vector<int> signature(26,0);
    for (int index = 0; index < s.size(); index++) {
        signature[alphabet[s[index]]]++;
    }
    return signature;
}

/*
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int sherlockAndAnagrams(string s) {
   unordered_map<int, unordered_map<string, int>> subStringFrequencyMap;
   int anagramPairCount = 0;
   vector<int> signatureVec(26,0);
   for (size_t i = 0; i < s.size(); i++) {
       unordered_map<string, int> map;
       subStringFrequencyMap.insert({i, map});
   }
   for(size_t charIndex = 0; charIndex < s.size(); charIndex++){
       fill(signatureVec.begin(),signatureVec.end(),0);
       for(size_t length = charIndex; length < s.size(); length++){
           signatureVec.at(alphabet[s[length]])++;
           bool signatureFound = false;
           for (auto iter = subStringFrequencyMap[length - charIndex + 1].begin(); iter != subStringFrequencyMap[length - charIndex + 1].end(); iter++) {
               if(getSignature(iter -> first) == signatureVec){
                   anagramPairCount -= ((iter -> second) * (iter -> second - 1)) / 2;
                   anagramPairCount += ((iter -> second + 1) * (iter -> second )) / 2;
                   iter -> second++;
                   signatureFound = true;
                   break;
               }
           }
           if(!signatureFound){
               subStringFrequencyMap[length - charIndex + 1].insert({s.substr(charIndex, length - charIndex + 1), 1});
           }
       }
   }
   return anagramPairCount;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

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
