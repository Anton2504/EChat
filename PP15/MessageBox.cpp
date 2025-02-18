#include "MessageBox.h"

void MessageBox::push_back(const string& lhs) { 
	_text.push_back(lhs); 
}
void MessageBox::push_back(string&& rhs) { 
	_text.push_back(move(rhs)); 
}