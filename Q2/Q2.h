//
// Created by Shreeya Jain on 23/10/18.
//

#include<iostream>
#include<string.h>
using namespace std;
/**
 * A structure to represent nodes of a linked list 
 */
struct NodeQ2 {
    std::string str; /**< string for each statement, followed by the rule */
    NodeQ2 *next; /**< pointer to the next node in the linked list */
};
/**
 * A class to check the validity of each statement of the proof according to the 
 * corresponding rules and line numbers
 */
class AssignmentQ2
{
private:

    NodeQ2 *head,*tail; /**< pointers to the first and the last node in the linked list */

public:

    /**
     * A default constructor for the class to create an empty list
     */
    AssignmentQ2();

    /**
     * function to add a new node to the linked list
     * @param s stores the string data for the new node
     */
    void addNode(std::string s); 

    /**
     * function to check the validity of each proof rule through string comparison
     * @return count an integer variable that keeps a count of the number of valid lines in the proof
     */
    int check(); 

    /**
     * function to check if the given statement is a valid ^ introduction
     * @param head is a pointer to the first node in the linked list
     * @param first stores the position of the first statement for ^ introduction
     * @param second stores the position of the second statement for ^ introduction
     * @return s stores the string obtained from ^ introduction to first and second 
     */
    std::string andIntro(NodeQ2 *head,int first,int second);

    /**
     * function to check if the the given statement is a valid ^ elimination
     * @param head is a pointer to the first node in the linked list
     * @param line stores the position of the statement from where ^ elimination is taking place
     * @param elimtype stores the type of ^ elimination - 1 or 2
     * @return s stores the string obtained from ^ elimination (1 or 2) to line
     */
    std::string andElim(NodeQ2 *head,int line,int elimtype);

    /**
     * function to check if the the given statement is a valid V elimination
     * @param head is a pointer to the first node in the linked list
     * @param line stores the position of the statement from where V elimination is taking place
     * @param s stores the statement to be checked
     * @param introtype stores the type of V elimination - 1 or 2
     * @return 1 or 0 depending on the validity of the statement
     */
    int orIntro(NodeQ2 *head,int line,std::string s,int introtype); 

    /**
     * function to check if the the given statement is a valid implication elimination or modulus tollens
     * @param head is a pointer to the first node in the linked list
     * @param first stores the position of the first statement for the rule
     * @param second stores the position of the second statement for the rule
     * @param type stores the type of rule - 1 for implication elimination and 2 for MT
     * @return s stores the string obtained from implication elimination or MT to first and second
     */
    std::string impliMT(NodeQ2 *head,int first,int second,int type); 

    /**
     * function to obtain statements (without the rule being used)
     * @param s stores a particular line from the proof, including the rule being used
     * @return cut stores the statements in a particular line from the proof, without the rule being used
     */
    std::string cutString(std::string s); 

    /**
     * function to delete all the nodes in the linked list
     */
    void deleteAll(); 
};