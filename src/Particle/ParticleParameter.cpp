#include "ParticleParameter.h"


ParticleParameter::ParticleParameter()
{
	attributes_bool.setName("Particles Attributes");
	attributes_bool.add(ATTR_BORDER_XYZ.set("Border XYZ", false);
	attributes_bool.add(ATTR_CONNECT_NEXT.set("Connect Next", false);
	attributes_bool.add(ATTR_CONNECT_PREV.set("Connect Prev", false);
	attributes_bool.add(ATTR_SPRING_NEXT.set("Spring to Next", false);
	attributes_bool.add(ATTR_SPRING_PREV.set("Spring to Prev", false);
	attributes_bool.add(ATTR_COLLISION.set("Collision", false);
	attributes_bool.add(ATTR_COLOR_DIFF.set("Attract from Color", false);
	
	parameter_double.setName("Particles Parameters");
	parameter_double.add(PARAM_COLOR_DIFF_MULT.set("Color Attraction", 0.1, 0.0, 1.0));
	parameter_double.add(PARAM_COLLISION_MULT.set("Collision", 0.1, 0.0, 1.0));

	parameter_double.add(PARAM_BORDER_X.set("borderX", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	parameter_double.add(PARAM_BORDER_Y.set("borderY", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));
	parameter_double.add(PARAM_BORDER_Z.set("borderZ", ofVec2f(-200,200), ofVec2f(-1000,-1000), ofVec3f(1000,1000)));

	parameter_double.add(drag.set("drag", 1.0, 0.0, 1.0));
	parameter_double.add(mass.set("mass", 1.0, 0.1, 4.0));

	parameter_double.add(springStiffness.set("springStiffness", 1.0, 0.0, 4.0));
	parameter_double.add(springDamping.set("springDamping", 0.1, 0.0, 1.0));
	
	
}