#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const double first_value = 0.0;
const int size_of_expenses_vector = 3;
const double Two_decimal_places_maker = 100.0;
const char comma_delimintor = ',';
const char semi_colon_delimintor = ';';
const char colon_delimintor = ':';
const string expenses_without_borrowers = " ";

struct person
{
    string name;
    double input_money;
    double output_money;
    double Property;
};

struct Result
{
    string from_someone;
    string to_another_one;
    double money;
};

vector<string> read_file(const string &path_file)
{
    vector<string> lines;

    ifstream file(path_file);
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    return lines;
}

vector<person> make_struct(vector<string> data_of_names_file)
{
    vector<person> result;
    person newperson;
    for (int i = 1; i < data_of_names_file.size(); i++)
    {
        newperson.name = data_of_names_file[i];
        newperson.input_money = first_value;
        newperson.output_money = first_value;
        newperson.Property = first_value;
        result.push_back(newperson);
    }
    return result;
}

vector<string> divider(const string &inputVector, char delimiter)
{
    vector<string> outputVector;

    stringstream ss(inputVector);

    string token;
    while (getline(ss, token, delimiter))
    {
        outputVector.push_back(token);
    }

    return outputVector;
}

vector<vector<string>> recognize_all_data_divided(vector<string> data_of_expenses_file)
{
    vector<vector<string>> all_data;
    for (int i = 1; i < data_of_expenses_file.size(); ++i)
    {
        all_data.push_back(divider(data_of_expenses_file[i], comma_delimintor));
    }
    for (int i = 0; i < all_data.size(); ++i)
    {
        if (all_data[i].size() < size_of_expenses_vector)
        {
            all_data[i].push_back(expenses_without_borrowers);
        }
    }
    return all_data;
}

void recognize_expenses(const vector<vector<string>> &all_data, vector<vector<string>> &equal_type, vector<vector<string>> &unequal_type, vector<vector<string>> &adjustment_type)
{
    for (int i = 0; i < all_data.size(); ++i)
    {
        const vector<string> &data = all_data[i];
        if (data.empty())
            continue;

        if (data[0] == "equally")
        {
            equal_type.push_back(data);
        }
        else if (data[0] == "unequally")
        {
            unequal_type.push_back(data);
        }
        else if (data[0] == "adjustment")
        {
            adjustment_type.push_back(data);
        }
    }
}

void enter_divided_data_semicolon_in_vectorofvecttor(vector<vector<string>> equal_data, vector<vector<string>> unequal_data, vector<vector<string>> adjustment_data,
                                                     vector<vector<string>> &equal_data_divided_semicolon, vector<vector<string>> &unequal_data_divided_semicolon, vector<vector<string>> &adjustment_data_divided_semicolon)
{
    for (int i = 0; i < equal_data.size(); ++i)
    {
        equal_data_divided_semicolon.push_back(divider(equal_data[i][1], semi_colon_delimintor));
    }

    for (int i = 0; i < unequal_data.size(); ++i)
    {
        unequal_data_divided_semicolon.push_back(divider(unequal_data[i][1], semi_colon_delimintor));
    }

    for (int i = 0; i < adjustment_data.size(); ++i)
    {
        adjustment_data_divided_semicolon.push_back(divider(adjustment_data[i][1], semi_colon_delimintor));
    }
}

vector<pair<string, double>> create_pairs(const vector<string> &data_divided_semicolon)
{
    vector<pair<string, double>> pairs;

    for (int i = 0; i < data_divided_semicolon.size(); i++)
    {
        const string &item = data_divided_semicolon[i];

        vector<string> colon_divided = divider(item, colon_delimintor);
        if (colon_divided.size() == 2)
        {
            pairs.push_back(make_pair(colon_divided[0], stod(colon_divided[1])));
        }
        else if (colon_divided.size() < 2)
        {
            pairs.push_back(make_pair(colon_divided[0], first_value));
        }
    }

    return pairs;
}

void create_payers_count_pair(vector<vector<pair<string, double>>> &payers_count_equally1, vector<vector<pair<string, double>>> &payers_count_unequally1, vector<vector<pair<string, double>>> &payers_count_adjustment,
                              vector<vector<string>> equal_data_divided_semicolon, vector<vector<string>> unequal_data_divided_semicolon, vector<vector<string>> adjustment_data_divided_semicolon)
{
    for (int i = 0; i < equal_data_divided_semicolon.size(); i++)
    {
        payers_count_equally1.push_back(create_pairs(equal_data_divided_semicolon[i]));
    }

    for (int i = 0; i < unequal_data_divided_semicolon.size(); i++)
    {
        payers_count_unequally1.push_back(create_pairs(unequal_data_divided_semicolon[i]));
    }

    for (int i = 0; i < adjustment_data_divided_semicolon.size(); i++)
    {
        payers_count_adjustment.push_back(create_pairs(adjustment_data_divided_semicolon[i]));
    }
}

void enter_divived_data_borrowers(vector<vector<string>> &equal_data_borrowers_divided_semicolon, vector<vector<string>> &unequal_data_borrowers_divided_semicolon, vector<vector<string>> &adjustment_data_borrowers_divided_semicolon,
                                  vector<vector<string>> equal_data, vector<vector<string>> unequal_data, vector<vector<string>> adjustment_data)
{
    for (int i = 0; i < equal_data.size(); ++i)
    {
        equal_data_borrowers_divided_semicolon.push_back(divider(equal_data[i][2], ';'));
    }

    for (int i = 0; i < unequal_data.size(); ++i)
    {
        unequal_data_borrowers_divided_semicolon.push_back(divider(unequal_data[i][2], ';'));
    }

    for (int i = 0; i < adjustment_data.size(); ++i)
    {
        adjustment_data_borrowers_divided_semicolon.push_back(divider(adjustment_data[i][2], ';'));
    }
}

void create_borroweras_count_pair(vector<vector<pair<string, double>>> &borrowers_count_equally1, vector<vector<pair<string, double>>> &borrowers_count_unequally1, vector<vector<pair<string, double>>> &borrowers_count_adjustment,
                                  vector<vector<string>> equal_data_borrowers_divided_semicolon, vector<vector<string>> unequal_data_borrowers_divided_semicolon, vector<vector<string>> adjustment_data_borrowers_divided_semicolon)
{

    for (int i = 0; i < equal_data_borrowers_divided_semicolon.size(); i++)
    {
        borrowers_count_equally1.push_back(create_pairs(equal_data_borrowers_divided_semicolon[i]));
    }

    for (int i = 0; i < unequal_data_borrowers_divided_semicolon.size(); i++)
    {
        borrowers_count_unequally1.push_back(create_pairs(unequal_data_borrowers_divided_semicolon[i]));
    }

    for (int i = 0; i < adjustment_data_borrowers_divided_semicolon.size(); i++)
    {
        borrowers_count_adjustment.push_back(create_pairs(adjustment_data_borrowers_divided_semicolon[i]));
    }
}

double adding_money_to_struct(vector<person> &names_data, vector<pair<string, double>> payers)
{
    double total_money = first_value;
    for (int i = 0; i < payers.size(); i++)
    {
        for (int j = 0; j < names_data.size(); j++)
        {
            if (payers[i].first == names_data[j].name)
            {
                names_data[j].output_money += payers[i].second;
                total_money += payers[i].second;
            }
        }
    }
    return total_money;
}

void Distribute_all(vector<person> &names_data, double total_money)
{
    double person_money = first_value;
    person_money = floor((total_money / names_data.size()) * Two_decimal_places_maker) / Two_decimal_places_maker;
    for (int i = 0; i < names_data.size() - 1; i++)
    {
        names_data[i].input_money += person_money;
    }
    names_data[names_data.size() - 1].input_money += total_money - ((names_data.size() - 1) * person_money);
}

void Distribute_borrowers(vector<person> &names_data, vector<pair<string, double>> borrowers_count_equally1, double total_money)
{
    double person_money = first_value;
    person_money = floor((total_money / borrowers_count_equally1.size()) * Two_decimal_places_maker) / Two_decimal_places_maker;
    for (int i = 0; i < borrowers_count_equally1.size() - 1; i++)
    {
        for (int j = 0; j < names_data.size(); j++)
        {
            if (borrowers_count_equally1[i].first == names_data[j].name)
            {
                names_data[j].input_money += person_money;
            }
        }
    }
    for (int i = 0; i < names_data.size(); i++)
    {
        if (borrowers_count_equally1[borrowers_count_equally1.size() - 1].first == names_data[i].name)
        {
            names_data[i].input_money += total_money - ((borrowers_count_equally1.size() - 1) * person_money);
        }
    }
}

void equallly_type(vector<person> &names_data, vector<vector<pair<string, double>>> &payers_count_equally1, vector<vector<pair<string, double>>> borrowers_count_equally1, vector<vector<string>> equal_data)
{
    double total_money;
    for (int i = 0; i < payers_count_equally1.size(); i++)
    {
        total_money = adding_money_to_struct(names_data, payers_count_equally1[i]);
        if (equal_data[i][2] == " ")
        {
            Distribute_all(names_data, total_money);
        }
        else
        {
            Distribute_borrowers(names_data, borrowers_count_equally1[i], total_money);
        }
    }
}

void Distribute_unequally(vector<pair<string, double>> &borrowers_count_unequally, vector<person> &names_data)
{
    for (int i = 0; i < borrowers_count_unequally.size(); i++)
    {
        for (int j = 0; j < names_data.size(); j++)
        {
            if (borrowers_count_unequally[i].first == names_data[j].name)
            {
                names_data[j].input_money += borrowers_count_unequally[i].second;
                break;
            }
        }
    }
}

void unequally_type(vector<person> &names_data, vector<vector<pair<string, double>>> &payers_count_unequally, vector<vector<pair<string, double>>> borrowers_count_unequally)
{
    for (int i = 0; i < payers_count_unequally.size(); i++)
    {
        adding_money_to_struct(names_data, payers_count_unequally[i]);
        Distribute_unequally(borrowers_count_unequally[i], names_data);
    }
}

void Distribute_all_adjustment(vector<person> &names_data, vector<pair<string, double>> borrowers_count_adjustment, double total_money)
{
    double person_money = first_value;
    person_money = floor((total_money / names_data.size()) * Two_decimal_places_maker) / Two_decimal_places_maker;
    for (int i = 0; i < names_data.size(); i++)
    {
        if (borrowers_count_adjustment[borrowers_count_adjustment.size() - 1].first == names_data[i].name)
        {
            continue;
        }
        names_data[i].input_money += person_money;
    }
    total_money -= (person_money * (names_data.size() - 1));

    for (int j = 0; j < names_data.size(); j++)
    {
        if (borrowers_count_adjustment[borrowers_count_adjustment.size() - 1].first == names_data[j].name)
        {
            names_data[j].input_money += total_money;
            break;
        }
    }
}

void adjustment_type(vector<vector<pair<string, double>>> &payers_count_adjustment, vector<person> &names_data, vector<vector<pair<string, double>>> borrowers_count_adjustment)
{
    double total_money = 0.0;
    for (int i = 0; i < borrowers_count_adjustment.size(); i++)
    {

        total_money = adding_money_to_struct(names_data, payers_count_adjustment[i]);

        Distribute_unequally(borrowers_count_adjustment[i], names_data);

        for (int j = 0; j < borrowers_count_adjustment[i].size(); j++)
        {
            total_money -= borrowers_count_adjustment[i][j].second;
        }

        Distribute_all_adjustment(names_data, borrowers_count_adjustment[i], total_money);
    }
}

void calculate_People_financial_balance(vector<person> &names_data)
{
    for (int i = 0; i < names_data.size(); i++)
    {
        names_data[i].Property = names_data[i].output_money - names_data[i].input_money;
    }
}

void bubble_Sort(vector<person> &names_data)
{
    bool swapped;
    int n = names_data.size();
    do
    {
        swapped = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (names_data[i].Property > names_data[i + 1].Property)
            {
                swap(names_data[i], names_data[i + 1]);

                swapped = true;
            }
            else if (names_data[i].Property == names_data[i + 1].Property)
            {
                if (names_data[i].name > names_data[i + 1].name)
                {
                    swap(names_data[i], names_data[i + 1]);
                }
            }
        }
        if (!swapped)
            break;
    } while (swapped);
}

void giving_Momey_to_members(vector<person> &names_data, vector<pair<string, double>> &from_somone, vector<pair<string, double>> &to_another)
{
    for (int i = 0; i < names_data.size(); i++)
    {
        if (names_data[i].Property < first_value)
        {
            from_somone.push_back(make_pair(names_data[i].name, names_data[i].Property));
        }
        else
        {
            to_another.push_back(make_pair(names_data[i].name, names_data[i].Property));
        }
    }
}

void solving(vector<pair<string, double>> &from_somone, vector<pair<string, double>> &to_another, vector<Result> &final_result)
{

    for (int i = 0; i < from_somone.size(); i++)
    {
        if (from_somone[i].second == first_value)
            continue;

        for (int j = to_another.size() - 1; j >= 0; j--)
        {
            if (from_somone[i].second == first_value)
                break;

            if (to_another[j].second == first_value)
                continue;
            double temp = from_somone[i].second + to_another[j].second;
            if (temp > 0)
            {
                Result new_result;
                new_result.money = to_another[j].second - temp;
                from_somone[i].second = first_value;
                to_another[j].second = temp;
                new_result.from_someone = from_somone[i].first;
                new_result.to_another_one = to_another[j].first;
                final_result.push_back(new_result);
            }
            else
            {
                Result new_result;
                new_result.money = to_another[j].second;
                from_somone[i].second = temp;
                to_another[j].second = first_value;
                new_result.from_someone = from_somone[i].first;
                new_result.to_another_one = to_another[j].first;
                final_result.push_back(new_result);
            }
        }
    }
}

void bubble_sort_for_result(vector<Result> &final_result)
{
    bool swapped;
    int n = final_result.size();
    do
    {
        swapped = false;
        for (int i = n - 1; i > 0; i--)
        {
            if (final_result[i].money > final_result[i - 1].money)
            {
                swap(final_result[i], final_result[i - 1]);

                swapped = true;
            }
        }
        for (int i = 0; i < n - 1; i++)
        {
            if (final_result[i].money == final_result[i + 1].money)
            {
                if (final_result[i].from_someone > final_result[i + 1].from_someone)
                {
                    swap(final_result[i], final_result[i + 1]);
                    swapped = true;
                }
                else if (final_result[i].from_someone == final_result[i + 1].from_someone)
                {
                    if (final_result[i].to_another_one > final_result[i + 1].to_another_one)
                    {
                        swap(final_result[i], final_result[i + 1]);
                        swapped = true;
                    }
                }
            }
        }
        if (!swapped)
            break;
    } while (swapped);
}

void print_finally(vector<Result> &final_result)
{
    for (int i = 0; i < final_result.size(); i++)
    {
        cout << final_result[i].from_someone << " -> " << final_result[i].to_another_one << ": " << final_result[i].money << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error\n";
        return 0;
    }

    string path_of_names_file = argv[1];

    vector<string> data_of_names_file = read_file(path_of_names_file);

    vector<person> names_data = make_struct(data_of_names_file);

    string path_of_expenses_file = argv[2];

    vector<string> data_of_expenses_file = read_file(path_of_expenses_file);

    vector<vector<string>> all_data = recognize_all_data_divided(data_of_expenses_file);

    vector<vector<string>> equal_data, unequal_data, adjustment_data;

    recognize_expenses(all_data, equal_data, unequal_data, adjustment_data);

    vector<vector<string>> equal_data_divided_semicolon, unequal_data_divided_semicolon, adjustment_data_divided_semicolon;

    enter_divided_data_semicolon_in_vectorofvecttor(equal_data, unequal_data, adjustment_data, equal_data_divided_semicolon, unequal_data_divided_semicolon, adjustment_data_divided_semicolon);

    vector<vector<pair<string, double>>> payers_count_equally1, payers_count_unequally1, payers_count_adjustment;

    create_payers_count_pair(payers_count_equally1, payers_count_unequally1, payers_count_adjustment, equal_data_divided_semicolon, unequal_data_divided_semicolon, adjustment_data_divided_semicolon);

    vector<vector<string>> equal_data_borrowers_divided_semicolon, unequal_data_borrowers_divided_semicolon, adjustment_data_borrowers_divided_semicolon;

    enter_divived_data_borrowers(equal_data_borrowers_divided_semicolon, unequal_data_borrowers_divided_semicolon, adjustment_data_borrowers_divided_semicolon, equal_data, unequal_data, adjustment_data);

    vector<vector<pair<string, double>>> borrowers_count_equally1, borrowers_count_unequally1, borrowers_count_adjustment;

    create_borroweras_count_pair(borrowers_count_equally1, borrowers_count_unequally1, borrowers_count_adjustment, equal_data_borrowers_divided_semicolon, unequal_data_borrowers_divided_semicolon, adjustment_data_borrowers_divided_semicolon);
    equallly_type(names_data, payers_count_equally1, borrowers_count_equally1, equal_data);
    unequally_type(names_data, payers_count_unequally1, borrowers_count_unequally1);
    adjustment_type(payers_count_adjustment, names_data, borrowers_count_adjustment);
    calculate_People_financial_balance(names_data);
    bubble_Sort(names_data);

    vector<Result> final_result;
    vector<pair<string, double>> from_somone;
    vector<pair<string, double>> to_another;
    
    giving_Momey_to_members(names_data, from_somone, to_another);
    solving(from_somone, to_another, final_result);
    bubble_sort_for_result(final_result);
    print_finally(final_result);
}