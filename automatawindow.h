#ifndef AUTOMATAWINDOW_H
#define AUTOMATAWINDOW_H

#include "growtharea.h"

class AutomataWindow: public Gtk::Window
{
protected:
	Gtk::VBox main_box;
	GrowthArea growth_area;
	Gtk::VBox widgets_box;
	Gtk::HButtonBox button_box;
	Gtk::Button five_button;
	Gtk::Button twenty_button;
	Gtk::Button screen_button;
	Gtk::Frame control_frame;
	Gtk::HBox rule_box;
	Gtk::Label msg_label;
	Gtk::Entry entry_rule;
	Gtk::Button set_button;

	virtual void on_five_button_clicked();
	virtual void on_twenty_button_clicked();
	virtual void on_screen_button_clicked();	

	virtual void on_set_button_clicked();		

public:
	AutomataWindow(short init_size, short init_rule);
};

#endif // AUTOMATAWINDOW_H