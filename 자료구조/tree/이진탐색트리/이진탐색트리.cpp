/*
자료 구조와 함께 배우는 알고리즘 입문(C언어) 책을 보고 구현한 이진 탐색 트리
*/
struct BinNode 
{
    BinNode* left;
    BinNode* right;
    int data;
    BinNode(int _data) : data(_data), left(nullptr), right(nullptr) {  }
};

// 검색
BinNode* Find(BinNode* p,const int x)
{
    if (nullptr == p)
    {
        return nullptr;
    }

    if (p->data == x)
    {
        return p;
    }
    else if (p->data < x)
    {
        return Find(p->right, x);
    }
    else 
    {
        return Find(p->left, x);
    }
}
// 삽입
BinNode* Add(BinNode* p, const int x) 
{
    if (nullptr == p)
    {
        p = new BinNode(x);
    }

    if (p->data == x)
    {
        return p;
    }
    else if (p->data < x)
    {
        p->right = Add(p->right, x);
    }
    else
    {
        p->left = Add(p->left, x);
    }

    return p;
}

// 삭제
BinNode* Remove(BinNode* p, const int x)
{
    if (x < p->data) 
    {
        p->left = Remove(p->left, x);
    }
    else if (x > p->data) 
    {
        p->right = Remove(p->right, x);
    }
    else 
    {
        if (p->left == nullptr) 
        {
            BinNode* rightChild = p->right;
            delete p;
            return rightChild;
        }
        else if (p->right == nullptr) 
        {
            BinNode* leftChild = p->left;
            delete p;
            return leftChild;
        }
        else 
        {
            BinNode* minNode = p->right;

            while (minNode->left != nullptr) 
            {
                minNode = minNode->left;
            }

            p->data = minNode->data; 
            p->right = Remove(p->right, minNode->data); 
        }
    }
    return p;
}

// 출력
void PrintTree(const BinNode* p) 
{
    if (nullptr == p)
    {
        return;
    }

    PrintTree(p->left);
    cout << p->data <<' ';
    PrintTree(p->right);

}

void FreeTree(BinNode* p) 
{
    if (p == nullptr) return;

    FreeTree(p->left);
    FreeTree(p->right);
    delete p;
}

int main()
{
    BinNode* root = nullptr;

    // 트리에 값 삽입
    root = Add(root, 4);
    root = Add(root, 2);
    root = Add(root, 6);
    root = Add(root, 1);
    root = Add(root, 3);
    root = Add(root, 5);
    root = Add(root, 7);

    cout << "Initial tree (in-order): ";
    PrintTree(root);
    cout << endl;

    // 검색 테스트
    int searchValue = 3;
    BinNode* found = Find(root, searchValue);
    if (found) {
        cout << "Found: " << found->data << endl;
    }
    else {
        cout << searchValue << " not found in the tree." << endl;
    }

    // 삭제 테스트
    root = Remove(root, 3);
    cout << "After removing 3: ";
    PrintTree(root);
    cout << endl;

    root = Remove(root, 4);
    cout << "After removing 4: ";
    PrintTree(root);
    cout << endl;

    // 메모리 해제
    FreeTree(root);

    return 0;
}
