#include <iostream> 
#include <string> 

using namespace std; 

struct OperationsSummary{ 
    int devices, online, criticalSignals, overloadedNodes, openIncidents, criticalIncidents; 
    double availability;   
    bool recovered; 
};

OperationsSummary readSummary(){
    OperationsSummary summary;
    cout << "Enter number of devices: ";
    cin >> summary.devices;

    cout << "Enter number of online devices: ";
    cin >> summary.online;

    cout << "Enter critical signals: ";
    cin >> summary.criticalSignals;

    cout << "Enter overloaded nodes: ";
    cin >> summary.overloadedNodes;

    cout << "Enter open incidents: ";
    cin >> summary.openIncidents;

    cout << "Enter critical incidents: ";
    cin >> summary.criticalIncidents;

    cout << "Enter availability (%): ";
    cin >> summary.availability;

    cout << "Was system recovered? (1 - yes, 0 - no): ";
    cin >> summary.recovered;

    return summary;
}

bool validateSummary(OperationsSummary summary){
     if (summary.devices < 0)
    {
        return false;
    }

    if (summary.online < 0)
    {
        return false;
    }

    if (summary.online > summary.devices)
    {
        return false;
    }

    if (summary.criticalSignals < 0)
    {
        return false;
    }

    if (summary.overloadedNodes < 0)
    {
        return false;
    }

    if (summary.openIncidents < 0)
    {
        return false;
    }

    if (summary.criticalIncidents < 0)
    {
        return false;
    }

    if (summary.availability < 0 || summary.availability > 100)
    {
        return false;
    }

    return true;
}

double calculateOnlinePercent(OperationsSummary summary){ 
    if (summary.devices == 0)
    {
        return 0;
    }

    return (double)summary.online / summary.devices * 100;
}

int calculateHealthScore(OperationsSummary summary){ 
    int score = 100;
    int offlineDevices = summary.devices - summary.online;
    score -= offlineDevices * 5;
    score -= summary.criticalSignals * 5;
    score -= summary.overloadedNodes * 7;
    score -= summary.openIncidents * 2;
    score -= summary.criticalIncidents * 10;

    if (score < 0)
    {
        score = 0;
    }

    if (score > 100)
    {
        score = 100;
    }

    return score;
}

string classifyPlatform(int score){
     if (score >= 80)
    {
        return "STABLE";
    }
    else if (score >= 50)
    {
        return "DEGRADED";
    }
    else
    {
        return "CRITICAL";
    }
}

void printRisks(OperationsSummary summary){ 
    cout << "Risks:\n";

    int offlineDevices = summary.devices - summary.online;

    if (offlineDevices > 0)
    {
        cout << "- " << offlineDevices << " devices are offline\n";
    }

    if (summary.criticalSignals > 0)
    {
        cout << "- Critical signals detected\n";
    }

    if (summary.overloadedNodes > 0)
    {
        cout << "- Overloaded nodes detected\n";
    }

    if (summary.openIncidents > 0)
    {
        cout << "- Open incidents detected\n";
    }

    if (summary.criticalIncidents > 0)
    {
        cout << "- Critical incidents detected\n";
    }
}

void printReport(OperationsSummary summary, double onlinePercent, int healthScore, string status){ 
    cout << "Devices: " << summary.devices << endl;
    cout << "Online devices: " << summary.online << endl;
    cout << "Online percentage: " << onlinePercent << "%" << endl;
    cout << "Availability: " << summary.availability << "%" << endl;
    cout << "Health score: " << healthScore << endl;
    cout << "Status: " << status << endl;

    printRisks(summary);
}

int main(){ 
    int choice;
    do
    {
        cout << "\n===== =====\n";
        cout << "1. Create report\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;


        if (choice == 1)
        {
            OperationsSummary summary;

            summary = readSummary();


            if (validateSummary(summary) == false)
            {
                cout << "Invalid data!\n";
                continue;
            }


            double onlinePercent;

            int healthScore;
            string status;


            onlinePercent = calculateOnlinePercent(summary);

            healthScore = calculateHealthScore(summary);

            status = classifyPlatform(healthScore);


            printReport(
                summary, onlinePercent,healthScore,status
            );
        }

    } while (choice != 0);


    cout << "Program finished\n";
}
