#include<iostream>
#include<vector>
#include<stack>
using namespace std;
/** \struct NodeQ1
    *The struct contains a data value as a character and a left pointer and a right pointer
    which denotes the address of the left subchild and right subchild. 
*/
struct NodeQ1
{
    char data; /** 
                    *Used to denote the data in the node. 
                */
    struct NodeQ1* left; /** 
                            *This denotes a pointer to left subtree.
                        */
    struct NodeQ1* right; /** 
                            *This denotes a pointer to right subtree. 
                        */
    
};
/** \class AssignmentQ1
    The AssignmentQ1 class contains code to convert a postfix expression 
*/   
class AssignmentQ1
{
    public:
    stack<char> st; /** 
                        *This variable is used to store the operators in the expression,
                         an operator when it finds a ) character. 
                    */
    string s;       /** 
                        *The input string which is in infix notation. 
                    */
    /**
        * A constructor.
        *  It is used to initialise the instance variables with parameters. 
        *  @param s is input string in infix notation.
    */
    AssignmentQ1(string s);

    //! A member taking no arguments and returning a string.
    /** @return op stores the evaluated postfix form of the string */
    string infixtoPostfix();

    //! A member which takes a character argument and returns a NodeQ1* value.
    /** The getNewNode function is used to create a new node in the parse tree
    and set its value as the data passed as the argument. 
        * @param data stores the value of the node in the parse tree.
        * @return pointer to the node 
    */ 
    NodeQ1* getNewNode(char data);

    //! A member which takes a vector as argument and returns a NodeQ1* value.
    /** This function is used to pop values from the vector. 
    * @param res vector stores the nodes of the parse tree.
    * @return pointer to the node
    */
    NodeQ1* pop(vector<NodeQ1* >res);

    //! A member which takes two arguments, root of the binary tree and a string and returns a NodeQ1* value.
    /** This function converts the postfix string to a rooted binary tree. 
    * @param pointer to the root node.
    * @param s stores the input string.
    * @return pointer to the node
    */
    NodeQ1* postfixToBinaryTree(NodeQ1* root,string s);

    //! A member which takes root of the tree as argument.
    /** This function prints the inorder traversal of the binary tree. 
    * @param pointer to the root node.
    */
    void inorderTraversal(NodeQ1* root);
}; 
