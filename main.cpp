#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <chrono>
#include <vector>
#include <string>
#include <cmath>
#include "functions.cpp"

using namespace std;

string customer::customer_file = "consumer.csv"; // id, name, password, fine, record, discount, cars_rented
string customer::employee_file = "employee.csv"; // id, name, password, fine, record, discount, cars_rented
string car::file = "car.csv"; // id, name, model, color, condition, is_booked, due_date, damage, renter_id, renter_name

int customer::customer_avg_record = 5;
int customer::number_of_customers = 0;
int customer::customer_id_count = 0;

int customer::employee_avg_record = 5;
int customer::number_of_employees = 0;
int customer::employee_id_count = 0;

int manager::manager_id_count = 0;
int car::car_id_count = 0;
int car::cost_per_day = 1000;
int car::fine_per_day = 1200;
int car::damage_cost = 200;

int main()
{
    if (!fileExists(customer::customer_file)) {
        ofstream file(customer::customer_file);
    }
    if (!fileExists(customer::employee_file)) {
        ofstream file(customer::employee_file);
    }
    if (!fileExists(car::file)) {
        ofstream file(car::file);
    }

    try
    {
        vector<vector<string>> init_data = readCSV(customer::customer_file);

        if (init_data.size()!=0) customer::customer_avg_record = 0;
        for (int i = 0; i < init_data.size(); i++) {
            string id = init_data[i][0];
            for (int j=0;j<id.length()-1;j++) id[j] = id[j+1];
            id.pop_back();
            customer::customer_id_count = max(customer::customer_id_count, stoi(id));
            customer::customer_avg_record += stoi(init_data[i][4]);
            customer::number_of_customers++;
        }
        
        if (customer::number_of_customers != 0)
        {
            customer::customer_id_count++;
            customer::customer_avg_record /= customer::number_of_customers;
        }

        init_data = readCSV(customer::employee_file);
        if (init_data.size()!=0) customer::employee_avg_record = 0;
        for (int i = 0; i < init_data.size(); i++) {
            string id = init_data[i][0];
            for (int j=0;j<id.length()-1;j++) id[j] = id[j+1];
            id.pop_back();
            customer::employee_id_count = max(customer::employee_id_count, stoi(id));
            customer::employee_avg_record += stoi(init_data[i][4]);
            customer::number_of_employees++;
        }
        if (customer::number_of_employees != 0)
        {
            customer::employee_id_count++;
            customer::employee_avg_record /= customer::number_of_employees;
        }

        init_data = readCSV(car::file);
        for (int i = 0; i < init_data.size(); i++) {
            string id = init_data[i][0];
            for (int j=0;j<id.length()-3;j++) id[j] = id[j+3];
            id.pop_back();
            car::car_id_count = max(car::car_id_count, stoi(id));
        }
        if (init_data.size()!=0) car::car_id_count++;
    }
    catch(const std::exception& e)
    {
        // std::cerr 
    }
    
    vector<vector<string>> managers;
    managers.push_back({"m0","manager", "123456"});
    manager::manager_id_count++;

    std::cout<<endl<<"-------------------------- Welcome to the Car Rental System --------------------------"<<endl<<endl;
    // std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;

    int finish = 0;
    int sign_up_finish = 0;
    int login_finish = 0;
    int login_customer_finish = 0;

    while (!finish)
    {
        std::cout<<"1. Login\n2. Sign up\n3. Exit\nPlease enter your choice: ";
        int choice;
        cin>>choice;
        std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;
        
        switch (choice)
        {
        case 1: // Login
            login_finish = 0;
            while (!login_finish)
            {
                std::cout<<"1. Login as a customer\n2. Login as an employee\n3. Login as a manager\n4. Go back\n";
                std::cout<<"Please enter your choice: ";
                int subchoice;
                cin>>subchoice;
                std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;

                switch (subchoice)
                {
                case 1: // Login as a customer
                    login_as_customer();
                    break;

                case 2:
                    login_as_employee();
                    break;

                case 3:
                    login_as_manager(managers);
                    break;

                case 4:
                    login_finish = 1;
                    break;
                
                default:
                    std::cout<<"Invalid choice. Please enter a valid choice\n"<<endl;
                    std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;
                    break;
                }
            }
            break;

        case 2: // Sign up
            sign_up_finish = 0;
            while (!sign_up_finish)
            {
                std::cout<<"1. Signup as a customer\n2. Signup as an employee\n3. Go back\n";
                std::cout<<"Please enter your choice: ";
                int subchoice;
                cin>>subchoice;
                std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;
                
                switch (subchoice)
                {
                case 1: // Signup as a customer
                    signup_customer();
                    break;

                case 2:  // Signup as an employee
                    signup_employee();
                    break;

                case 3:
                    sign_up_finish = 1;
                    break;
                
                default:
                    std::cout<<"Invalid choice. Please enter a valid choice\n";
                    std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;
                    break;
                }
            }

            break;

        case 3:
            finish = 1;
            break;
        
        default:
            std::cout<<"Invalid choice. Please enter a valid choice\n";
            std::cout<<endl<<"--------------------------------------------------------------------------------------"<<endl<<endl;
            break;
        }
    }
    return 0;
}