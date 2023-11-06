# linkedListServer

A console server app running an interactive demo for linked lists and their applications. Basically, this is my [linkedListDemo](https://github.com/JohnWSweeney/linkedListDemo) project running on top of a tcp server that receives commands for the demos via a companion [client app](https://github.com/JohnWSweeney/linkedListClient). 

## Starting the Server
The app opens a console window on startup. Enter the *command* keywords separated by a space. Commands are case-sensitive. 

Start the server by entering:
>*start portNum*

where *portNum* is the port on your computer where the server will send/receive demo commands.

Once the server is running, run the companion client app to connect to the server and send demo commands. 

## ChangeLog
v0.0.13
- Added queue class and demo.
- Removed cmd struct member "output".

v0.0.12
- Updated populateCmd in commands cpp to allow only one server thread.
- Updated Session::run to allow only one demo at a time.
- Added stop server condition to startMenu.

v0.0.11
- Added stack class and demo.

v0.0.10
- Added circular doubly linked list class `cdlist` and demo.

v0.0.9
- Added circular singly linked list class `cslist` and demo.

v0.0.8
- Added doubly linked list class `dlist` and demo.

v0.0.7
- Added random class, updated sList header/cpp and singly linked list demo.
- Updated convertBufferToCmd in session cpp to copy all JSON fields to command struct fields.

v0.0.6
- Working draft of singly linked list demo running on server, controlled by JSON commands from client.

v0.0.5
- Added convertBufferToCmd to session cpp to streamline buffer conversion to command struct, via JSON.
- Updated session cpp to end session by client command. 

v0.0.4
- Updated startMenu function, threads, server, session header/cpps to give all access to cmd struct.

v0.0.3
- Added commands header/cpp and updated startMenu, threads header/cpp to accept user commands to start server.

v0.0.2
- Merged Session::run and list functions.
- Added while loop to Session::run to hold connction open.

v0.0.1
- Added basic json receive functionality session cpp.

v0.0.0
- Initial commit.
	- Basic server/session functionality.