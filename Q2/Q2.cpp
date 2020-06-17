#include<iostream>
#include<string.h>
#include "Q2.h"
#include<ctime>

using namespace std;

AssignmentQ2::AssignmentQ2() 
{
    head = NULL; tail = NULL;
}

void AssignmentQ2::addNode(std::string s) //function to add a new node to the linked list
{
    NodeQ2 *temp = new NodeQ2;
    temp->str = s;
    temp->next = NULL;
    if(head == NULL) //for the first node
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = tail->next;
    }
}

int AssignmentQ2::check()
{
    NodeQ2 *temp=head;
    int i,count=0; //count variable keeps a count of the number of valid lines in the proof
    while(temp != NULL)
    {
        std::string s=temp->str;
        for(i=0;i<s.length();i++)
        {
            if(s[i]=='/' && s[i+1]=='^' && s[i+2]=='i') //AND introduction
            {
                int j;
                for(j=i+4;j<s.length();j++)
                    if(s[j]=='/')
                        break;
                if(cutString(s)==andIntro(head,stoi(s.substr(i+4,j-i-4)),stoi(s.substr(j+1,s.length()-j-1)))) 
                    count++;
                else   
                    return 0;
            }
            else if(s[i]=='/' && s[i+1]=='^' && s[i+2]=='e') //AND elimination
            {
                if(cutString(s)==andElim(head,stoi(s.substr(i+5,s.length()-i-5)),(int)s[i+3]-'0')) //s[i+3] is 1 for ^e1 and 2 for ^e2
                    count++;
                else
                    return 0;
            }
            else if(s[i]=='/' && s[i+1]=='V' && s[i+2]=='i') //OR introduction
            {
                if(orIntro(head,stoi(s.substr(i+5,s.length()-i-5)),s,(int)s[i+3]-'0')==1) //s[i+3] is 1 for Vi1 and 2 for Vi2
                    count++;
                else
                    return 0;
            }
            else if(s[i]=='/' && s[i+1]=='>') //Implication elimination
            {
                int j;
                for(j=i+4;j<s.length();j++)
                    if(s[j]=='/')
                        break;
                if(cutString(s)==impliMT(head,stoi(s.substr(i+4,j-i-4)),stoi(s.substr(j+1,s.length()-j-1)),1))
                    count++;
                else
                    return 0;
            }
            else if(s[i]=='/' && s[i+1]=='M' && s[i+2]=='T') //Modulus Tollens
            {
                int j;
                for(j=i+4;j<s.length();j++)
                    if(s[j]=='/')
                        break;
                if(cutString(s)==impliMT(head,stoi(s.substr(i+4,j-i-4)),stoi(s.substr(j+1,s.length()-j-1)),2))
                    count++;
                else
                    return 0;
            }
            else if(s[i]=='/' && (s[i+1]=='P' || s[i+1]=='p')) //Premise
                count++;
        }
        temp=temp->next;
    }
    return count; 
}

std::string AssignmentQ2::andIntro(NodeQ2 *head,int first,int second)
{
    NodeQ2 *temp=head;
    for(int i=1;i<first;i++)
        temp=temp->next;
    std::string s="("+cutString(temp->str)+"^";
    temp=head;
    for(int i=1;i<second;i++)
        temp=temp->next;
    s=s+cutString(temp->str)+")";
    return s; 
}

std::string AssignmentQ2::andElim(NodeQ2 *head,int line,int elimtype) //elimtype variable gives the type of AND elimination - 1 or 2
{
    NodeQ2 *temp=head;
    for(int i=1;i<line;i++)
        temp=temp->next;
    std::string s=cutString(temp->str);
    s=s.substr(1,s.length()-2);
    int counto=0,countc=0; //counto keeps a count of ( while countc keeps a count of )
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='(')
            counto++;
        else if(s[i]==')')
            countc++;
        else if(s[i]=='^' && counto==countc)
        {
            if(elimtype==1)
                s=s.substr(0,i);
            else
                s=s.substr(i+1,s.length()-i-1);
            break;
        }
    }
    return s; //s gives the string obtained from AND elimination (1 or 2) to line
}

int AssignmentQ2::orIntro(NodeQ2 *head,int line,std::string s,int introtype) //introtype variable gives the type of OR introduction - 1 or 2
{
    s=cutString(s);
    s=s.substr(1,s.length()-2);
    int counto=0,countc=0; //counto keeps a count of ( while countc keeps a count of )
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='(')
            counto++;
        else if(s[i]==')')
            countc++;
        else if(s[i]=='V' && counto==countc)
        {
            if(introtype==1)
                s=s.substr(0,i);
            else
                s=s.substr(i+1,s.length()-i-1);
            break;
        }
    }
    NodeQ2 *temp=head;
    for(int i=1;i<line;i++)
        temp=temp->next;
    if(s==cutString(temp->str))
        return 1; 
    else    
        return 0;
}

std::string AssignmentQ2::impliMT(NodeQ2 *head,int first,int second,int type) //type variable is 1 for implication elimination and 2 for MT
{
    NodeQ2 *temp=head;
    int i;
    for(i=1;i<first;i++)
        temp=temp->next;
    std::string s=cutString(temp->str),r;
    s=s.substr(1,s.length()-2);
    int counto=0,countc=0; //counto keeps a count of ( while countc keeps a count of )
    for(i=0;i<s.length();i++)
    {
        if(s[i]=='(')
            counto++;
        else if(s[i]==')')
            countc++;
        else if(s[i]=='>' && counto==countc)
        {
            if(type==1)
                r=s.substr(0,i);
            else
                r=s.substr(i+1,s.length()-i-1);
            break;
        }
    }
    if(type==2)
    {
        if(r[0]=='~')
            r="~("+r+")";
        else    
            r="~"+r;
    } 
    temp=head;
    for(int i=1;i<second;i++)
        temp=temp->next;
    if(r==cutString(temp->str))
    {
        if(type==1)
            s=s.substr(i+1,s.length()-i-1);
        else
        {
            s=s.substr(0,i);
            if(s[0]=='~')
                s="~("+s+")";
            else    
                s="~"+s;
        }
    }
    return s; //s gives the string obtained from implication elimination or MT to first and second 
}

std::string AssignmentQ2::cutString(std::string s) //function to obtain statements, without the rule being used
{
    int i=0;
    std::string cut;
    while(s[i]!='/')
    {
        cut+=s[i];
        i++;
    }
    return cut; 
}

void AssignmentQ2::deleteAll() 
{
	NodeQ2 *temp=head;
    while(temp!=tail)
	{
        temp=head->next;
        delete(head);
	    head=temp;
	}
	delete(head);
}

int main()
{
   int i,n;
   cin>>n;
   cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
   AssignmentQ2 a;
   std::string s;
   for(i=0;i<n;i++)
   {
      getline(cin,s);
      a.addNode(s);
   }
   clock_t tStart = clock(); /* Calculates the time when the code starts executing. */
   if(a.check()==n) //check() function checks validity of each proof rule
        cout<<"Valid Proof";
   else
        cout<<"Invalid Proof";
   a.deleteAll();
   cout<<endl<<"Time for code to run: ";
   cout<<(double)(clock() - tStart)/(CLOCKS_PER_SEC)<<endl;
   return 0;
}

/**
 * @mainpage Logic Assignment 2
 * 
 * @section intro_sec Introduction

 *  Part 1: \n
 *  A tool for the construction of a parse tree for a propositional logic formula. \n
 *  Task 1 is a function to convert the infix propositional logic expression into a postfix propositional logic expression. \n
 *  Task 2 is a function to convert the postfix expression into a rooted binary parse tree. \n
 *  Task 3 is a function to traverse the parse tree to output the infix expression back by in-order traversal of the parse tree. \n\n
 *  Once the parse tree has been constructed, it can be verifed that the given formula is well formed. \n\n
 *  Part 2: \n
 *  A tool that checks whether the given proof for a sequent is valid or not.\n
 *  The following proof rules can be checked: \n
 *  1. Premise \n
 *  2. AND Introduction \n
 *  3. AND Elimination \n
 *  4. OR Introduction \n
 *  5. Implies Elimination \n
 *  6. Modus Tollens \n\n\n
 *  Note: Refer to Related Pages for the experiments on code - assumptions, definitions and test cases.\n
 		  Memory usages and related graphs have been added in a separate folder.\n \n
 *  
 *  @author Shreeya Jain 2016B3A70237H
 *  @author Parth Anand 2016B4A70873H
 *  @author Akshat Govil 2016B4A70502H
 *  @date 24/10/2018
 * 
 */

/**
 * @page page1 Experiments for Q1
 * @tableofcontents
 * 1. Assumptions
 * 2. Definitions
 * 3. Limitations
 * 4. Test Cases
 * @section sec1 Assumptions
 * 1. The formula is well formed and fully parenthesized. 
 * 2. Statements should not contain spaces.
 * 3. ~ should be bracketed. For example ((~a)^(~b)) is valid but(~a^~b) is invalid.
 * 4. The input should be in infix notation.
 * 5. The input should be in lower case.
 *
 * @section sec2 Definitions
 * 1. The connective symbols used for this assignment are:
 * a. ~ for negation
 * b. V for OR
 * c. ^ for AND
 * d. > for implication.
 *
 * @section sec3 Limitations
 * 1. If the input format is not as that mentioned above, then an incorrect output will be produced.
 * 2. The code only uses lower case inputts to accomodate for the symbol of OR which is a capital V on the keyboard.
 * 3. The memory usage is high for inputs with high number of variables.
 *
 * @section sec4 TestCases
 * 
 * @subsection sub1 TestCase1
 * Input: \n
 * (a^b) \n
 * Output: \n
 * Postfix Notation of the formula is: ab^ \n
 * Inorder Traversal of the binary parse tree: (a^b) \n
 * Time taken: 0.001s \n
 *
 * @subsection sub2 TestCase2
 * Input: \n
 * (((~a)^b)V((~b)^a)) \n
 * Output: \n
 * Postfix Notation of the formula is: a~b^b~a^V \n
 * Inorder Traversal of the binary parse tree: (((~a)^b)V((~b)^a)) \n
 * Time taken: 0.005s \n
 * 
 * @subsection sub3 TestCase3
 * Input: \n
 * ((((bVc)^(cVe))>(~((a^d)>c)))V((a^b)V(a^c))) \n
 * Output: \n
 * Postfix Notation of the formula is: bcVceV^ad^c>~>ab^ac^VV \n
 * Inorder Traversal of the binary parse tree: ((((bVc)^(cVe))>(~((a^d)>c)))V((a^b)V(a^c))) \n
 * Time taken: 0.008s \n
 *
 * @subsection sub4 TestCase4
 * Input: \n
 * ((((aVb)>(e^d))^(f>c))^(a>(cV(e^(bVa))))) \n
 * Output:  \n
 * Postfix Notation of the formula is: abVed^>fc>^acebaV^V>^ \n
 * Inorder Traversal of the binary parse tree: ((((aVb)>(e^d))^(f>c))^(a>(cV(e^(bVa))))) \n
 * Time taken: 0.016s \n
 *
 * @subsection sub5 TestCase5
 * Input: \n
 * ((b>(~(c>(a^(bV(~f))))))^(((f^(e>(~(c^d))))V(f^(i>(d^e))))V(((~c)^h)V((~j)^d)))) \n
 * Output: \n
 * Postfix Notation of the formula is: bcabf~V^>~>fecd^~>^fide^>^Vc~h^j~d^VV^ \n
 * Inorder Traversal of the binary parse tree: ((b>(~(c>(a^(bV(~f))))))^(((f^(e>(~(c^d))))V(f^(i>(d^e))))V(((~c)^h)V((~j)^d)))) \n
 * Time taken: 0.017s \n
 *
 * @subsection sub6 TestCase6
 * Input: \n
 * ((~(a>b)^c)>(aV(~(bVc)))) \n
 * Output: \n
 * Postfix Notation of the formula is: ab>c^abcV~V> \n
 * Inorder Traversal of the binary parse tree: ((~(a>b)^c)>(aV(~(bVc)))) \n
 * Time taken: 0.012s \n
 *
 * @subsection sub7 TestCase7
 * Input: \n
 * ((aVb)^c) \n
 * Output: \n
 * Postfix Notation of the formula is: abVc^ \n
 * Inorder Traversal of the binary parse tree: ((aVb)^c) \n
 * Time taken: 0.006s \n
 *
 * @subsection sub8 TestCase8
 * Input: \n
 * (((a>b)V(~(c^d)))^(a>c)) \n
 * Output: ab>cd^~Vac>^ \n
 * Postfix Notation of the formula is:  \n
 * Inorder Traversal of the binary parse tree: (((a>b)V(~(c^d)))^(a>c)) \n
 * Time taken: 0.008s \n
 */

/**
 * @page page2 Experiments for Q2
 * 
 * @tableofcontents
 * 1. Assumptions
 * 2. Definitions
 * 3. Limitations
 * 4. Test Cases
 * 
 * @section sec1 Assumptions
 * 1.  Line Number starts from 1. \n
 * 2.  Statements are perfectly parenthesized. For example [((a^b)^c) is valid, but (a^b)^c is invalid.] \n
 * 3.  ~ is succeeded only by a literal or a ‘(’. [~(~a) is valid, but ~~a is invalid.] \n
 * 4.  Statements should NOT contain spaces. For example [(a^b) is valid, but (a ^ b) is invalid.] \n
 * 5.  Premises should not contradict each other. \n
 *     Eg. a/P \n
 *         ~a/P \n
 * 6.  User should enter a proof of exactly n lines, where n is the length of the proof as previously entered by the user. \n
 * 7.  n inputted by the user should be a positive integer < 2147483647. \n
 * 
 * @section sec2 Definitions
 * <statement> ::= p | ¬p | ¬(<statement>) | (<statement> ∧ <statement>) | (<statement> ∨ <statement>) | (<statement> → <statement>) \n
 * <rule> ::= ∧i | ∧e1 | ∧e2 | ∨i1 | ∨i2 | →e |P \n
 * 
 * @section sec3 Limitations
 * 1.  Rules like >i , Ve, ~e ~~e ~i aren’t taken into consideration so they will give invalid proof even if they are valid. \n
 * 2.  For proofs of length > 2,50,00 lines, the time taken and memory usage is substantially high. \n
 * 3.  If the proof inputted does not follow the assumptions as specified above, the program will return invalid proof. \n
 * 4.  If the statements, reasons  and line numbers aren’t separated by ‘/’ properly, the program will return invalid proof or give runtime error. \n
 * 5.  If line number formats don’t match the reasons (eg >e/1), the program will give runtime error. \n
 * 
 * @section sec4 TestCases
 * 
 * @subsection sub1 TestCase1
 * Input: \n
 * 6 \n
 * ((p^q)^r)/P \n
 * (s^t)/P \n
 * (p^q)/^e1/1 \n
 * q/^e2/3 \n
 * s/^e1/2 \n
 * (q^s)/^i/4/5 \n\n 
 * Output:Valid Proof \n
 * Expected Output: Valid Proof \n
 * Time taken: 0.000164s \n
 * 
 * @subsection sub2 TestCase2
 * Input: \n
 * 5 \n
 * (p>(q>r))/P \n
 * p/P \n
 * ~r/P \n
 * (q>r)/>e/1/2 \n
 * ~q/MT/4/3 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid Proof \n
 * Time taken: 0.000218s \n
 * 
 * @subsection sub3 TestCase3
 * Input: \n
 * 6 \n
 * (p>(q>r))/P \n
 * (p>q)/P \n
 * p/P \n
 * (q>r)/>e/1/3 \n
 * q/>e/2/3 \n
 * r/>e/4/5 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid Proof \n
 * Time taken: 0.000175s \n
 * 
 * @subsection sub4 TestCase4
 * Input: \n
 * 3 \n
 * a/P \n
 * (aVb)/Vi1/1 \n
 * (cV(aVb))/Vi2/2 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid Proof \n
 * Time taken: 0.00018s \n
 * 
 * @subsection sub5 TestCase5
 * Input: \n
 * 6 \n
 * (a^b)/P \n
 * (cVd)/P \n
 * ((a^b)V(cVd))/Vi1/1 \n 
 * (~((a^b)V(cVd))>~(e^h))/P \n 
 * ~(~(e^h))/P \n
 * ~(~((a^b)V(cVd)))/MT/4/5 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid Proof \n
 * Time taken: 0.000184s \n
 * 
 * @subsection sub6 TestCase6
 * Input: \n
 * 4 \n
 * (a^b)/P \n
 * c/P \n
 * b/^e2/1 \n
 * (b^c)/^i/3/2 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid Proof \n
 * Time taken: 0.00015s \n
 * 
 * @subsection sub7 TestCase7
 * Input: \n
 * 3 \n
 * a/P \n
 * ~b/P \n
 * (a^~b)/^i/1/2 \n\n
 * Output: Invalid Proof \n
 * Expected Output: Valid Proof \n
 * Time Taken: 0.000299s \n
 * 
 * @subsection sub8 TestCase8
 * Input: \n
 * 3 \n
 * (~a>~b)/P \n
 * b/P \n
 * a/MT/1/2 \n\n
 * Output: Invalid Proof \n
 * Expected Output: Invalid proof \n
 * Time Taken: 0.0003s \n
 * 
 * @subsection sub9 TestCase9
 * Input: \n
 * 11 \n
 * (~a^~b)/P \n
 * ~b/^e2/1 \n
 * (~aV~b)/Vi2/2 \n
 * (c>(d^e))/P \n
 * ~(d^e)/P \n
 * ~c/MT/4/5 \n
 * ((p^~r)>~(qV~s))/P \n
 * p/P \n
 * ~r/P \n
 * (p^~r)/^i/8/9 \n
 * ~(qV~s)/>e/7/10 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid proof \n
 * Time Taken: 0.000195s \n
 * 
 * @subsection sub10 TestCase10
 * Input: \n
 * 12 \n
 * (a>b)/P \n
 * a/P \n
 * b/P \n
 * (d^~e)/P \n
 * (b>~(fVg))/P \n
 * ((a>b)V~b)/Vi1/1 \n
 * (b^(d^~e))/^i/3/4 \n
 * ~(fVg)/>e/5/3 \n
 * (~(fVg)^(d^~e))/^i/8/4 \n
 * ((a^(b^(c>~d)))V(~(fVg)^(d^~e)))/Vi2/9 \n
 * d/^e1/4 \n
 * ~e/^e2/4 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid proof \n
 * Time Taken: 0.000223s \n
 * 
 * @subsection sub11 TestCase11
 * Input: \n
 * 11 \n
 * (((((a^b)^c)^((d^e)^f))^g^(h^i))^j)/P \n
 * ((a^b)^c)^((d^e)^f))^g)^(h^i))/^e1/1 \n
 * j/^e2/1 \n
 * (h^i)/^e2/2 \n
 * ((((a^b)^c)^((d^e)^f))^g)/^e1/2 \n
 * (((a^b)^c)^((d^e)^f))/^e1/5 \n
 * g/^e2/5 \n
 * ((d^e)^f)/^e2/6 \n
 * ((a^b)^c)/^e1/6 \n
 * (d^e)/^e1/8 \n
 * c/^e2/9 \n\n
 * Output: Invalid Proof \n
 * Expected Output: Invalid proof \n
 * (Due to incorrect parenthisis) \n
 * Time Taken: 0.000146s \n
 * 
 * @subsection sub12 TestCase12
 * Input: \n
 * 13 \n
 * (a>(b>(c>(d>(e>(f>g))))))/P \n
 * a/P \n
 * b/P \n
 * c/P \n
 * d/P \n
 * e/P \n
 * f/P \n
 * (b>(c>(d>(e>(f>g)))))/>e/1/2 \n
 * (c>(d>(e>(f>g))))/>e/8/3 \n
 * (d>(e>(f>g)))/>e/9/4 \n
 * (e>(f>g))/>e/10/5 \n
 * (f>g)/>e/11/6 \n
 * g/>e/12/7 \n\n
 * Output: Valid Proof \n
 * Expected Output: Valid proof \n
 * Time Taken: 0.000192s \n
 * 
 * @subsection sub13 TestCase13
 * For the rest of the test cases, we took a large number of proof line inputs in the following manner: \n
 * Input: \n
 * (Number of proof lines) \n
 * a(p>(q>r))/P \n
 * p/P \n
 * ~r/P \n
 * (q>r)/>e/1/2 \n
 * ~q/MT/4/3 \n
 * (p>(q>r))/P \n
 * p/P \n
 * ~r/P \n
 * (q>r)/>e/1/2 \n
 * ~q/MT/4/3 \n\n
 * and so on until we had an input of around 40000 lines.\n
 * Each case gave the expected output. The time taken for the 40000 input lines case was 6.345s. \n
 * 
 */
