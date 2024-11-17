#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class BST {
private:
//---------------------------------------------------------------------------------------
	struct Node {
		int key;
		Node* l = nullptr, * r = nullptr;
		int height = 1;
		Node(int key) : key(key) {}
	}*root = nullptr;
//---------------------------------------------------------------------------------------


// Функция для получения высоты узла
//---------------------------------------------------------------------------------------
	int height(Node* n) {
		return n ? n->height : 0;
	}
//---------------------------------------------------------------------------------------


// Функция для вычисления баланса узла
//---------------------------------------------------------------------------------------
	int getBalance(Node* n) {
		return n ? height(n->l) - height(n->r) : 0;
	}
//---------------------------------------------------------------------------------------


// Обновляет высоту узла на основе его дочерних узлов
//---------------------------------------------------------------------------------------
	void updateHeight(Node* n) {
		if (n) {
			n->height = 1 + max(height(n->l), height(n->r));
		}
	}
//---------------------------------------------------------------------------------------


// Поворот узла вправо
//---------------------------------------------------------------------------------------
	Node* rotateRight(Node* y) {
		Node* x = y->l;
		Node* t2 = x->r;

		x->r = y;
		y->l = t2;

		updateHeight(y);
		updateHeight(x);

		return x;
	}
//---------------------------------------------------------------------------------------


// Поворот узла влево
//---------------------------------------------------------------------------------------
	Node* rotateLeft(Node* x) {
		Node* y = x->r;
		Node* t2 = y->l;

		y->l = x;
		x->r = t2;

		updateHeight(x);
		updateHeight(y);

		return y;
	}
//---------------------------------------------------------------------------------------


// Проверяет, содержится ли ключ в дереве, подсчитывая шаги
//---------------------------------------------------------------------------------------
	bool contains(Node* n, int key, int& steps) const {
		if (!n) {
			return false;
		}
		steps++;
		if (key == n->key) {
			return true;
		}
		if (key < n->key) {
			return contains(n->l, key, steps);
		}
		else {
			return contains(n->r, key, steps);
		}
	}
//---------------------------------------------------------------------------------------


// Вставляет новый ключ в дерево, балансируя его при необходимости
//---------------------------------------------------------------------------------------
	Node* insert(Node*& n, int key) {
		if (!n) {
			return new Node(key);
		}
		if (key < n->key) {
			n->l = insert(n->l, key);
		}
		else if (key > n->key) {
			n->r = insert(n->r, key);
		}
		else {
			return n;
		}

		updateHeight(n);

		int balance = getBalance(n);

		// LL
		if (balance > 1 && key < n->l->key) {
			return rotateRight(n);
		}

		// RR
		if (balance < -1 && key > n->r->key) {
			return rotateLeft(n);
		}

		// LR
		if (balance > 1 && key > n->l->key) {
			n->l = rotateLeft(n->l);
			return rotateRight(n);
		}

		// RL
		if (balance < -1 && key < n->r->key) {
			n->r = rotateRight(n->r);
			return rotateLeft(n);
		}

		return n;
	}
//---------------------------------------------------------------------------------------


// Удаляет ключ из дерева, балансируя его при необходимости
//---------------------------------------------------------------------------------------
	Node* remove(Node* n, int key) {
		if (!n) {
			return nullptr;
		}
		if (key < n->key) {
			n->l = remove(n->l, key);
		}
		else if (key > n->key) {
			n->r = remove(n->r, key);
		}
		else {
			if (!n->l) {
				Node* temp = n->r;
				delete n;
				return temp;
			}
			else if (!n->r) {
				Node* temp = n->l;
				delete n;
				return temp;
			}
			else {
				Node* minNode = findMin(n->r);
				n->key = minNode->key;
				n->r = remove(n->r, minNode->key);
			}
		}

		updateHeight(n);

		int balance = getBalance(n);

		// RR
		if (balance > 1 && getBalance(n->l) >= 0) {
			return rotateRight(n);
		}

		// LR
		if (balance > 1 && getBalance(n->l) < 0) {
			n->l = rotateLeft(n->l);
			return rotateRight(n);
		}

		// LL
		if (balance < -1 && getBalance(n->r) <= 0) {
			return rotateLeft(n);
		}

		// RL
		if (balance < -1 && getBalance(n->r) > 0) {
			n->r = rotateRight(n->r);
			return rotateLeft(n);
		}

		return n;
	}
//---------------------------------------------------------------------------------------


// Находит узел с минимальным ключом в поддереве
//---------------------------------------------------------------------------------------
	Node* findMin(Node* n) {
		while (n->l)
		{
			n = n->l;;
		}
		return n;
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void printTree(Node* n, const string& prefix = "", bool isLeft = true) const {
		if (n) {
			cout << prefix;

			cout << (isLeft ? "|-- " : "\\-- ");

			cout << n->key << endl;

			printTree(n->l, prefix + (isLeft ? "|   " : "    "), true);
			printTree(n->r, prefix + (isLeft ? "|   " : "    "), false);
		}
	}
//---------------------------------------------------------------------------------------


// Обходит дерево в прямом порядке и выводит ключи
//---------------------------------------------------------------------------------------
	void preOrder(Node* n) const {
		if (n) {
			cout << n->key << " ";
			preOrder(n->l);
			preOrder(n->r);
		}
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void preOrderVec(Node* n, vector<Node*>& nodes) const {
		if (n) {
			nodes.push_back(n);
			preOrderVec(n->l, nodes);
			preOrderVec(n->r, nodes);
		}
	}
//---------------------------------------------------------------------------------------
public:

//---------------------------------------------------------------------------------------
	bool contains(int key) const {
		int steps = 0;
		bool result = contains(root, key, steps);
		cout << "Элемент найден за " << steps << " Шагов" << endl;
		return result;
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void insert(int key) {
		root = insert(root, key);
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void remove(int key) {
		root = remove(root, key);
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void printTree() const {
		if (!root) {
			cout << "Дерево пусто" << endl;
		}
		else {
			printTree(root);
		}
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void preOrder() const {
		preOrder(root);
		cout << endl;
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	vector<Node*> preOrderVec() {
		vector<Node*> nodes;
		preOrderVec(root, nodes);
		return nodes;
	}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
	void cyclicRemoveOddNodes() {
		while (true) {
			vector<Node*> nodes = preOrderVec();
			if (nodes.size() <= 1) {
				cout << "Остался последний элемент: " << (nodes.empty() ? "дерево пусто" : to_string(nodes[0]->key)) << endl;
				break;
			}

			for (size_t i = 0; i < nodes.size(); i++) {
				if ((i + 1) % 2 != 0) {
					remove(nodes[i]->key);
				}
			}

			cout << "Текущее дерево после удаления нечётных узлов:" << endl;
			printTree();
			cout << endl;
		}
	}
//---------------------------------------------------------------------------------------
};

using namespace std;
int main() {
	setlocale(LC_ALL, "RUS");
	BST tree;
	while (true)
	{

		cout << "1 - Добавить элемент в дерево" << endl;
		cout << "2 - Вывести дерево" << endl;
		cout << "3 - найти элемент в дереве" << endl;
		cout << "4 - Удалить элемент из дерева" << endl;
		cout << "5 - удалить всё дерево" << endl;
		cout << "6 - обойти дерево" << endl;
		cout << ">>>>";
		int c;
		cin >> c;
		if(c == 1){
			int num;
			cout << "Введите число>>";
			cin >> num;
			tree.insert(num);
		}
		else if(c==2){
			cout << "Дерево:" << endl;
			tree.printTree();
		}
		else if (c == 3) {
			int num;
			cout << "Введите элемент>>>>" << endl;
			cin >> num;
			tree.contains(num);
		}
		else if (c == 4) {
			int num;
			cout << "Введите элемент>>>>" << endl;
			cin >> num;
			tree.remove(num);
		}
		else if (c == 5) {
			tree.cyclicRemoveOddNodes();
		}
		else if (c == 6) {
			tree.preOrder();
		}
		else {
			break;
		}
	}
};