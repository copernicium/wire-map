#!/bin/bash

for test in ./bin/tests/*; do
    $test --gtest_color=yes --gtest_catch_exceptions=0
done
