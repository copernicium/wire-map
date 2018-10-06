#!/bin/bash

for test in ./bin/tests/*; do
    $test --gtest_color=yes
done
