#ifndef GROWTHAREA_H
#define GROWTHAREA_H

#include <gtkmm.h>

class GrowthArea: public Gtk::DrawingArea
{
	static const short MAXCELL = 480;

private:
	short sites[MAXCELL][MAXCELL];
	short bounds, start, end;
	short rule[8];

	short new_value(short v2, short v1, short v0); // return a new value for some site

public:
	GrowthArea(short init_size, short default_rule = 90);

	bool on_expose_event(GdkEventExpose *e);

	void set_rule(short new_rule);
	void apply_rule(short step);

	short get_bounds() const;
	short get_start() const;
	short get_end() const;
};

#endif // GROWTHAREA_H
