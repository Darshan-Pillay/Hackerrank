#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumPasses' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER m
 *  2. LONG_INTEGER w
 *  3. LONG_INTEGER p
 *  4. LONG_INTEGER n
 */
 bool isValidUpperBound(long machines, long workers, long price, long noCandies, long upperBound){
     if(upperBound == 0){
         return false;
     }
     if(machines >= ((noCandies + workers - 1)/workers)){
         return true;
     }
     long currentNoCandies = machines * workers;
     upperBound--;
     while(0 < upperBound){
         long remainingCandiesNeeded = noCandies - currentNoCandies;
         long rounds = (remainingCandiesNeeded + (machines * workers) - 1) / (machines * workers);
         if(rounds <= upperBound){
             return true;
         }
         if(currentNoCandies < price){
             long noCandiesNeededToIncreaseProduction = price - currentNoCandies;
             rounds = (noCandiesNeededToIncreaseProduction + machines*workers -1) / (machines * workers);
             upperBound = upperBound - rounds;
             if(upperBound < 1){
                 return false;
             }
             currentNoCandies = currentNoCandies + (rounds * machines * workers);
         }
         currentNoCandies = currentNoCandies - price;
         if(machines > workers){
             workers++;
         }
         else{
             machines++;
         }
     }
     return false;
 }
 
long minimumPasses(long machines, long workers, long price, long noCandies) {
    long low = 1;
    long high = 1e12l;
    long currentMin = 1e12l;
    while(low < high){
        long mid = (high + low) / 2;
        if(isValidUpperBound(machines,workers,price,noCandies,mid)){
            high = mid;
        }
        else{
            low = mid + 1;
        }
    }
    return low;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    long m = stol(first_multiple_input[0]);

    long w = stol(first_multiple_input[1]);

    long p = stol(first_multiple_input[2]);

    long n = stol(first_multiple_input[3]);

    long result = minimumPasses(m, w, p, n);

    fout << result << "\n";

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
