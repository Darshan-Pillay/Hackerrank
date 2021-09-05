#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countInversions' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

unordered_map<int, int> coordinateCompress(vector<int>& arr){
    unordered_map<int,int> coordinateCompressedVecMap;
    vector<int> arrCopy = arr;
    sort(arrCopy.begin(), arrCopy.end());
    arrCopy.erase(unique(arrCopy.begin(),arrCopy.end() ),arrCopy.end());
    for (size_t index = 0; index < arrCopy.size(); index++)
    {
        coordinateCompressedVecMap.insert({arrCopy[index], index+1});
    }
    return coordinateCompressedVecMap;
}

inline int extractLeastSignificantOneBit(int nonNegativeInteger){
    return (nonNegativeInteger & (nonNegativeInteger - 1));
}

vector<int> computePrefixSumArray(vector<int> arr){
    int currentPrefixSum = 0;
    vector<int> prefixSumArray(arr.size() + 1);
    for (size_t index = 0; index < arr.size(); index++)
    {
        currentPrefixSum = currentPrefixSum + arr[index];
        prefixSumArray[index + 1] = currentPrefixSum;
    }
    return prefixSumArray;
}

bool checkBounds(vector<int>& arr, long index){
    if(0 <= index && index < arr.size()){
        return true;
    }
    return false;
}

long getRangedPrefixSum(vector<int>& prefixSumArray, long lowerBound, long upperBound){
    if(checkBounds(prefixSumArray, lowerBound) && checkBounds(prefixSumArray, upperBound) && lowerBound <= upperBound ){
        if(lowerBound == 1 || lowerBound == 0){
            return prefixSumArray[upperBound];
        }
        else{
            return prefixSumArray[upperBound] - prefixSumArray[lowerBound - 1];
        }
    }
    return 0;
}

struct BIT{
    vector<int>* fenwickTree;
    BIT(vector<int>& constructionArray){
        fenwickTree = new vector<int>(constructionArray.size() + 1,0);
        vector<int> prefixSumArray = computePrefixSumArray(constructionArray);
        for (size_t index = 1; index < constructionArray.size() + 1; index++)
        {   
            fenwickTree -> at(index) = getRangedPrefixSum(prefixSumArray,extractLeastSignificantOneBit(index) + 1,index);
        }
        
    }
    ~BIT(){
        delete fenwickTree;
    }
    long getJthPrefixSum(size_t j){
        long result = 0;
        if(0 < j && j < fenwickTree -> size()){
            long r = j;
            while (r > 0)
            {
                result = result + fenwickTree -> at(r);
                r = extractLeastSignificantOneBit(r);
            }
        }
        return result;
    }
    void updateJthEntry(size_t j, long delta){
        if(0 < j && j < fenwickTree -> size()){
           long r = j;
           while(r < fenwickTree -> size()){
               fenwickTree -> at(r) += delta;
               r = r + (r & -r);
           }
        }
    }
    bool checkBound(long index){
        if(0 < index && index < fenwickTree -> size()){
            return true;
        }
        return false;
    }
    long getRangedSum(long lowerBound, long upperBound){
        if(checkBound(lowerBound) && checkBound(upperBound)){
            if(lowerBound == 1 || lowerBound == 0){
                return getJthPrefixSum(upperBound);
            }
            else{
                return getJthPrefixSum(upperBound) - getJthPrefixSum(lowerBound - 1);
            }
        }
        return 0;
    }
};

long countInversions(vector<int> arr) {
    long invCount = 0;
    unordered_map<int, int> rankMap = coordinateCompress(arr);
    long maxRank = rankMap[*max_element(arr.begin(), arr.end())];
    vector<int> rankFreqArray(rankMap.size(), 0);
    for(size_t index = 0; index < arr.size(); index++){
        rankFreqArray[rankMap[arr[index]] - 1]++;
    }
    BIT cumalativeFreqTree(rankFreqArray);
    for(int index = arr.size() -1; -1 < index; index--){
        invCount =  invCount + cumalativeFreqTree.getRangedSum(rankMap[arr[index]] + 1,maxRank);
        cumalativeFreqTree.updateJthEntry(rankMap[arr[index]], -1);
    }
    return invCount;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        long result = countInversions(arr);

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

