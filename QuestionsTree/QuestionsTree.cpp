#include "QuestionsTree.h"

QuestionsTree::Node::Node(string questionGuess, Node * no, Node * yes) : questionGuess(questionGuess), no(no), yes(yes) {
}

QuestionsTree::QuestionsTree() {
	
	root = new Node("Is it an animal?");
	root->no = new Node("a carrot", NULL, NULL);
	root->yes = new Node("a tucan", NULL, NULL);
}

QuestionsTree::~QuestionsTree() {
	destructorFunc(root);
}

void QuestionsTree::destructorFunc(Node * node) {
	if (node->no != NULL)
		destructorFunc(node->no);
	if (node->yes != NULL)
		destructorFunc(node->yes);
	delete node;
}

void QuestionsTree::play() {
	string input;
	bool wantToPlay = true;
	Node * playNode;

	cout << "Welcome to Josh's 20 questions game." << endl;
	cout << "Please think of an object/entity/noun and I'll try and guess it!" << endl;
	cout << "The more we play the smarter I'll get..." << endl;

	while (wantToPlay) {
		playNode = this->root;
		cout << root->questionGuess << endl;
		getInYesOrNoIfNotAlready(input);
		while (playNode->hasAtLeastOneChild()) {	
			if (input.compare("no") == 0) {
				if (playNode->no != NULL) {
					playNode = playNode->no;
					if (playNode->hasAtLeastOneChild()) {
						cout << playNode->questionGuess << "?" << endl;
						getInYesOrNoIfNotAlready(input);
					}
				}
			}
			else if (input.compare("yes") == 0) {
				if (playNode->yes != NULL) {
					playNode = playNode->yes;
					if (playNode->hasAtLeastOneChild()) {
						cout << playNode->questionGuess << "?" << endl;
						getInYesOrNoIfNotAlready(input);
						//Gets here
					}
				}
			}
		}
		cout << "I guess you are thinking of " << playNode->questionGuess << " - am I right?" << endl;
		getInYesOrNoIfNotAlready(input);
		if (input.compare("no") == 0) {
			couldNotGuess(wantToPlay, playNode);
		}
		else if (input.compare("yes") == 0)
			getIfWantToPlayAgain(input, wantToPlay);
	}
}

bool QuestionsTree::Node::hasAtLeastOneChild() {

	if (this->no != NULL || this->yes != NULL)
		return true;
	else
		return false;

}

void QuestionsTree::getInYesOrNoIfNotAlready(string & in) {

	cin >> in;

	if (in.compare("yes") == 0 || in.compare("Yes") == 0 || in.compare("yes.") == 0 || in.compare("Yes.") == 0)
		in = "yes";
	else if (in.compare("no") == 0 || in.compare("no.") == 0 || in.compare("No") == 0 || in.compare("No.") == 0)
		in = "no";
	else {

		cout << "Sorry, your answer has to be either yes, Yes, Yes., yes., no, No, No., or no., please try again." << endl;
		getInYesOrNoIfNotAlready(in);

	}

}

void QuestionsTree::couldNotGuess(bool & playAgain, Node * currentNode) {
	cout << "What is it?" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string newGuess, newQuestion, newYesNo;
	getline(cin, newGuess);
	cin.clear();
	cout << "What can I ask to tell " << currentNode->questionGuess << " from " << newGuess << "?" << endl;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, newQuestion);
	cin.clear();
	cout << "Is the answer to that question yes or no for '" << newGuess << "'?" << endl;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getInYesOrNoIfNotAlready(newYesNo);
	cin.clear();
	if (newYesNo.compare("yes") == 0) {
		currentNode->no = new Node(currentNode->questionGuess, NULL, NULL);
		currentNode->yes = new Node(newGuess, NULL, NULL);
		currentNode->questionGuess = newQuestion;
	}
	else {
		currentNode->yes = new Node(currentNode->questionGuess, NULL, NULL);
		currentNode->no = new Node(newGuess, NULL, NULL);
		currentNode->questionGuess = newQuestion;
	}
	getIfWantToPlayAgain(newYesNo, playAgain);
}

void QuestionsTree::getIfWantToPlayAgain(string & in, bool & playAgain) {

	cout << "Cool. Wanna play again?" << endl;
	getInYesOrNoIfNotAlready(in);
	if (in.compare("no") == 0)
		playAgain = false;
}