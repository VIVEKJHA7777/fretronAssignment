//approach1:- actually i have used greedy approach and a two-pointer appraoch but this code is giving the correct result 
//if the apples in definite proportion means it is divisible by their propration

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(vector<int> apples, vector<int> &ram, vector<int> &sham, vector<int> &rahim)
{
  //sort the array
    sort(apples.begin(), apples.end(), greater<int>());
    int sum = 0;
    int n = apples.size();
    for (int i = 0; i < n; i++)
    {
        sum += apples[i];
    }

    int total_paid = 50 + 30 + 20;
    double ram_target = (50.0 / total_paid) * sum;
    double sham_target = (30.0 / total_paid) * sum;
    double rahim_target = (20.0 / total_paid) * sum;

// take two pointer i and j
    int i = 0, j = n - 1;
    int ram_total = 0, sham_total = 0, rahim_total = 0;
    while (i <= j)
    {
        if (apples[i] + ram_total <= ram_target)
        {
            ram.push_back(apples[i]);
            ram_total += apples[i];
            i++;
        }
        else if (apples[j] + ram_total <= ram_target)
        {
            ram.push_back(apples[j]);
            ram_total += apples[j];
            j--;
        }
        else if (apples[i] + sham_total <= sham_target)
        {
            sham.push_back(apples[i]);
            sham_total += apples[i];
            i++;
        }
        else if (apples[j] + sham_total <= sham_target)
        {
            sham.push_back(apples[j]);
            sham_total += apples[j];
            j--;
        }
        else if (apples[i] + rahim_total <= rahim_target)
        {
            rahim.push_back(apples[i]);
            rahim_total += apples[i];
            i++;
        }
        else if (apples[j] + rahim_total <= rahim_target)
        {
            rahim.push_back(apples[j]);
            rahim_total += apples[j];
            j--;
        }
    }
}

int main()
{
    vector<int> apples;
    vector<int> ram, sham, rahim;
    int weight;

    while (1)
    {
        cout << "Enter apple weight in gram (-1 to stop): ";
        cin >> weight;
        if (weight == -1)
        {
            break;
        }
        apples.push_back(weight);
    }

    solve(apples, ram, sham, rahim);

    cout << "Distribution Result:" << endl;
    cout << "Ram: ";
    for (int w : ram)
    {
        cout << w << " ";
    }
    cout << endl;

    cout << "Sham: ";
    for (int w : sham)
    {
        cout << w << " ";
    }
    cout << endl;

    cout << "Rahim: ";
    for (int w : rahim)
    {
        cout << w << " ";
    }
    cout << endl;

    return 0;
}




//approach 2 :- In approach 2 i have tried it to solve for various other test case i have think that
//when i give apple to anyone after that again calculate the distribution between the people
//but again this approach give result for some test case but fail for other

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to distribute apples proportionally
void distributeApples(vector<int> apples, vector<int> &ram, vector<int> &sham, vector<int> &rahim)
{
    // Sort the apples in descending order of weight
    sort(apples.begin(), apples.end(), greater<int>());
    int sum = 0;
    int n = apples.size();
    for (int i = 0; i < n; i++)
    {
        sum += apples[i];
    }

    // Initial weights and proportions
    int total_paid = 50 + 30 + 20;
    double ram_target = (50.0 / total_paid) * sum;
    double sham_target = (30.0 / total_paid) * sum;
    double rahim_target = (20.0 / total_paid) * sum;

    int ram_total = 0, sham_total = 0, rahim_total = 0;

    for (int i = 0; i < n; i++)
    {
        if (ram_total < ram_target)
        {
            ram.push_back(apples[i]);
            ram_total += apples[i];
            //after giving the apple again calculating the target after reducing the weight which is given to them
            sum -= apples[i];
            ram_target = (50.0 / total_paid) * sum;
            sham_target = (30.0 / total_paid) * sum;
            rahim_target = (20.0 / total_paid) * sum;
        }
        else if (sham_total < sham_target)
        {
            sham.push_back(apples[i]);
            sham_total += apples[i];
            sum -= apples[i];
            ram_target = (50.0 / total_paid) * sum;
            sham_target = (30.0 / total_paid) * sum;
            rahim_target = (20.0 / total_paid) * sum;
        }
        else if (rahim_total < rahim_target)
        {
            rahim.push_back(apples[i]);
            rahim_total += apples[i];
            sum -= apples[i];
            ram_target = (50.0 / total_paid) * sum;
            sham_target = (30.0 / total_paid) * sum;
            rahim_target = (20.0 / total_paid) * sum;
        }
        else
        {
            // Distribute remaining apples to those who are the farthest from their target
            if (ram_total < sham_total && ram_total < rahim_total)
            {
                ram.push_back(apples[i]);
                ram_total += apples[i];
                sum -= apples[i];
                ram_target = (50.0 / total_paid) * sum;
                sham_target = (30.0 / total_paid) * sum;
                rahim_target = (20.0 / total_paid) * sum;
            }
            else if (sham_total < rahim_total)
            {
                sham.push_back(apples[i]);
                sham_total += apples[i];
                sum -= apples[i];
                ram_target = (50.0 / total_paid) * sum;
                sham_target = (30.0 / total_paid) * sum;
                rahim_target = (20.0 / total_paid) * sum;
            }
            else
            {
                rahim.push_back(apples[i]);
                rahim_total += apples[i];
                sum -= apples[i];
                ram_target = (50.0 / total_paid) * sum;
                sham_target = (30.0 / total_paid) * sum;
                rahim_target = (20.0 / total_paid) * sum;
            }
        }
    }
}

int main()
{
    vector<int> apples;
    vector<int> ram, sham, rahim;
    int weight;

    // Input apple weights
    while (1)
    {
        cout << "Enter apple weight in grams (-1 to stop): ";
        cin >> weight;
        if (weight == -1)
        {
            break;
        }
        apples.push_back(weight);
    }

    // Distribute the apples
    distributeApples(apples, ram, sham, rahim);

    // Output the result
    cout << "Distribution Result:" << endl;
    cout << "Ram: ";
    for (int w : ram)
    {
        cout << w << " ";
    }
    cout << endl;

    cout << "Sham: ";
    for (int w : sham)
    {
        cout << w << " ";
    }
    cout << endl;

    cout << "Rahim: ";
    for (int w : rahim)
    {
        cout << w << " ";
    }
    cout << endl;

    return 0;
}


