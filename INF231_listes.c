#include <stdio.h>
#include <stdlib.h>

/* === Structures === */
// Liste simplement chaînée
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Liste doublement chaînée
typedef struct DNode {
    int data;
    struct DNode *prev, *next;
} DNode;

// Liste simplement chaînée circulaire
typedef struct CNode {
    int data;
    struct CNode *next;
} CNode;

// Liste doublement chaînée circulaire
typedef struct DCNode {
    int data;
    struct DCNode *prev, *next;
} DCNode;

/* === Fonctions utilitaires === */
Node* createNode(int val) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = val; n->next = NULL;
    return n;
}
DNode* createDNode(int val) {
    DNode *n = (DNode*)malloc(sizeof(DNode));
    n->data = val; n->prev = n->next = NULL;
    return n;
}
CNode* createCNode(int val) {
    CNode *n = (CNode*)malloc(sizeof(CNode));
    n->data = val; n->next = n;
    return n;
}
DCNode* createDCNode(int val) {
    DCNode *n = (DCNode*)malloc(sizeof(DCNode));
    n->data = val; n->prev = n->next = n;
    return n;
}

/* === 1. Suppression des occurrences dans liste simplement chaînée === */
void insertEnd(Node **head, int val) {
    Node *n = createNode(val);
    if (*head == NULL) *head = n;
    else {
        Node *temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = n;
    }
}
void deleteOccurrences(Node **head, int val) {
    Node *temp = *head, *prev = NULL;
    while (temp != NULL) {
        if (temp->data == val) {
            Node *toDel = temp;
            if (prev == NULL) *head = temp->next;
            else prev->next = temp->next;
            temp = temp->next;
            free(toDel);
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}
void printList(Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/* === 2. Insertion triée dans une liste simplement chaînée === */
void insertSorted(Node **head, int val) {
    Node *n = createNode(val);
    if (*head == NULL || (*head)->data >= val) {
        n->next = *head; *head = n;
        return;
    }
    Node *temp = *head;
    while (temp->next && temp->next->data < val) temp = temp->next;
    n->next = temp->next;
    temp->next = n;
}

/* === 3. Insertion triée dans une liste doublement chaînée === */
void insertSortedD(DNode **head, int val) {
    DNode *n = createDNode(val);
    if (*head == NULL || (*head)->data >= val) {
        n->next = *head;
        if (*head) (*head)->prev = n;
        *head = n;
        return;
    }
    DNode *temp = *head;
    while (temp->next && temp->next->data < val) temp = temp->next;
    n->next = temp->next;
    if (temp->next) temp->next->prev = n;
    temp->next = n;
    n->prev = temp;
}
void printDList(DNode *head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

/* === 4. Insertion en tête et queue liste simplement circulaire === */
void insertHeadC(CNode **head, int val) {
    CNode *n = createCNode(val);
    if (*head == NULL) { *head = n; return; }
    CNode *temp = *head;
    while (temp->next != *head) temp = temp->next;
    n->next = *head;
    temp->next = n;
    *head = n;
}
void insertTailC(CNode **head, int val) {
    CNode *n = createCNode(val);
    if (*head == NULL) { *head = n; return; }
    CNode *temp = *head;
    while (temp->next != *head) temp = temp->next;
    temp->next = n;
    n->next = *head;
}
void printCList(CNode *head) {
    if (!head) { printf("Liste vide\n"); return; }
    CNode *temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(retour tete)\n");
}

/* === 5. Insertion en tête et queue liste doublement circulaire === */
void insertHeadDC(DCNode **head, int val) {
    DCNode *n = createDCNode(val);
    if (*head == NULL) { *head = n; return; }
    DCNode *tail = (*head)->prev;
    n->next = *head;
    n->prev = tail;
    tail->next = n;
    (*head)->prev = n;
    *head = n;
}
void insertTailDC(DCNode **head, int val) {
    DCNode *n = createDCNode(val);
    if (*head == NULL) { *head = n; return; }
    DCNode *tail = (*head)->prev;
    n->next = *head;
    n->prev = tail;
    tail->next = n;
    (*head)->prev = n;
}
void printDCList(DCNode *head) {
    if (!head) { printf("Liste vide\n"); return; }
    DCNode *temp = head;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(retour tete)\n");
}

/* === MAIN AVEC MENU === */
int main() {
    Node *list1 = NULL, *listSorted = NULL;
    DNode *listD = NULL;
    CNode *listC = NULL;
    DCNode *listDC = NULL;

    int choix, val, x;

    do {
        printf("\n===== MENU INF 231 =====\n");
        printf("1. Lire et supprimer toutes les occurrences dans liste simple\n");
        printf("2. Insertion triée liste simplement chaînée\n");
        printf("3. Insertion triée liste doublement chaînée\n");
        printf("4. Insertion tete/queue liste simplement circulaire\n");
        printf("5. Insertion tete/queue liste doublement circulaire\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("Entrer valeurs (-1 pour arreter) : ");
                while (1) {
                    scanf("%d", &val);
                    if (val == -1) break;
                    insertEnd(&list1, val);
                }
                printf("Liste avant suppression : ");
                printList(list1);
                printf("Entrer la valeur a supprimer : ");
                scanf("%d", &x);
                deleteOccurrences(&list1, x);
                printf("Liste apres suppression : ");
                printList(list1);
                break;

            case 2:
                printf("Entrer valeurs (-1 pour arreter) : ");
                while (1) {
                    scanf("%d", &val);
                    if (val == -1) break;
                    insertSorted(&listSorted, val);
                }
                printf("Liste triee : ");
                printList(listSorted);
                break;

            case 3:
                printf("Entrer valeurs (-1 pour arreter) : ");
                while (1) {
                    scanf("%d", &val);
                    if (val == -1) break;
                    insertSortedD(&listD, val);
                }
                printf("Liste doublement chainee triee : ");
                printDList(listD);
                break;

            case 4:
                printf("1. Inserer en tete\n2. Inserer en queue\nChoix : ");
                scanf("%d", &x);
                printf("Entrer valeur : "); scanf("%d", &val);
                if (x == 1) insertHeadC(&listC, val);
                else insertTailC(&listC, val);
                printf("Liste circulaire simple : ");
                printCList(listC);
                break;

            case 5:
                printf("1. Inserer en tete\n2. Inserer en queue\nChoix : ");
                scanf("%d", &x);
                printf("Entrer valeur : "); scanf("%d", &val);
                if (x == 1) insertHeadDC(&listDC, val);
                else insertTailDC(&listDC, val);
                printf("Liste circulaire double : ");
                printDCList(listDC);
                break;

            case 0:
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide!\n");
        }
    } while (choix != 0);

    return 0;
}
