#include "types.h"

void freeRequestLine(RequestLine *rl) {
    free(rl->method);
    free(rl->uri);
    free(rl->version);
    free(rl);
}

void freeResponse(Response *r) {
    free(r->msg);
    free(r);
}
