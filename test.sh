#!/bin/bash

for test in ./bin/tests/*; do
    $test
done
