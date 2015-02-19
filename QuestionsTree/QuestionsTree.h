#ifndef QUESTIONSTREE_H
#define QUESTIONSTREE_H

#include <iostream>
#include <string>

using namespace std;

class QuestionsTree {
private:
	class Node {
	public:
		string questionGuess;
		Node * no;
		Node * yes;
		Node(string questionGuess = "", Node * no = NULL, Node * yes = NULL);
		bool hasAtLeastOneChild();
	};
public:
	QuestionsTree();
	~QuestionsTree();

	void destructorFunc(Node * node);
	void getInYesOrNoIfNotAlready(string & in);
	void couldNotGuess(bool & playAgain, Node * currentNode);
	void getIfWantToPlayAgain(string & in, bool & playAgain);
	void play();
private:
	Node * root;
};

#endif