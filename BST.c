/*
    Authored by Chaitanya Datar
    Panel F8
    1262242226

    1. Insert
    2. Delete
    3. Mirror
    4. Display Levelwise
    5. Copy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct TreeNode {
    char word[10];
    char meaning[20];
    struct TreeNode *left;
    struct TreeNode *right;
};

void inorder(struct TreeNode* root){
    if(root == NULL){
        return;
    }

    inorder(root->left);
    printf("Word: %s, Meaning: %s\n", root->word, root->meaning);
    inorder(root->right);
}

void init(struct TreeNode* root){
    printf("Enter word at root: ");
    scanf("%s", root->word);
    getchar();

    printf("Enter meaning: ");
    fgets(root->meaning, 20, stdin);
}

void insert(struct TreeNode* root){
    struct TreeNode* t;
    t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    t->left = NULL;
    t->right = NULL;

    printf("Enter word to add: ");
    scanf("%s", t->word);
    getchar();

    printf("Enter meaning: ");
    fgets(t->meaning, 20, stdin);

    struct TreeNode* current = root;
    
    while(true){
        if(strcmp(t->word, current->word) < 0){
            if(current->left == NULL){
                current->left = t;
                break;
            }
            else{
                current = current->left;
            }
        }
        else if(strcmp(t->word, current->word) > 0){
            if(current->right == NULL){
                current->right = t;
                break;
            }
            else{
                current = current->right;
            }
        }
    }
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int insertQ(struct TreeNode* node, struct TreeNode* Q[50], int r){
    r++;
    Q[r] = node;
    return(r);
}

int deleteQ(struct TreeNode* Q[50], int f){
    f++;
    printf("Word: %s Meaning: %s\n", Q[f]->word, Q[f]->meaning);
    return(f);
}

int depth(struct TreeNode* root){
    if(root == NULL){
        return(0);
    }
    int l = depth(root->left);
    int r = depth(root->right);

    return(max(l , r) + 1);
}

bool isEmpty(int f, int r){
    return(f == r);
}

void dispLevel(struct TreeNode* root){
    if (root == NULL) {
        return;
    }

    struct TreeNode* Q[50];
    int f = -1;
    int r = -1;

    r = insertQ(root, Q, r);

    while (!isEmpty(f, r)) {
        f = deleteQ(Q, f);
        struct TreeNode* node = Q[f];

        if (node->left != NULL) {
            r = insertQ(node->left, Q, r);
        }
        if (node->right != NULL) {
            r = insertQ(node->right, Q, r);
        }
    }
}

struct TreeNode* copyTree(struct TreeNode* root) {
    if(root == NULL){
        return(NULL);
    }
    
    struct TreeNode* copy = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    strcpy(copy->word, root->word);
    strcpy(copy->meaning, root->meaning);

    copy->left = copyTree(root->left);
    copy->right = copyTree(root->right);

    return copy;
}

struct TreeNode* search(struct TreeNode* root, char word[]){
    if(root == NULL){
        return(NULL);
    }

    int cmp = strcmp(word, root->word);
    printf("visiting %s\n", root->word);

    if(cmp < 0){
        return(search(root->left, word));
    }

    if(cmp > 0){
        return(search(root->right, word));
    }

    if(cmp == 0){
        return(root);
    }
}

struct TreeNode* mirror(struct TreeNode* root){
    if(root == NULL){
        return NULL;
    }
    
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirror(root->left);
    mirror(root->right);
    
    return(root);
}

int main() {
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;
    init(root);

    struct TreeNode* copy;
    
    char yn = 'y';

    while (yn == 'y') {
        printf("Enter Operation- \n");
        printf("1 for inserting a node\n");
        printf("2 for deleting a node\n");
        printf("3 for mirroring the tree\n");
        printf("4 for displaying levelwise\n");
        printf("5 for copying the tree\n");
        printf("6 for searching a node\n");
        printf("7 for inorder traversal\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert(root);
                break;
            
            case 3:
                printf("original tree-\n");
                inorder(root);
                printf("mirrored tree-\n");
                inorder(mirror(copyTree(root)));
                break;

            case 4:
                dispLevel(root);
                break;
            
            case 5:
                copy = copyTree(root);
                printf("original tree-\n");
                inorder(root);
                printf("copied tree-\n");
                inorder(copy);
                break;
                
            case 6:
                char word[20];
                printf("Enter word to search: ");
                scanf("%s", word);
                struct TreeNode* found = search(root, word);
                if(found == NULL){
                    printf("word does not exist\n");
                }
                else{
                    printf("found Word: %s, Meaning: %s", found->word, found->meaning);
                }

                break;

            case 7:
                inorder(root);
                break;

            default:
                printf("Invalid choice.\n");
        }

        printf("Another operation? y/n: ");
        scanf(" %c", &yn);
    }

    return 0;
}
