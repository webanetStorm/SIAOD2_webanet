#include <iostream>
#include <string>
#include <queue>

using namespace std;


struct Node
{

    string Name;

    string Color;

    Node* Parent;

    Node* Left;

    Node* Right;


    Node( string Name ) : Name( Name ), Color( "RED" ), Parent( nullptr ), Left( nullptr ), Right( nullptr )
    {
    }

};

class RedBlackTree
{

private:

    Node* _root;

    Node* _TNULL;


    void InitializeTNULL()
    {
        _TNULL = new Node( "" );
        _TNULL->Color = "BLACK";
        _TNULL->Left = nullptr;
        _TNULL->Right = nullptr;
    }

    void LeftRotate( Node *x )
    {
        Node *y = x->Right;
        x->Right = y->Left;

        if ( y->Left != _TNULL ) 
            y->Left->Parent = x;
        y->Parent = x->Parent;

        if ( x->Parent == nullptr ) 
            _root = y;
        else if ( x == x->Parent->Left ) 
            x->Parent->Left = y;
        else 
            x->Parent->Right = y;

        y->Left = x;
        x->Parent = y;
    }

    void RightRotate( Node *x )
    {
        Node *y = x->Left;
        x->Left = y->Right;

        if ( y->Right != _TNULL ) 
            y->Right->Parent = x;
        y->Parent = x->Parent;

        if ( x->Parent == nullptr ) 
            _root = y;
        else if ( x == x->Parent->Right ) 
            x->Parent->Right = y;
        else 
            x->Parent->Left = y;

        y->Right = x;
        x->Parent = y;
    }

    void BalanceInsert( Node *k )
    {
        Node *u;

        while ( k->Parent->Color == "RED" )
        {
            if ( k->Parent == k->Parent->Parent->Right )
            {

                u = k->Parent->Parent->Left;
                if ( u->Color == "RED" )
                {
                    u->Color = "BLACK";
                    k->Parent->Color = "BLACK";
                    k->Parent->Parent->Color = "RED";
                    k = k->Parent->Parent;
                }
                else
                {
                    if ( k == k->Parent->Left )
                    {
                        k = k->Parent;
                        RightRotate( k );
                    }

                    k->Parent->Color = "BLACK";
                    k->Parent->Parent->Color = "RED";
                    LeftRotate( k->Parent->Parent );
                }
            }
            else
            {
                u = k->Parent->Parent->Right;

                if ( u->Color == "RED" )
                {
                    u->Color = "BLACK";
                    k->Parent->Color = "BLACK";
                    k->Parent->Parent->Color = "RED";
                    k = k->Parent->Parent;
                }
                else
                {
                    if ( k == k->Parent->Right )
                    {
                        k = k->Parent;
                        LeftRotate( k );
                    }

                    k->Parent->Color = "BLACK";
                    k->Parent->Parent->Color = "RED";
                    RightRotate( k->Parent->Parent );
                }
            }

            if ( k == _root ) 
                break;
        }

        _root->Color = "BLACK";
    }

    void PreOrderHelper( Node *node )
    {
        if ( node != _TNULL )
        {
            cout << node->Name << " ";
            PreOrderHelper( node->Left );
            PreOrderHelper( node->Right );
        }
    }

    void PostOrderHelper( Node *node )
    {
        if ( node != _TNULL )
        {
            PostOrderHelper( node->Left );
            PostOrderHelper( node->Right );
            cout << node->Name << " ";
        }
    }

    void InOrderHelper( Node *node )
    {
        if ( node != _TNULL )
        {
            InOrderHelper( node->Left );
            cout << node->Name << " ";
            InOrderHelper( node->Right );
        }
    }

    void LevelOrderHelper()
    {
        if ( _root == _TNULL ) 
            return;

        queue<Node *> q;
        q.push( _root );

        while ( !q.empty() )
        {
            Node *temp = q.front();
            q.pop();

            cout << temp->Name << " ";

            if ( temp->Left != _TNULL ) 
                q.push( temp->Left );
            if ( temp->Right != _TNULL ) 
                q.push( temp->Right );
        }
    }


public:

    RedBlackTree()
    {
        InitializeTNULL();
        _root = _TNULL;
    }

    void Insert( string key )
    {
        Node *node = new Node( key );

        node->Parent = nullptr;
        node->Name = key;
        node->Left = _TNULL;
        node->Right = _TNULL;

        Node *y = nullptr, *x = _root;

        while ( x != _TNULL )
        {
            y = x;
            x = node->Name < x->Name ? x->Left : x->Right;
        }

        node->Parent = y;
        if ( y == nullptr ) 
            _root = node;
        else if ( node->Name < y->Name ) 
            y->Left = node;
        else 
            y->Right = node;

        if ( node->Parent == nullptr )
        {
            node->Color = "BLACK";
            return;
        }

        if ( node->Parent->Parent == nullptr ) 
            return;

        BalanceInsert( node );
    }

    void PreOrder()
    {
        PreOrderHelper( _root );
        cout << endl;
    }

    void PostOrder()
    {
        PostOrderHelper( _root );
        cout << endl;
    }

    void InOrder()
    {
        InOrderHelper( _root );
        cout << endl;
    }

    void LevelOrder()
    {
        LevelOrderHelper();
        cout << endl;
    }

    void Display( Node *node, string indent, bool last )
    {
        if ( node != _TNULL )
        {
            cout << indent;
            if ( last )
            {
                cout << "R----";
                indent += "     ";
            }
            else
            {
                cout << "L----";
                indent += "|    ";
            }

            string Color = ( node->Color == "RED" ) ? "RED" : "BLACK";

            cout << node->Name << "(" << Color << ")" << endl;

            Display( node->Left, indent, false );
            Display( node->Right, indent, true );
        }
    }

    void Display()
    {
        if ( _root ) 
            Display( _root, "", true );
    }

};


void Menu( RedBlackTree& tree )
{
    while ( true )
    {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Прямой обход\n";
        cout << "3. Обратный обход\n";
        cout << "4. Симметричный обход\n";
        cout << "5. Обход в ширину\n";
        cout << "6. Показать дерево\n";
        cout << "7. Выход\n";
        cout << "Выберите опцию: ";

        int choice;
        cin >> choice;

        if ( choice == 7 ) 
            break;

        string name;
        switch ( choice )
        {
            case 1:
                cout << "Введите имя для добавления: ";
                cin >> name;
                tree.Insert( name );
                break;
            case 2:
                cout << "Прямой обход: ";
                tree.PreOrder();
                break;
            case 3:
                cout << "Обратный обход: ";
                tree.PostOrder();
                break;
            case 4:
                cout << "Симметричный обход: ";
                tree.InOrder();
                break;
            case 5:
                cout << "Обход в ширину: ";
                tree.LevelOrder();
                break;
            case 6:
                cout << "Дерево:\n";
                tree.Display();
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

int main()
{
    setlocale( LC_ALL, "" );


    RedBlackTree tree;
    cout << "Введите 10 элементов для дерева:\n";

    for ( int i = 0; i < 10; i++ )
    {
        string name;

        cout << "Элемент " << i + 1 << ": ";
        cin >> name;

        tree.Insert( name );
    }

    Menu( tree );


    return 0;
}
