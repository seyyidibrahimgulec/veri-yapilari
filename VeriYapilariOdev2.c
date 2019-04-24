#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define LINE_SIZE 1024
typedef struct Node {
    int kimlikNo;
    char ad[SIZE];
    char soyad[SIZE];
    int arkadas[SIZE];
    struct Node *left;
    struct Node *right;
} Node;

void insertNewUser(Node*, Node*);
Node* deleteUser(Node*, int);
struct Node* createNode();
void printInOrder(Node*);
Node* contains(Node*, int);
void friends(Node*, Node*, int);
int size(Node*);
void printNext(Node*, int);
void printGreater(Node*, int);
Node* findMax(Node*);

int main() {
    FILE *fp; // Dosya isaretcisi
    int offset; // Okuma yaparken buffer pointerinin ilerleme degeri
    int tmp; // Gecici deger
    int i; // Arkadas kimlik noları dongusu icin index degeri
    int count = 0; // Her 10 eleman eklemede bir ekrana yazdirma islemi icin sayac degeri
    int flag = 0; // Menu dongusunden cikis icin gereken bayrak degeri
    int id; // Menude yeni kullanici ekleme yaparken yapilan kimlik no okumalari icin gerekli gecici deger
    int arkadasSayisi; // Menudeki yeni kullanici arkadas ekleme icin arkadas sayisi
    int arkadasKimlikNo; // Menudeki yeni kullanici arkadas ekleme icin gecici arkadas kimlik nosu
    char ad[SIZE]; // Menude yeni kullanici ekleme yaparken yapilan ad okumalari icin gerekli gecici deger
    char soyad[SIZE]; // Menude yeni kullanici ekleme yaparken yapilan soyad okumalari icin gerekli gecici deger
    char dosyaAdi[SIZE]; // Text dosyasinin adi
    char *buffer; // Dosyadan satir satir okuma yaparken gerekli buffer
    char *temp; // Dosyadan satir satir okuma yaparken gerekli gecici deger
    char ch; // Menude secim icin okuma yaparken gerekli karakter
    char dummy; // Menudeki enter degeri icin gerekli dummy deger
    Node *node; // Her kullanici dugumu icin gerekli pointer
    Node *root = NULL; // Iklili agacin kok pointeri
    buffer = (char*) malloc(LINE_SIZE * sizeof(char));
    temp = (char*) malloc(SIZE * sizeof(char));
    printf("Okuma yapmak istediginiz text dosyasinin adini giriniz :");
    scanf("%s", dosyaAdi);
    scanf("%c", &dummy);
    fp = fopen(dosyaAdi, "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        exit(-1);
    }
    while(fgets(buffer,LINE_SIZE,fp)) {
        if(*buffer >= '0' && *buffer <= '9') {
            node = createNode();
            // kimlik no okuma
            temp = strtok(buffer, ",");
            tmp = atoi(temp);
            node->kimlikNo = tmp;
            offset = strlen(temp);
            offset++;
            buffer += offset;

            // Ad okuma
            temp = strtok(buffer, " ");
            strcpy(node->ad, temp);
            offset = strlen(temp);
            offset++;
            buffer += offset;

            // Soyad okuma
            temp = strtok(buffer, ",\n");
            strcpy(node->soyad, temp);
            offset = strlen(temp);
            offset++;
            buffer += offset;

            // Arkadas id okuma
            if(*buffer >= '0' && *buffer <= '9') {
                temp = strtok(buffer, "-\n");
                i = 0;
                while(*buffer) {
                    tmp = atoi(temp);
                    offset = strlen(temp);
                    offset++;
                    buffer += offset;
                    node->arkadas[i] = tmp;
                    temp = strtok(buffer, "-\n");
                    i++;
                }
            }
            
            if(root == NULL) {
                root = node;
            } else {
                insertNewUser(root,node);
            }
            ++count;
            if(count % 10 == 0) {
                // Her 10 eleman ekleme sonrası printInOrder cagrilir
                printf("---------------------------------\n");
                printf("%d tane eleman agaca eklendi\n", count);
                printf("---------------------------------\n");
                printInOrder(root);
            }
        }
    }
    printf("---------------------------------\n");
    printf("Dosya okundu\n");
    printf("%d tane eleman agaca eklendi\n", count);
    printf("---------------------------------\n");
    printInOrder(root);
    // MENU
    while(!flag) {
        printf("---------------------------------------MENU-------------------------------------\n");
        printf("a) Yeni kullanici eklemek icin -a- giriniz.\n");
        printf("b) Kullanici silmek icin -b- giriniz.\n");
        printf("c) Kullanici agaca dahil mi diye sorgulamak icin -c- giriniz.\n");
        printf("d) Kullanicinin arkadaslarini yazdirmak icin -d- giriniz.\n");
        printf("e) Agactaki eleman sayisini yazdirmak icin -e- giriniz.\n");
        printf("f) Kullancinin alt agacini yazdirmak icin -f- girinz.\n");
        printf("g) Kullanicinin kimlik nosundan buyuk kullaniciları yazdirmak icin -g- giriniz.\n");
        printf("h) Agacin tamamini kucukten buyuge yazdirmak icin -h- giriniz.\n");
        printf("i) Cikmak icin -i- giriniz.\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("Secim :");
        ch = getchar();
        switch(ch) {
            case 'a':
                node = (Node*) malloc(sizeof(Node));
                printf("Kullanici kimlik no :"); scanf("%d", &id);
                printf("Kullanici adi :"); scanf("%s", ad);
                printf("Kullanici soyadi :"); scanf("%s", soyad);
                printf("Kullanici arkadas sayisini giriniz :"); scanf("%d", &arkadasSayisi);
                for(i=0; i < arkadasSayisi; i++) {
                    printf("%d. arkadas kimlik no :", i+1);
                    scanf("%d", &arkadasKimlikNo);
                    node->arkadas[i] = arkadasKimlikNo;
                }
                node->kimlikNo = id;
                strcpy(node->ad, ad);
                strcpy(node->soyad, soyad);
                insertNewUser(root, node);
                break;
            case 'b':
                printf("Kullanici kimlik no :"); scanf("%d", &id);
                deleteUser(root, id);
                break;
            case 'c':
                printf("Kullanici kimlik no :"); scanf("%d", &id);
                contains(root, id);
                break;
            case 'd':
                printf("Kullanici kimlik no :"); scanf("%d", &id);
                friends(root, root, id);
                break;
            case 'e':
                printf("Agac eleman sayisi :%d\n", size(root));
                break; 
            case 'f':
                printf("Kullanici kimlik no :"); scanf("%d", &id);
                printNext(root, id);
                break;
            case 'g':
                printf("Kullanici kimlik no :"); scanf("%d", &id);
                printGreater(root, id);
                break;
            case 'h':
                printf("---------------------------------------\n");
                printf("Ikili agacin tamami. Eleman Sayisi: %d\n", size(root));
                printf("---------------------------------------\n");
                printInOrder(root);
                printf("---------------------------------------\n");
                break;
            case 'i':
                flag = 1;
                break;
            default:
                printf("Hatali tuslama yaptiniz.\n");
                break;
        }
        scanf("%c", &dummy);
    }
    fclose(fp);
    return 0;
}

void insertNewUser(Node *root, Node *node) {
    if(node->kimlikNo < root->kimlikNo) {
        if(root->left == NULL) {
            root->left = node;
        } else {
            insertNewUser(root->left, node);
        }
    } else {
        if(root->right == NULL) {
            root->right = node;
        } else {
            insertNewUser(root->right, node);
        }
    }
}
Node* findMax(Node *node) {
    Node *tmp = node;
    while(tmp->right != NULL) {
        tmp = tmp->right;
    }
    return tmp;
}
Node* deleteUser(Node *root, int id) {
    Node *tmp;
    if(root == NULL) {
        return root;
    } else if(id < root->kimlikNo) {
        root->left = deleteUser(root->left, id);
    } else if(id > root->kimlikNo) {
        root->right = deleteUser(root->right, id);
    } else {
        if(root->right == NULL && root->left == NULL) {
            // Child yoksa
            free(root);
            return NULL;
        } else if(root->right == NULL) {
            tmp = root;
            root = root->left;
            free(tmp);
        } else if(root->left == NULL) {
            tmp = root;
            root = root->right;
            free(tmp);
        } else {
            Node *tmp = findMax(root->left);
            int i = 0;
            root->kimlikNo = tmp->kimlikNo;
            strcpy(root->ad, tmp->ad);
            strcpy(root->soyad, tmp->soyad);
            while(tmp->arkadas[i]) {
                root->arkadas[i] = tmp->arkadas[i];
                i++;
            }
            while(root->arkadas[i]) {
                root->arkadas[i] = 0;
                i++;
            }
            root->left = deleteUser(root->left, tmp->kimlikNo);
        }
    }
    return root;
}

Node* createNode() {
    Node *node = (Node*) malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printInOrder(Node *root) {
    int i;
    if(root != NULL) {
        printInOrder(root->left);
        printf("%d %s %s", root->kimlikNo, root->ad, root->soyad);
        i = 0;
        while(root->arkadas[i]) {
            printf(" %d", root->arkadas[i]);
            i++;
        }
        printf("\n");
        printInOrder(root->right);
    }
}

Node* contains(Node *root, int id) { 
    if(root == NULL || root->kimlikNo == id) {
        if(root != NULL) {
            printf("------------------------------------------\n");
            printf("%.2d ile %.2d karsilastirildi eslesme oldu\n", root->kimlikNo, id);
            printf("Kullanici Adi ve Soyadi :%s %s\n", root->ad, root->soyad);
            printf("------------------------------------------\n");
        }
        return root;
    } else {
        printf("%.2d ile %.2d karsilastirildi eslesme olmadi\n", root->kimlikNo, id);
    }
    if (root->kimlikNo < id) 
       return contains(root->right, id); 
  
    return contains(root->left, id); 
} 

void friends(Node *root, Node *tmp, int id) {
    int i;
    if(tmp != NULL) {
        friends(root,tmp->left, id);
        if(tmp->kimlikNo == id) {
            i = 0;
            printf("-----------------------------------\n");
            printf("%d kimlik nolu kullanicinin arkadaslari\n", id);
            printf("-----------------------------------\n");
            while(tmp->arkadas[i]) {
                contains(root, tmp->arkadas[i]);
                i++;
            }
            printf("-----------------------------------\n");
        }
        friends(root, tmp->right, id);
    }
}

int size(Node *root) {
    if (root == NULL)  
        return 0;  
    return size(root->left) + 1 + size(root->right);  
}  

void printNext(Node *root, int id) {
    if(root != NULL) {
        if(id == root->kimlikNo) {
            printf("-------------------------------------\n");
            printf("%d kimlik nolu kullanicinin alt agaci\n", id);
            printf("-------------------------------------\n");
            printInOrder(root);
            printf("-------------------------------------\n");
        }
        printNext(root->left, id);
        printNext(root->right, id);
    }
}

void printGreater(Node *root, int id) {
    if(root != NULL) {
        printGreater(root->left, id);
        if(root->kimlikNo > id) {
            printf("%d %s %s\n", root->kimlikNo, root->ad, root->soyad);
        }
        printGreater(root->right, id);
    }
}
