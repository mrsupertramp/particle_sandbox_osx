#include "ParticleAttributes.h"

ParticleAttributes::ParticleAttributes()
{
	border_xyz.addListener(this, &ParticleAttributes::set_border_xyz);
	
	connect_next.addListener(this, &ParticleAttributes::set_connect_next);
	connect_prev.addListener(this, &ParticleAttributes::set_connect_prev);
	spring_next.addListener(this, &ParticleAttributes::set_spring_next);
	spring_prev.addListener(this, &ParticleAttributes::set_spring_prev);
	collision.addListener(this, &ParticleAttributes::set_collision);
	attraction_color.addListener(this, &ParticleAttributes::set_attraction_color);
	
	group.add(border_xyz.set("Border XYZ",				false));
	group.add(connect_next.set("Connect Next",			false));
	group.add(connect_prev.set("Connect Prev",			false));
	group.add(spring_next.set("Spring Next",			false));
	group.add(spring_prev.set("Spring Prev",			false));
	group.add(collision.set("Collision",				false));
	group.add(attraction_color.set("Attraction Color",	false));
	bits = 0;
}

bool ParticleAttributes::checkAttribute(int attribute){
	return attribute & bits;
}

bool ParticleAttributes::checkAttributes(int attributes_)
{
	bool check = true;
	for (unsigned int i=0; i<26; ++i){
		if (attributes_ & (1<<i))
			check &= checkAttribute(1<<i);
	}
	return check;
}

void ParticleAttributes::set_border_xyz(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_BORDER_XYZ;
	} else {
		bits &= ~(1 << ATTR_BORDER_XYZ);
	}
}
void ParticleAttributes::set_border_circle(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_BORDER_CIRCLE;
	} else {
		bits &= ~(1 << ATTR_BORDER_CIRCLE);
	}
}
void ParticleAttributes::set_connect_next(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_CONNECT_NEXT;
	} else {
		bits &= ~(1 << ATTR_CONNECT_NEXT);
	}
}
void ParticleAttributes::set_connect_prev(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_CONNECT_PREV;
	} else {
		bits &= ~(1 << ATTR_CONNECT_PREV);
	}
}
void ParticleAttributes::set_spring_next(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_SPRING_NEXT;
	} else {
		bits &= ~(1 << ATTR_SPRING_NEXT);
	}
}
void ParticleAttributes::set_spring_prev(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_SPRING_PREV;
	} else {
		bits &= ~(1 << ATTR_SPRING_PREV);
	}
}
void ParticleAttributes::set_collision(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_COLLISION;
	} else {
		bits &= ~(1 << ATTR_COLLISION);
	}
}
void ParticleAttributes::set_attraction_color(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_ATTRACTION_COLOR;
	} else {
		bits &= ~(1 << ATTR_ATTRACTION_COLOR);
	}
}
void ParticleAttributes::set_draw_line_dist(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_DRAW_LINE_DIST;
	} else {
		bits &= ~(1 << ATTR_DRAW_LINE_DIST);
	}
}
void ParticleAttributes::set_draw_line_next(bool &b_)
{
	if (b_) {
		bits |= 1 << ATTR_DRAW_LINE_NEXT;
	} else {
		bits &= ~(1 << ATTR_DRAW_LINE_NEXT);
	}
}