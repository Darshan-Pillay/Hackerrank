#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'largestRectangle' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY h as parameter.
 */

long largestRectangle(vector<int> h) {
    long largestArea = 0;
    stack<int> indexStack;
    vector<int> previous(h.size(),-1);
    vector<int> next(h.size(),h.size());
    for(int index = 0; index < h.size(); index++){
        while(!indexStack.empty() && h[indexStack.top()] >= h[index]){
            indexStack.pop();
        }
        if(!indexStack.empty()){
            previous[index] = indexStack.top();
        }
        indexStack.push(index);
    }
    while(!indexStack.empty()){
        indexStack.pop();
    }
    for(int index = h.size() - 1; index >= 0; --index){
        while(!indexStack.empty() && h[indexStack.top()] >= h[index]){
            indexStack.pop();
        }
        if(!indexStack.empty()){
            next[index] = indexStack.top();
        }
        indexStack.push(index);
    }
    for(int index = 0; index < h.size(); index++){
        long currentArea = (next[index] - previous[index] - 1) * h[index];
        largestArea = max(currentArea,largestArea);
    }
    return largestArea;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string h_temp_temp;
    getline(cin, h_temp_temp);

    vector<string> h_temp = split(rtrim(h_temp_temp));

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        int h_item = stoi(h_temp[i]);

        h[i] = h_item;
    }

    long result = largestRectangle(h);

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
