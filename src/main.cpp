#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>

using namespace std;

struct Route {

    string network;
    int prefixLength;
    string nextHop;
    bool isActive;
    int priority;
};

int totalPackets = 0;
int successfulLookups = 0;
int droppedPackets = 0;

string ipToBinary(string ip) {

    stringstream ss(ip);

    string octet;

    string binaryIP = "";

    while(getline(ss, octet, '.')) {

        int num = atoi(octet.c_str());

        binaryIP += bitset<8>(num).to_string();
    }

    return binaryIP;
}

string longestPrefixMatch(vector<Route>& routingTable,
                          string destinationIP) {

    string binaryIP = ipToBinary(destinationIP);

    int maxPrefix = -1;

    int bestPriority = -1;

    string selectedRoute = "No Route Found";

    string matchedNetwork = "";

    for(int i = 0; i < routingTable.size(); i++) {

        Route route = routingTable[i];

        if(route.isActive == false) {

            continue;
        }

        string routeBinary = ipToBinary(route.network);

        string ipPrefix =
        binaryIP.substr(0, route.prefixLength);

        string routePrefix =
        routeBinary.substr(0, route.prefixLength);

        if(ipPrefix == routePrefix) {

            if(route.prefixLength > maxPrefix ||

              (route.prefixLength == maxPrefix &&
               route.priority > bestPriority)) {

                maxPrefix = route.prefixLength;

                bestPriority = route.priority;

                selectedRoute = route.nextHop;

                stringstream temp;

                temp << route.network
                     << "/"
                     << route.prefixLength;

                matchedNetwork = temp.str();
            }
        }
    }

    cout << "\n=====================================\n";
    cout << "            PACKET TRACE\n";
    cout << "=====================================\n";

    cout << "Destination IP : "
         << destinationIP << endl;

    if(selectedRoute != "No Route Found") {

        cout << "Matched Route  : "
             << matchedNetwork << endl;

        cout << "Next Hop       : "
             << selectedRoute << endl;

        cout << "Routing Status : SUCCESS\n";
    }

    else {

        cout << "Routing Status : FAILED\n";

        cout << "Reason         : "
             << "No matching active route found\n";

        cout << "Packet Dropped\n";
    }

    cout << "=====================================\n";

    return selectedRoute;
}

void displayRoutingTable(vector<Route>& routingTable) {

    cout << "\n============================================================\n";

    cout << "NETWORK\t\tPREFIX\tNEXT HOP\tSTATUS\t\tPRIORITY\n";

    cout << "============================================================\n";

    for(int i = 0; i < routingTable.size(); i++) {

        Route route = routingTable[i];

        cout << route.network
             << "\t/"
             << route.prefixLength
             << "\t"
             << route.nextHop
             << "\t\t"
             << (route.isActive ? "ACTIVE" : "DISABLED")
             << "\t"
             << route.priority
             << endl;
    }
}

void addRoute(vector<Route>& routingTable) {

    Route newRoute;

    cout << "\nEnter Network Address : ";
    cin >> newRoute.network;

    cout << "Enter Prefix Length  : ";
    cin >> newRoute.prefixLength;

    cout << "Enter Next Hop       : ";
    cin >> newRoute.nextHop;

    cout << "Enter Route Priority : ";
    cin >> newRoute.priority;

    newRoute.isActive = true;

    routingTable.push_back(newRoute);

    cout << "\nRoute added successfully.\n";
}

void deleteRoute(vector<Route>& routingTable) {

    string network;

    int prefix;

    cout << "\nEnter Network Address : ";
    cin >> network;

    cout << "Enter Prefix Length  : ";
    cin >> prefix;

    bool found = false;

    for(int i = 0; i < routingTable.size(); i++) {

        if(routingTable[i].network == network &&
           routingTable[i].prefixLength == prefix) {

            routingTable.erase(routingTable.begin() + i);

            found = true;

            cout << "\nRoute deleted successfully.\n";

            break;
        }
    }

    if(!found) {

        cout << "\nRoute not found.\n";
    }
}

void toggleRouteStatus(vector<Route>& routingTable) {

    string network;

    int prefix;

    cout << "\nEnter Network Address : ";
    cin >> network;

    cout << "Enter Prefix Length  : ";
    cin >> prefix;

    bool found = false;

    for(int i = 0; i < routingTable.size(); i++) {

        if(routingTable[i].network == network &&
           routingTable[i].prefixLength == prefix) {

            routingTable[i].isActive =
            !routingTable[i].isActive;

            found = true;

            cout << "\nRoute status updated.\n";

            break;
        }
    }

    if(!found) {

        cout << "\nRoute not found.\n";
    }
}

void displayStatistics() {

    cout << "\n========== ROUTING STATISTICS ==========\n";

    cout << "Total Packets Processed : "
         << totalPackets << endl;

    cout << "Successful Lookups     : "
         << successfulLookups << endl;

    cout << "Dropped Packets        : "
         << droppedPackets << endl;

    if(totalPackets > 0) {

        double successRate =
        ((double)successfulLookups /
         totalPackets) * 100;

        cout << "Success Rate           : "
             << successRate
             << "%\n";
    }

    cout << "========================================\n";
}

int main() {

    vector<Route> routingTable;

    Route r1;
    r1.network = "192.168.0.0";
    r1.prefixLength = 16;
    r1.nextHop = "Router_A";
    r1.isActive = true;
    r1.priority = 1;

    Route r2;
    r2.network = "192.168.1.0";
    r2.prefixLength = 24;
    r2.nextHop = "Router_B";
    r2.isActive = true;
    r2.priority = 2;

    Route r3;
    r3.network = "10.0.0.0";
    r3.prefixLength = 8;
    r3.nextHop = "Router_C";
    r3.isActive = true;
    r3.priority = 1;

    routingTable.push_back(r1);
    routingTable.push_back(r2);
    routingTable.push_back(r3);

    int choice;

    while(true) {

        cout << "\n=====================================\n";
        cout << "   Intelligent IP Routing Engine\n";
        cout << "=====================================\n";

        cout << "1. Display Routing Table\n";
        cout << "2. Add Route\n";
        cout << "3. Delete Route\n";
        cout << "4. Enable/Disable Route\n";
        cout << "5. Route Packet\n";
        cout << "6. Routing Statistics\n";
        cout << "7. Exit\n";

        cout << "\nEnter Choice : ";

        cin >> choice;

        if(choice == 1) {

            displayRoutingTable(routingTable);
        }

        else if(choice == 2) {

            addRoute(routingTable);
        }

        else if(choice == 3) {

            deleteRoute(routingTable);
        }

        else if(choice == 4) {

            toggleRouteStatus(routingTable);
        }

        else if(choice == 5) {

            string destinationIP;

            cout << "\nEnter Destination IP : ";

            cin >> destinationIP;

            string result =
            longestPrefixMatch(routingTable,
                               destinationIP);

            totalPackets++;

            if(result == "No Route Found") {

                droppedPackets++;
            }

            else {

                successfulLookups++;
            }
        }

        else if(choice == 6) {

            displayStatistics();
        }

        else if(choice == 7) {

            cout << "\nExiting Routing Engine...\n";

            break;
        }

        else {

            cout << "\nInvalid choice.\n";
        }
    }

    return 0;
}