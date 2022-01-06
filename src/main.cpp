#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <window.hpp>
#include <shared.hpp>
#include <engine.hpp>

const std::string PATH = "static/mock.txt";

using std::cout;
using std::string;

string mock_input() {
	std::ifstream filein(PATH);
	if (!filein) {
		return "Error Opening File!";
	}

	string s;
	std::getline(filein, s);
	return s;
}

InputWindow *input_window;
TextWindow *text_window;
Engine *engine;

int parse_char(int char_code) {
	switch (char_code) {
	case KEY_BACKSPACE:
	{
		bool success = engine->handle_bs();
		if (success) {
			input_window->bs();
			text_window->bs();
		}
		break;
	}

	case 1:
		// Ctrl + A
		engine->set_current_typed_word("");
		input_window->clear();
		text_window->clear();
		break;

	case ' ':
	{
		bool success = engine->handle_space();
		text_window->keypress(success);
		if (success) {
			input_window->clear();
			int y, x;
			getyx(text_window->get_win(), y, x);
			text_window->set_word_start(y, x);
		} else {
			input_window->append_char(' ', false);
		}
		break;
	}

	default:
		bool is_correct = engine->tick(char_code);
		input_window->append_char(char_code, is_correct);
		text_window->keypress(is_correct);
		return 1;
	}
	return 0;
}

int main() {
	initscr();
	cbreak();
	// raw();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	keypad(stdscr, TRUE);
	string s = mock_input();
	move(0, 0);

	text_window = new TextWindow(s);
	input_window = new InputWindow();

	// Split strings by space
	engine = new Engine(s);

	int b;
	do {
		b = getch();
		parse_char(b);
		// wprintw(input_window->get_win(), "%c", b);
		// wrefresh(input_window->get_win());
	} while (b != '0');

	// getch();

	text_window->destroy_window();
	input_window->destroy_window();

	delete text_window;
	delete input_window;
	delete engine;
	endwin();

	return 0;
}