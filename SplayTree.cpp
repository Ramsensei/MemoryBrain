#include <bits/stdc++.h>
#include <cstdio>
#include "dataStruct.cpp"
using namespace std;

// An Splay tree node
class node
{
public:
    int key;
    card *data;
    node *left, *right;
};
class SplayTree
{
public:
    node *root;

    SplayTree()
    {
        root = NULL;
    }

    /* Helper function that allocates
    a new node with the given key and
        NULL left and right pointers. */
    node *newNode(card *d)
    {
        node *Node = new node();
        Node->key = d->id;
        Node->data = d;
        Node->left = Node->right = NULL;
        return (Node);
    }

    // A utility function to right
    // rotate subtree rooted with y
    // See the diagram given above.
    node *rightRotate(node *x)
    {
        node *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    // A utility function to left
    // rotate subtree rooted with x
    // See the diagram given above.
    node *leftRotate(node *x)
    {
        node *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // This function brings the key at
    // root if key is present in tree.
    // If key is not present, then it
    // brings the last accessed item at
    // root. This function modifies the
    // tree and returns the new root
    node *splay(node *root, int key)
    {
        // Base cases: root is NULL or
        // key is present at root
        if (root == NULL || root->key == key)
            return root;

        // Key lies in left subtree
        if (root->key > key)
        {
            // Key is not in tree, we are done
            if (root->left == NULL)
                return root;

            // Zig-Zig (Left Left)
            if (root->left->key > key)
            {
                // First recursively bring the
                // key as root of left-left
                root->left->left = splay(root->left->left, key);

                // Do first rotation for root,
                // second rotation is done after else
                root = rightRotate(root);
            }
            else if (root->left->key < key) // Zig-Zag (Left Right)
            {
                // First recursively bring
                // the key as root of left-right
                root->left->right = splay(root->left->right, key);

                // Do first rotation for root->left
                if (root->left->right != NULL)
                    root->left = leftRotate(root->left);
            }

            // Do second rotation for root
            return (root->left == NULL) ? root : rightRotate(root);
        }
        else // Key lies in right subtree
        {
            // Key is not in tree, we are done
            if (root->right == NULL)
                return root;

            // Zig-Zag (Right Left)
            if (root->right->key > key)
            {
                // Bring the key as root of right-left
                root->right->left = splay(root->right->left, key);

                // Do first rotation for root->right
                if (root->right->left != NULL)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->key < key) // Zag-Zag (Right Right)
            {
                // Bring the key as root of
                // right-right and do first rotation
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }

            // Do second rotation for root
            return (root->right == NULL) ? root : leftRotate(root);
        }
    }

    // Function to insert a new key k
    // in splay tree with given root
    node *insert(card *c)
    {
        int k = c->id;
        // Simple Case: If tree is empty
        if (root == NULL)
        {
            root = newNode(c);
            return root;
        }
        // Bring the closest leaf node to root
        root = splay(root, k);

        // If key is already present, then return
        if (root->key == k)
            return root;

        // Otherwise allocate memory for new node
        node *newnode = newNode(c);

        // If root's key is greater, make
        // root as right child of newnode
        // and copy the left child of root to newnode
        if (root->key > k)
        {
            newnode->right = root;
            newnode->left = root->left;
            root->left = NULL;
        }

        // If root's key is smaller, make
        // root as left child of newnode
        // and copy the right child of root to newnode
        else
        {
            newnode->left = root;
            newnode->right = root->right;
            root->right = NULL;
        }
        root = newnode;
        return newnode; // newnode becomes new root
    }

    // A utility function to print
    // preorder traversal of the tree.
    // The function also prints height of every node
    void preOrder()
    {
        preOrder(this->root);
    }
    void preOrder(node *root)
    {
        if (root != NULL)
        {
            cout << "(" << root->key << ", " << root->data->type << ") " << endl;
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    void Alola(node *a, int espacios = 0)
    {
        if (a != NULL)
        {
            if (a->left)
            {
                Alola(a->left, espacios + 4);
            }
            if (a->right)
            {
                Alola(a->right, espacios + 4);
            }
            if (espacios)
            {
                std::cout << std::setw(espacios) << ' ';
            }
            cout << a->key << "\n ";
        }
    }
    card *search(int key)
    {
        root = splay(root, key);
        if (root->key == key)
            return root->data;
        else
            return NULL;
    }

    node *findLast(int prevNode = 0, std::string path = "")
    {
        if (path == "")
            std::string path = getMayorPath();
        node *temp = root;
        while (path.size() > prevNode)
        {
            if (path.substr(0, 1) == "r")
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
            path = path.substr(1);
        }
        return temp;
    }

    void replaceLast(card *c)
    {
        deleteLast();
        insert(c);
    }

    void deleteLast()
    {
        std::string path = getMayorPath();
        char step = path.back();

        node *aux = findLast(1, path);
        node *toDel = NULL;

        if (step == 'r')
        {
            toDel = aux->right;
            aux->right = NULL;
        }
        else
        {
            toDel = aux->left;
            aux->left = NULL;
        }
        delete toDel;
        toDel = nullptr;
    }

    std::string getMayorPath()
    {
        return getMayorPath(this->root);
    }

    std::string getMayorPath(node *root, std::string path = "")
    {
        if (root == NULL)
            return "";
        if (root->left == NULL && root->right == NULL)
            return path;
        if (root->left == NULL)
            return getMayorPath(root->right, path + "r");
        if (root->right == NULL)
            return getMayorPath(root->left, path + "l");

        std::string left = getMayorPath(root->left, path + "l");
        std::string right = getMayorPath(root->right, path + "r");

        if (left.size() > right.size())
            return left;
        else
            return right;
    }
};
/* Driver code*/
// int main()
// {
//     SplayTree tree = SplayTree();
//     card *c = new card();
//     c->id = 11;
//     c->type = 3;
//     c->status = 3;
//     c->img = "img";
//     tree.insert(c);
//     c->id = 12;
//     tree.insert(c);
//     c->id = 13;
//     tree.insert(c);
//     c->id = 24;
//     tree.insert(c);
//     c->id = 32;
//     tree.insert(c);
//     c->id = 63;
//     tree.insert(c);
//     c->id = 34;
//     tree.insert(c);
//     tree.search(13);
//     tree.search(63);
//     tree.search(24);
//     c->id = 90;
//     cout << "Preorder traversal of the modified Splay tree is \n";
//     tree.Alola(tree.root);
//     tree.replaceLast(c);
//     cout << "Preorder traversal of the modified Splay tree is \n";
//     tree.Alola(tree.root);
//     tree.deleteLast();
//     cout << "Preorder traversal of the modified Splay tree is \n";
//     tree.Alola(tree.root);
//     return 0;
// }
