template<class T>
class BST{
private:
    int n;
    T *v;
    int vn;
    struct node {
        T val;
        node *left, *right;
        node(T v) { val = v; left = right = 0; }
    };
    node *root;
    node *rinsert(node *p, T t){
        if (p == 0){
            p = new node(t);
            n++;
        }else if (t < p->val){
            p->left = rinsert (p->left, t);
        }else if (t > p->val){
            p->right = rinsert (p->right, t);
        }
        // p->val == t;
        return p;
    }
    void rdelete(node *p){
        if (p->left) rdelete(p->left);
        if (p->right) rdelete(p->right);
        delete p;
        
    }
    void traverse(node *p){
        if (p == 0) return;
        traverse(p->left);
        v[vn++] = p->val;
        traverse(p->right);
    }

public:
    BST() { root = 0; n = 0; }
    int size() { return n;}
    void insert(T t) { root = rinsert(root, t); }
    void clear(){ rdelete(root); root = 0; n = 0;}
    void report(T * x) { v = x; vn = 0; traverse(root); }
};