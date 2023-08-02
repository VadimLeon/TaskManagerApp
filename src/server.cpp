#include <string>
#include <iostream>
#include "rpc_interface.h"

// Class containing responses to client requests
class RemoteProcedures : public IRemoteProcedures {
public:
    std::string Hello() override {
        std::cout << "Hello" << std::endl;
        return "Hello";
    }

    void Print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

int main() {
    RemoteProcedures remoteProcedures;
    HRESULT hRes; // Result handle

    hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED); // Initializes the com library
    if (FAILED(hRes)) {
        std::cerr << "Error initializing COM library." << std::endl;
        return 1;
    }

    // Registers security and sets security defaults for a process
    hRes = CoInitializeSecurity(
        NULL,                           // The access permissions that a server will use to receive calls
        -1,                             // The count of entries in the asAuthSvc parameter
        NULL,                           // An array of authentication services that a server is willing to use to receive a call
        NULL,                           // This parameter is reserved and must be NULL
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,  // The default authentication level for the process
        RPC_C_IMP_LEVEL_IMPERSONATE,    // The default impersonation level for proxies
        NULL,                           // This list indicates the information for each authentication service that a client can use to call a server
        EOAC_NONE,                      // Additional capabilities of the server
        NULL);                          // This parameter is reserved and must be NULL

    if (FAILED(hRes)) {
        std::cerr << "Error initializing security." << std::endl;
        CoUninitialize();
        return 1;
    }

    // Registers an EXE class object with OLE so other applications can connect to it
    hRes = CoRegisterClassObject(
        __uuidof(RemoteProcedures), // The CLSID to be registered
        &remoteProcedures,          // A pointer to the IUnknown interface on the class object whose availability is being published
        CLSCTX_LOCAL_SERVER,        // The context in which the executable code is to be run
        REGCLS_MULTIPLEUSE,         // Indicates how connections are made to the class object
        NULL,                       // A pointer to a value that identifies the class object registered
        NULL);

    if (FAILED(hRes)) {
        std::cerr << "Error registering class object." << std::endl;
        CoUninitialize();
        return 1;
    }

    std::cout << "Server is running. Press Enter to exit." << std::endl;
    std::cin.get();

    CoRevokeClassObject(hRes);
    CoUninitialize();

    return 0;
}