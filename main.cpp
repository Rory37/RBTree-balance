#include <iostream>
#include "node.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

void add(node*);
node* create(int*, int);
void reccreate(node*, int*, int);
void print(node*, int);

int main() {
  cout << "Welcome to Binary tree creater" << endl;
  //input code adapted from heap
  char c [80];
  bool b = true;
  int treear [100]; //array to initially hold values for tree
  while ( b == true) {//runs the input until valid
    cout << "Please input a input method (series or filename)" << endl;
    cin >> c;//takes method
    for(int i = 0; i < 100; i++) {//sets everything in array to val 0 (was issue at home computer)
      treear[i] = 0;
    }
    if (strcmp(c, "series") == 0) {//If the input is series
      b = false;//Proper input
      bool stillIn = true;//While still adding
      int count = 0;//spot to put new number
      cin.ignore(); //ignores previous cin in
      while(stillIn == true) {
	cout << "Please input a number to be in your heap, or END to construct your heap" << endl;
	char input [1000];//can hold number for input
	cin.getline(input,1000);//gets input
	if(strcmp(input, "END") == 0) { //Once end is typed, quits
	  stillIn = false;
	}
	else{
	  treear[count] = atoi(input); //take input, convert to int and add to array
	  count++;//increment spot to put int
	}
      }
    }
    else if (strcmp(c, "filename") == 0) {//if file
      cout << "Please input the list in the given input method" << endl;
      char filename[80];//for name of file
      cin.ignore();//ignores past cin
      cin.getline(filename, 80);//takes in the name
      ifstream newFile; //new file
      newFile.open(filename);//opens file with the name put in
      if (newFile == NULL) {//if file doesn't exist
	cout << "There was an error reading the file" << endl;
      }
      else {
	b = false;//input method correct
	int i = 0; //keeps track of spots in heap
	while (newFile.eof() != true) {//while not end of file
	  newFile >> treear[i];//puts each number seperated by whitespace in
	  i++;
	}
      }
      newFile.close();//closes file
    }
  }
  int length;
  for (int i = 0; i < sizeof(treear)/sizeof(treear[0]); i++) {//calculates elements in int array, puts in length
    if (treear[i] == 0) {
      length = i;
      break;
    }
  }
  
  node* root = create(treear, length); //creates tree of node
  cout << root -> getData() << endl;
  cout << 'h' << endl;
  print(root, 0);
}


void add (node* root) {

  
}

node* create(int* treear, int length){
  node* root = new node(treear[0]);
  for (int i = 1; i < length; i++) {
    reccreate(root, treear, i);
  }
  return root;
}

void reccreate(node* comp, int* treear, int i) {
  node* newp = new node(treear[i]);
  if(treear[i] < comp -> getData()) {
    if (comp -> getLeft() == NULL) {
      comp -> setLeft(newp);
    }
    else{
      if (comp -> getRight() == NULL && treear[i] > comp -> getLeft() -> getData()) {//to keep balanced
	newp -> setData(comp -> getData());
	comp -> setData(treear[i]);
	comp -> setRight(newp);
      }
      else if (comp -> getRight() == NULL) {
	newp -> setData(comp -> getData());
	comp -> setData(comp -> getLeft() -> getData());
	comp -> getLeft() -> setData(treear[i]);
	comp -> setRight(newp);
      }
      else {
	reccreate(comp -> getLeft(), treear, i);
      }
    }
  }
  else {
    if (comp -> getRight() == NULL) {
      comp -> setRight(newp);
    }
    else{
      if (comp -> getLeft() == NULL && treear[i] < comp -> getRight() -> getData()) {//to keep balanced
	newp -> setData(comp -> getData());
	comp -> setData(treear[i]);
	comp -> setLeft(newp);
      }
      else if (comp -> getLeft() == NULL) {
	newp -> setData(comp -> getData());
	comp -> setData(comp -> getRight() -> getData());
	comp -> getRight() -> setData(treear[i]);
	comp -> setLeft(newp);
      }
      else {
	reccreate(comp -> getRight(), treear, i);
      }
    }
  }
}

void print(node* parent, int count) {
  if(parent -> getRight() != NULL) {
    print(parent -> getRight(), count + 1);
  }
  int temp = count;
  while (count > 0) {
    cout << "   ";
    count --;
  }
  cout << parent -> getData() << endl;
  if (parent -> getLeft() != NULL) {
    print (parent -> getLeft(), temp + 1);
  }
}
