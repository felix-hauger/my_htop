#include "discount_htop.h"

void show_usage(WINDOW *win)
{
    // printf("USAGE: %d\n", getrusage(4476));
    // FILE **statuses;
    DIR *proc;
    struct dirent *dt;
    FILE *status;
    char line[200];

    // struct dirent *current_processus;

    proc = opendir("/proc");

    if (proc == NULL) {
        perror("Error accessing process list\n");
        exit(1);
    }

    while ((dt = readdir(proc)) != NULL) {
        // current_processus = readdir(dt);
        // mvwprintw("%s\n", dt->d_name);
        char path[500];
        snprintf(path, sizeof(path), "/proc/%s/status", dt->d_name);
        
        status = fopen(path, "r");
        if (status != NULL) {
            while (fgets(line, sizeof(line), status)) {
                // printf("Processus: %s\n", line);
                if (my_strncmp(line, "Name:", 5) == 0 || my_strncmp(line, "Pid:", 4) == 0 || my_strncmp(line, "VmSize:", 7) == 0 ||) {
                    // printf("Processus: %s\n", line);
                    // wprintw(win, "%s", line);
                    int length = strlen(line);
                    if (length > 0 && line[length - 1] == '\n') {
                        line[length - 1] = '\0'; // Remove the newline character
                    }
                    wprintw(win, "%s ", line);
                    // while ((c = fgetc(line[])) != EOF) {
                    //     wprintw(win, "%c", c);
                    // }
                    wprintw(win, " | ");
                }
            }
            wprintw(win, "\n");

            fclose(status);
        }            
    }

    closedir(proc);
    wrefresh(win);
};