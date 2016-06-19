#include "ParticleParameter.h"


ParticleParameter::ParticleParameter()
{	
	
	group.setName("Particles Parameters");
	
	group.add(color_diff_mult.set("Color Attraction", 0.1, 0.0, 1.0));
	group.add(collision_mult.set("Collision", 0.1, 0.0, 1.0));

	group.add(border_x_range.set("borderX", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	group.add(border_y_range.set("borderY", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	group.add(border_z_range.set("borderZ", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));

	group.add(drag.set("drag", 1.0, 0.0, 1.0));
	group.add(mass.set("mass", 1.0, 0.01, 4.0));

	group.add(spring_stiffness.set("springStiffness", 1.0, 0.0, 4.0));
	group.add(spring_damping.set("springDamping", 0.1, 0.0, 1.0));

}