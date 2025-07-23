#include <iostream>

using namespace std;

#define TEN 10

long long digit_counter(long long n)
{
    if (n == 0)
        return 0;
    else
        return 1 + digit_counter(n / TEN);
}
long long one_maker_up(long long n, long long one = 1)
{
    long long digit_num = digit_counter(n);
    for (int i = 0; i < digit_num; i++)
    {
        one = (one * TEN) + 1;
    }
    return one;
}
long long one_maker_down(long long n, long long one = 1)
{
    long long digit_num = digit_counter(n);
    for (int i = 0; i < digit_num; i++)
    {
        one = (one * TEN) + 1;
    }
    return (one / TEN);
}
int answer = 0;
long long solver(long long n)
{
    if (n == 0)
        return 0;
    long long up = one_maker_up(n);
    long long down = one_maker_down(n);
    long long up_distance = abs(up - n);
    long long down_distance = abs(n - down);
    if (up_distance < down_distance)
    {
        solver(up_distance);
        answer += digit_counter(up);
        return answer;
    }
    else
    {
        solver(down_distance);
        answer += digit_counter(down);
        return answer;
    }
}
int main()
{
    long long n;
    cin >> n;
    cout << solver(n) << endl;
}