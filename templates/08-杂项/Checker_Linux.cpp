#!/bin/bash
while true; do
    ./gen > test.in
    ./my < test.in > test.out
    ./brute < test.in > test.ans
    if ! diff -wB test.out test.ans; then
        break
    fi
done

# 加权限（一次就行） chmod +x gen my brute run.sh
# 运行 ./run.sh