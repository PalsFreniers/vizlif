#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int c, char **v) {
        NOB_GO_REBUILD_URSELF(c, v);

        Nob_Procs procs = {0};

        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, "gcc");
        // cflags
        nob_cmd_append(&cmd, "-Wall", "-Wextra", "-ggdb", "-pedantic");
        // executable
        nob_cmd_append(&cmd, "-o", "vizlif");
        // sources
        nob_cmd_append(&cmd, "vizlif.c");
        // libs
        nob_cmd_append(&cmd, "-lm");
        nob_da_append(&procs, nob_cmd_run_async(cmd));

        cmd.count = 0;
        nob_cmd_append(&cmd, "gcc");
        // cflags
        nob_cmd_append(&cmd, "-Wall", "-Wextra", "-ggdb", "-pedantic");
        // executable
        nob_cmd_append(&cmd, "-o", "img2raw");
        // sources
        nob_cmd_append(&cmd, "img2raw.c");
        // libs
        nob_cmd_append(&cmd, "-lm");
        nob_da_append(&procs, nob_cmd_run_async(cmd));
        
        if(!nob_procs_wait(procs)) return 1;

//         cmd.count = 0;
//         nob_cmd_append(&cmd, "./main");
//         for(int i = 1; i < c; i++) nob_cmd_append(&cmd, v[i]);
//         if(!nob_cmd_run_sync(cmd)) return 1;
        return 0;
}
