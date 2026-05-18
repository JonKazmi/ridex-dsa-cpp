#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

// ============================================================
//  CONSTANTS
// ============================================================
const int INF = numeric_limits<int>::max();
const int MAX_LOCATIONS = 10;

// ============================================================
//  CITY LOCATIONS
// ============================================================
string locations[MAX_LOCATIONS] = {
    "Airport",        // 0
    "City Center",    // 1
    "University",     // 2
    "Hospital",       // 3
    "Mall",           // 4
    "Train Station",  // 5
    "Park",           // 6
    "Market",         // 7
    "Hotel",          // 8
    "Bus Terminal"    // 9
};

// ============================================================
//  GRAPH (Adjacency Matrix)
//  graph[i][j] = distance between location i and j
//  0 means no direct road
// ============================================================
int graph[MAX_LOCATIONS][MAX_LOCATIONS] = {
    //  0   1   2   3   4   5   6   7   8   9
    {   0,  10,  0,  0,  0, 15,  0,  0,  0,  0 },  // 0 Airport
    {  10,   0,  8,  5,  7,  0,  0,  0,  0,  0 },  // 1 City Center
    {   0,   8,  0,  0,  0,  0,  4,  0,  0,  0 },  // 2 University
    {   0,   5,  0,  0,  6,  0,  0,  3,  0,  0 },  // 3 Hospital
    {   0,   7,  0,  6,  0,  0,  0,  5,  9,  0 },  // 4 Mall
    {  15,   0,  0,  0,  0,  0,  0,  0,  0, 11 },  // 5 Train Station
    {   0,   0,  4,  0,  0,  0,  0,  2,  0,  0 },  // 6 Park
    {   0,   0,  0,  3,  5,  0,  2,  0,  0,  8 },  // 7 Market
    {   0,   0,  0,  0,  9,  0,  0,  0,  0,  6 },  // 8 Hotel
    {   0,   0,  0,  0,  0, 11,  0,  8,  6,  0 }   // 9 Bus Terminal
};

// ============================================================
//  LINKED LIST - Driver Management
// ============================================================
struct Driver {
    int id;
    string name;
    int locationIndex;   // current location
    bool available;
    Driver* next;
};

Driver* driverHead = nullptr;
int driverIdCounter = 1;

void addDriver(string name, int locationIndex) {
    Driver* newDriver = new Driver();
    newDriver->id = driverIdCounter++;
    newDriver->name = name;
    newDriver->locationIndex = locationIndex;
    newDriver->available = true;
    newDriver->next = nullptr;

    if (driverHead == nullptr) {
        driverHead = newDriver;
    } else {
        Driver* temp = driverHead;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newDriver;
    }
    cout << "\n  Driver " << name << " added at " << locations[locationIndex] << "!\n";
}

void showDrivers() {
    if (driverHead == nullptr) {
        cout << "\n  No drivers registered yet.\n";
        return;
    }
    cout << "\n  +----+------------------+------------------+-----------+\n";
    cout << "  | ID | Name             | Location         | Status    |\n";
    cout << "  +----+------------------+------------------+-----------+\n";
    Driver* temp = driverHead;
    while (temp != nullptr) {
        cout << "  | " << temp->id
             << "  | " << temp->name;
        // padding
        for (int i = temp->name.length(); i < 16; i++) cout << " ";
        cout << " | " << locations[temp->locationIndex];
        for (int i = locations[temp->locationIndex].length(); i < 16; i++) cout << " ";
        cout << " | " << (temp->available ? "Available " : "On Ride   ") << "|\n";
        temp = temp->next;
    }
    cout << "  +----+------------------+------------------+-----------+\n";
}

Driver* findAvailableDriver() {
    Driver* temp = driverHead;
    while (temp != nullptr) {
        if (temp->available) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// ============================================================
//  DIJKSTRA'S ALGORITHM
//  Returns shortest distance from src to all nodes
//  Also fills 'parent' array to reconstruct path
// ============================================================
void dijkstra(int src, int dist[], int parent[]) {
    bool visited[MAX_LOCATIONS] = { false };

    for (int i = 0; i < MAX_LOCATIONS; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < MAX_LOCATIONS - 1; count++) {
        // Find unvisited node with minimum distance
        int minDist = INF, u = -1;
        for (int i = 0; i < MAX_LOCATIONS; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = true;

        // Update neighbors
        for (int v = 0; v < MAX_LOCATIONS; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

// Print the shortest path from src to dest using parent array
void printPath(int parent[], int dest) {
    if (parent[dest] == -1) {
        cout << locations[dest];
        return;
    }
    printPath(parent, parent[dest]);
    cout << " -> " << locations[dest];
}

// ============================================================
//  BFS - Find all reachable locations from a source
// ============================================================
void bfs(int src) {
    bool visited[MAX_LOCATIONS] = { false };
    queue<int> q;

    visited[src] = true;
    q.push(src);

    cout << "\n  BFS from " << locations[src] << ": ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << locations[node];

        for (int i = 0; i < MAX_LOCATIONS; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
        if (!q.empty()) cout << " -> ";
    }
    cout << "\n";
}

// ============================================================
//  DFS - Explore city map depth first
// ============================================================
void dfsHelper(int node, bool visited[]) {
    visited[node] = true;
    cout << locations[node];

    for (int i = 0; i < MAX_LOCATIONS; i++) {
        if (graph[node][i] != 0 && !visited[i]) {
            cout << " -> ";
            dfsHelper(i, visited);
        }
    }
}

void dfs(int src) {
    bool visited[MAX_LOCATIONS] = { false };
    cout << "\n  DFS from " << locations[src] << ": ";
    dfsHelper(src, visited);
    cout << "\n";
}

// ============================================================
//  QUEUE - Ride Requests
// ============================================================
struct RideRequest {
    string passengerName;
    int fromLocation;
    int toLocation;
};

queue<RideRequest> rideQueue;

void requestRide(string name, int from, int to) {
    RideRequest r;
    r.passengerName = name;
    r.fromLocation = from;
    r.toLocation = to;
    rideQueue.push(r);
    cout << "\n  Ride request added for " << name << "!\n";
    cout << "  From: " << locations[from] << " -> To: " << locations[to] << "\n";
}

void showRideQueue() {
    if (rideQueue.empty()) {
        cout << "\n  No pending ride requests.\n";
        return;
    }
    queue<RideRequest> temp = rideQueue;
    cout << "\n  Pending Ride Requests:\n";
    cout << "  +------------------+------------------+------------------+\n";
    cout << "  | Passenger        | From             | To               |\n";
    cout << "  +------------------+------------------+------------------+\n";
    while (!temp.empty()) {
        RideRequest r = temp.front();
        temp.pop();
        cout << "  | " << r.passengerName;
        for (int i = r.passengerName.length(); i < 16; i++) cout << " ";
        cout << " | " << locations[r.fromLocation];
        for (int i = locations[r.fromLocation].length(); i < 16; i++) cout << " ";
        cout << " | " << locations[r.toLocation];
        for (int i = locations[r.toLocation].length(); i < 16; i++) cout << " ";
        cout << " |\n";
    }
    cout << "  +------------------+------------------+------------------+\n";
}

// ============================================================
//  STACK - Ride History
// ============================================================
struct RideRecord {
    string passengerName;
    string driverName;
    string fromLocation;
    string toLocation;
    int distance;
    int fare;
};

stack<RideRecord> rideHistory;

void showRideHistory() {
    if (rideHistory.empty()) {
        cout << "\n  No ride history yet.\n";
        return;
    }
    stack<RideRecord> temp = rideHistory;
    cout << "\n  Ride History (Most Recent First):\n";
    cout << "  +------------------+------------------+------------------+------------------+----------+--------+\n";
    cout << "  | Passenger        | Driver           | From             | To               | Dist(km) | Fare   |\n";
    cout << "  +------------------+------------------+------------------+------------------+----------+--------+\n";
    while (!temp.empty()) {
        RideRecord r = temp.top();
        temp.pop();
        cout << "  | " << r.passengerName;
        for (int i = r.passengerName.length(); i < 16; i++) cout << " ";
        cout << " | " << r.driverName;
        for (int i = r.driverName.length(); i < 16; i++) cout << " ";
        cout << " | " << r.fromLocation;
        for (int i = r.fromLocation.length(); i < 16; i++) cout << " ";
        cout << " | " << r.toLocation;
        for (int i = r.toLocation.length(); i < 16; i++) cout << " ";
        cout << " | " << r.distance;
        for (int i = to_string(r.distance).length(); i < 8; i++) cout << " ";
        cout << " | Rs." << r.fare << "\n";
    }
    cout << "  +------------------+------------------+------------------+------------------+----------+--------+\n";
}

// ============================================================
//  PROCESS NEXT RIDE FROM QUEUE
// ============================================================
void processNextRide() {
    if (rideQueue.empty()) {
        cout << "\n  No ride requests in queue!\n";
        return;
    }

    Driver* driver = findAvailableDriver();
    if (driver == nullptr) {
        cout << "\n  No available drivers right now!\n";
        return;
    }

    RideRequest r = rideQueue.front();
    rideQueue.pop();

    cout << "\n  Processing ride for " << r.passengerName << "...\n";
    cout << "  Assigned Driver: " << driver->name << "\n";

    // Dijkstra from driver location to passenger pickup
    int dist1[MAX_LOCATIONS], parent1[MAX_LOCATIONS];
    dijkstra(driver->locationIndex, dist1, parent1);
    cout << "\n  Driver route to passenger (" << locations[driver->locationIndex]
         << " -> " << locations[r.fromLocation] << "):\n  ";
    printPath(parent1, r.fromLocation);
    cout << "\n  Distance: " << dist1[r.fromLocation] << " km\n";

    // Dijkstra from passenger to destination
    int dist2[MAX_LOCATIONS], parent2[MAX_LOCATIONS];
    dijkstra(r.fromLocation, dist2, parent2);

    if (dist2[r.toLocation] == INF) {
        cout << "\n  No path found between these locations!\n";
        return;
    }

    cout << "\n  Ride route (" << locations[r.fromLocation]
         << " -> " << locations[r.toLocation] << "):\n  ";
    printPath(parent2, r.toLocation);
    cout << "\n  Distance: " << dist2[r.toLocation] << " km\n";

    int fare = dist2[r.toLocation] * 20;  // Rs. 20 per km
    cout << "  Fare: Rs. " << fare << "\n";

    // Save to history
    RideRecord record;
    record.passengerName = r.passengerName;
    record.driverName = driver->name;
    record.fromLocation = locations[r.fromLocation];
    record.toLocation = locations[r.toLocation];
    record.distance = dist2[r.toLocation];
    record.fare = fare;
    rideHistory.push(record);

    // Mark driver as busy and move to destination
    driver->available = false;
    driver->locationIndex = r.toLocation;

    cout << "\n  Ride completed and saved to history!\n";
    cout << "  Use option [11] to mark " << driver->name << " as available again.\n";
}

// ============================================================
//  SHOW CITY MAP
// ============================================================
void showCityMap() {
    cout << "\n  City Map (Roads with Distances in km):\n";
    cout << "  ----------------------------------------\n";
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        for (int j = i + 1; j < MAX_LOCATIONS; j++) {
            if (graph[i][j] != 0) {
                cout << "  " << locations[i] << " <--" << graph[i][j] << "km--> " << locations[j] << "\n";
            }
        }
    }
}

// ============================================================
//  SHOW LOCATIONS LIST
// ============================================================
void showLocations() {
    cout << "\n  City Locations:\n";
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        cout << "  [" << i << "] " << locations[i] << "\n";
    }
}

// ============================================================
//  COMPLETE DRIVER
// ============================================================
void completeDriverRide() {
    cout << "\n  Enter Driver ID to mark as available: ";
    int id;
    cin >> id;
    Driver* temp = driverHead;
    while (temp != nullptr) {
        if (temp->id == id) {
            temp->available = true;
            cout << "  Driver " << temp->name << " is now available!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "  Driver not found!\n";
}

// ============================================================
//  MAIN MENU
// ============================================================
void showMenu() {
    cout << "\n  +========================================+\n";
    cout << "  |        RIDE BOOKING SYSTEM             |\n";
    cout << "  +========================================+\n";
    cout << "  | [1] Add Driver                         |\n";
    cout << "  | [2] Show All Drivers                   |\n";
    cout << "  | [3] Request a Ride                     |\n";
    cout << "  | [4] Show Ride Queue                    |\n";
    cout << "  | [5] Process Next Ride                  |\n";
    cout << "  | [6] Show Ride History                  |\n";
    cout << "  | [7] Show City Map                      |\n";
    cout << "  | [8] BFS Traversal                      |\n";
    cout << "  | [9] DFS Traversal                      |\n";
    cout << "  | [10] Find Shortest Path                |\n";
    cout << "  | [11] Mark Driver Available             |\n";
    cout << "  | [0] Exit                               |\n";
    cout << "  +========================================+\n";
    cout << "  Enter choice: ";
}

int main() {
    // Add some default drivers
    addDriver("Ali", 1);       // City Center
    addDriver("Ahmed", 5);     // Train Station
    addDriver("Sara", 3);      // Hospital

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // Add Driver
            string name;
            int loc;
            showLocations();
            cout << "\n  Enter driver name: ";
            getline(cin, name);
            cout << "  Enter location number: ";
            cin >> loc;
            cin.ignore();
            if (loc >= 0 && loc < MAX_LOCATIONS)
                addDriver(name, loc);
            else
                cout << "  Invalid location!\n";

        } else if (choice == 2) {
            // Show Drivers
            showDrivers();

        } else if (choice == 3) {
            // Request Ride
            string name;
            int from, to;
            showLocations();
            cout << "\n  Enter passenger name: ";
            getline(cin, name);
            cout << "  Enter pickup location number: ";
            cin >> from;
            cout << "  Enter destination number: ";
            cin >> to;
            cin.ignore();
            if (from >= 0 && from < MAX_LOCATIONS && to >= 0 && to < MAX_LOCATIONS)
                requestRide(name, from, to);
            else
                cout << "  Invalid location!\n";

        } else if (choice == 4) {
            // Show Queue
            showRideQueue();

        } else if (choice == 5) {
            // Process Next Ride
            processNextRide();

        } else if (choice == 6) {
            // Show History
            showRideHistory();

        } else if (choice == 7) {
            // Show Map
            showCityMap();

        } else if (choice == 8) {
            // BFS
            showLocations();
            cout << "\n  Enter starting location number for BFS: ";
            int src;
            cin >> src;
            cin.ignore();
            if (src >= 0 && src < MAX_LOCATIONS)
                bfs(src);
            else
                cout << "  Invalid location!\n";

        } else if (choice == 9) {
            // DFS
            showLocations();
            cout << "\n  Enter starting location number for DFS: ";
            int src;
            cin >> src;
            cin.ignore();
            if (src >= 0 && src < MAX_LOCATIONS)
                dfs(src);
            else
                cout << "  Invalid location!\n";

        } else if (choice == 10) {
            // Shortest Path
            showLocations();
            cout << "\n  Enter source location number: ";
            int src, dest;
            cin >> src;
            cout << "  Enter destination location number: ";
            cin >> dest;
            cin.ignore();
            if (src >= 0 && src < MAX_LOCATIONS && dest >= 0 && dest < MAX_LOCATIONS) {
                int dist[MAX_LOCATIONS], parent[MAX_LOCATIONS];
                dijkstra(src, dist, parent);
                if (dist[dest] == INF)
                    cout << "\n  No path found!\n";
                else {
                    cout << "\n  Shortest path: ";
                    printPath(parent, dest);
                    cout << "\n  Total distance: " << dist[dest] << " km\n";
                }
            } else {
                cout << "  Invalid location!\n";
            }

        } else if (choice == 11) {
            // Mark driver available
            completeDriverRide();

        } else if (choice == 0) {
            cout << "\n  Thank you for using Ride Booking System!\n\n";

        } else {
            cout << "\n  Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}