#define KHI 0;
#define GWD 1;
#define UET 2;
#define LHE 3;
#define ISB 4;
#define SKD 6;
#include <queue>
#include <string>
#include "Dijkstra.h"
using namespace std;

struct flight{string name;int priority;};

vector<vector<int>> actual_airport_distances =
    {//K,    G,      Q,      L,     I,      P,      S
    {0,     488,    5955,   1022,   0,      0,      0},//K
    {488,   0,      719,    0,      0,      0,      0},//G
    {5955,  719,    0,      727,    0,      599,    0},//Q
    {1022,  0,      727,    0,      264,    0,      0},//L
    {0,     0,      0,      264,    0,      0,      294},//I
    {0,     0,      599,    0,      0,      0,      247}, //P
    {0,     0,      0,      0,      294,    247,    0} //S
    };


vector<vector<int>> airport_distances =
{//  K,G,Q,L,I,P,S
    {0,     488,    5955,   1022,   0,      0,      0},//K
    {488,   0,      719,    0,      0,      0,      0},//G
    {5955,  719,    0,      727,    0,      599,    0},//Q
    {1022,  0,      727,    0,      264,    0,      0},//L
    {0,     0,      0,      264,    0,      0,      294},//I
    {0,     0,      599,    0,      0,      0,      247}, //P
    {0,     0,      0,      0,      294,    247,    0} //S
};

string aircraft_types[] = {"Normal Passenger Aircraft","Government Aircraft", "Medical Aircraft"};

priority_queue<flight> landing_queue;
priority_queue<flight> takeoff_queue;

bool airportStatus = true;
string reason = "Unspecified";

void runway_manager();
void landing_manager();
void takeoff_manager();
void flights_manager();
void airport_manager();
void airport_status();
void printQueue(priority_queue<flight> q);

void main()
{
    cout <<  "WELCOME TO THE AIR TRAFFIC CONTROL TOWER OF JINNAH INTERNATIONAL AIRPORT (KHI)\n\n";
    while (1)
    {
        cout << "\n\nSelect your desired function:\n1. Runway Management\n2. Flights Management\n3. Airport Management\n4. Airport Status Board\n0. Exit\n";
        int response;
        cin >> response;
        switch (response)
        {
        case 0:
            cout << "\nSYSTEM SHUTDOWN INITIATED";
            exit(0);
            break;
        case 1:
            runway_manager();
            break;
        case 2:
            flights_manager();
            break;
        case 3:
            airport_manager();
            break;
        case 4:
            airport_status();
            break;
        default:
            cout << "\nINVALID RESPONSE, ABORTING";
            break;
        }
    }
}
void runway_manager()
{
    cout << "1. Landing Strip Management\n2. TakeOff Strip Management\n";
    int response;
    cin >> response;
    switch (response)
    {
    case 1:
        landing_manager();
        break;
    case 2:
        takeoff_manager();
        break;
    }
}
void landing_manager()
{
    cout << "1. Request Landing\n2. Land next Aircraft\n3. Display Pending Requests\n";
    int response;
    cin >> response;
    switch (response)
    {
    case 1:
        {
            string name;
            int priority;
            cout << "Enter name of Aircraft/Flight: ";
            cin >> name;
            cout << "Enter priority status of Aircraft/Flight (1. Normal, 2. Government/Diplomatic, 3. Medical Emergency): ";
            cin >> priority;
            flight f;
            f.name = name;
            f.priority = priority;
            landing_queue.push(f);
            break;
        }
    case 2:
        if (airportStatus)
        {
            if (!landing_queue.empty())
            {
                cout << landing_queue.top().name << " has now landed!\n";
                landing_queue.pop();
            }
            else
            {
                cout << "No Planes awaiting landing!\n";
            }
        }
        else
        {
            cout << "Landing Denied due to " << reason << " \n";
        }
        break;
    case 3:
        cout << landing_queue.size() << " planes are currently awaiting landing\n";
        printQueue(landing_queue);
        break;
    default:
        cout<<"INVALID RESPONSE";
        break;
    }
}
void takeoff_manager()
{
    cout << "1. Request TakeOff\n2. TakeOff next Aircraft\n3. Display Pending Requests\n";
    int response;
    cin >> response;
    switch (response)
    {
    case 1:
        {
            string name;
            int priority;
            cout << "Enter name of Aircraft/Flight: ";
            cin >> name;
            cout << "Enter priority status of Aircraft/Flight (1. Normal, 2. Government/Diplomatic, 3. Medical Emergency): ";
            cin >> priority;
            flight f;
            f.name = name;
            f.priority = priority;
            takeoff_queue.push(f);
            break;
        }
    case 2:
        if (airportStatus)
        {
            if (!takeoff_queue.empty())
            {
                cout << takeoff_queue.top().name << " just took off!\n";
                takeoff_queue.pop();
            }
            else
            {
                cout << "No Planes awaiting takeoff!\n";
            }
        }
        else
        {
            cout << "TakeOff Denied due to " << reason << " \n";
        }
        break;
    case 3:
        cout << takeoff_queue.size() << " planes are currently awaiting takeoff\n";
        printQueue(takeoff_queue);
        break;
    default:
        cout<<"INVALID RESPONSE";
        break;
    }
}
void flights_manager()
{
    int departure, destination;
    cout << "\nWELCOME TO FLIGHT PLAN GENERATOR";
    cout << "\nEnter departure location: (1. KHI, 2. GWD, 3. UET, 4. LHE, 5. ISB, 6. PEW, 7. SKD)";
    cin >> departure;
    cout << "Enter destination location: (1. KHI, 2. GWD, 3. UET, 4. LHE, 5. ISB, 6. PEW, 7. SKD)";
    cin >> destination;
    if(airport_distances[destination-1] != vector<int>{0,0,0,0,0,0,0})
        dijkstra(airport_distances,departure-1,destination-1);
    else
    {
        int least_distance_index = 0;
        int least_distance = INT_MAX;
        for (int i=0; i < 6; i++)
        {
            if(actual_airport_distances[destination-1][i] != 0 && actual_airport_distances[destination-1][i] < least_distance && i != departure-1)
            {
                least_distance = actual_airport_distances[destination-1][i];
                least_distance_index = i;
            }
        }
        
        cout << "\nYour destination airport is currently shutdown due to harsh weather. \nYou shall drop your passengers off at "<< airport_names[least_distance_index] << " which is the nearest to your destination, from which a shuttle should be arranged for the passengers by the airline.";
        cout << "\nYour flight plan is as follows:\n";
        dijkstra(airport_distances,departure-1,least_distance_index);
    }
}
void airport_manager()
{
    cout << "\nWelcome to Airports management console";
    cout << "\n1. ShutDown self\n2. Reopen Self\n3. Shutdown others\n4. Reopen others\n";
    int choice ;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "Specify reason: ";
        cin >> reason;
        airportStatus = false;
        cout << "Airport shut down successfully";
        break;
    case 2:
        airportStatus = true;
        cout << "Airport reopen successfully";
        break;
    case 3:
        {
            cout << "Specify Airport: ( 1. GWD, 2. UET, 3. LHE, 4. ISB, 5. PEW, 6. SKD)\n";
            int selection;
            cin >> selection;
            airport_distances[selection] = vector<int>{0,0,0,0,0,0,0};
            airport_distances[0][selection]=0;
            airport_distances[1][selection]=0;
            airport_distances[2][selection]=0;
            airport_distances[3][selection]=0;
            airport_distances[4][selection]=0;
            airport_distances[5][selection]=0;
            airport_distances[6][selection]=0;
            cout << "Successfully shutdown";
            break;
        }
    case 4:
        {
            cout << "Specify Airport: (1. GWD, 2. UET, 3. LHE, 4. ISB, 5. PEW, 6. SKD)\n";
            int selection;
            cin >> selection;
            airport_distances[selection] = actual_airport_distances[selection];
            airport_distances[0][selection]=actual_airport_distances[0][selection];
            airport_distances[1][selection]=actual_airport_distances[1][selection];
            airport_distances[2][selection]=actual_airport_distances[2][selection];
            airport_distances[3][selection]=actual_airport_distances[3][selection];
            airport_distances[4][selection]=actual_airport_distances[4][selection];
            airport_distances[5][selection]=actual_airport_distances[5][selection];
            airport_distances[6][selection]=actual_airport_distances[6][selection];
            cout << "Successfully reopen";
            break;
        }
    }
}
void airport_status()
{
    if(airportStatus)
    {
        cout << landing_queue.size() << " planes are currently awaiting landing\n";
        printQueue(landing_queue);
        cout << "\n" << takeoff_queue.size() << " planes are currently awaiting takeoff\n";
        printQueue(takeoff_queue);
    }
    else
    {
        cout << "Airport is currently down due to "<<reason;
    }
}
bool operator<(const flight& a, const flight& b) {
    return a.priority < b.priority;
}
void printQueue(priority_queue<flight> q)
{
    int i=1;
    while (!q.empty())
    {
        cout <<i << ". " << q.top().name << "\n";
        q.pop();
        i++;
    }
    cout<<endl;
}