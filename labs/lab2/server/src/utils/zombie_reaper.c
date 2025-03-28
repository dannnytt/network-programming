#include "zombie_reaper.h"

void zombie_process_reaper(int signal) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {}
}