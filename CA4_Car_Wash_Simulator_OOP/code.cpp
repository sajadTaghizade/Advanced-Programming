#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

const char comma_delimintor = ',';
const char space_delimintor = ' ';
const string pass_time = "pass_time";
const string car_arrival = "car_arrival";
const string get_worker_status = "get_worker_status";
const string get_car_status = "get_car_status";
const string get_stage_status = "get_satge_status";
const int start_time = 0;

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

class Worker
{
public:
    Worker(int _id, int _Stage_id, int _Time_to_finish)
    {
        id = _id;
        Stage_id = _Stage_id;
        Time_to_finish = _Time_to_finish;
        status = 0;
    }

    int get_id() { return id; }
    int get_car_id() { return car_id; }
    int get_Time_to_finish() { return Time_to_finish; }
    int get_Stage_id() { return Stage_id; }
    bool get_status() { return status; }
    void set_status(bool _status) { status = _status; }
    void set_car_id(int _car_id) { car_id = _car_id; }

private:
    int id;
    int Stage_id;
    int Time_to_finish;
    int car_id;
    bool status;
};

class Stage
{
public:
    Stage(int _id, int _price)
    {
        id = _id;
        price = _price;
    }

    int get_id() { return id; }

    void add_worker(int worker_id)
    {
        workers_id.push_back(worker_id);
    }
    void give_worker(Worker worker)
    {
    }

    vector<int> workers_id;

private:
    int id;
    int price;
};

class Car
{

public:
    Car(int _id, vector<string> command)
    {
        id = _id;
        index = 0;
        for (int i = 1; i < command.size(); i++)
        {
            car_stages.push_back(stoi(command[i]));
        }
    }
    int get_id() { return id; }

    int get_stage_id()
    {
        return car_stages[index];
    }

private:
    int id;
    int index;
    vector<int> car_stages;
};

class Car_wash
{
public:
    Car_wash(string path_of_stage_file, string path_of_worker_file)
    {
        vector<string> data_of_stage_file = read_file(path_of_stage_file);
        store_stages(data_of_stage_file);
        vector<string> data_of_worker_file = read_file(path_of_worker_file);
        store_workers(data_of_worker_file);
        add_worker();
        sort_workers();
    }
    void store_stages(vector<string> data_of_stage_file)
    {
        for (int i = 1; i < data_of_stage_file.size(); i++)
        {
            vector<string> temp = divider(data_of_stage_file[i], comma_delimintor);
            Stage *stage = new Stage(stoi(temp[0]), stoi(temp[1]));
            stages.push_back(stage);
        }
    }
    void store_workers(vector<string> data_of_worker_file)
    {
        for (int i = 1; i < data_of_worker_file.size(); i++)
        {
            vector<string> temp = divider(data_of_worker_file[i], comma_delimintor);
            Worker *worker = new Worker(stoi(temp[0]), stoi(temp[1]), stoi(temp[2]));
            workers.push_back(worker);
        }
    }
    int pass_time(int time_to_pass)
    {
    }
    int car_arrival(vector<string> command)
    {
        int id = cars.size() + 1;
        Car *car = new Car(id, command);
        cars.push_back(car);
        int new_id = car->get_stage_id();
        Stage *stage = get_stage_by_id(new_id);
        bool check = false;
        for (int i = 0; i < stage->workers_id.size(); i++)
        {
            Worker *worker = get_worker_by_id(stage->workers_id[i]);
            if (worker->get_status() == 0)
            {
                worker->set_car_id(car->get_id());
                worker->set_status(1);
                check = true;
                cout << start_time << ' ' << "Car" << ' ' << car->get_id() << ": Arrived -> Stage " << stage->get_id() << endl;
                break;
            }
        }
        if (!check)
        {
            cout << start_time << ' ' << "Car" << ' ' << car->get_id() << ": Arrived -> Queue " << stage->get_id() << endl;
        }
    }

    int get_stage_status(int stage_id)
    {
    }
    int get_worker_status(int worker_id)
    {

        Worker *worker = get_worker_by_id(worker_id);

        if (worker->get_status() == 0)
        {
            cout << "Idle" << endl;
        }
        else
        {
            cout << "Working: " << worker->get_car_id() << endl;
        }
    }

    int get_car_status(int car_id)
    {
        Car *car = get_car_by_id(car_id);
    }

private:
    Stage *get_stage_by_id(int new_id)
    {
        for (int i = 0; i < stages.size(); i++)
        {
            if (stages[i]->get_id() == new_id)
            {
                return stages[i];
            }
        }
    }

    Worker *get_worker_by_id(int worker_id)
    {

        for (int i = 0; i < workers.size(); i++)
        {
            if (workers[i]->get_id() == worker_id)
            {
                return workers[i];
            }
        }
    }

    Car *get_car_by_id(int car_id)
    {

        for (int i = 0; i < workers.size(); i++)
        {
            if (cars[i]->get_id() == car_id)
            {
                return cars[i];
            }
        }
    }

    vector<Stage *> stages;
    vector<Worker *> workers;
    vector<Car *> cars;

    void sort_workers()
    {
        for (int i = 0; i < stages.size(); i++)
        {
            vector<int> newid = stages[i]->workers_id;

            for (int j = 0; j < newid.size(); j++)
            {
                for (int k = 0; k < newid.size(); k++)
                {
                    if (get_worker_by_id(newid[j])->get_Time_to_finish() < get_worker_by_id(newid[k])->get_Time_to_finish())
                    {
                        swap((newid[j]), (newid[k]));
                    }
                    else if (get_worker_by_id(newid[j])->get_Time_to_finish() == get_worker_by_id(newid[k])->get_Time_to_finish())
                    {
                        if (newid[j] < newid[k])
                        {
                            swap((newid[j]), (newid[k]));
                        }
                    }
                }
            }
            stages[i]->workers_id = newid;
        }
    }
    void add_worker()
    {
        for (int i = 0; i < workers.size(); i++)
        {
            int stage_id = workers[i]->get_Stage_id();
            Stage *stage = get_stage_by_id(stage_id);
            stage->add_worker(workers[i]->get_id());
        }
    }
};

void get_input(Car_wash &car_wash)
{
    string line;
    vector<string> command;
    while (getline(cin, line))
    {
        command = divider(line, space_delimintor);
        if (command[0] == pass_time)
        {
            int number_of_time_units_to_pass;
            cin >> number_of_time_units_to_pass;
            car_wash.pass_time(number_of_time_units_to_pass);
        }
        else if (command[0] == car_arrival)
        {
            car_wash.car_arrival(command);
        }
        else if (command[0] == get_stage_status)
        {
            car_wash.get_stage_status(stoi(command[1]));
        }
        else if (command[0] == get_worker_status)
        {
            car_wash.get_worker_status(stoi(command[1]));
        }
        else if (command[0] == get_car_status)
        {
            car_wash.get_car_status(stoi(command[1]));
        }
    }
}

int main(int argc, char *argv[])
{
    Car_wash car_wash(argv[1], argv[2]);
    get_input(car_wash);
    return 0;
}