#include <bits/stdc++.h>

using namespace std;

int lookUpTable[5001][5001] = {0};
/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */
int commonChild(string s1, string s2) {
    for(size_t charIndexS1 = 0; charIndexS1 < s1.size(); charIndexS1++){
        for(size_t charIndexS2 = 0; charIndexS2 < s2.size(); charIndexS2++){
            if(s1[charIndexS1] == s2[charIndexS2]){
                lookUpTable[charIndexS1 + 1][charIndexS2 + 1] = lookUpTable[charIndexS1][charIndexS2] + 1;
            }
            else{
                lookUpTable[charIndexS1 + 1][charIndexS2 + 1] = max(lookUpTable[charIndexS1][charIndexS2 + 1], lookUpTable[charIndexS1 + 1][charIndexS2]);
            }
        }
    }
    return lookUpTable[s1.size()][s2.size()];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    return 0;
}
