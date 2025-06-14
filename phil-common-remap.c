#include <linux/input-event-codes.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <linux/input.h>

void print_usage(FILE* stream, const char* program) {
    fprintf(stream,
            "A plugin for Interception Tools with my common remaps.\n"
            "\n"
            "usage: %s [-h | [-c] [-s]]\n"
            "\n"
            "options:\n"
            "   -h      show this message and exit\n"
            "   -c      enable remapping caps lock to escape\n"
            "   -s      enable swapping left alt and left super\n",
            program);
}

int read_event(struct input_event *event) {
    return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

void write_event(const struct input_event *event) {
    if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    int enable_caps_to_esc = 0,
        enable_alt_super_swap = 0;

    for(int opt; (opt = getopt(argc, argv, "hcs")) != -1;) {
        switch(opt) {
            case 'h':
                return print_usage(stdout, argv[0]), EXIT_SUCCESS;
            case 'c':
                enable_caps_to_esc = 1;
                continue;
            case 's':
                enable_alt_super_swap = 1;
                continue;
        }

        return print_usage(stderr, argv[0]), EXIT_FAILURE;
    }

    if(!(enable_caps_to_esc || enable_alt_super_swap)) {
        printf("No modes provided.");
        return EXIT_FAILURE;
    }

    struct input_event input;

    setbuf(stdin, NULL), setbuf(stdout, NULL);
    while(read_event(&input)) {
        if(input.type == EV_MSC && input.code == MSC_SCAN)
            continue;

        if(input.type != EV_KEY && input.type != EV_REL &&
           input.type != EV_ABS) {
            write_event(&input);
            continue;
        }

        if(enable_caps_to_esc) {
            if(input.type == EV_KEY && input.code == KEY_CAPSLOCK) {
                input.code = KEY_ESC;
            }
        }
        if(enable_alt_super_swap) {
            if(input.type == EV_KEY && input.code == KEY_LEFTALT) {
                input.code = KEY_LEFTMETA;
            } else if(input.type == EV_KEY && input.code == KEY_LEFTMETA) {
                input.code = KEY_LEFTMETA;
            }
        }
        write_event(&input);
    }
}
