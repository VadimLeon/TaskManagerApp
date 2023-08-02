## Create client-server applications using RPC (Remote Procedure Call) protocol.

### These should be the simple console applications:

1) client part can sends the following **commands**: "`hello`" and "`print [x]`" (where "`[x]`" is parameter with some text message).
2) server part can receive the commands from client and process them the following way:
- when the "`hello`" command is received, it should print the "`hello`" string in console.
- when the "`print [x]`" command is received, it should print the "`[x]`" string in console.

### Requirements:

- language: **C++**.
- the programs should be able to run on **Windows system**.
- the "**Remote Procedure Call**" protocol must be used.
- **commentaries** in code.

## How to work with a project

### Compile the IDL file

Open a command prompt and navigate to the folder containing the "rpc_interface.idl" file. Then, run the following command to compile the IDL file and generate necessary files: `midl rpc_interface.idl`
This will generate "rpc_interface.h" and "rpc_interface_i.c" files.

### Compile and Run

Compile both the **server** (`src/server.cpp`) and **client** (`src/client.cpp`) applications using a C++ compiler. 
Then, _run the server application_ **first** and the _client application_ **afterwards**.
