#include<iostream>
#include<vector>
#include<stack>
#include<ctime>
#include "Q1.h"
using namespace std;

AssignmentQ1::AssignmentQ1(string s)
{
    this->s=s;
}
string AssignmentQ1::infixtoPostfix()
{    
    int l=s.length();
    string op="";
    for(int i=0;i<l;i++)
    {
        if((s[i]>='a' and s[i]<='z')) /** Assumption that all operands will be lower case. */
            {
                op+=s[i];
            }
        else if(s[i]=='(' or s[i]!=')')
        {
            st.push(s[i]);
        }
        if(s[i]==')')
        {   
            op+=st.top();
            st.pop();
            if(st.top()=='(')
                st.pop();
        }
    }
    return op;
}  
NodeQ1* AssignmentQ1::getNewNode(char data)
{
    NodeQ1* newNode = new NodeQ1();
    newNode -> data = data;
    newNode -> left = newNode -> right=NULL;

    return newNode;
}
NodeQ1* AssignmentQ1::pop(vector<NodeQ1* >res)
{
    NodeQ1* val=res[res.size()-1];
    return val;

}
NodeQ1* AssignmentQ1::postfixToBinaryTree(NodeQ1* root,string s)
{   
    vector<NodeQ1* > res;
    int l=s.length();
    NodeQ1* root1= NULL;
    NodeQ1* root2= NULL;
    for(int i=0;i<l;i++)
    {
        if(islower(s[i]))
        {
            root = getNewNode(s[i]);
            res.push_back(root);
        }
        else
        {
            if(s[i]=='~')
            {
                root = getNewNode(s[i]);
                root1=pop(res);
                res.pop_back();
                root -> right = root1;
                root -> left = NULL;
                res.push_back(root);
            }
            else
            {
                root = getNewNode(s[i]);
                root1=pop(res);
                res.pop_back();
                root2=pop(res);
                res.pop_back();
                root -> right = root1;
                root -> left = root2;
                res.push_back(root);   
            }
        }

    }
    root = pop(res);
    res.pop_back();
    return root;
}
void AssignmentQ1::inorderTraversal(NodeQ1* root) 
{ 
    if (root == NULL) 
        return;  
    if(root-> data == '^' || root-> data == '>' || root-> data == '~' || root-> data == 'V')
    {
        cout << '(';
        inorderTraversal(root -> left);
        cout << root -> data;
        inorderTraversal(root -> right); 
        cout << ')';
    }
    else
    {
        cout << root -> data;
    }
}
int main() 
{ 
	string inp;  /** This variable denotes the input in the infix form. */
	cin >> inp;
	clock_t tStart = clock(); /* Calculates the time when the code starts executing. */
	AssignmentQ1 obj(inp);
    string output= obj.infixtoPostfix();
    cout << endl; 
    cout << "Postfix Notation of the formula is: " << endl;
    cout << output << endl << endl;    

    NodeQ1* root = NULL;
    root= obj.postfixToBinaryTree(root,output);

    cout << "Inorder Traversal of the binary parse tree: " << endl; 
    obj.inorderTraversal(root);
    cout << endl; 
 
 	cout << "Time for code to run: " << endl;
 	cout << (double)(clock() - tStart)/(CLOCKS_PER_SEC) << endl;
    return 0; 
} 

