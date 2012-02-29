
#include "automatawindow.h"

int main(int argc, char **argv)
{
	Gtk::Main automata(argc, argv);
	AutomataWindow wolfram(470, 90);

	automata.run(wolfram);

	return 0;
}
