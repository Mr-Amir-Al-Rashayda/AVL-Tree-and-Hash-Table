// Name : Amir Rasmi Al-Rashayda
// ID : 1222596
// Sec : 1

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/***************************************** "Global" *****************************************/

#define TABLE_SIZE 101 // prime
int counterCaseOne = 1;
int counterCaseTwo = 1;
int counterCaseSix = 1;

/***************************************** "Structs Implementations" *****************************************/

typedef struct node
{
    char *element;
    struct node *left;
    struct node *right;
    int frequency;
    int height;
} *TNode;

typedef struct HashNode
{
    char *element;
    int frequency;
    struct HashNode *next;
} HashNode;

// Define the hash table itself
typedef struct HashTable
{
    HashNode *table[TABLE_SIZE];
} HashTable;

/***************************************** "Tree Functions" *****************************************/

TNode createNode(char *element);
TNode makeEmpty(TNode T);
TNode find(char *element, TNode T);
TNode findMin(TNode T);
int max(int rightHeight, int leftHeight);
int getHeight(TNode T);
TNode RSR(TNode T);
TNode LSR(TNode T);
TNode LRDR(TNode T);
TNode RLDR(TNode T);
TNode insert(TNode T, char *element);
void printInOrder(TNode T);
void printPreOrder(TNode T);
void printPostOrder(TNode T);
char *loadTextFromFile(const char *filename, char *fileText);
TNode insertWordsFromFileText(TNode T, char *fileText);
TNode deleteNode(TNode T, char *element);

/***************************************** "Hash Functions" *****************************************/

HashTable *createHashTable();
unsigned int hashFunction(char *word);
void insertToHashTable(HashTable *hashTable, char *word, int frequency);
HashNode *searchHashTable(HashTable *hashTable, char *word);
void deleteFromHashTable(HashTable *hashTable, char *word);
void printHasStatistics(HashTable *hashTable);
void freeHashTable(HashTable *hashTable);
void insertAVLToHashTable(TNode T, HashTable *hashTable);

/***************************************** "_________Main_________" *****************************************/

int main()
{
    TNode T = NULL;
    char *fileText;
    char *element;
    HashTable *hashTable = createHashTable();
    int operation = 0;
    printf("Hello my friend");

    while (operation != 11)
    { // while it's not 11
        printf("\nWhich operation you want to do next sir :\n\n1. Load data from the file.\n2. Create the AVL tree.\n3. Insert a word to the AVL tree.\n4. Delete a word from the AVL tree.\n5. Print the words as sorted in the AVL tree.\n");
        printf("6. Create the Hash Table.\n7. Insert a word to the Hash table.\n8. Delete a word from the hash table.\n9. Search for a word in the hash table and print its frequency.\n10. Print words statistics.\n11. Exit the application. \n");

        int result;
        while (1)
        {
            result = scanf("%d%*c", &operation);
            if (result != 1)
            { // Clear Entered buffer if non-numeric value is entered
                while ((getchar()) != '\n')
                    ;
                printf("Invalid input. Please enter a number.\n");
            }
            else
            { // Break the loop if a valid number is entered
                break;
            }
        }
        switch (operation)
        {
        case 1:
            if (counterCaseOne)
            {
                printf("Loading data from file...\n");
                fileText = loadTextFromFile("input.txt", fileText);
                printf("\n%s \n", fileText);
                counterCaseOne = 0;
            }
            else
                printf("The Data has been already loaded !\n");
            break;
        case 2:
            if (counterCaseTwo)
            {
                if (counterCaseOne)
                    printf("Please Load The Data From The File First (Press One) !\n");
                else
                {
                    T = insertWordsFromFileText(T, fileText);
                    printInOrder(T);
                }
                counterCaseTwo = 0;
            }
            else
                printf("The AVL Tree has been already \n");
            break;
        case 3:
        {
            char word[50];
            printf("Enter the word to insert: ");
            scanf("%49s", word);
            T = insert(T, word);
            break;
        }
        case 4:
        {
            char word[50];
            printf("Enter the word to insert: ");
            scanf("%49s", word);
            deleteNode(T, word);
            break;
        }
        case 5:
            printf("Printing in-order traversal:\n");
            printInOrder(T);
            printf("\n");
            break;
        case 6:
            if (counterCaseSix)
            {
                insertAVLToHashTable(T, hashTable);
                counterCaseSix = 0;
            }
            else
                printf("Can't load Twice !\n");
            break;
        case 7:
        {
            if (counterCaseSix == 0)
            {
                char element[50];
                printf("Enter the word: ");
                scanf("%49s", element);
                insertToHashTable(hashTable, element, 1);
            }
            else
                printf("Load the AVL Tree to the Hash Table first (Case Six)\n");
        }
        break;
        case 8:
        {
            char element[50];
            printf("Enter the word to delete from hash table: ");
            scanf("%49s", element);
            deleteFromHashTable(hashTable, element);
            break;
        }
        case 9:
        {
            char element[50];
            printf("Enter the word to search in the hash table: ");
            scanf("%49s", element);
            HashNode *node = searchHashTable(hashTable, element);
            if (node)
            {
                printf("The word %s does EXIST !\n", node->element);
                printf("Frequency of '%s' is: %d\n", element, node->frequency);
            }
            else
            {
                printf("Word '%s' Does NOT EXIST in hash table.\n", element);
            }
            break;
        }
        case 10:
            if (counterCaseSix == 0)
            {
                printHasStatistics(hashTable);
            }
            else
                printf("Load the AVL Tree to the Hash Table first (Case Six)\n");
            break;
        case 11:
            printf("Exiting...\n");
            free(fileText);           // Free the loaded file text
            T = makeEmpty(T);         // Free all allocated memory for AVL tree
            freeHashTable(hashTable); // Free all allocated memory for hash table
            break;
        default:
            printf("Enter a valid number from the choices\n\n");
            continue;
        }
    }
    return 0;
}

/***************************************** "Tree Functions" *****************************************/

TNode createNode(char *element)
{
    TNode myNode = (TNode)malloc(sizeof(struct node)); // malloc for the creation
    if (myNode == NULL)                                // case didn't malloc
    {
        printf("Out of memory!\n");
        return NULL;
    }
    myNode->element = strdup(element);   // use dup so it doesn't points at the same address and now they are unlinked
    myNode->left = myNode->right = NULL; // initial values ..
    myNode->frequency = 1;               // initialize frequency to 1
    myNode->height = 0;
    return myNode;
}

TNode makeEmpty(TNode T)
{
    if (T != NULL)
    {
        makeEmpty(T->left);
        makeEmpty(T->right);
        free(T->element); // basse case
        free(T);          // baase case
    }
    return NULL; // base case
}

TNode find(char *element, TNode T)
{
    if (T == NULL)
    {
        return NULL; //  not found "base case"
    }
    else if (strcasecmp(element, T->element) < 0)
    {
        return find(element, T->left);
    }
    else if (strcasecmp(element, T->element) > 0)
    {
        return find(element, T->right);
    }
    else
    {
        return T; // found "base case"
    }
}

TNode findMin(TNode T)
{
    if (T == NULL)
    {
        return NULL; // tree is empty "base case"
    }
    else if (T->left == NULL)
    {
        return T; // the minimum element has been found
    }
    else
    {
        return findMin(T->left); // recursive ....
    }
}

int max(int rightHeight, int leftHeight)
{
    if (rightHeight > leftHeight)
    {
        return rightHeight;
    }
    else
    {
        return leftHeight;
    }
}

int getHeight(TNode T)
{
    if (T == NULL) // the cae height -1
    {
        return -1;
    }
    else
    {
        return T->height;
    }
}

TNode RSR(TNode T)
{
    TNode newT = T->left;                                         // let it be point at the left one
    T->left = newT->right;                                        // then let the left original one to be the right of the original left
    newT->right = T;                                              // now the right for the original left points the t itself
    T->height = max(getHeight(T->left), getHeight(T->right)) + 1; // organize the height
    newT->height = max(getHeight(newT->left), T->height) + 1;     // organize the height
    return newT;                                                  // return it as itself
}

TNode LSR(TNode T)
{
    TNode newT = T->right;                                        // let it be point at the right one
    T->right = newT->left;                                        // then let the right original one to be the left of the original right
    newT->left = T;                                               // now the left for the original right points the t itself
    T->height = max(getHeight(T->left), getHeight(T->right)) + 1; // organize the height
    newT->height = max(T->height, getHeight(newT->right)) + 1;    // organize the height
    return newT;                                                  // return it as itself
}

TNode LRDR(TNode T)
{
    T->left = LSR(T->left); // can be done if we make left single rotation for the left
    return RSR(T);          // then return the right single rotation of t
}

TNode RLDR(TNode T)
{
    T->right = RSR(T->right); // can be done if we make right single rotation for the right
    return LSR(T);            // then return the left single rotation of t
}

TNode insert(TNode T, char *element)
{
    if (T == NULL)
    {
        T = createNode(element);
    }
    else if (strcasecmp(element, T->element) < 0) // since it's less then should go left
    {
        T->left = insert(T->left, element);                // going left
        if (getHeight(T->left) - getHeight(T->right) == 2) ///(left-heavy) to check if the tree has become unbalanced
        {
            if (strcasecmp(element, T->left->element) < 0) // now if new element was less than left child -> do a right single rotation
            {
                T = RSR(T);
            }
            else /// else than perform a left/right double rotation
            {
                T = LRDR(T);
            }
        }
    }
    else if (strcasecmp(element, T->element) > 0) // if it's more .. go right
    {
        T->right = insert(T->right, element);
        if (getHeight(T->right) - getHeight(T->left) == 2) // right heavy ..
        {
            if (strcasecmp(element, T->right->element) > 0) // now if new element was more than right child -> do a left single rotation
            {
                T = LSR(T);
            }
            else
            {
                T = RLDR(T);
            }
        }
    }
    else
    {
        T->frequency++;
        return T;
    }
    T->height = max(getHeight(T->left), getHeight(T->right)) + 1; // Update the height of the ancestor node

    return T;
}

void printInOrder(TNode T)
{
    if (T != NULL)
    {
        printInOrder(T->left);
        printf("%s:%d ", T->element, T->frequency);
        printInOrder(T->right);
    }
}

void printPreOrder(TNode T)
{
    if (T != NULL)
    {
        printf("%s ", T->element);
        printPreOrder(T->left);
        printPreOrder(T->right);
    }
}

void printPostOrder(TNode T)
{
    if (T != NULL)
    {
        printPostOrder(T->left);
        printPostOrder(T->right);
        printf("%s ", T->element);
    }
}

char *loadTextFromFile(const char *filename, char *fileText)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file!\n");
        return NULL;
    }

    char buffer[10000]; // holding the file text
    fileText = buffer;
    fileText[0] = '\0'; // let it be initailly null

    char word[50]; // since there's no words exceed 50 characters // buufer that word

    while (fscanf(file, "%49s", word) != EOF)
    {
        char ValidCharWords[50];
        int j = 0;
        for (int i = 0; word[i] != '\0'; i++)
        {
            if (word[i] != '?' && word[i] != '1' && word[i] != '2' && word[i] != '3' && word[i] != '4' && word[i] != '5' && word[i] != '6' && word[i] != '7' && word[i] != '8' && word[i] != '9' && word[i] != '0' && word[i] != '-' && word[i] != '=' && word[i] != '+' && word[i] != '_' && word[i] != ')' && word[i] != '(' && word[i] != '*' && word[i] != '&' && word[i] != '^' && word[i] != '%' && word[i] != '$' && word[i] != '#' && word[i] != '@' && word[i] != '!' && word[i] != '>' && word[i] != '<' && word[i] != ':' && word[i] != ';' && word[i] != '"' && word[i] != ']' && word[i] != '[' && word[i] != '}' && word[i] != '{' && word[i] != '/')
            {
                ValidCharWords[j++] = word[i]; // keep the original case and add to ValidCharWords
            }
        }
        ValidCharWords[j] = '\0'; // null-terminate for the valid word
        if (j > 0)
        { // Check if there's at least one alphabetical character, otherwise it's empty
            strcat(fileText, ValidCharWords);
            strcat(fileText, " ");
        }
    }
    fclose(file);
    return fileText;
}

TNode insertWordsFromFileText(TNode T, char *fileText)
{
    char *textCopy = strdup(fileText); // dup so don't make it points at the same thing
    char *token = strtok(textCopy, " ");
    while (token != NULL)
    {
        T = insert(T, token);
        token = strtok(NULL, " ");
    }
    free(textCopy);
    return T;
}

TNode deleteNode(TNode T, char *element)
{
    // Check if the tree is empty
    if (T == NULL)
    {
        printf("The Element You Entered not found!\n");
        return T;
    }

    // Traverse the left subtree if the element to be deleted is smaller than the current node's element
    if (strcasecmp(element, T->element) < 0)
    {
        T->left = deleteNode(T->left, element);
    }
    // Traverse the right subtree if the element to be deleted is greater than the current node's element
    else if (strcasecmp(element, T->element) > 0)
    {
        T->right = deleteNode(T->right, element);
    }
    // The element to be deleted is found
    else
    {
        // Node with only one child or no child
        if (T->left == NULL || T->right == NULL)
        {
            TNode temp;
            if (T->left != NULL)
            {
                temp = T->left;
            }
            else
            {
                temp = T->right;
            }

            // no child case
            if (temp == NULL)
            {
                temp = T;
                T = NULL;
            }
            // one child case
            else
            {
                // Free current element and copy temp node data
                free(T->element);
                T->element = strdup(temp->element);
                T->left = temp->left;
                T->right = temp->right;
                T->frequency = temp->frequency;
                T->height = temp->height;
            }
            free(temp->element); // Free the element of the temporary node
            free(temp);          // Free the temporary node
        }
        // Node with two children
        else
        {
            // Find the smallest node in the right subtree
            TNode temp = findMin(T->right);

            /// replace current node's element with the smallest node's element
            free(T->element);
            T->element = strdup(temp->element);
            T->frequency = temp->frequency;

            /// delete the smallest node in the right subtree
            T->right = deleteNode(T->right, temp->element);
        }
    }

    // if the tree has only one node then return NULL
    if (T == NULL)
    {
        return T;
    }

    // update the height of the current node
    T->height = max(getHeight(T->left), getHeight(T->right)) + 1;

    // get the balance factor of the current node to check if it became unbalanced
    int balance = getHeight(T->left) - getHeight(T->right);

    // left left case
    if (balance > 1 && getHeight(T->left->left) >= getHeight(T->left->right))
    {
        return RSR(T);
    }

    /// left right Case
    if (balance > 1 && getHeight(T->left->left) < getHeight(T->left->right))
    {
        T->left = LSR(T->left);
        return RSR(T);
    }

    // right right Case
    if (balance < -1 && getHeight(T->right->right) >= getHeight(T->right->left))
    {
        return LSR(T);
    }

    // right left Case
    if (balance < -1 && getHeight(T->right->right) < getHeight(T->right->left))
    {
        T->right = RSR(T->right);
        return LSR(T);
    }

    // Return the (potentially new) T of the subtree
    return T;
}

void freeAVLTree(TNode T)
{
    if (T != NULL)
    {
        freeAVLTree(T->left);
        freeAVLTree(T->right);
        free(T->element);
        free(T);
    }
}

/***************************************** "Tree Functions" *****************************************/

HashTable *createHashTable()
{

    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable)); /// allocate memory to make the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable->table[i] = NULL; // initialize all the entries to NULL
    }
    return hashTable;
}

void insertAVLToHashTable(TNode T, HashTable *hashTable)
{
    if (T != NULL)
    {
        insertToHashTable(hashTable, T->element, T->frequency); /// make it looks like the pre order
        insertAVLToHashTable(T->left, hashTable);
        insertAVLToHashTable(T->right, hashTable);
    }
}

void insertToHashTable(HashTable *hashTable, char *element, int frequency)
{
    unsigned int hashIndex = hashFunction(element);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode)); // Create the new node
    newNode->element = strdup(element);                       // copy the data
    newNode->frequency = frequency;
    newNode->next = NULL;

    HashNode *currentNode = hashTable->table[hashIndex]; // let it points at the node in that hashtable index ..
    if (currentNode == NULL)
    {
        /// if there's noo collision then directly insert
        hashTable->table[hashIndex] = newNode;
    }
    else
    {
        /// now the  collision handling by chaining
        HashNode *prevNode = NULL;
        while (currentNode != NULL && strcasecmp(currentNode->element, element) != 0)
        {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode == NULL) // reach last then link
        {
            // End of the chain, insert new node
            prevNode->next = newNode;
        }
        else // mean that it's already exist therefor ...
        {
            /// element already exists then update frequency
            currentNode->frequency += frequency;
            // and free the node since no need to it .
            free(newNode->element);
            free(newNode);
        }
    }
}

unsigned int hashFunction(char *element)
{
    unsigned int hash = 0;
    while (*element) /// calculate hash using a simple shift and sum method
    {
        hash = (hash << 5) + tolower(*element++); // a simple hash equation // هاي معناها شيفت << 
    }
    return hash % TABLE_SIZE; // this make sure the hash value fits within the bounds of the hash table array.
}

HashNode *searchHashTable(HashTable *hashTable, char *element)
{
    unsigned int hashIndex = hashFunction(element);

    HashNode *currentNode = hashTable->table[hashIndex]; /// traverse the chain to find the element
    while (currentNode != NULL)
    {
        if (strcasecmp(currentNode->element, element) == 0) // when it's equal means we found it ..
        {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

void deleteFromHashTable(HashTable *hashTable, char *element)
{
    unsigned int hashIndex = hashFunction(element);
    HashNode *currentNode = hashTable->table[hashIndex];
    HashNode *prevNode = NULL;

    while (currentNode != NULL && strcasecmp(currentNode->element, element) != 0) // traverse the chain to find the element we want to delete

    {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL) // the case If the element is not found
    {
        printf("element not found in hash table.\n");
        return;
    }

    if (prevNode == NULL) // remove the node from the chain
    {
        hashTable->table[hashIndex] = currentNode->next;
    }
    else
    {
        prevNode->next = currentNode->next;
    }

    // free memory for the node
    free(currentNode->element);
    free(currentNode);
}

void printHasStatistics(HashTable *hashTable)
{
    // initial data
    int totaleOfFrequencies = 0;
    int numberOfElements = 0;
    int maxFrequency = 0;
    char *MostFrequentElement = NULL;
    int thersholdCounter = 1;

    int thershold;
    printf("What's the specific threshold you want words repeated more than it:\n");
    scanf("%d", &thershold);

    printf("\n____________________________________________\n\n");
    printf("->The words with frequency more than %d are :\n", thershold);

    /// nested loop // go for the array first index by index ..
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *currentNode = hashTable->table[i];
        // then if index has nodes then make another loop goes on the nodes one by one
        while (currentNode != NULL)
        {
            if (currentNode->frequency > thershold)
            {
                printf("  %s with a frquancy of %d\n", currentNode->element, currentNode->frequency);
                thersholdCounter = 0;
            }

            currentNode = currentNode->next;
        }
    }
    if (thersholdCounter)
        printf("There's no word with more than frequency %d\n", thershold);
    printf("____________________________________________\n\n");

    /// same thing but for unique ones now
    printf("->The unique elements are : ");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *currentNode = hashTable->table[i];
        while (currentNode != NULL)
        {
            if (currentNode->frequency == 1)
                printf("%s ", currentNode->element);
            numberOfElements++;
            if (currentNode->frequency > maxFrequency)
            {
                maxFrequency = currentNode->frequency;
                MostFrequentElement = currentNode->element;
            }
            currentNode = currentNode->next;
        }
    }
    printf("\n____________________________________________\n\n");
    printf("->Most frequent element: %s (Frequency: %d)\n", MostFrequentElement, maxFrequency);
    printf("____________________________________________\n\n");
    printf("->Total number of elements: %d\n", numberOfElements);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *currentNode = hashTable->table[i];
        // then if index has nodes then make another loop goes on the nodes one by one
        while (currentNode != NULL)
        {
                printf("  %s:%d ", currentNode->element, currentNode->frequency);
            currentNode = currentNode->next;
        }
    }
    printf("\n____________________________________________\n\n");
}

void freeHashTable(HashTable *hashTable)
{

    for (int i = 0; i < TABLE_SIZE; i++) // go on the array one by one
    {
        HashNode *currentNode = hashTable->table[i]; // make the current

        while (currentNode != NULL)
        {
            HashNode *tempNode = currentNode;
            currentNode = currentNode->next;
            free(tempNode->element);
            free(tempNode);
        }
    }
    free(hashTable);
}








