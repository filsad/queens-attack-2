#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

class Solve {
public:
    Solve(int n, int r_q, int c_q)
    {
        this->n = n;
        this->qr = r_q;
        this->qc = c_q;
        this->diag1_lo = max(1, 1 - c_q + r_q);
        this->diag1_hi = min(n, n - c_q + r_q);
        this->diag2_lo = max(1, c_q + r_q - n);
        this->diag2_hi = min(n, c_q + r_q - 1);
        this->horiz_lo = 1;
        this->horiz_hi = n;
        this->vert_lo = 1;
        this->vert_hi = n;
    }

    void add_vertical_obstacle(int o_r, int o_c)
    {
        if (o_c == qc) {
            if (o_r > qr && o_r <= vert_hi)
                vert_hi = o_r - 1;
            else if(o_r < qr && o_r >= vert_lo)
                vert_lo = o_r + 1;
        }
    }
    
    void add_horizontal_obstacle(int o_r, int o_c)
    {
        if (o_r == qr) {
            if (o_c > qc && o_c <= horiz_hi)
                horiz_hi = o_c - 1;
            else if (o_c < qc && o_c >= horiz_lo)
                horiz_lo = o_c + 1;
        }
    }
    
    void add_diagonal1_obstacle(int o_r, int o_c)
    {
        if (o_c == o_r + qc - qr) {
            if (o_r > qr && o_r <= diag1_hi)
                diag1_hi = o_r - 1;
            else if (o_r < qr && o_r >= diag1_lo)
                diag1_lo = o_r + 1;
        }
    }

    void add_diagonal2_obstacle(int o_r, int o_c)
    {
        if (o_c == -o_r + qc + qr) {
            if (o_r > qr && o_r <= diag2_hi)
                diag2_hi = o_r - 1;
            else if (o_r < qr && o_r >= diag2_lo)
                diag2_lo = o_r + 1;
        }
    }

    void add_obstacle(int o_r, int o_c)
    {
        add_vertical_obstacle(o_r, o_c);
        add_horizontal_obstacle(o_r, o_c);
        add_diagonal1_obstacle(o_r, o_c);
        add_diagonal2_obstacle(o_r, o_c);
    }

    int count_fields()
    {
        return diag1_hi - diag1_lo + diag2_hi - diag2_lo + horiz_hi - horiz_lo + vert_hi - vert_lo;
    }

private:
    int n;
    int qr;
    int qc;
    int diag1_lo;
    int diag1_hi;
    int diag2_lo;
    int diag2_hi;
    int horiz_lo;
    int horiz_hi;
    int vert_lo;
    int vert_hi;
};

// Complete the queensAttack function below.
int queensAttack(int n, int r_q, int c_q, const vector<vector<int>>& obstacles) {
    Solve solver(n, r_q, c_q);
    
    for (auto obst : obstacles)
        solver.add_obstacle(obst[0], obst[1]);

    return solver.count_fields();

}

int main()
{
    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector<vector<int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }

    int result = queensAttack(n, r_q, c_q, obstacles);

    std::cout << result << "\n";
    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = std::unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
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
