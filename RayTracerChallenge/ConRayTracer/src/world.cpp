#include "world.h"

World::World(const WorldType& type) {
  if (type == WorldType::DEFAULT) {
    objects_.push_back(new PointLight("pointlight1", Point(-10, 10, -10), Color(1, 1, 1)));

    Material m;
    m.SetColor(Color(0.8f, 1.0f, 0.6f));
    m.SetDiffuse(0.7f);
    m.SetSpecular(0.2f);
    objects_.push_back(new Sphere("sphere1", m));

    objects_.push_back(new Sphere("sphere2", Matrix4().scaling(0.5f, 0.5f, 0.5f)));
  }
}

World::~World() {
  for (int i = 0; i < objects_.size(); i++) {
    delete objects_[i];
  }
}

std::vector<Object*> World::GetObjects() const {
  return objects_;
}

std::vector<LightSource*> World::GetLights() const {
  std::vector<LightSource*> lights;
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetObjectType() == ObjectType::kPointLight)
      lights.push_back((LightSource*)objects_[i]);
  }
  return lights;
}

std::vector<Mesh*> World::GetMeshes() const {
  std::vector<Mesh*> meshes;
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetObjectType() == ObjectType::kMesh ||
        objects_[i]->GetObjectType() == ObjectType::kSphere)
      meshes.push_back((Mesh*)objects_[i]);
  }
  return meshes;
}

std::vector<Camera*> World::GetCameras() const {
  std::vector<Camera*> cameras;
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetObjectType() == ObjectType::kCamera)
      cameras.push_back((Camera*)objects_[i]);
  }
  return cameras;
}

int World::GetObjectCount() const {
  return objects_.size();
}

void World::ListObjects() const {
  for (int i = 0; i < objects_.size(); i++) {
    std::cout << objects_[i]->GetName() << std::endl;
  }
}

void World::ListObjects(ObjectType type) const {
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetObjectType() == type)
      std::cout << objects_[i]->GetName() << std::endl;
  }
}

void World::AddObject(Object* object) {
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetName() == object->GetName()) {
      std::cout << "Error: Cannot add object to world. An object with the name '"
          << object->GetName() << "' already exists." << std::endl;
      return;
    }
  }
  objects_.push_back(object);
}
void World::DeleteObject(std::string name) {
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetName() == name) {
      objects_.erase(objects_.begin() + i);
    }
  }
}

bool World::ContainsLightSource() const {
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetObjectType() == ObjectType::kPointLight)
      return true;
  }
  return false;
}

bool World::ContainsCamera() const {
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetObjectType() == ObjectType::kCamera)
      return true;
  }
  return false;
}

bool World::ContainsObject(Object* object) const {
  for (int i = 0; i < objects_.size(); i++) {
    if ((*objects_[i]) == (*object)) {
      return true;
    }
  }
  return false;
}