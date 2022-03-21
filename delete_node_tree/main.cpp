/*
 * ID 
 * Спринт 5. Задача B "Удали узел"
 * Палкин Богдан. Когорта 20.
 * 
 * -- ПРИНИП РАБОТЫ --
 * 
 * В данном задании требуется реализовать функцию, удаляющую
 * узел из дерева.
 * 
 * Решение задачи основано на материале из видео, доступного по
 * следующей ссылке:
 *     https://www.youtube.com/watch?v=gcULXE7ViZw
 * 
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 * 
 * Доказательство можно провести для трёх случаев, которые зависят
 * от того, сколько потомков есть у удаляемой вершины. Оно будет строится
 * на  соответствии реализации теоретическому алгоритму.
 * 
 *     1. Удаляемая вершина лист. В таком случае алгоритм присвоит этой 
 *        вершине nullptr;
 *     2. У удаляемой вершины есть один потомок(правый или левый). 
 *        В этом случае потомок присоединяется к непосредственному предку
 *        удаляемой вершины.
 *     3. У удаляемой вершины есть оба потомка.
 *        В этом случае находится вершина, которая заменит удаляемый узел.
 *        В данной реализации этой вершиной будет самый левый узел в правом
 *        поддереве. После этого копируем хранящийся ключ из вершины, найденной
 *        на замену, в текущую вершину и рекурсивно удаляем потомки найденной
 *        на замену вершины пока не попадём в один из первых двух случаев.
 * 
 * В результате всех этих вариантов возвращается указатель на корень обновлённого
 * дерева.
 * 
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 * 
 * Сложность работы алгоритма зависит от места, в котором находится узел, 
 * который нужно удалить. В любом случае сложность не превышает O(h), где
 * h - высота дерева.
 * 
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 * 
 * Алгоритм не требует дополнительной памяти для своей работы.
 */

//Comment it before submitting
struct Node {
  Node* left;
  Node* right;
  int value;
};


//#include "solution.h"
#include <cassert>

Node* findReplacement(Node* node)
{
    Node* temp = node;

    while (temp && root->left != nullptr)
    {
        temp = root->left;
    }

    return temp;
}

Node* remove(Node* root, int key) {
    if (root == nullptr)
    {
        return root;
    }

    if (key < root->value)
    {
        root->left = remove(root->left, key);
    }
    else if (key > root->value)
    {
        root->right = remove(root->right, key);
    }
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            return nullptr;
        }
        else if(root->left == nullptr)
        {
            Node* temp = root->right;
            root = nullptr;
            return temp;
        }
        else if(root->right == nullptr)
        {
            Node* temp = root->left;
            root = nullptr;
            return temp;
        }
        else
        {
            Node* temp = findReplacement(root->right);
            root->value = temp->value;
            root->right = remove(root->right, temp->value);
        }
    }
    return root;
}

void test() {
    Node node1({nullptr, nullptr, 14});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}
