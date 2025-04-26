# AVL Tree and Hash Table Application

This C program implements an application that uses an AVL tree and a hash table to efficiently index words found in a text file. The AVL tree is used to maintain a balanced order of words for fast retrieval and sorting, while the hash table provides fast access to word frequencies.

## Features

*   **Data Loading**: Reads text data from a specified input file (`input.txt`).
*   **AVL Tree Operations**:
    *   **Creation**: Builds an AVL tree by inserting words from the input file.
    *   **Insertion**: Inserts new words or updates the frequency of existing words.
    *   **Deletion**: Deletes words from the AVL tree.
    *   **Display**: Prints the words and their frequencies using an in-order traversal.
*   **Hash Table Operations**:
    *   **Creation**: Creates a hash table and inserts words and their frequencies from the AVL tree.
    *   **Insertion**: Inserts new words or updates the frequency of existing words.
    *   **Deletion**: Deletes words from the hash table.
    *   **Search**: Searches for a word in the hash table and retrieves its frequency.
*   **Word Count Statistics**: Provides statistics such as the total number of unique words, the most frequent word, and words repeated more than a specified threshold.
*   **Menu-Driven Interface**: Provides a simple menu for users to select operations.

## Data Structures

*   **`node` (TNode)**: Represents a node in the AVL tree.
    *   `element`: Stores the word.
    *   `left`: Pointer to the left child.
    *   `right`: Pointer to the right child.
    *   `frequency`: Stores the frequency of the word.
    *   `height`: Stores the height of the node.

*   **`HashNode`**: Represents a node in the hash table.
    *   `element`: Stores the word.
    *   `frequency`: Stores the frequency of the word.
    *   `next`: Pointer to the next node in the case of a collision (chaining).

*   **`HashTable`**: Represents the hash table.
    *   `table`: An array of `HashNode` pointers, where each element represents a bucket in the hash table.

## Algorithms

*   **AVL Tree Operations**:
    *   **Insertion**: Implements AVL tree insertion with rotations (RSR, LSR, LRDR, RLDR) to maintain balance.
    *   **Deletion**: Implements AVL tree deletion with balance adjustments after deletion.
*   **Hash Table Operations**:
    *   **Hashing**: Uses a hash function (`hashFunction`) to compute the index for each word in the hash table.
    *   **Collision Handling**: Implements collision handling using chaining (linked lists).

## File Formats

*   **Input File (`input.txt`):** Contains the text data from which words are extracted.

## Usage

1.  **Compile the Program**:

    ```bash
    gcc main.c -o word_indexer
    ```

2.  **Run the Program**:

    ```bash
    ./word_indexer
    ```

3.  **Interact with the Menu**: Follow the prompts to load data, perform operations, and display results.

## Menu Options

1.  Load data from the file.
2.  Create the AVL tree.
3.  Insert a word to the AVL tree.
4.  Delete a word from the AVL tree.
5.  Print the words as sorted in the AVL tree.
6.  Create the Hash Table.
7.  Insert a word to the Hash table.
8.  Delete a word from the hash table.
9.  Search for a word in the hash table and print its frequency.
10. Print words statistics.
11. Exit the application.

## Code Structure

*   **Includes**:
    *   `<stdio.h>`: For standard input/output functions.
    *   `<ctype.h>`: For character handling functions (e.g., `tolower`).
    *   `<stdlib.h>`: For memory allocation functions (e.g., `malloc`, `free`).
    *   `<string.h>`: For string manipulation functions (e.g., `strdup`, `strcasecmp`).

*   **Global Definitions**:
    *   `TABLE_SIZE`: The size of the hash table.

*   **Data Structure Definitions**:
    *   `struct node` (TNode): AVL tree node structure.
    *   `struct HashNode`: Hash table node structure.
    *   `struct HashTable`: Hash table structure.

*   **AVL Tree Functions**:
    *   `createNode()`: Creates a new AVL tree node.
    *   `makeEmpty()`: Empties the AVL tree by freeing all nodes.
    *   `find()`: Searches for a word in the AVL tree.
    *   `findMin()`: Finds the minimum element in the AVL tree.
    *   `max()`: Returns the maximum of two integers.
    *   `getHeight()`: Returns the height of an AVL tree node.
    *   `RSR()`: Performs a right single rotation.
    *   `LSR()`: Performs a left single rotation.
    *   `LRDR()`: Performs a left-right double rotation.
    *   `RLDR()`: Performs a right-left double rotation.
    *   `insert()`: Inserts a word into the AVL tree.
    *   `printInOrder()`: Prints the AVL tree using in-order traversal.
    *   `printPreOrder()`: Prints the AVL tree using pre-order traversal.
    *   `printPostOrder()`: Prints the AVL tree using post-order traversal.
    *   `loadTextFromFile()`: Loads text from the file, extracts valid words.
    *   `insertWordsFromFileText()`: Inserts words from file text into the AVL tree.
    *   `deleteNode()`: Deletes a node from the AVL tree.

*   **Hash Table Functions**:
    *   `createHashTable()`: Creates a new hash table.
    *   `hashFunction()`: Calculates the hash value for a given word.
    *   `insertToHashTable()`: Inserts a word into the hash table.
    *   `searchHashTable()`: Searches for a word in the hash table.
    *   `deleteFromHashTable()`: Deletes a word from the hash table.
    *   `printHasStatistics()`: Prints statistics about the hash table contents.
    *   `freeHashTable()`: Frees the memory allocated for the hash table.
    *   `insertAVLToHashTable()`: Inserts all words from the AVL tree into the hash table.

*   **`main()` Function**:
    *   Presents the menu and processes user input.
    *   Calls the appropriate functions based on the user's selection.

## Notes

*   The program assumes that the input file (`input.txt`) exists in the same directory as the executable.
*   Error handling is implemented to handle file I/O errors, invalid user inputs, and memory allocation failures.
*   The hash table uses separate chaining to handle collisions.

## Author

*   Amir Rasmi Al-Rashayda
