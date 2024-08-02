#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <sstream>
#include <string>
#include <set>

using namespace std;
vector<vector<pair<int, int>>> ans;

//print function to print the result
void print()
{
    cout << "Thanks. There are " << ans.size() << " unique paths for your 'specialized castle'" << endl;

    for (int i = 0; i < ans.size(); ++i)
    {
        cout << "Path " << (i + 1) << endl;
        cout << "=======" << endl;

        for (int j = 0; j < ans[i].size(); ++j)
        {
            if (j == 0)
            {
                cout << "Start (" << ans[i][j].first << "," << ans[i][j].second << ")" << endl;
            }
            else
            {
                cout << "Kill (" << ans[i][j].first << "," << ans[i][j].second << "). Turn Left" << endl;
            }
        }
        cout << "Arrive (" << ans[i][0].first << "," << ans[i][0].second << ")" << endl;
        cout << endl;
    }
}

void solve(vector<vector<char>> &board, vector<vector<int>> &visited, vector<pair<int, int>> &path, int x, int y, int startX, int startY, int numSoldiers)
{
   
    if (x == startX && y == startY && !path.empty())
    {
        ans.push_back(path);
        return;
    }

    //checking for same column if their soldier is present is not if present then moving left
    for (int i = x + 1; i < 10; ++i)
    {
        if (board[i][y] == 'S')
        { 
            path.push_back({i, y});
            char temp = board[i][y];
            board[i][y] = '.';
            
            for (int j = y - 1; j >= 0; --j)
            {
                if (visited[i][j] == 0)
                {
                    visited[i][j] = 1;
                    solve(board, visited, path, i, j, startX, startY, numSoldiers - 1);
                    visited[i][j] = 0;
                }
            }


            for (int j = y + 1; j < 10; ++j)
            {
                if (visited[i][j] == 0)
                {
                    visited[i][j] = 1;
                    solve(board, visited, path, i, j, startX, startY, numSoldiers - 1);
                    visited[i][j] = 0;
                }
            }
       
            board[i][y] = temp;
            path.pop_back();
        }
    }
}

int main()
{
    int numSoldiers;
    cout << "Enter number of soldiers: ";
    cin >> numSoldiers;

    vector<vector<char>> board(10, vector<char>(10, '.'));

    cout << "Enter coordinates for soldiers (format x,y):" << endl;
    for (int i = 0; i < numSoldiers; ++i)
    {
        int x, y;
        cout << "Enter coordinates for soldier " << (i + 1) << ": ";
        string input;
        cin >> input;
        replace(input.begin(), input.end(), ',', ' ');
        stringstream ss(input);
        ss >> x >> y;
        if (cin.fail() || x < 1 || x > 10 || y < 1 || y > 10)
        {
            cout << "Invalid coordinates. Please enter values between 1 and 10." << endl;
            cin.clear();                                         // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            --i;                                                 // decrement index to retry
        }
        else
        {
            board[x - 1][y - 1] = 'S';
        }
    }

    int startX, startY;
    cout << "Enter the coordinates for your specialized castle (format x,y): ";
    string input;
    cin >> input;
    replace(input.begin(), input.end(), ',', ' ');
    stringstream ss(input);
    ss >> startX >> startY;
    if (cin.fail() || startX < 1 || startX > 10 || startY < 1 || startY > 10)
    {
        cout << "Invalid coordinates. Please enter values between 1 and 10." << endl;
        return 1;
    }

    board[startX - 1][startY - 1] = 'C';

    vector<vector<int>> visited(10, vector<int>(10, 0));
    vector<pair<int, int>> path;

    //traversing through the board....
    solve(board, visited, path, startX - 1, startY - 1, startX - 1, startY - 1, numSoldiers);
    
    //printing the output
    print();

    return 0;
}
