#!/bin/bash

RUNS=10
PC="./pc"
PC2="./pc2"

echo "Measuring $RUNS runs of $PC and $PC2..."
echo

measure_average_runtime() {
    PROGRAM=$1
    TOTAL=0

    echo "Running $PROGRAM..."

    for i in $(seq 1 $RUNS); do
        START=$(date +%s.%N)
        $PROGRAM > /dev/null
        END=$(date +%s.%N)
        RUNTIME=$(echo "$END - $START" | bc)
        echo "  Run $i: $RUNTIME seconds"
        TOTAL=$(echo "$TOTAL + $RUNTIME" | bc)
    done

    AVG=$(echo "scale=4; $TOTAL / $RUNS" | bc)
    echo "Average runtime of $PROGRAM: $AVG seconds"
    echo
}

measure_average_runtime $PC
measure_average_runtime $PC2
