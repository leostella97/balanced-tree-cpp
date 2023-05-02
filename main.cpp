#include <iostream>
using namespace std;

// Definição da estrutura da árvore
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // inicialmente a altura é 1
    return(node);
}

// Função para obter a altura de um nó
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Função para calcular o fator de balanceamento de um nó
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Função para realizar a rotação simples à direita em um nó
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // realiza a rotação
    x->right = y;
    y->left = T2;

    // atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // retorna o novo nó raiz
    return x;
}

// Função para realizar a rotação simples à esquerda em um nó
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // realiza a rotação
    y->left = x;
    x->right = T2;

    // atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // retorna o novo nó raiz
    return y;
}

// Função para inserir um nó na árvore
Node* insert(Node* node, int key) {
    // realiza a inserção como em uma árvore binária de busca
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // chave já existe, não faz nada
        return node;

    // atualiza a altura do nó
    node->height = 1 + max(height(node->left), height(node->right));

    // calcula o fator de balanceamento do nó
    int balance = getBalance(node);

    // realiza as rotações necessárias para balancear a árvore
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
        node->right = rotateRight(node->right);
    return rotateLeft(node);

    // retorna o nó raiz atualizado
    return node;
}

// Função para imprimir a árvore em ordem
void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}

// Função principal
int main() {
    Node* root = NULL;
    int n, x;
    cout << "Digite o número de elementos da árvore: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Digite o " << i+1 << "º elemento: ";
        cin >> x;
        root = insert(root, x);
    }
    cout << "Árvore balanceada em ordem: ";
    inorder(root);
    cout << endl;
    return 0;
}

