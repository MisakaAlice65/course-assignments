#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
      { }
    
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

  protected:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode   *left;
        BinaryNode   *right;
        int       height;

    BinaryNode( const Comparable & ele, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, int h = 1 )
        : element{ ele }, left{ lt }, right{ rt }, height{ h } {}

    // 修改后的 BinaryNode 构造函数（移动构造）
    BinaryNode( Comparable && ele, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr, int h = 1 )
        : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } {}
    };

    BinaryNode *root;



    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        
        balance( t );
    }


    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        
        balance( t );
    }
     

    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            return; 
        }

        if (x < t->element) {
            remove(x, t->left);  
        } else if (x > t->element) {
            remove(x, t->right);  
        } else {
    
            BinaryNode *toDelete = t;

            if (t->left == nullptr && t->right == nullptr) {

                t = nullptr;
                delete toDelete;
            } else if (t->left == nullptr) {
             
                t = t->right;
                delete toDelete;
            } else if (t->right == nullptr) {
             
                t = t->left;
                delete toDelete;
            } else {
          
                BinaryNode* minNode = detachMin(t->right);
 
                minNode->left = t->left;
                minNode->right = t->right;  
                t = minNode; 
                delete toDelete;  
            }
        }


        if (t != nullptr) {
            t->height = 1 + std::max(height(t->left), height(t->right));  
            balance(t);  
        }
    }
    BinaryNode* detachMin(BinaryNode* &t) {
        if (t == nullptr) {
            return nullptr;
        }

        if (t->left == nullptr) {
            BinaryNode* minNode = t;
            t = t->right;
            return minNode;
        }

        return detachMin(t->left);
    }


    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance(BinaryNode *&t) {
        if (t == nullptr) return;

   
        int balanceFactor = height(t->left) - height(t->right);

        if (balanceFactor > 1) {
 
            if (height(t->left->left) >= height(t->left->right)) {
                // 左左情况，进行右旋转
                rotateWithLeftChild(t);
            } else {
                // 左右情况，先对左子树进行左旋，再进行右旋
                doubleWithLeftChild(t);
            }
        } else if (balanceFactor < -1) {
            // 右子树比左子树高，需要处理不平衡情况
            if (height(t->right->right) >= height(t->right->left)) {
                // 右右情况，进行左旋转
                rotateWithRightChild(t);
            } else {
                // 右左情况，先对右子树进行右旋，再进行左旋
                doubleWithRightChild(t);
            }
        }
    }


    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }




    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }


    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( BinaryNode *t ) const
    {
        return t == nullptr ? 0 : t->height;  // 空节点的高度为 0
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    
    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }


    void doubleWithLeftChild( BinaryNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }


    void doubleWithRightChild( BinaryNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};



#endif
