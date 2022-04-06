#!/bin/zsh

qemu-system-x86_64 -serial mon:stdio -machine accel=tcg -smp "" -drive format=raw,file=$1
# qemu-system-i386 -serial mon:stdio -machine accel=tcg -smp "" -drive format=raw,file=./build/hello-x86-qemu

# qemu-system-x86_64 \
#     -s -S \
#     -serial none \
#     -nographic \
#     -drive format=raw,file=$1 &
# pid=$!
#
# gdb \
#     -ex "target remote localhost:1234" \
#     -ex "set confirm off"
#
# kill -9 $!!
