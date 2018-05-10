# Telnet menu  

A telnet server displaying basic navigation menu in terminal. Written as an assignment for network programming course at MIM UW, spring semester 2017-18.  
  
## Features  
The menu is implemented as a C++ library, and is highly customizable. Basic features include:  
* choosing between any number of options displayed as strings  
* displaying last selected option below the menu  
* nesting menus  
* using designated menu options to go back  
* implementing any custom logic based on selected options  

Usage of menu library is demonstrated in 'src/main.cpp'.  

## Implementation  

Library is separated into classes, each class responsible for a single purpose:  
* `server::listener` is responsible for listening on a TCP socket and accepting incoming connections  
* `server::connection` is an object responsible for managing single incoming connection  
* `server::nvt` is a class reflecting a state of telnet Network Virtual Terminal (NVT) shared between client and server  
* `server::menu` represents a menu, with its options and current state, that can be displayed via NVT  
* `server::io` is a helper class that allows to translate high level concepts to byte strings and send / receive them via TCP socket  
Some of the classes also use custom exceptions.  

Client-server interaction begins when a client connects to the server via telnet. If the server is free, it creates a connection that immediately spawns `server::nvt` instance. The nvt negotiates all options necessary for displaying a menu on the terminal, and proceeds to display its content - an instance of `server::menu`. All further client-server communications are hidden inside `server::nvt::interact()` that represents a single request-response cycle (typically user pressing a key and receiving updated menu). Any logic and behaviour can be acheived by using hooks provided by menu and loops, as demonstrated in `src/main.cpp`.  
