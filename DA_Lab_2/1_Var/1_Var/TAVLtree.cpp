#include "TAVLtree.h"

TAVLtree::TAVLtree() : root(0) {}

TNode* TAVLtree::TurnRight(TNode* n) {
    TNode* lNode = n->l;
    n->l = lNode->r;
    lNode->r = n;
    lNode->FixHeight();
    n->FixHeight();
    return lNode;
}

TNode* TAVLtree::TurnLeft(TNode* n) {
    TNode* rNode = n->r;
    n->r = rNode->l;
    rNode->l = n;
    n->FixHeight();
    rNode->FixHeight();
    return rNode;
}

TNode* TAVLtree::Balancing(TNode* n) {
    n->FixHeight();
    if (n->Balance() == 2) {
        if (n->r->Balance() < 0)
            n->r = TurnRight(n->r);
        return TurnLeft(n);
    }
    if (n->Balance() == -2) {
        if (n->l->Balance() > 0)
            n->l = TurnLeft(n->l);
        return TurnRight(n);
    } 
    return n;
}

void TAVLtree::Insert(const char* k, unsigned long long val) {
    root = Insert(root, k, val);
}

TNode* TAVLtree::Insert(TNode* tree, const char* k, unsigned long long val) {
    if (!tree) {
        TNode *n;
        n = new TNode(k, val);
        printf("OK\n");
        return n;
    }
    if (strcmp(tree->key, k) > 0)
        tree->l = Insert(tree->l, k, val);
    else if (strcmp(tree->key, k) < 0)
        tree->r = Insert(tree->r, k, val);
    else
        printf("Exist\n");
    return Balancing(tree);
}

TNode* TAVLtree::DeleteMin(TNode* n, TNode*& min) {
    if (n->l == 0) {
        min = n;
        return n->r;
    }
    n->l = DeleteMin(n->l, min);
    return Balancing(n);
}

void TAVLtree::DeleteNode(const char *k) {
    root = DeleteNode(root, k);
}

TNode* TAVLtree::DeleteNode(TNode *n, const char *k) {
    if (!n) {
        printf("NoSuchWord\n");
        return 0;
    }
    if (strcmp(n->key, k) > 0)
        n->l = DeleteNode(n->l, k);
    else if (strcmp(n->key, k) < 0)
        n->r = DeleteNode(n->r, k);
    else {
        TNode *r = n->r;
        TNode *l = n->l;
        delete n;
        if (!r) {    
            printf("OK\n");
            return l;
        }
        TNode* min = nullptr;
        r = DeleteMin(r, min);
        min->l = l;
        min->r = r;
        printf("OK\n");
        return Balancing(min);
    }
    return Balancing(n);
}

void TAVLtree::Search(const char* k) {
    Search(root, k);
}

void TAVLtree::Search(TNode* n, const char* k) {
    if (!n) {
        printf("NoSuchWord\n");
        return;
    }
    if (strcmp(n->key, k) > 0)
        Search(n->l, k);
    else if (strcmp(n->key, k) < 0)
        Search(n->r, k);
    else
        printf("OK: %llu\n", n->value);
}

void TAVLtree::DeleteTree(TNode *n) {
    if (!n) return;
    DeleteTree(n->l);
    DeleteTree(n->r);
    delete n;
}

TAVLtree::~TAVLtree() {
    DeleteTree(root);
}

void TAVLtree::Write(TNode* n, FILE *out) {
    if(!n) return;
    int len = strlen(n->key) + 1;
    fwrite(&len, sizeof(int), 1, out);
    fwrite(n->key, len, 1, out);
    fwrite(&n->value, sizeof(unsigned long long), 1, out);
    fwrite(&n->height, sizeof(int), 1, out);
    bool tr = true;
    bool fl = false;
    if (n->l)
        fwrite(&tr, sizeof(bool), 1, out);
    else
        fwrite(&fl, sizeof(bool), 1, out);
    if (n->r)
        fwrite(&tr, sizeof(bool), 1, out);
    else
        fwrite(&fl, sizeof(bool), 1, out);
    Write(n->l, out);
    Write(n->r, out);
}


void TAVLtree::Serialization(const char* nameFile) {
    FILE* out = fopen(nameFile, "wb");
    if (!out) {
        printf("ERROR: Couldn't create file\n");
        return;
    }
    if (!root) {
        int flag = -1;
        fwrite(&flag, sizeof(int), 1, out);
    }
    else
        Write(root, out);
    fclose(out);
    printf("OK\n");
}

int TAVLtree::Read(TNode* n, FILE* in) {
    bool lNode, rNode;
    int flag;
    if (fread(&flag, sizeof(int), 1, in) != 1) return -1;
    if (flag == -1) {
        root = nullptr;
        return 0;
    }
    n->key = new char[flag];
    if (fread(n->key, flag, 1, in) != 1)
        return -1;
    if (fread(&n->value, sizeof(unsigned long long), 1, in) != 1) return -1;
    if (fread(&n->height, sizeof(int), 1, in) != 1) return -1;
    if (fread(&lNode, sizeof(bool), 1, in) != 1) return -1;
    if (fread(&rNode, sizeof(bool), 1, in) != 1) return -1;

    if (lNode) {
        n->l = new TNode();
        if (Read(n->l, in) == -1) return -1;
    }
    else
        n->l = 0;

    if (rNode) {
        n->r = new TNode();
        if (Read(n->r, in) == -1) return -1;
    }
    else
        n->r = 0;
    return 0;
}

int TAVLtree::DeSerialization(const char *nameFile) {
    FILE *in = fopen(nameFile, "rb");
    if (!in) return -2;
    root = new TNode();
    int ans = Read(root, in);
    fclose(in);
    return ans;
}

