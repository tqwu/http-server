# HTTP Server
This server creates, listens, and accepts connections from clients that arrive on the specified port. The server will then process the bytes sent by the clients using the HTTP protocol.

## Build/Clean
Build/clean this program using the Makefile included in the asgn2 folder and these following instructions:

    $ make
    $ make all
    $ make clean

## Running
Run this program with the following command:

    $ ./httpserver <port number>

## Files included
    httpserver.c     : source file for HTTP server
    connection {h,c} : header/source file for accepting, processing, and closing connections
    parse {h,c}      : header/source file for parsing HTTP requests
    request {h,c}    : header/source file for processing a GET request
    status {h,c}     : header/source file for sending and setting status codes
    types {h,c}      : header/source file for struct definitions and functions
