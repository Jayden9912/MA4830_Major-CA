#! /bin/bash

cc -o main main.c pass_args.c kbd.c global_args.c utils.c waves.c display_ui.c -lm -lncurses
