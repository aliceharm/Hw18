#include <iostream>
#include <string>

using namespace std;

class Player {
    string name;
    int count;

public:
    string getName() const {
        return name;
    }
    int getCount() const {
        return count;
    }
    void setName(string n) {
        name = n;
    }
    void setCount(int c) {
        count = c;
    }
};

// Узел бинарного дерева
struct TreeNode {
    Player player;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Player& p) : player(p), left(nullptr), right(nullptr) {}
};

// Вставка игрока в бинарное дерево поиска
TreeNode* insert(TreeNode* root, const Player& player) {
    if (root == nullptr) {
        return new TreeNode(player);
    }

    if (player.getCount() < root->player.getCount()) {
        root->right = insert(root->right, player);
    }
    else {
        root->left = insert(root->left, player);
    }

    return root;
}

// Обход дерева с сохранением данных в массиве
void inOrder(TreeNode* root, Player* players, int& index) {
    if (root == nullptr) {
        return;
    }

    inOrder(root->left, players, index);
    players[index++] = root->player; // Записываем игрока в массив
    inOrder(root->right, players, index);
}

// Освобождение памяти дерева
void freeTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    int n;

    cout << "Enter num of players: ";
    cin >> n;

    Player* playersArray = new Player[n];
    TreeNode* root = nullptr;

    for (int i = 0; i < n; i++) {
        string name;
        int point;
        cout << "Enter NAME for player " << i + 1 << ": ";
        cin >> name;
        cout << "Enter POINTS for player " << i + 1 << ": ";
        cin >> point;
        playersArray[i].setName(name);
        playersArray[i].setCount(point);

        // Вставляем игрока в бинарное дерево
        root = insert(root, playersArray[i]);
    }

    // Создаем массив для хранения отсортированных игроков
    Player* sortedPlayers = new Player[n];
    int index = 0;

    // Обходим дерево и заполняем отсортированный массив
    inOrder(root, sortedPlayers, index);

    cout << "\nPlayers sorted by points:\n";
    for (int i = 0; i < n; i++) {
        cout << sortedPlayers[i].getName() << " " << sortedPlayers[i].getCount() << '\n';
    }

    // Освобождение памяти
    freeTree(root);
    delete[] playersArray;
    delete[] sortedPlayers;

    return 0;
}