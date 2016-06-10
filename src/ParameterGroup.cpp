#include "ParameterGroup.h"

void ParameterGroup::ParameterGroup()
{
	attr_border_xyz.addListener(this, &ofApp::setAttributeBorderXYZ);

	attr_collision.addListener(this, &ofApp::setAttributeCollision);
	attr_color_diff.addListener(this, &ofApp::setAttributeColorDiff);
	attr_spring_prev.addListener(this, &ofApp::setAttributeSpringPrev);
	attr_connect_next.addListener(this, &ofApp::setAttributeConnectNext);
	attr_connect_prev.addListener(this, &ofApp::setAttributeConnectPrev);
	overrideAttributes.addListener(this, &ofApp::setAttributesAllParticles);
	
	para_drag.addListener(this, &ofApp::update)
	para_mass
	para_spring_stiffness
	para_spring_damping
	paraCollisionMult
	paraColorDiffMult
	paraBorderX
	paraBorderY
	paraBorderZ
			
	gui.setup();
	gui.add(para_drag.setup("drag", 1.0, 0.1, 1.0));
	gui.add(para_mass.setup("mass", 1.0, 0.01, 4.0));
	gui.add(para_spring_stiffness.setup("spring stiffness", 1.0, 0.01, 4.0));
	gui.add(para_spring_damping.setup("spring damping", 1.0, 0.01, 1.0));
	gui.add(paraCollisionMult.setup("collision mult", 0.03, 0.0, 0.08));
	gui.add(paraColorDiffMult.setup("color diff mult", 0.2, 0.0, 0.04));
	gui.add(paraBorderX.setup("border x",ofVec2f(-200,200),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	gui.add(paraBorderY.setup("border y",ofVec2f(-200,200),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));
	gui.add(paraBorderZ.setup("border z",ofVec2f(-150,150),ofVec2f(-1000,-1000),ofVec2f(1000,1000)));

	gui.add(attr_border_xyz.setup("attr_border_xyz",false));
	gui.add(attr_collision.setup("attr_collision",false));
	gui.add(attr_spring_prev.setup("attr_spring_dev",false));
	gui.add(attr_connect_next.setup("attr_connect_next",false));
	gui.add(attr_connect_prev.setup("attr_connect_prev",false));
	gui.add(attr_color_diff.setup("attr_color_diff",false));

	gui.add(overrideAttributes.setup("override"));
}