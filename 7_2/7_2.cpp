#include <algorithm>
#include <iostream>
#include <string>

using namespace std;


struct Node
{

    string Key;

    Node* Left;

    Node* Right;

    int Height;


    Node( string k ) : Key( k ), Height( 1 ), Left( nullptr ), Right( nullptr )
    {
    }

};


class AVLTree
{

private:

    int Height( Node* n )
    {
        return n == nullptr ? 0 : n->Height;
    }

    int GetBalance( Node* n )
    {
        return n == nullptr ? 0 : Height( n->Left ) - Height( n->Right );
    }

    void UpdateHeight( Node* n )
    {
        if ( n )
            n->Height = 1 + max( Height( n->Left ), Height( n->Right ) );
    }

    Node* RotateRight( Node* y )
    {
        Node* x = y->Left;
        Node* T = x->Right;

        x->Right = y;
        y->Left = T;

        UpdateHeight( y );
        UpdateHeight( x );

        return x;
    }

    Node* RotateLeft( Node* x )
    {
        Node* y = x->Right;
        Node* T = y->Left;

        y->Left = x;
        x->Right = T;

        UpdateHeight( x );
        UpdateHeight( y );

        return y;
    }

    Node* Insert( Node* node, string Key )
    {
        if ( node == nullptr )
            return new Node( Key );

        if ( Key < node->Key )
            node->Left = Insert( node->Left, Key );
        else if ( Key > node->Key )
            node->Right = Insert( node->Right, Key );
        else
            return node;

        UpdateHeight( node );

        int balance = GetBalance( node );

        if ( balance > 1 && Key < node->Left->Key )
            return RotateRight( node );

        if ( balance < -1 && Key > node->Right->Key )
            return RotateLeft( node );

        if ( balance > 1 && Key > node->Left->Key )
        {
            node->Left = RotateLeft( node->Left );
            return RotateRight( node );
        }

        if ( balance < -1 && Key < node->Right->Key )
        {
            node->Right = RotateRight( node->Right );
            return RotateLeft( node );
        }

        return node;
    }

    Node* Remove( Node* node, string Key )
    {
        if ( node == nullptr )
            return node;

        if ( Key < node->Key )
        {
            node->Left = Remove( node->Left, Key );
        }
        else if ( Key > node->Key )
        {
            node->Right = Remove( node->Right, Key );
        }
        else
        {
            if ( node->Left == nullptr || node->Right == nullptr )
            {
                Node* temp = node->Left ? node->Left : node->Right;

                if ( temp == nullptr )
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node* temp = MinValueNode( node->Right );
                node->Key = temp->Key;
                node->Right = Remove( node->Right, temp->Key );
            }
        }

        if ( node == nullptr )
            return node;

        UpdateHeight( node );

        int balance = GetBalance( node );

        if ( balance > 1 && GetBalance( node->Left ) >= 0 )
            return RotateRight( node );

        if ( balance > 1 && GetBalance( node->Left ) < 0 )
        {
            node->Left = RotateLeft( node->Left );
            return RotateRight( node );
        }

        if ( balance < -1 && GetBalance( node->Right ) <= 0 )
            return RotateLeft( node );

        if ( balance < -1 && GetBalance( node->Right ) > 0 )
        {
            node->Right = RotateRight( node->Right );
            return RotateLeft( node );
        }

        return node;
    }

    Node* MinValueNode( Node* node )
    {
        Node* current = node;

        while ( current->Left != nullptr )
            current = current->Left;

        return current;
    }

    void PreOrder( Node* node )
    {
        if ( node != nullptr )
        {
            cout << node->Key << " ";

            PreOrder( node->Left );
            PreOrder( node->Right );
        }
    }

    void InOrder( Node* node )
    {
        if ( node != nullptr )
        {
            InOrder( node->Left );
            cout << node->Key << " ";
            InOrder( node->Right );
        }
    }

    void PostOrder( Node* node )
    {
        if ( node != nullptr )
        {
            PostOrder( node->Left );
            PostOrder( node->Right );
            cout << node->Key << " ";
        }
    }

    void Display( Node* node, string indent, bool last )
    {
        if ( node != nullptr )
        {
            cout << indent;

            if ( last )
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            cout << node->Key << endl;

            Display( node->Left, indent, false );
            Display( node->Right, indent, true );
        }
    }


public:

    Node* Root;


    AVLTree() : Root( nullptr )
    {
    }

    void Insert( string Key )
    {
        Root = Insert( Root, Key );
    }

    void Remove( string Key )
    {
        Root = Remove( Root, Key );
    }

    void PreOrder()
    {
        PreOrder( Root );
        cout << endl;
    }

    void InOrder()
    {
        InOrder( Root );
        cout << endl;
    }

    void PostOrder()
    {
        PostOrder( Root );
        cout << endl;
    }

    void Display()
    {
        Display( Root, "", true );
    }

};


int main()
{
    setlocale( LC_ALL, "" );


    AVLTree tree;

    cout << "Введите 10 ключей для AVL-дерева: ";
    for ( int i = 0; i < 10; i++ )
    {
        string Key;
        cin >> Key;
        tree.Insert( Key );
    }

    cout << "\nСимметричный обход: ";
    tree.InOrder();

    cout << "\nУдалите элемент: ";
    string keyToRemove;
    cin >> keyToRemove;
    tree.Remove( keyToRemove );

    cout << "\nДерево после удаления: \n";
    tree.Display();

    cout << "\nПрямой обход: ";
    tree.PreOrder();

    cout << "\nОбратный обход: ";
    tree.PostOrder();


    return 0;
}
