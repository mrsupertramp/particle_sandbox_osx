#include "ParticleAttributes.h"

ParticleAttributes::ParticleAttributes()
{
	
	group.add(border_xyz.set("Border XYZ",				true));
	group.add(connect_next.set("Connect Next",			false));
	group.add(connect_prev.set("Connect Prev",			false));
	group.add(spring_next.set("Spring Next",			false));
	group.add(spring_prev.set("Spring Prev",			false));
	group.add(collision.set("Collision",				false));
	group.add(attraction_color.set("Attraction Color",	false));

}
