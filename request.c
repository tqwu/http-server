#include "request.h"

static int closeFile(int fd) {
    if (close(fd) == -1) {
        statusCode status = INTERNAL_SERVER_ERROR;
        sendStatus(status);
        return -1;
    }
    return 0;
}

int requestGET(RequestLine *rl) {

    // If version is not supported, send 505
    char versionnum[4];
    strncpy(versionnum, rl->version + 5, 3);
    versionnum[3] = '\0';
    if ((strcmp(versionnum, "1.1") != 0)) {
        statusCode status = HTTP_VERSION_NOT_SUPPORTED;
        sendStatus(status);
        return -1;
    }

    int filenamelen = strlen(rl->uri) - 1; // Minus the leading slash
    char filename[filenamelen];
    strncpy(filename, rl->uri + 1, filenamelen - 1);
    filename[filenamelen - 1] = '\0';

    // If file doesn't exist, send 404
    int fd = open(filename, O_RDONLY, 0);
    if (fd == -1) {
        statusCode status = NOT_FOUND;
        sendStatus(status);
        return -1;
    }

    // If file is not a regular file, send 403
    struct stat pathStat;
    stat(filename, &pathStat);
    if (S_ISREG(pathStat.st_mode) == 0) {
        if (closeFile(fd) == -1) {
            return -1;
        }
        statusCode status = FORBIDDEN;
        sendStatus(status);
        return -1;
    }

    // If file size cannot be determined, send 500
    int filesizeStat = getFileSize(filename);
    if (filesizeStat == -1) {
        if (closeFile(fd) == -1) {
            return -1;
        }
        statusCode status = INTERNAL_SERVER_ERROR;
        sendStatus(status);
        return -1;
    }

    //////////////////////////////////
    // Begin processing GET request //
    //////////////////////////////////

    // Send OK status message
    statusCode status = OK;
    sendStatus(status);

    // Send Content-Type header
    char contentLength[64];
    sprintf(contentLength, "Content Length: %d\r\n\r\n", filesizeStat);
    writeToSocket(contentLength, strlen(contentLength));

    // Send the contents of the file
    char buf[BUFSIZE];
    int bytesRead = 0;
    int filelen = 0;
    // Taken from Professor Kerry Veenstra's CSE 130 Midterm Review Lecture 11
    do {
        bytesRead = read(fd, buf, BUFSIZE);

        // If read fails, send 403
        if (bytesRead == -1) {
            if (closeFile(fd) == -1) {
                return -1;
            }
            statusCode status = FORBIDDEN;
            sendStatus(status);
            return -1;
        } else if (bytesRead > 0) {
            filelen += bytesRead;
            int bytesWritten = 0;
            do {
                int bytes = writeToSocket(buf + bytesWritten, bytesRead - bytesWritten);

                // If write fails, send 500
                if (bytes == -1) {
                    if (closeFile(fd) == -1) {
                        return -1;
                    }
                    statusCode status = INTERNAL_SERVER_ERROR;
                    sendStatus(status);
                    return -1;
                }
                bytesWritten += bytes;
            } while (bytesWritten < bytesRead);
        }
    } while (bytesRead > 0);

    // If bytes read doesn't match file size determined by sys/stat, send 500
    if (filelen != filesizeStat) {
        if (closeFile(fd) == -1) {
            return -1;
        }
        statusCode status = INTERNAL_SERVER_ERROR;
        sendStatus(status);
        return -1;
    }

    // Close the file
    if (closeFile(fd) == -1) {
        return -1;
    }
    return 0;
}
