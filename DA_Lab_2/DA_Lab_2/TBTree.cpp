#include <strings.h>
#include <string.h>
#include <iostream>
#include "TBTree.h"

TBTree::TBTree(size_t t) {
    this->root = TSmartPointer<TNode>(new TNode);
    this->t = t;
}                                              
                                          
TSmartPointer<TNode>& TBTree::GetRoot() {
    return root;
}


int FindElem(TVector<TSmartPointer<TElem>>& elem, char* key) {
    int left = 0,
        right = elem.Size() ,
        mid = 0,
        cmp;
    while (left < right){
        mid = left + ((right - left) >> 1);
        cmp = strcasecmp(elem[mid]->key, key);
        if (cmp > 0) right = mid;
        else if (cmp < 0) left = mid + 1;
        else return mid;
    }
    return left - 1;
}

bool CheckExist(TVector<TSmartPointer<TElem>>& elem, char* key, int i) {
    return !(i == NOT_FOUND || strcasecmp(elem[i]->key, key));
}

int TBTree::Search(TSmartPointer<TNode>& node, char* key) {
    int i = FindElem(node->elem, key);
    if (CheckExist(node->elem, key, i)) {
            std::cout << "OK: " << node->elem[i]->value << std::endl;
            return JUST_RETURN;
    }
    if (node->leaf) return NOT_FOUND;
    return Search(node->child[i + 1], key);
}

void TBTree::PrintTree(TSmartPointer<TNode>& node, size_t lvl, size_t k) {
    if (!root->elem.Empty()) {
        for (size_t i = 0; i < lvl; i++) std::cout << "\t\t";
        std::cout << "[" << k << "]";
        for (size_t i = 0; i < node->elem.Size(); i++)
            std::cout << node->elem[i]->key << ":" << node->elem[i]->value << "  ";
        std::cout << std::endl;
        if (!node->leaf)
            for (int i = node->child.Size() - 1; i >= 0; i--)
                PrintTree(node->child[i], lvl + 1, i);
    }
}

int TBTree::SplitTree(TSmartPointer<TNode>& node, int i) {
    TSmartPointer<TNode> newNode(new TNode);
    if (!newNode) return MEMORY_ERROR;
    TSmartPointer<TNode> fullNode = node->child[i];
    newNode->leaf = fullNode->leaf;
    newNode->elem.Resize(t - 1);
    for (size_t j = 0; j < t - 1; j++) {
        newNode->elem.Push(fullNode->elem[t]);
        fullNode->elem.Erase(t);
    }
    if (!fullNode->leaf) {
        newNode->child.Resize(t);
        for (size_t j = 0; j < t; j++) {
            newNode->child.Push(fullNode->child[t]);
            fullNode->child.Erase(t);
        }
        fullNode->child.Resize(t);
    }
    node->elem.Insert(i, fullNode->elem[t - 1]);
    fullNode->elem.Erase(t - 1);
    node->child[i] = fullNode;
    node->child.Insert(i + 1, newNode);
    return OK;
}

int TBTree::InsertNonFull(TSmartPointer<TNode>& node, TSmartPointer<TElem>& elem) {
    int i = FindElem(node->elem, elem->key);
    if (CheckExist(node->elem, elem->key, i)) return EXIST;
    if (node->leaf)
        node->elem.Insert(i + 1, elem);
    else {
        i++;
        if (node->child[i]->elem.Size() == 2 * t - 1) {
            SplitTree(node, i);
            if (strcasecmp(elem->key, node->elem[i]->key) > 0) i++;
        }
        return InsertNonFull(node->child[i], elem);
    }
    return OK;
}

int TBTree::Insert(TSmartPointer<TElem>& elem) {
    if (root->elem.Empty()) {
        root->elem.Push(elem);
        return OK;
    }
    else if (root->elem.Size() == 2 * t - 1) {
        TSmartPointer<TNode> newRoot(new TNode);
        if (!newRoot) return MEMORY_ERROR;
        newRoot->leaf = false;
        newRoot->child.Push(root);
        root = newRoot;
        if (SplitTree(root, 0)) return MEMORY_ERROR;
    }
    return InsertNonFull(root, elem);
}

int TBTree::MergeTree(TSmartPointer<TNode>& node, int& i) {
    if (i > 0 && node->child[i - 1]->elem.Size() > t - 1) {
        node->child[i]->elem.Insert(0, node->elem[i - 1]);
        node->child[i]->child.Insert(0, node->child[i - 1]->child[node->child[i - 1]->child.Size() - 1]);
        node->child[i - 1]->child.Pop();
        node->elem[i - 1] = node->child[i - 1]->elem[node->child[i - 1]->elem.Size() - 1];
        node->child[i - 1]->elem.Pop();
    }
    else if ((size_t)(i + 1) < node->child.Size() && node->child[i + 1]->elem.Size() > t - 1) {
        node->child[i]->elem.Push(node->elem[i]);
        node->child[i]->child.Push(node->child[i + 1]->child[0]);
        node->child[i + 1]->child.Erase(0);
        node->elem[i] = node->child[i + 1]->elem[0];
        node->child[i + 1]->elem.Erase(0);
    }
    else {
        if (i > 0) i--;
        node->child[i]->elem.Push(node->elem[i]);
        node->elem.Erase(i);
        node->child[i]->elem.Add(node->child[i + 1]->elem);
        node->child[i]->child.Add(node->child[i + 1]->child);
        node->child.Erase(i + 1);
        if (node == root && !node->elem.Size()) {
            root = TSmartPointer<TNode>(node->child[i]);
            return JUST_RETURN;
        }
    }
    return OK;
}

int TBTree::DelInNode(TSmartPointer<TNode>& node, int i, char* key) {
    if (node->child[i]->elem.Size() > t - 1) {
        TSmartPointer<TNode> bufNode = node->child[i];
        while (!bufNode->leaf)
            bufNode = bufNode->child[bufNode->child.Size() - 1];
        node->elem[i] = bufNode->elem[bufNode->elem.Size() - 1];
        if (node->child[i]->leaf)
            return DelInLeaf(node, i, node->elem[i]->key);
        return DeleteNonEmpty(node->child[i], bufNode->elem[bufNode->elem.Size() - 1]->key);
    }
    else if (node->child[i + 1]->elem.Size() > t - 1) {
        TSmartPointer<TNode> bufNode = node->child[i + 1];
        while (!bufNode->leaf)
            bufNode = bufNode->child[0];
        node->elem[i] = bufNode->elem[0];
        if (node->child[i + 1]->leaf)
            return DelInLeaf(node, i + 1, node->elem[i]->key);
        return DeleteNonEmpty(node->child[i + 1], bufNode->elem[0]->key);
    }
    else {
        node->child[i]->elem.Push(node->elem[i]);
        node->child[i]->elem.Add(node->child[i + 1]->elem);
        if (!node->child[i]->leaf)
            node->child[i]->child.Add(node->child[i + 1]->child);
        node->child.Erase(i + 1);
        node->elem.Erase(i);
        if (node == root && !node->elem.Size()) {
            root = TSmartPointer<TNode>(node->child[i]);
            return Delete(key);
        }
        if (node->child[i]->leaf)
            return DelInLeaf(node, i, key);
        return DeleteNonEmpty(node->child[i], key);
    }
}


int TBTree::DelInLeaf(TSmartPointer<TNode>& node, int i, char* key) {
    int delElem = FindElem(node->child[i]->elem, key);
    if (!CheckExist(node->child[i]->elem, key, delElem)) return NOT_FOUND;
    node->child[i]->elem.Erase(delElem);
    if (node->child[i]->elem.Size() >= t - 1) return OK;
    if (i > 0 && node->child[i - 1]->elem.Size() > t - 1) {
        node->child[i]->elem.Insert(0, node->elem[i - 1]);
        node->elem[i - 1] = node->child[i - 1]->elem[node->child[i - 1]->elem.Size() - 1];
        node->child[i - 1]->elem.Pop();
    }
    else if ((size_t)(i + 1) < node->child.Size() && node->child[i + 1]->elem.Size() > t - 1) {
        node->child[i]->elem.Push(node->elem[i]);
        node->elem[i] = node->child[i + 1]->elem[0];
        node->child[i + 1]->elem.Erase(0);
    }
    else {
        if (i > 0) i--;
        node->child[i]->elem.Push(node->elem[i]);
        node->elem.Erase(i);
        node->child[i]->elem.Add(node->child[i + 1]->elem);
        node->child.Erase(i + 1);
        if (node == root && !node->elem.Size())
            root = TSmartPointer<TNode>(node->child[i]);
    }
    return OK;
}

int TBTree::DeleteNonEmpty(TSmartPointer<TNode>& node, char* key) {
    int i = FindElem(node->elem, key);
    if (CheckExist(node->elem, key, i))
        return DelInNode(node, i, key);
    else if (node->child[i + 1]->leaf)
        return DelInLeaf(node, i + 1, key);
    else {
        i++;
        if (!node->child[i]->leaf && node->child[i]->elem.Size() == t - 1)
            if(MergeTree(node, i) == JUST_RETURN)
                return Delete(key);
        return (DeleteNonEmpty(node->child[i], key));
    }
}

int TBTree::Delete(char* key) {
    if (root->leaf) {
        int i = FindElem(root->elem, key);
        if (!CheckExist(root->elem, key, i)) return NOT_FOUND;
        if (root->elem.Size() == 1)
            root = TSmartPointer<TNode>(new TNode);
        else if (root->elem.Size() > 1)
            root->elem.Erase(i);
        return OK;
    }
    return DeleteNonEmpty(root, key);
}

void TBTree::WriteNode(FILE* out, TSmartPointer<TNode>& node) {
    fwrite(&node->leaf, sizeof(bool), 1, out);
    size_t elemCount = node->elem.Size();
    fwrite(&elemCount, sizeof(size_t), 1, out);
    if (!node->elem.Empty()) {
        for(size_t i = 0; i < elemCount; i++){
            size_t len = strlen(node->elem[i]->key) + 1;
	    fwrite(&len, sizeof(len), 1, out);
            fwrite(node->elem[i]->key, sizeof(char)*len, 1, out);
            fwrite(&(node->elem[i]->value), sizeof(node->elem[i]->value), 1, out);
	}
        if (!node->leaf)
            for (size_t i = 0; i <= elemCount; i++)
                WriteNode(out, node->child[i]);
    }
}

int TBTree::Serialization(char* fileName) {
    FILE *out = fopen(fileName, "wb");
    if (!out) return FILE_ERROR;
    fwrite(&t, sizeof(size_t), 1, out);
    WriteNode(out, root);
    fclose(out);
    return OK;
}

int TBTree::ReadNode(FILE* in, TSmartPointer<TNode>& node) {
    if(fread(&node->leaf, sizeof(bool), 1, in) != 1) return DESERIALIZATION_ERROR;
    size_t elemCount;
    if (fread(&elemCount, sizeof(size_t), 1, in) != 1) return DESERIALIZATION_ERROR;
    node->elem.Resize(elemCount);
    for (size_t i = 0; i < elemCount; i++) {
        TSmartPointer<TElem> elem(new TElem);
        size_t len;
        if (fread(&len, sizeof(len), 1, in) != 1) return DESERIALIZATION_ERROR;
        elem->key = new char[len];
        if (fread(elem->key, sizeof(char)*len, 1, in) != 1) return DESERIALIZATION_ERROR;
        if (fread(&(elem->value), sizeof(elem->value), 1, in) != 1) return DESERIALIZATION_ERROR;
        node->elem.Push(elem);
    }
    if (!node->leaf)
        for (size_t i = 0; i <= elemCount; i++) {
            TSmartPointer<TNode> sNode(new TNode);
            node->child.Push(sNode);
            ReadNode(in, node->child[i]);
        }
    return OK;
}

int TBTree::DeSerialization(char* fileName) {
    FILE *in = fopen(fileName, "rb");
    if (!in) return FILE_ERROR;
    fread(&t, sizeof(size_t), 1, in);
    int buf = ReadNode(in, root);
    fclose(in);
    return buf;
}
