
#include "growtharea.h"

#include <vector>


GrowthArea::GrowthArea(short init_size, short default_rule):
	bounds(init_size),
	start(0),
	end(0)
{
	// sets the size of drawing area
	this->set_size_request(this->bounds, this->bounds);

	// puts the default rule into this growth area
	this->set_rule(default_rule);

	// applies the default rule
	for (int step = 1; step < this->bounds; step++)
		this->apply_rule(step);
}

short GrowthArea::new_value(short v2, short v1, short v0)
{
	return rule[v2*4 + v1*2 + v0*1];
}

bool GrowthArea::on_expose_event(GdkEventExpose *e)
{
 	Glib::RefPtr<Gdk::Window> curr_win = get_window();

	// creates a white gc to draw points
	Glib::RefPtr<Gdk::GC> point_gc = get_style()->get_white_gc();

	// creates a black gc to draw background
	Glib::RefPtr<Gdk::GC> backg_gc = get_style()->get_black_gc();

	// a container to store the GrowthArea points
	std::vector<Gdk::Point> square;
	
	// storing the points
	square.push_back(Gdk::Point(0, 0));
	square.push_back(Gdk::Point(this->bounds - 1, 0));
	square.push_back(Gdk::Point(this->bounds - 1, this->bounds - 1));
	square.push_back(Gdk::Point(0, this->bounds - 1));

	// drawing a black polygon which fills the entire GrowthArea
	curr_win->draw_polygon(backg_gc, true, square);

	// drawing the rule evolution
	int traveller = this->start;
	for (int y = 0; y < this->bounds; y++)
	{
		for (int x = 0; x < this->bounds; x++)
			if (this->sites[traveller][x])
				curr_win->draw_point(point_gc, x, y);
			
		if (traveller == this->end)
			break;
		else if(traveller >= this->bounds - 1)
			traveller = 0;
		else
			traveller++;
	}
}

void GrowthArea::set_rule(short new_rule)
{
	// initializing rule array
	for (int w = 0; w < 8; w++)
		rule[w] = 0;	

	// converting new_rule to bin rule
	for (int w = 0; new_rule > 0 ; w++)
	{
		rule[w] = new_rule % 2;
		new_rule /= 2;
	} 

	// initializing sites
	for (int step = 0; step < bounds; step++)
		for (int w = 0; w < bounds; w++)
			sites[step][w] = 0;
	sites[0][bounds/2] = 1;

	start = 1;
	end = bounds - 1;
}

void GrowthArea::apply_rule(short step)
{
	// sets the growth pointers
	if (start >= bounds-1)
		start = 0;
	else
		start++;

	if (end >= bounds - 1)
		end = 0;
	else
		end++;

	// applies the current rule
	for (int w = 0; w < bounds; w++)
	{
		if (step > 0)
		{
			if (w == 0)
				sites[step][w] = new_value(sites[step-1][bounds-1], sites[step-1][w], sites[step-1][w+1]);
			else if (w == bounds - 1)
				sites[step][w] = new_value(sites[step-1][w-1], sites[step-1][w], sites[step-1][0]);
			else
				sites[step][w] = new_value(sites[step-1][w-1], sites[step-1][w], sites[step-1][w+1]);
		}
		else
		{
			if (w == 0)
				sites[step][w] = new_value(sites[bounds-1][bounds-1], sites[bounds-1][w], sites[bounds-1][w+1]);
			else if (w == bounds-1)
				sites[step][w] = new_value(sites[bounds-1][w-1], sites[bounds-1][w], sites[bounds-1][0]);
			else
				sites[step][w] = new_value(sites[bounds-1][w-1], sites[bounds-1][w], sites[bounds-1][w+1]);
		}
	}
}

short GrowthArea::get_bounds() const
{
	return bounds;
}

short GrowthArea::get_start() const
{
	return start;
}

short GrowthArea::get_end() const
{
	return end;
}
