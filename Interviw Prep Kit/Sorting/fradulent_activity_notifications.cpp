#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */

long findDoubleMedian(vector<int>& freqArray, size_t arraySize)
{
    int doubleMedian = 0;
    int cumalativeFrequency = 0;
    if (arraySize % 2 == 1)
    {
        int medianPosition = (arraySize / 2) + 1;
        for(size_t keyIndex = 0; keyIndex < freqArray.size(); keyIndex++){
            cumalativeFrequency = cumalativeFrequency + freqArray[keyIndex];
            if(cumalativeFrequency >= medianPosition)
            {
                doubleMedian = 2 * keyIndex;
                break;  
            }
        }
    }
    else
    {
        int firstMedianPosition = (arraySize / 2);
        int secondMedianPosition = (arraySize / 2) + 1;
        for (size_t keyIndex = 0; keyIndex < freqArray.size(); keyIndex++)
        {
            cumalativeFrequency = cumalativeFrequency + freqArray[keyIndex];
            if(cumalativeFrequency >= firstMedianPosition)
            {
                doubleMedian = keyIndex;
                break;  
            }
        } 
        if(cumalativeFrequency >= secondMedianPosition)
        {
            doubleMedian = doubleMedian + doubleMedian;
        }
        else
        {
            for (size_t keyIndex = doubleMedian + 1; keyIndex < freqArray.size(); keyIndex++)
            {
                cumalativeFrequency = cumalativeFrequency + freqArray[keyIndex];
                if (cumalativeFrequency >= secondMedianPosition)
                {
                    doubleMedian = doubleMedian + keyIndex;
                    break;
                }
                
            }
        }
    }
    return doubleMedian;
}

long activityNotifications(vector<int> expenditure, int d) 
{
    long fradulentNotifications = 0;
    int currentDoubleMedian = 0;
    vector<int> dWindowFreqVector(201,0);
    if(d < expenditure.size())
    {
        for (size_t index = 0; index < d; index++)
        {
            dWindowFreqVector[expenditure[index]]++;
        }
        for (size_t expenditureIndex = d; expenditureIndex < expenditure.size(); expenditureIndex++)
        {
            currentDoubleMedian = findDoubleMedian(dWindowFreqVector, d);
            if(expenditure[expenditureIndex] >= (currentDoubleMedian))
            {
                fradulentNotifications++;
            }
            dWindowFreqVector[expenditure[expenditureIndex - d]]--;
            dWindowFreqVector[expenditure[expenditureIndex]]++;
        }  
    }
    return fradulentNotifications;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
