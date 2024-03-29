#include "parse.h"

int getFileSize(char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1;
    // FIXME: return 500?
    fprintf(stderr, "Error: Cannot determine size of %s\n", filename);
    exit(1);
}

int parseRequestLine(RequestLine *rl, char *str_request) {

    int match;
    int err;
    regex_t preg;
    regmatch_t pmatch[4];
    size_t nmatch = 4;
    const char *str_regex = "^([a-zA-Z]{1,8}) +(/[a-zA-Z0-9.-]{2,64}) +(HTTP/[0-9].[0-9])";
    err = regcomp(&preg, str_regex, REG_EXTENDED);

    if (err == 0) {
        match = regexec(&preg, str_request, nmatch, pmatch, 0);
        nmatch = preg.re_nsub;
        regfree(&preg);

        // If a REGEX match is found
        if (match == 0) {

            // Allocate memory for each field of RequestLine struct
            rl->method = malloc(pmatch[1].rm_eo - pmatch[1].rm_so + 2);
            rl->uri = malloc(pmatch[2].rm_eo - pmatch[2].rm_so + 2);
            rl->version = malloc(pmatch[3].rm_eo - pmatch[3].rm_so + 2);

            int methodlen = pmatch[1].rm_eo - pmatch[1].rm_so + 1;
            int urilen = pmatch[2].rm_eo - pmatch[2].rm_so + 1;
            int versionlen = pmatch[3].rm_eo - pmatch[3].rm_so + 1;

            strncpy(rl->method, str_request, methodlen);
            rl->method[methodlen] = '\0';

            strncpy(rl->uri, str_request + methodlen, urilen);
            rl->uri[urilen] = '\0';

            strncpy(rl->version, str_request + methodlen + urilen, versionlen);
            rl->version[versionlen] = '\0';

            return 0;
        }

        // If REGEX match was not found, return 1
        else if (match == REG_NOMATCH) {
            statusCode status = BAD_REQUEST;
            sendStatus(status);
            return -1;
        }
    }
    statusCode status = INTERNAL_SERVER_ERROR;
    sendStatus(status);
    return -1;
}
