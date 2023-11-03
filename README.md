# linkedListServer

Companion client app for [linkedListClient](https://github.com/JohnWSweeney/linkedListClient).

## ChangeLog
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