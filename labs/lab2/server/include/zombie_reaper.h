#ifndef ZOMBIE_REAPER_H
#define ZOMBIE_REAPER_H

#include <signal.h>
#include <sys/wait.h>

void zombie_process_reaper(int signal);

#endif // ZOMBIE_REAPER_H