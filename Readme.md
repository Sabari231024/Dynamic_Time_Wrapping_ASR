# Spoken Digit Recognition using Dynamic Time Warping (DTW)

This project implements a C-based system for recognizing spoken digits (0-9, and 'z' for zero) from audio files. It uses **Dynamic Time Warping (DTW)** as the core algorithm to compare audio sequences and a **Top-K voting mechanism** for classification.

The system first converts raw audio (`.wav`) files into **Mel-frequency Cepstral Coefficient (MFCC)** features. Then, for a given test audio file, it calculates the DTW distance to all training audio files. The final prediction is determined by a majority vote from the 'K' training files with the smallest DTW distances.

## 🚀 Core Concepts

### Dynamic Time Warping (DTW)

Dynamic Time Warping is an algorithm used to measure the similarity between two temporal sequences that may vary in speed or timing. For instance, if two people speak the same word, the duration and pace of their speech might differ. DTW finds the optimal alignment between the two sequences, producing a "distance" score that represents their dissimilarity. A lower score means the sequences are more similar.

### Top-K Voting Rule for Classification

This project uses the DTW distance scores to perform classification with a top-K voting rule. The process is as follows:

1.  For an unknown test sample, calculate its DTW distance to **every** sample in the training dataset.
2.  Select the **top K** training samples that have the shortest distances to the test sample.
3.  The predicted label for the test sample is the most common label (the majority vote) among these K matches. The value of `K` is a variable parameter.

## ⚙️ Project Workflow & Pipeline

The entire process, from raw audio to final prediction, follows these steps:

1.  **Data Preparation**: The audio data is split into training (80%) and testing (20%) sets. The audio files represent spoken digits.
2.  **Feature Extraction**:
      * The provided `extract.sh` script is used to process the `.wav` audio files and extract MFCC features.
      * These features are saved into `.mfcc` files.
      * **Note**: The configuration for feature extraction, specifically the sampling rate, was adjusted for different digit folders (`1`, `4`, `6`, `0`, `z`) to ensure correctness.
3.  **Classification**:
      * A test file's MFCC features are loaded.
      * The program iterates through all training MFCC files, calculating the DTW distance for each pair.
      * These distances are sorted, and the top `K` matches (those with the lowest distance scores) are identified.
      * A voting rule is applied to the labels of these top `K` matches to determine the final predicted digit.
4.  **Evaluation**: The system outputs the top matches for each test file, the predicted label, and the actual label for comparison. The final results are compiled into a `predictionsubmission.csv` file.

## 📂 File Structure and Code

The project is written in **C** and consists of several source files that are compiled together.

  * `main.c`: The main driver program that handles the classification logic, file iteration, and result printing.
  * `dtw.c`: Contains the implementation of the Dynamic Time Warping algorithm.
  * `distance.c`: Implements the distance metric (e.g., Euclidean distance) used between MFCC vectors at each step of the DTW calculation.
  * `readfile.c`: Contains functions for reading and parsing the MFCC feature files.
  * `main2audios.c`: A separate utility to implement DTW for just two specific audio signals, likely for testing and debugging purposes.
  * `extract.sh`: A shell script used for batch feature extraction from audio folders.

## 🛠️ How to Compile and Run

### Prerequisites

  * A C compiler (e.g., `gcc`)
  * A Unix-like environment with a `bash` shell to run the extraction script.

### Step 1: Feature Extraction

Use the provided shell script to extract MFCC features from the raw audio data folders.

```bash
# Usage: ./extract.sh <path_to_audio_folder> <output_feature_folder> mfcc
./extract.sh ~/Speech/Assg3/6-20250824T061519Z-1-001/6 ~/Speech/Assg3/Features/6 mfcc 
```

*This command is an example shown in the project documentation. You will need to run this for all digit folders.*

### Step 2: Compilation

Compile the C source files using `gcc`. The `-lm` flag is required to link the math library.

**To compile the main classification program:**

```bash
gcc main.c dtw.c distance.c readfile.c -o output -lm
```

**To compile the utility for comparing two audio files:**

```bash
gcc main2audios.c dtw.c distance.c readfile.c -o out -lm
```

### Step 3: Execution

Run the compiled classifier program. The program takes one command-line argument: the value of `K` for the voting rule.

```bash
./output 5
```

This command will run the classification using the **top 5** matches for voting.

## 📊 Results and Output

The program provides detailed output for each test file, showing the closest matches from the training data and the final prediction.

### Example Console Output:

```
Top-5 matches for pe_1.mfcc:
ac_1.mfcc:1014.116229
ld_1.mfcc:1043.679446
jj_1.mfcc:1094.210336
ai_1.mfcc:1098.067951
ac_o.mfcc:1112.759539
Actual Label: 1
Predicted Label: 1 (4 votes)
```

### Final Submission File (`predictionsubmission.csv`)

The program generates a CSV file summarizing the results for the entire test set. The format is `test_filename,actual_label,predicted_label`.

**Sample Content:**

```csv
pe_1.mfcc,1,1
pp_o.mfcc,0,0
ng_6.mfcc,6,6
ng_z.mfcc,z,o
mm_4.mfcc,4,0
...
```

As seen in the results, the system performs well but also has some misclassifications (e.g., a spoken 'z' being identified as 'o', and a '4' identified as '0').
