#! /bin/bash

cc -o main main.c pass_args.c kbd.c global_args.c utils.c waves.c ui.c -lm
./main