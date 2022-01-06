#include "engine.hpp"
#include <sstream>
#include <iterator>

Engine::Engine() {}

Engine::Engine(string text) {
	// Split text by spaces.
	std::stringstream ss(text);
	std::istream_iterator<string> begin(ss);
	std::istream_iterator<string> end;
	std::vector<std::string> vstrings(begin, end);
	full_text = vstrings;
}

string Engine::get_current_typed_word() { return current_typed_word; }

void Engine::set_current_typed_word(string s) { current_typed_word = s; }

int Engine::get_index() { return index; }

void Engine::set_index(int idx) {
	index = idx;
}

void Engine::set_index_rel(int idx) {
	index += idx;

	if (index < 0) index = 0;
}

// void Engine::set_current_position_rel(int dpos) { current_position += dpos; }

void Engine::log_key(int c) { keylog.push_back(c); }

bool Engine::handle_space() {
	if (current_typed_word == full_text[index]) {
		index++;
		current_typed_word = "";
		return true;
	}
	return false;
}

bool Engine::handle_bs() {
	if (current_typed_word.length() > 0) {
		current_typed_word.pop_back();
		return true;
	}
	return false;
}

/*
TODO implement engine
Handle an input character and act accordingly
	- compare current typed word with the correct word char by char
	- log_key

*/
bool Engine::tick(char c) {
	int l = current_typed_word.length();
	string correct_word = full_text[index];
	current_typed_word.push_back(c);
	log_key(c);

	if (l >= correct_word.length()) {
		return false;
	} else if (correct_word[l] != c) {
		return false;
	}
	return true;
}