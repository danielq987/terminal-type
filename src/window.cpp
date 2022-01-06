#include <window.hpp>
#include <string>

using std::string;

WINDOW *create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win) {
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

int get_max_width() {
	int max_w, max_h;
	getmaxyx(stdscr, max_h, max_w);
	return std::min(max_w, 60);
}

void relative_move(WINDOW *window, int dy, int dx) {
	int y, x, maxy, maxx;
	getyx(window, y, x);
	getmaxyx(window, maxy, maxx);

	y += dy;
	x += dx;

	if (y < 0) y = 0;
	if (x < 0) x = 0;
	if (y >= maxy) y = maxy - 1;
	if (x >= maxx - 1) x = maxx - 2;

	wmove(window, y, x);
}

void BorderedWindow::create_window() {
	border = create_newwin(dimensions.height + 2, dimensions.width,
		dimensions.starty, dimensions.startx);
	win = create_newwin(dimensions.height, dimensions.width - 2,
		dimensions.starty + 1, dimensions.startx + 1);

	refresh();
	box(border, 0, 0);
	wrefresh(border);
	wrefresh(win);
}

void BorderedWindow::destroy_window() {
	destroy_win(win);
	destroy_win(border);
}

void BorderedWindow::set_dimensions(WindowInit d) {
	dimensions = d;
}

TextWindow::TextWindow(string s) {
	type_string = s;
	window_init.width = get_max_width();
	this->set_dimensions(window_init);
	BorderedWindow::create_window();

	wprintw(get_win(), "%s", s.data());
	wmove(get_win(), 0, 0);
	wrefresh(get_win());
}

TextWindow::TextWindow() {};

void TextWindow::bs() {
	relative_move(get_win(), 0, -1);
	wchgat(get_win(), 1, A_NORMAL, 0, NULL);
	wrefresh(get_win());
};

void TextWindow::clear() {
	wmove(get_win(), word_start.first, word_start.second);
	wchgat(get_win(), -1, A_NORMAL, 0, NULL);
	wmove(get_win(), word_start.first, word_start.second);
	wrefresh(get_win());
}

void TextWindow::keypress(bool is_correct) {
	wchgat(get_win(), 1, A_NORMAL, is_correct ? 2 : 1, NULL);
	relative_move(get_win(), 0, 1);
	wrefresh(get_win());
};

void TextWindow::set_word_start(int y, int x) {
	word_start.first = y;
	word_start.second = x;
}

InputWindow::InputWindow() {
	window_init.width = get_max_width();
	this->set_dimensions(window_init);
	BorderedWindow::create_window();
	wmove(get_win(), 0, 0);

	wrefresh(get_win());
}

void InputWindow::clear() {
	werase(get_win());
	wmove(get_win(), 0, 0);
	wrefresh(get_win());
}

void InputWindow::bs() {
	relative_move(get_win(), 0, -1);
	waddch(get_win(), ' ');
	relative_move(get_win(), 0, -1);
	wrefresh(get_win());

	if (value.length() > 0) value.pop_back();
}

void InputWindow::append_char(char c, bool is_correct) {
	int y, x;
	getyx(get_win(), y, x);

	if (x < window_init.width - 3) {
		if (!is_correct)
			wattron(get_win(), COLOR_PAIR(1));
		wprintw(get_win(), "%c", c);
		wattroff(get_win(), COLOR_PAIR(1));
		wrefresh(get_win());
		value.push_back(c);
	}
}