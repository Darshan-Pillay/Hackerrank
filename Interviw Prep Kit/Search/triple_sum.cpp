#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the triplets function below.
long triplets(vector<int> a, vector<int> b, vector<int> c) {
    long noTriplets = 0;
    set<int> distinctElementsOfA(a.begin(),a.end());
    set<int> distinctElementsOfB(b.begin(),b.end());
    set<int> distinctElementsOfC(c.begin(),c.end());
    auto aIter = distinctElementsOfA.begin();
    auto bIter = distinctElementsOfB.begin();
    auto aEnd = distinctElementsOfA.end();
    auto bEnd = distinctElementsOfB.end();
    cout << distinctElementsOfA.size() << endl;
    map<int,long> cumaltativeFreqOfPossibleValidPairs;
    while(aIter != aEnd && bIter != bEnd){
        if(*aIter <= *bIter){
            cumaltativeFreqOfPossibleValidPairs[*bIter]++;
            aIter++;
        }
        else{
            int lastValue = *bIter;
            bIter++;
            if(bIter != bEnd){
                cumaltativeFreqOfPossibleValidPairs[*bIter] = cumaltativeFreqOfPossibleValidPairs[lastValue];
            }
        }
    }
    int lastValue = 0;
    while(bIter != bEnd){
        lastValue = *bIter;
        bIter++;
        if(bIter != bEnd){
            cumaltativeFreqOfPossibleValidPairs[*bIter] = cumaltativeFreqOfPossibleValidPairs[lastValue];
        }
    }
    map<int,long> cumaltativeFreqOfPairsinC;
    auto cIter = distinctElementsOfC.begin();
    auto cEnd = distinctElementsOfC.end();
    bIter = distinctElementsOfB.begin();
    while(bIter != bEnd && cIter != cEnd){
        if(*cIter <= *bIter){
            cumaltativeFreqOfPairsinC[*bIter]++;
            cIter++;
        }
        else{
            int lastValue = *bIter;
            bIter++;
            if(bIter != bEnd){
                cumaltativeFreqOfPairsinC[*bIter] = cumaltativeFreqOfPairsinC[lastValue];
            }
        }
    }
    lastValue = 0;
    while(bIter != bEnd){
        lastValue = *bIter;
        bIter++;
        if(bIter != bEnd){
            cumaltativeFreqOfPairsinC[*bIter] = cumaltativeFreqOfPairsinC[lastValue];
        }
    }
    for(auto iter = distinctElementsOfB.begin(); iter != bEnd; iter++){
        noTriplets += (cumaltativeFreqOfPossibleValidPairs[*iter] * cumaltativeFreqOfPairsinC[*iter]);
    }
    return noTriplets;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string lenaLenbLenc_temp;
    getline(cin, lenaLenbLenc_temp);

    vector<string> lenaLenbLenc = split_string(lenaLenbLenc_temp);

    int lena = stoi(lenaLenbLenc[0]);

    int lenb = stoi(lenaLenbLenc[1]);

    int lenc = stoi(lenaLenbLenc[2]);

    string arra_temp_temp;
    getline(cin, arra_temp_temp);

    vector<string> arra_temp = split_string(arra_temp_temp);

    vector<int> arra(lena);

    for (int i = 0; i < lena; i++) {
        int arra_item = stoi(arra_temp[i]);

        arra[i] = arra_item;
    }

    string arrb_temp_temp;
    getline(cin, arrb_temp_temp);

    vector<string> arrb_temp = split_string(arrb_temp_temp);

    vector<int> arrb(lenb);

    for (int i = 0; i < lenb; i++) {
        int arrb_item = stoi(arrb_temp[i]);

        arrb[i] = arrb_item;
    }

    string arrc_temp_temp;
    getline(cin, arrc_temp_temp);

    vector<string> arrc_temp = split_string(arrc_temp_temp);

    vector<int> arrc(lenc);

    for (int i = 0; i < lenc; i++) {
        int arrc_item = stoi(arrc_temp[i]);

        arrc[i] = arrc_item;
    }

    long ans = triplets(arra, arrb, arrc);

    fout << ans << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
