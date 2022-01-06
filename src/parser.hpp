#include <string>
#include <vector>

using std::string;
using std::vector;

class Engine {
private:
	string current_typed_word = "";
	const string full_text;
	int current_position = 0;
	vector<char> keylog;

public:
	Engine(string text);
	string get_full_text();
	string get_current_typed_word();
	void set_current_typed_word(string s);
	int get_current_position();
	void set_current_position(int pos);
	void log_key(char c);
	int tick(char c);
};

