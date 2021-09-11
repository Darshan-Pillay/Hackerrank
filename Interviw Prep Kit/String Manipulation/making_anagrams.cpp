#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'makeAnagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING a
 *  2. STRING b
 */   
int makeAnagram(string a, string b){
    int noDeletions = 0;
    unordered_map<char,int> aLetterFreqMap;
    unordered_map<char,int> bLetterFreqMap;
    for(char letter : a){
        aLetterFreqMap[letter]++;
    }
    for(char letter : b){
        bLetterFreqMap[letter]++;
    }
    for (auto iter = aLetterFreqMap.begin(); iter != aLetterFreqMap.end(); iter++){
        if(bLetterFreqMap.count(iter -> first) == 0){
            noDeletions = noDeletions + (iter -> second);
        }
        else{
            noDeletions = noDeletions + abs(bLetterFreqMap[iter -> first] - (iter -> second));
        }
    }
    for (auto iter = bLetterFreqMap.begin(); iter != bLetterFreqMap.end(); iter++){
        if(aLetterFreqMap.count(iter -> first) == 0){
            noDeletions = noDeletions + (iter -> second);
        }
    }
    return noDeletions;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
