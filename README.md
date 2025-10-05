# Decision Tree Algorithm

This project is a C++ implementation of a Decision Tree classifier. A decision tree is a supervised learning algorithm used for classification and regression tasks. It works by splitting the dataset into smaller subsets based on feature values, forming a tree structure with decision nodes and leaf nodes.

## Description

This program builds a decision tree from user-provided data. It interactively asks for the number of columns and rows, the data for each cell (as strings), and the class labels (0 for "No" and 1 for "Yes"). It then calculates the entropy and information gain for each feature to determine the best splits and construct the tree. The final output displays the root node and the child nodes of the tree.

This implementation is based on the concepts explained in this article: [Decision Tree for Classification, Entropy, and Information Gain](https://medium.com/codex/decision-tree-for-classification-entropy-and-information-gain-cd9f99a26e0d).

## Features

*   **Handles String Data:** The program accepts string values for all features.
*   **Interactive Input:** It interactively prompts the user for data, making it easy to test with small datasets.
*   **Entropy and Information Gain:** It uses these core concepts of the Decision Tree algorithm to find the optimal splits.
*   **Clear Output:** It displays the constructed tree in a simple, readable format.

## How to Use

1.  **Compile the code:** You will need a C++ compiler (like g++).
    ```bash
    g++ source/Decision_Tree.cpp -o Decision_Tree
    ```
2.  **Run the executable:**
    ```bash
    ./Decision_Tree
    ```
3.  **Provide Input:** The program will then prompt you to enter:
    *   The number of columns (features).
    *   The number of rows (data points).
    *   The value for each cell in your dataset.
    *   The class label for each row (1 for "Yes", 0 for "No").

## Example

Here's an example of how to run the program with a simple dataset.

**Input:**

```
Enter Count Of Column :- 2
Enter Count Of Rows :- 4
Enter 1 Text Column 1 Row Value :- sunny
Enter 1 Text Column 2 Row Value :- sunny
Enter 1 Text Column 3 Row Value :- overcast
Enter 1 Text Column 4 Row Value :- rainy
Enter 2 Text Column 1 Row Value :- hot
Enter 2 Text Column 2 Row Value :- hot
Enter 2 Text Column 3 Row Value :- mild
Enter 2 Text Column 4 Row Value :- cool
Enter 1 Class Value :- 0
Enter 2 Class Value :- 0
Enter 3 Class Value :- 1
Enter 4 Class Value :- 1
```

**Output:**

```
--------------------------Root Node--------------------------

sunny For 2 Column
overcast For Yes
rainy For Yes

--------------------------Child Node--------------------------

hot For No
mild For Yes
cool For Yes
```

## Algorithm

The program implements the core logic of the Decision Tree algorithm:

1.  **Calculate Entropy:** It first calculates the entropy of the entire dataset. Entropy is a measure of impurity or disorder.
2.  **Calculate Information Gain:** For each feature, it calculates the information gain, which is the expected reduction in entropy after splitting on that feature.
3.  **Select Root Node:** The feature with the highest information gain is chosen as the root node of the tree.
4.  **Build Subtrees:** The dataset is then split based on the values of the root node feature, and the process is recursively repeated for each subtree until a stopping criterion is met (e.g., all data points in a node belong to the same class).

For a more detailed explanation of the algorithm, please refer to the article linked in the [Description](#description) section.
