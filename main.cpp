#include <iostream>
#include "Process.h"
using namespace std;



int main() {
    Process p;
    p.addCitiesToArr();
    p.addNeighbours();
    p.addFlights();
    p.exeCommands();

    return 0;
}
