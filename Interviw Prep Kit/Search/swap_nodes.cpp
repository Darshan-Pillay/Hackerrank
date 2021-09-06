#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */

vector<vector<int>> swapNodes(vector<vector<int>> tree, vector<int> queries) {
    vector<vector<int>> inorderSequences(queries.size());
    stack<pair<int,int>> dfSearchStack;
    vector<bool> visitedVector(tree.size(),false);
    for(size_t queryNumber = 0; queryNumber < queries.size(); queryNumber++){
        int swapDepthNumber = queries[queryNumber];
        vector<int> currentInorderSequence;
        pair<int,int> currentNode;
        dfSearchStack.push({1,1});
        while(!dfSearchStack.empty()){
            currentNode = dfSearchStack.top();
            dfSearchStack.pop();
            if(!visitedVector[currentNode.first - 1]){
                visitedVector[currentNode.first - 1]  = true;
                if(currentNode.second % swapDepthNumber == 0){
                    swap(tree[currentNode.first - 1][0],tree[currentNode.first - 1][1]);
                }
                if(tree[currentNode.first - 1][0] != -1){
                    dfSearchStack.push(currentNode);
                    dfSearchStack.push({tree[currentNode.first - 1][0], currentNode.second + 1});
                }
                else{
                    dfSearchStack.push(currentNode);
                }
            }
            else{
                currentInorderSequence.push_back(currentNode.first);
                if(tree[currentNode.first - 1][1] != -1){
                    dfSearchStack.push({tree[currentNode.first - 1][1], currentNode.second + 1});
                }
            }
        }
        inorderSequences.push_back(currentInorderSequence);
        fill(visitedVector.begin(),visitedVector.end(),false);
    }
    return inorderSequences;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> indexes(n);

    for (int i = 0; i < n; i++) {
        indexes[i].resize(2);

        string indexes_row_temp_temp;
        getline(cin, indexes_row_temp_temp);

        vector<string> indexes_row_temp = split(rtrim(indexes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int indexes_row_item = stoi(indexes_row_temp[j]);

            indexes[i][j] = indexes_row_item;
        }
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            cout << result[i][j];

            if (j != result[i].size() - 1) {
                cout << " ";
            }
        }

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

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