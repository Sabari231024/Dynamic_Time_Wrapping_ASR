#!/bin/bash

SRC=$1
TGT=$2
CF="./ComputeFeatures"

for SUB in dev train; do
    INPUT_DIR="$SRC/$SUB"
    OUTPUT_DIR="$TGT/${SUB}_mfcc"

    mkdir -p "$OUTPUT_DIR"
    for FILE in "$INPUT_DIR"/*.wav; do
        if [[ -f "$FILE" ]]; then
            BASE=$(basename "$FILE")
            OUT="$OUTPUT_DIR/${BASE%.*}.mfcc"

            echo "EXTRACTING THE FEATURES FROM THE FILE $FILE -> $OUT"
            $CF mfcc.config "$FILE" frameCepstrum+frameDeltaCepstrum "$OUT" 0.06 A
        fi
    done
done

