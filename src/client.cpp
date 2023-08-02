#include <iostream>
#include "rpc_interface.h"
#include "server.cpp"

int main() {
    HRESULT hRes; // Result handle

    hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED); // Initializes the com library
    if (FAILED(hRes)) {
        std::cerr << "Error initializing COM library." << std::endl;
        return 1;
    }

    IRemoteProcedures *remoteProcedures;

    // Creates a single class object associated with the specified CLSID
    hRes = CoCreateInstance(
        __uuidof(RemoteProcedures),                  // CLSID associated with the data and code that will be used to create the object
        NULL,                                        // The object is not created as part of the aggregate
        CLSCTX_LOCAL_SERVER,                         // The context in which the code that controls the newly created object will be executed
        __uuidof(IRemoteProcedures),                 // A reference to an interface identifier for interacting with the object
        reinterpret_cast<void **>(&remoteProcedures) // Pointer variable address
    );

    // Check of create a single class object associated with the specified CLSID
    if (FAILED(hRes)) {
        std::cerr << "Error creating instance." << std::endl;
        CoUninitialize(); // Closes the COM library
        return 1;
    }

    std::string command;
    std::cout << "Enter a command (hello, print [text] or exit):\n";

    while (true) {
        // Reading commands from the console
        std::getline(std::cin, command);

        // Closing the client application
        if(command == "exit") { break; }

        // Command processing
        if (command.length() > 5 && command.substr(0, 6) == "print ") {
            remoteProcedures->Print(command.substr(6));
        } else if (command == "hello" || command == "Hello") {
            remoteProcedures->Hello();
        } else {
            std::cerr << "Invalid command." << std::endl;
        }

        remoteProcedures->Release();
    }

    CoUninitialize(); // Closes the COM library

    return 0;
}
