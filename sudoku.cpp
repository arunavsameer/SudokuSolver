#include <bits/stdc++.h>
using namespace std;

#define order 2
#define length order *order

class game
{
    int matrix[order][order][order][order];
    bool bit_matrix[order][order][order][order][length];

public:
    void take_input()
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                int a;
                cin >> a;
                matrix[i % order][j % order][i / order][j / order] = a;
            }
        }
    }

    void print_matrix()
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                cout << matrix[i % order][j % order][i / order][j / order];
            }
            cout << endl;
        }
    }

    void print_bit_matrix(int n)
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                cout << (bit_matrix[i % order][j % order][i / order][j / order][n - 1] == true) ? 1 : 0;
            }
            cout << endl;
        }
    }

    void print_mini_matrix(int k, int l)
    {
        for (int i = 0; i < order; i++)
        {
            for (int j = 0; j < order; j++)
            {
                cout << matrix[i][j][k][l];
            }
            cout << endl;
        }
    }

    void print_horz_matrix(int i)
    {
        for (int l = 0; l < length; l++)
        {
            cout << matrix[i % order][l % order][i / order][l / order];
        }
    }

    void print_vertical_matrix(int j)
    {
        for (int l = 0; l < length; l++)
        {
            cout << matrix[l % order][j % order][l / order][j / order];
        }
    }

    void set_all_bit_matrix_posn_0(int i, int j)
    {
        for (int n = 0; n < length; n++)
        {
            bit_matrix[i % order][j % order][i / order][j / order][n] = 0;
        }
    }

    void reset_bit_matrix()
    {
        for (int n = 0; n < length; n++)
        {
            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < length; j++)
                {
                    bit_matrix[i % order][j % order][i / order][j / order][n] = 1;
                }
            }
        }
    }

    bool can_go(int i, int j, int n)
    {
        return bit_matrix[i % order][j % order][i / order][j / order][n - 1];
    }

    void initiate_bit_matrix()
    {
        reset_bit_matrix();
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                int n = matrix[i % order][j % order][i / order][j / order];
                if (n != 0)
                {
                    set_all_bit_matrix_posn_0(i, j);
                    // along horizontal
                    for (int l = 0; l < length; l++)
                    {
                        bit_matrix[i % order][l % order][i / order][l / order][n - 1] = 0;
                    }
                    // along vertical
                    for (int l = 0; l < length; l++)
                    {
                        bit_matrix[l % order][j % order][l / order][j / order][n - 1] = 0;
                    }
                    // int mini matrix
                    for (int i_temp = 0; i_temp < order; i_temp++)
                    {
                        for (int j_temp = 0; j_temp < order; j_temp++)
                        {
                            bit_matrix[i_temp][j_temp][i / order][j / order][n - 1] = 0;
                        }
                    }
                }
            }
        }
    }

    bool solve(int i, int j)
    {
        initiate_bit_matrix();
        if (i == length - 1 && j == length)
        {
            return true;
        }
        if (j == length)
        {
            j = 0;
            i++;
        }
        if (matrix[i % order][j % order][i / order][j / order] != 0)
        {
            return solve(i, j + 1);
        }

        for (int possible = 1; possible <= length; possible++)
        {
            if (can_go(i, j, possible))
            {
                matrix[i % order][j % order][i / order][j / order] = possible;

                bool bit_matrix_temp[order][order][order][order][length];
                for (int n = 0; n < length; n++)
                {
                    for (int i = 0; i < length; i++)
                    {
                        for (int j = 0; j < length; j++)
                        {
                            bit_matrix_temp[i % order][j % order][i / order][j / order][n] = bit_matrix[i % order][j % order][i / order][j / order][n];
                        }
                    }
                }
                initiate_bit_matrix();

                if (solve(i, j + 1))
                {
                    return true;
                }
                for (int n = 0; n < length; n++)
                {
                    for (int i = 0; i < length; i++)
                    {
                        for (int j = 0; j < length; j++)
                        {
                            bit_matrix[i % order][j % order][i / order][j / order][n] = bit_matrix_temp[i % order][j % order][i / order][j / order][n];
                        }
                    }
                }
            }
            matrix[i % order][j % order][i / order][j / order] = 0;
        }
        return false;
    }
};

int main()
{
    game A;
    A.take_input();
    A.solve(0, 0);
    A.print_matrix();
}
