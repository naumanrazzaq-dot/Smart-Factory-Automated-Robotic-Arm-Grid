#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class IndustrialMachine {
protected:
    string machineSerial;
    bool isActive;

public:
    static int operationalUnits;

    IndustrialMachine(string serial) : machineSerial(serial), isActive(true) {
        operationalUnits++;
    }

    virtual ~IndustrialMachine() {
        operationalUnits--;
    }

    virtual void performDiagnostics() = 0;
};

int IndustrialMachine::operationalUnits = 0;

class HydraulicArmModule : virtual public IndustrialMachine {
protected:
    double hydraulicPressurePSI;

public:
    HydraulicArmModule(string serial, double pressure) : IndustrialMachine(serial), hydraulicPressurePSI(pressure) {}

    void checkHydraulics() {
        cout << "Hydraulic system [" << machineSerial << "] pressure: " << hydraulicPressurePSI << " PSI." << endl;
    }
};

class WeldingLaserModule : virtual public IndustrialMachine {
protected:
    double laserPowerKilowatts;

public:
    WeldingLaserModule(string serial, double power) : IndustrialMachine(serial), laserPowerKilowatts(power) {}

    void checkLaser() {
        cout << "Welding laser [" << machineSerial << "] output: " << laserPowerKilowatts << " kW." << endl;
    }
};

class RoboticWeldingCell : public HydraulicArmModule, public WeldingLaserModule {
private:
    int componentsWeldedToday;

public:
    RoboticWeldingCell(string serial, double pressure, double power, int welded)
        : IndustrialMachine(serial),
          HydraulicArmModule(serial, pressure),
          WeldingLaserModule(serial, power),
          componentsWeldedToday(welded) {}

    ~RoboticWeldingCell() {
        cout << "Welding cell " << machineSerial << " powered down safely." << endl;
    }

    void performDiagnostics() override {
        cout << "\n--- Robotic Welding Cell Report: " << machineSerial << " ---" << endl;
        checkHydraulics();
        checkLaser();
        cout << "Components Welded Today: " << componentsWeldedToday << endl;
        cout << "Operational Status: Normal" << endl;
    }
};

int main() {
    IndustrialMachine* cell = new RoboticWeldingCell("ROBO-CELL-05", 3200.5, 4.5, 1420);

    cell->performDiagnostics();

    cout << "\nActive Industrial Units: " << IndustrialMachine::operationalUnits << endl;

    delete cell;

    cout << "Active Units After Shutdown: " << IndustrialMachine::operationalUnits << endl;

    return 0;
}
