#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;

typedef pair<int, int> IntPair;

struct Stats {
	int total_typed_chars;
	int correct_chars;
	int incorrect_chars;
	float time;
};

class Engine {
private:
	string current_typed_word = "";
	// Text which user will type.
	vector<string> full_text;
	// First index is word index, second index is character index.
	int index = 0;
	vector<int> keylog;

public:
	Engine();
	Engine(string text);
	string get_current_typed_word();
	void set_current_typed_word(string s);
	int get_index();
	void set_index(int idx);
	void set_index_rel(int idx);
	void log_key(int c);

	// Returns true if the word was correct (submitted). Else returns false.
	bool handle_space();

	// Returns true if a backspace was actually performed.
	bool handle_bs();

	// Returns true if c is a correct character. 
	bool tick(char c);
};

