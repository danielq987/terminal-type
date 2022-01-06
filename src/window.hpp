#pragma once
#include <ncurses.h>
#include <string>

using std::string;

const int MAX_WINDOW_WIDTH = 60;

struct WindowInit {
	int height;
	int width;
	int starty;
	int startx;
};

// Creates a bordered window.
class BorderedWindow {
private:
	WINDOW *win;
	WINDOW *border;

	// Default dimensions
	WindowInit dimensions;
public:
	WINDOW *get_win() { return win; }
	WINDOW *get_border() { return border; }
	void create_window();
	void destroy_window();
	void set_dimensions(WindowInit d);
};

// Window for displaying text.
class TextWindow : public BorderedWindow {
private:
	string type_string;
	WindowInit window_init = { .height = 4, .width = 80,
		.starty = 0, .startx = 0 };
	std::pair<int, int> word_start = std::make_pair(0, 0);
public:
	string get_string() { return type_string; };
	void set_string(string s) { this->type_string = s; };
	void set_word_start(int y, int x);
	TextWindow(string s);
	TextWindow();
	void keypress(bool is_correct);
	void bs();
	void clear();
};

// Window for user input.
class InputWindow : public BorderedWindow {
private:
	string value = "";
	WindowInit window_init = { .height = 1, .width = 80,
		.starty = 6, .startx = 0 };
public:
	InputWindow();
	// Clear the window of all input and value.
	void clear();
	// Simulate a backspace keypress.
	void bs();
	// Simulate a space press.
	void space();
	// Add a character to the input window
	void append_char(char c, bool is_correct);
};

// Functions for creating and destroying windows.
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

// Get maximum width of the stdscr.
int get_max_width();

// Move cursor relative to current position, (y, x) by (dy, dx).
void relative_move(WINDOW *window, int dy, int dx);