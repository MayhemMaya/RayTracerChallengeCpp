#include "hexagon.h"

Hexagon::Hexagon(const std::string& name, const Material& material) : Group(name) {
	this->SetMaterial(material);
	for (int n = 0; n < 6; n++) {
		sides_[n] = Group("side");
		sides_[n].SetMaterial(material);

		corners_[n] = Sphere("corner");
		corners_[n].SetTransform(Matrix4().translation(0, 0, -1)
																 .scaling(0.25f, 0.25f, 0.25f));

		edges_[n] = Cylinder("edge", 0, 1);
		edges_[n].SetTransform(Matrix4().translation(0, 0, -1)
															 .rotation_y(-utils::kPI / 6)
															 .rotation_z(-utils::kPI / 2)
															 .scaling(0.25f, 1, 0.25f));

		sides_[n].AddChild(&corners_[n]);
		sides_[n].AddChild(&edges_[n]);

		sides_[n].SetTransform(Matrix4().rotation_y(n * utils::kPI / 3));
		this->AddChild(&sides_[n]);
	}
}