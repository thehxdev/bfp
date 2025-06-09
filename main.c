#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CMDS_COUNT 8
#define READ_BUFFER_SIZE 1024

enum {
    CMD_INC_DP  = '>',
    CMD_DEC_DP  = '<',
    CMD_INC_VAL = '+',
    CMD_DEC_VAL = '-',
    CMD_OUTPUT  = '.',
    CMD_INPUT   = ',',
    CMD_JUMP_F  = '[',
    CMD_JUMP_B  = ']',
};

void usage(void);
void process_file(const char *path, size_t *results);

int main(int argc, char *argv[]) {
    int i;
    char **files;
    size_t results[UCHAR_MAX] = {0};
    const char cmds[CMDS_COUNT] = {
        CMD_INC_DP, CMD_DEC_DP, CMD_INC_VAL, CMD_DEC_VAL,
        CMD_OUTPUT, CMD_INPUT, CMD_JUMP_F, CMD_JUMP_B
    };

    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    argv++;
    argc--;
    files = argv;

    while (argc--)
        process_file(*(argv++), results);

    for (i = 0; i < CMDS_COUNT; i++)
        printf("%c => %zu\n", cmds[i], results[cmds[i]]);

    return EXIT_SUCCESS;
}

void usage(void) {
    const char msg[] = "BrainFuck token profiler\nUsage:\n    bfp <list of files>";
    fprintf(stderr, "%s\n", msg);
}

void process_file(const char *path, size_t *results) {
    FILE *fp = fopen(path, "rb");
    if (!fp)
        return;
    size_t nread, i;
    char buffer[READ_BUFFER_SIZE] = {0};
#ifdef UNIQUE_SEQ
    char prev, curr;
#endif
    while ((nread = fread(buffer, sizeof(char), READ_BUFFER_SIZE, fp)) > 0) {
#ifdef UNIQUE_SEQ
        for (i = 1; i < nread; i++) {
            prev = buffer[i-1];
            curr = buffer[i];
            if (curr != prev)
                results[curr] += 1;
        }
#else
        for (i = 0; i < nread; i++)
            results[buffer[i]] += 1;
#endif
    }
    fclose(fp);
}
