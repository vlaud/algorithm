// ============================================================
// Red-Black Tree — 학습용 구현
// ------------------------------------------------------------
//  섹션 구성:
//    1) 기본 타입 (Color, Node)
//    2) RedBlackTree 선언
//    3) 회전 (Left/Right Rotate)
//    4) 삽입 + InsertFixup (3 Cases)
//    5) 삭제 + DeleteFixup (4 Cases)   ← 원본 코드에 빠져 있던 부분
//    6) 탐색 & 순회 (in-order, level-order)
//    7) 시각화 (ANSI 컬러 + 레벨 출력)
//    8) 속성 검증 (5가지 속성 + Black Height)
//    9) 데모 main
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <string>

// ============================================================
// 1. 기본 타입
// ============================================================

enum class Color { Red, Black };

struct Node
{
    int   Key;
    Color Col;
    Node* Left;
    Node* Right;
    Node* Parent;

    Node(int k, Color c = Color::Red)
        : Key(k), Col(c), Left(nullptr), Right(nullptr), Parent(nullptr) {}
};

// ============================================================
// 2. RedBlackTree 클래스
// ============================================================

class RedBlackTree
{
public:
    RedBlackTree()
    {
        // NIL 센티넬: 모든 리프를 대체하는 검정 더미 노드.
        //  - 자기참조로 초기화해 두면 어느 포인터로 접근해도 NPE 없음.
        NIL = new Node(0, Color::Black);
        NIL->Left = NIL->Right = NIL->Parent = NIL;
        mRoot = NIL;
    }

    ~RedBlackTree()
    {
        destroyRec(mRoot);
        delete NIL;
    }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    // ----- Public API -----
    void  Insert(int key);
    bool  Remove(int key);                 // 성공 시 true
    Node* Search(int key) const;

    std::vector<int> InOrder() const;
    int   BlackHeight() const;             // -1 이면 속성 위반
    bool  Validate()    const;

    void  PrintTree()   const;             // 우측이 위, 좌측이 아래로
    void  PrintLevels() const;             // BFS 레벨 출력

    Node* GetRoot() const { return mRoot; }
    Node* GetNil()  const { return NIL; }

private:
    Node* mRoot;
    Node* NIL;

    // --- 회전 ---
    void  LeftRotate(Node* x);
    void  RightRotate(Node* y);

    // --- 삽입 ---
    void  InsertFixup(Node* z);

    // --- 삭제 ---
    void  Transplant(Node* u, Node* v);    // u 자리에 v 를 이식
    Node* Minimum(Node* x) const;
    void  DeleteFixup(Node* x);

    // --- 유틸 ---
    void  destroyRec(Node* node);
    void  inOrderRec(Node* node, std::vector<int>& out) const;
    int   validateRec(Node* node) const;
    void  printRec(Node* node, int depth) const;
};

// ============================================================
// 3. 회전 (Rotation)
//   - BST 순서는 보존되고 색은 건드리지 않는 O(1) 연산.
//   - LeftRotate 와 RightRotate 는 정확히 서로의 역연산.
// ============================================================

void RedBlackTree::LeftRotate(Node* x)
{
    // y = x 의 오른쪽 자식. y 가 x 의 자리로 올라간다.
    Node* y = x->Right;

    // 1) y 의 왼쪽 서브트리(β) → x 의 오른쪽
    x->Right = y->Left;
    if (y->Left != NIL) y->Left->Parent = x;

    // 2) y 를 x 의 자리에 연결 (루트 케이스 포함)
    y->Parent = x->Parent;
    if (x->Parent == NIL)        mRoot = y;
    else if (x == x->Parent->Left)    x->Parent->Left = y;
    else                              x->Parent->Right = y;

    // 3) x 를 y 의 왼쪽 자식으로
    y->Left = x;
    x->Parent = y;
}

void RedBlackTree::RightRotate(Node* y)
{
    Node* x = y->Left;

    y->Left = x->Right;
    if (x->Right != NIL) x->Right->Parent = y;

    x->Parent = y->Parent;
    if (y->Parent == NIL)        mRoot = x;
    else if (y == y->Parent->Left)    y->Parent->Left = x;
    else                              y->Parent->Right = x;

    x->Right = y;
    y->Parent = x;
}

// ============================================================
// 4. 삽입
// ============================================================

void RedBlackTree::Insert(int key)
{
    Node* z = new Node(key, Color::Red);   // 새 노드는 항상 RED
    z->Left = NIL;
    z->Right = NIL;

    // --- 표준 BST 삽입 ---
    Node* parent = NIL;
    Node* cur = mRoot;
    while (cur != NIL)
    {
        parent = cur;
        cur = (key < cur->Key) ? cur->Left : cur->Right;
    }
    z->Parent = parent;
    if (parent == NIL)         mRoot = z;
    else if (key < parent->Key)     parent->Left = z;
    else                            parent->Right = z;

    // --- RB 속성 복구 ---
    InsertFixup(z);
}

// InsertFixup: 부모가 RED 일 때만 속성 4(연속 RED) 를 위반한다.
//   부모가 조부모의 "왼쪽" 자식인 경우 기준:
//     Case 1 : 삼촌 = RED
//              → 부모/삼촌 BLACK, 조부모 RED, z ← 조부모 (위로 전파)
//     Case 2 : 삼촌 = BLACK, z 가 꺾인 모양 (부모의 오른쪽)
//              → z ← 부모, LeftRotate(z)  ⇒ Case 3 모양으로 정렬
//     Case 3 : 삼촌 = BLACK, z 가 일직선   (부모의 왼쪽)
//              → 부모 BLACK, 조부모 RED, RightRotate(조부모)  (루프 종료)
//   부모가 오른쪽 자식이면 좌우 대칭.
void RedBlackTree::InsertFixup(Node* z)
{
    while (z->Parent->Col == Color::Red)
    {
        Node* gp = z->Parent->Parent;

        if (z->Parent == gp->Left)
        {
            Node* uncle = gp->Right;

            if (uncle->Col == Color::Red)                // Case 1
            {
                z->Parent->Col = Color::Black;
                uncle->Col = Color::Black;
                gp->Col = Color::Red;
                z = gp;
            }
            else
            {
                if (z == z->Parent->Right)               // Case 2
                {
                    z = z->Parent;
                    LeftRotate(z);
                }
                z->Parent->Col = Color::Black;   // Case 3
                z->Parent->Parent->Col = Color::Red;
                RightRotate(z->Parent->Parent);
            }
        }
        else  // 좌우 대칭
        {
            Node* uncle = gp->Left;

            if (uncle->Col == Color::Red)                // Case 1'
            {
                z->Parent->Col = Color::Black;
                uncle->Col = Color::Black;
                gp->Col = Color::Red;
                z = gp;
            }
            else
            {
                if (z == z->Parent->Left)                // Case 2'
                {
                    z = z->Parent;
                    RightRotate(z);
                }
                z->Parent->Col = Color::Black;   // Case 3'
                z->Parent->Parent->Col = Color::Red;
                LeftRotate(z->Parent->Parent);
            }
        }
    }
    mRoot->Col = Color::Black;   // 루트는 항상 BLACK
}

// ============================================================
// 5. 삭제 (CLRS 기준)
//   RB Tree 에서 가장 까다로운 부분. 학습 필수.
// ============================================================

// u 의 자리에 v 를 이식한다. v 의 자식은 호출자가 처리.
// v 가 NIL 이어도 NIL->Parent 를 세팅해 두어야 DeleteFixup 이 동작함.
void RedBlackTree::Transplant(Node* u, Node* v)
{
    if (u->Parent == NIL)        mRoot = v;
    else if (u == u->Parent->Left)    u->Parent->Left = v;
    else                              u->Parent->Right = v;
    v->Parent = u->Parent;
}

Node* RedBlackTree::Minimum(Node* x) const
{
    while (x->Left != NIL) x = x->Left;
    return x;
}

bool RedBlackTree::Remove(int key)
{
    Node* z = Search(key);
    if (z == NIL) return false;

    Node* y = z;                       // 실제 "이동/삭제되는" 노드
    Node* x;                           // y 자리를 대체하는 노드 (Fixup 기준점)
    Color yOrigColor = y->Col;

    if (z->Left == NIL)
    {
        x = z->Right;
        Transplant(z, z->Right);
    }
    else if (z->Right == NIL)
    {
        x = z->Left;
        Transplant(z, z->Left);
    }
    else
    {
        // 두 자식이 있으면 오른쪽 서브트리의 최솟값(= 후계자)으로 대체
        y = Minimum(z->Right);
        yOrigColor = y->Col;
        x = y->Right;
        if (y->Parent == z)
        {
            x->Parent = y;             // x 가 NIL 이어도 반드시 설정
        }
        else
        {
            Transplant(y, y->Right);
            y->Right = z->Right;
            y->Right->Parent = y;
        }
        Transplant(z, y);
        y->Left = z->Left;
        y->Left->Parent = y;
        y->Col = z->Col;
    }
    delete z;

    // 사라진/이동한 노드가 BLACK 이었다면 Black Height 가 깨졌으므로 복구
    if (yOrigColor == Color::Black) DeleteFixup(x);
    return true;
}

// DeleteFixup: "x 쪽 경로에 검정이 하나 부족하다(doubly-black)" 는 상태 해소.
//   형제 w 의 상태에 따라 4 Case (x 가 왼쪽 자식 기준, 반대는 대칭):
//     Case 1 : w = RED
//              → w BLACK, 부모 RED, LeftRotate(부모) ⇒ Case 2/3/4 로
//     Case 2 : w BLACK, w 의 두 자식 모두 BLACK
//              → w RED, x ← 부모 (여분 검정을 위로 전파)
//     Case 3 : w BLACK, w 의 먼쪽 자식 BLACK, 가까운쪽 자식 RED
//              → 회전 + 재채색  ⇒ Case 4 로
//     Case 4 : w BLACK, w 의 먼쪽 자식 RED
//              → 회전 + 재채색 (루프 종료)
void RedBlackTree::DeleteFixup(Node* x)
{
    while (x != mRoot && x->Col == Color::Black)
    {
        if (x == x->Parent->Left)
        {
            Node* w = x->Parent->Right;

            if (w->Col == Color::Red)                         // Case 1
            {
                w->Col = Color::Black;
                x->Parent->Col = Color::Red;
                LeftRotate(x->Parent);
                w = x->Parent->Right;
            }
            if (w->Left->Col == Color::Black &&
                w->Right->Col == Color::Black)                // Case 2
            {
                w->Col = Color::Red;
                x = x->Parent;
            }
            else
            {
                if (w->Right->Col == Color::Black)            // Case 3
                {
                    w->Left->Col = Color::Black;
                    w->Col = Color::Red;
                    RightRotate(w);
                    w = x->Parent->Right;
                }
                w->Col = x->Parent->Col;             // Case 4
                x->Parent->Col = Color::Black;
                w->Right->Col = Color::Black;
                LeftRotate(x->Parent);
                x = mRoot;   // 루프 탈출
            }
        }
        else  // 좌우 대칭
        {
            Node* w = x->Parent->Left;

            if (w->Col == Color::Red)
            {
                w->Col = Color::Black;
                x->Parent->Col = Color::Red;
                RightRotate(x->Parent);
                w = x->Parent->Left;
            }
            if (w->Right->Col == Color::Black &&
                w->Left->Col == Color::Black)
            {
                w->Col = Color::Red;
                x = x->Parent;
            }
            else
            {
                if (w->Left->Col == Color::Black)
                {
                    w->Right->Col = Color::Black;
                    w->Col = Color::Red;
                    LeftRotate(w);
                    w = x->Parent->Left;
                }
                w->Col = x->Parent->Col;
                x->Parent->Col = Color::Black;
                w->Left->Col = Color::Black;
                RightRotate(x->Parent);
                x = mRoot;
            }
        }
    }
    x->Col = Color::Black;
}


// ============================================================
// 6. 탐색 & 순회
// ============================================================

Node* RedBlackTree::Search(int key) const
{
    Node* cur = mRoot;
    while (cur != NIL && cur->Key != key)
    {
        cur = (key < cur->Key) ? cur->Left : cur->Right;
    }
    return cur;   // 못 찾으면 NIL
}

std::vector<int> RedBlackTree::InOrder() const
{
    std::vector<int> out;
    inOrderRec(mRoot, out);
    return out;
}

void RedBlackTree::inOrderRec(Node* node, std::vector<int>& out) const
{
    if (node == NIL) return;
    inOrderRec(node->Left, out);
    out.push_back(node->Key);
    inOrderRec(node->Right, out);
}

// ============================================================
// 7. 시각화
// ============================================================

void RedBlackTree::PrintTree() const
{
    if (mRoot == NIL) { std::cout << "(empty)\n"; return; }
    printRec(mRoot, 0);
}

void RedBlackTree::printRec(Node* node, int depth) const
{
    // ANSI: 빨강 = 굵은 빨강, 검정 = 굵은 흰색(어두운 터미널 대비용)
    static const char* CLR_RED = "\033[1;31m";
    static const char* CLR_BLACK = "\033[1;37m";
    static const char* CLR_RESET = "\033[0m";

    if (node == NIL) return;

    printRec(node->Right, depth + 1);

    for (int i = 0; i < depth; ++i) std::cout << "    ";
    std::cout << (node->Col == Color::Red ? CLR_RED : CLR_BLACK)
        << node->Key
        << (node->Col == Color::Red ? "(R)" : "(B)")
        << CLR_RESET << "\n";

    printRec(node->Left, depth + 1);
}

void RedBlackTree::PrintLevels() const
{
    if (mRoot == NIL) { std::cout << "(empty)\n"; return; }

    std::queue<std::pair<Node*, int>> q;
    q.push({ mRoot, 0 });
    int curLevel = -1;

    while (!q.empty())
    {
        auto [n, lvl] = q.front();
        q.pop();

        if (lvl != curLevel)
        {
            if (curLevel != -1) std::cout << "\n";
            std::cout << "L" << lvl << ": ";
            curLevel = lvl;
        }
        std::cout << n->Key
            << (n->Col == Color::Red ? "(R) " : "(B) ");

        if (n->Left != NIL) q.push({ n->Left,  lvl + 1 });
        if (n->Right != NIL) q.push({ n->Right, lvl + 1 });
    }
    std::cout << "\n";
}

// ============================================================
// 8. 검증 — 5가지 속성 모두 체크
// ============================================================

bool RedBlackTree::Validate() const
{
    // 속성 2: 루트는 BLACK
    if (mRoot != NIL && mRoot->Col != Color::Black) return false;
    // 속성 3: NIL 은 BLACK (생성자에서 보장)
    if (NIL->Col != Color::Black) return false;
    // 속성 1 은 enum 으로 보장됨. 속성 4, 5 는 재귀로 검증.
    return validateRec(mRoot) != -1;
}

// 반환값: 해당 서브트리의 Black Height (속성 4 또는 5 위반 시 -1)
int RedBlackTree::validateRec(Node* node) const
{
    if (node == NIL) return 1;   // NIL 은 BLACK 이므로 높이 1

    // 속성 4: RED 의 자식은 모두 BLACK
    if (node->Col == Color::Red)
    {
        if (node->Left->Col == Color::Red) return -1;
        if (node->Right->Col == Color::Red) return -1;
    }

    int lh = validateRec(node->Left);
    int rh = validateRec(node->Right);
    if (lh == -1 || rh == -1 || lh != rh) return -1;   // 속성 5

    return lh + (node->Col == Color::Black ? 1 : 0);
}

int RedBlackTree::BlackHeight() const
{
    return validateRec(mRoot);
}

// ============================================================
// 9. 유틸
// ============================================================

void RedBlackTree::destroyRec(Node* node)
{
    if (node == NIL) return;
    destroyRec(node->Left);
    destroyRec(node->Right);
    delete node;
}

// ============================================================
// 10. 데모 main
// ============================================================

static void section(const std::string& title)
{
    std::cout << "\n===== " << title << " "
        << std::string(std::max(0, 44 - (int)title.size()), '=') << "\n";
}

int main()
{
    RedBlackTree tree;

    section("Insert demo");
    std::vector<int> inserts = { 20, 10, 30, 5, 15, 25, 35, 1, 8, 40, 50 };
    for (int v : inserts)
    {
        tree.Insert(v);
        std::cout << "[+" << v << "] valid=" << (tree.Validate() ? "O" : "X")
            << "  bh=" << tree.BlackHeight() << "\n";
    }

    section("Tree (rotated: right=top, left=bottom)");
    tree.PrintTree();

    section("Level order");
    tree.PrintLevels();

    section("In-order (sorted result)");
    for (int v : tree.InOrder()) std::cout << v << " ";
    std::cout << "\n";

    section("Search");
    for (int v : { 15, 99, 1, 35 })
    {
        Node* n = tree.Search(v);
        if (n != tree.GetNil())
            std::cout << "found " << v << " ("
            << (n->Col == Color::Red ? "R" : "B") << ")\n";
        else
            std::cout << "not found " << v << "\n";
    }

    section("Delete demo (루트/내부/리프 골고루)");
    for (int v : { 10, 20, 1, 50, 25 })
    {
        bool ok = tree.Remove(v);
        std::cout << "[-" << v << "] ok=" << (ok ? "O" : "X")
            << "  valid=" << (tree.Validate() ? "O" : "X")
            << "  bh=" << tree.BlackHeight() << "\n";
    }

    section("After deletes");
    tree.PrintTree();

    section("Final in-order");
    for (int v : tree.InOrder()) std::cout << v << " ";
    std::cout << "\n";

    return 0;
}