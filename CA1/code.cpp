#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
int arae_shode(vector<string> arae, vector<string> want, int k, int m)
{
    for (int i = 0; i < k; i++)
    {
        bool found = false;

        for (int j = 0; j < m; j++)
        {
            if (want[i] == arae[j])
            {
                found = true;
            }
        }
        if (!found)
        {
            return 0;
        }
    }
    return 1;
}

int kaf_vahed(vector<string> arae, vector<int> vahed, vector<string> want, int k, int m)
{
    int sum = 0;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (want[i] == arae[j])
            {
                sum += vahed[j];
            }
        }
    }
    if (sum < 12)
    {
        return 0;
    }
    return 1;
}

float moadel(vector<int> vahed2, vector<float> nomre, int n)
{
    int moaddel = 0;
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        sum1 += vahed2[i] * nomre[i];
    }
    for (int i = 0; i < n; i++)
    {
        sum2 += vahed2[i];
    }
    moaddel = sum1 / sum2;
    return moaddel;
}

int saghf_vahed(vector<string> want, int k, vector<string> arae, vector<int> vahed, int m, vector<int> vahed2, vector<float> nomre, int n)
{
    int sum = 0;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (want[i] == arae[j])
            {
                sum += vahed[j];
            }
        }
    }

    int moaddel;
    moaddel = moadel(vahed2, nomre, n);
    if (moaddel < 12)
    {
        if (sum > 14)
        {
            return 0;
        }
    }
    if (moaddel >= 12 or moaddel < 17)
    {
        if (sum > 20)
        {
            return 0;
        }
    }
    if (moaddel >= 17 or moaddel <= 20)
    {
        if (sum > 24)
        {
            return 0;
        }
    }
    return 1;
}

int akhz_shode(vector<string> akhz, vector<float> nomre, vector<string> want, int k, int n)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (nomre[j] >= 10)
            {
                if (want[i] == akhz[j])
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

vector<string> divider(string &inputVector)
{
    vector<string> outputVector;

    stringstream ss(inputVector);

    string token;
    while (getline(ss, token, ','))
    {
        outputVector.push_back(token);
    }

    return outputVector;
}

int pish_niaz(vector<string> want, vector<string> arae, vector<string> pish, vector<string> akhz, vector<float> nomre, int k, int m, int n)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (want[i] == arae[j])
            {
                vector<string> pish_divided = divider(pish[j]);

                for (const string &pish_course : pish_divided)
                {
                    bool found = false;

                    for (int z = 0; z < n; z++)
                    {
                        if (pish_course == akhz[z])
                        {
                            if (nomre[z] >= 10)
                            {
                                found = true;
                                break;
                            }
                        }
                    }

                    if (!found)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main()
{
    int m;
    cin >> m;

    vector<string> arae;
    string Arae;

    vector<int> vahed;
    int Vahed;

    vector<string> pish;
    string Pish;
    for (int i = 0; i < m; i++)
    {
        cin >> Arae;
        arae.push_back(Arae);
        cin >> Vahed;
        vahed.push_back(Vahed);
        cin >> Pish;
        pish.push_back(Pish);
    }

    int n;
    cin >> n;

    vector<string> akhz;
    string Akhz;

    vector<int> vahed2;
    int Vahed2;

    vector<float> nomre;
    int Nomre;
    for (int i = 0; i < n; i++)
    {
        cin >> Akhz;
        akhz.push_back(Akhz);
        cin >> Vahed2;
        vahed2.push_back(Vahed2);
        cin >> Nomre;
        nomre.push_back(Nomre);
    }

    int k;
    cin >> k;
    vector<string> want;
    string Want;
    for (int i = 0; i < k; i++)
    {
        cin >> Want;
        want.push_back(Want);
    }

    if (arae_shode(arae, want, k, m))
    {
        if (kaf_vahed(arae, vahed, want, k, m))
        {
            if (saghf_vahed(want, k, arae, vahed, m, vahed2, nomre, n))
            {
                if (akhz_shode(akhz, nomre, want, k, n))
                {
                    if (pish_niaz(want, arae, pish, akhz, nomre, k, m, n))
                    {
                        cout << "OK!";
                    }
                    else
                    {
                        cout << "Prerequisites Not Met!";
                    }
                }
                else
                {
                    cout << "Course Already Taken!";
                }
            }
            else
            {
                cout << "Maximum Units Validation Failed!";
            }
        }
        else
        {
            cout << "Minimum Units Validation Failed!";
        }
    }
    else
    {
        cout << "Course Not Offered!";
    }
    return 0;
}