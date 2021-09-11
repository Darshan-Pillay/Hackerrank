#include <bits/stdc++.h>

using namespace std;

// Complete the substrCount function below.
long substrCount(int n, string s) {
    long noSpecialStrings = 0;
    int charIndex = 0;
    int currentCharIndex = 0;
    int currentCount = 0;
    /*
        The ith index of this vector
        represents the number of characters N
        in the substring s[i+1....n] such that
        s[i + 1] = s[i + 2] = ...... = s[i + N + 1]
    */
    vector<int> noContingousCharsVec(n,0);
    while(charIndex < n){
        currentCharIndex = charIndex + 1;
        currentCount = 1;
        while(currentCharIndex < n && s[currentCharIndex] == s[charIndex]){
            currentCharIndex++;
            currentCount++;
        }
        noSpecialStrings = noSpecialStrings + (((currentCount) * (currentCount + 1)) / 2);
        noContingousCharsVec[charIndex] = currentCount;
        charIndex = currentCharIndex;
    
    }
    for(size_t charIndex = 1; charIndex < n; charIndex++){
        if(s[charIndex] == s[charIndex - 1]){
            noContingousCharsVec[charIndex] = noContingousCharsVec[charIndex - 1];
        }
        
        if(s[charIndex - 1] == s[charIndex + 1] && s[charIndex] != s[charIndex - 1]){
            noSpecialStrings = noSpecialStrings + min(noContingousCharsVec[charIndex - 1], noContingousCharsVec[charIndex + 1]);
        }
    }
    return noSpecialStrings;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
