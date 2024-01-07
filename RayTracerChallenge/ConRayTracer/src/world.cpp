#include "world.h"

bool check_for_light_source(const std::vector<Object*>& world_objects) {
  for (auto world_object : world_objects) {
    if (utils::instance_of<LightSource>(world_object))
      return true;
  }
  return false;
}

World::World() : objects_({}), hasLightSource_(false) {}

std::vector<Object*> default_world(const WorldType& type) {
  if (type == WorldType::DEFAULT) {
    Material m;
    m.SetColor(Color(0.8f, 1.0f, 0.6f));
    m.SetDiffuse(0.7f);
    m.SetSpecular(0.2f);

    return {
      new PointLight("PointLight1", Point(-10, 10, -10), Color(1, 1, 1)),
      new Sphere("Sphere1", m),
      new Sphere("Sphere2", Matrix4().scaling(0.5f, 0.5f, 0.5f))
    };
  }
  return {};
}

World::World(const WorldType& type)
  : objects_(default_world(type)), hasLightSource_(type == WorldType::DEFAULT) {}

World::~World() {
  for (int i = 0; i < objects_.size(); i++) {
    objects_[i] = nullptr;
    delete objects_[i];
  }
}

std::vector<Object*> World::GetObjects() const {
  return objects_;
}

std::vector<LightSource*> World::GetLights() const {
  std::vector<LightSource*> lights;
  for (auto& object : objects_) {
    if (utils::instance_of<LightSource>(object))
      lights.push_back((LightSource*)(object));
  }
  return lights;
}

std::vector<Shape*> World::GetShapes() const {
  std::vector<Shape*> shapes;
  for (auto& object : objects_) {
    if (utils::instance_of<Shape>(object))
      shapes.push_back((Shape*)(object));
  }
  return shapes;
}

std::vector<Camera*> World::GetCameras() const {
  std::vector<Camera*> cameras;
  for (auto object : objects_) {
    if (utils::instance_of<Camera>(object))
      cameras.push_back((Camera*)(object));
  }
  return cameras;
}

int World::GetObjectCount() const {
  return objects_.size();
}

void World::ListObjects() const {
  for (auto& object : objects_) {
    std::cout << object->GetName() << std::endl;
  }
}

void World::ListObjects(const ObjectType& type) const {
  for (auto& object : objects_) {
    if (object->GetObjectType() == type)
      std::cout << object->GetName() << std::endl;
  }
}

void World::AddObject(Object* other) {
  for (auto& object : objects_) {
    if (object->GetName() == other->GetName()) {
      std::cout << "Error: Cannot add object to world. An object with the name '"
          << other->GetName() << "' already exists." << std::endl;
      return;
    }
  }
  objects_.push_back(other);
  hasLightSource_ = check_for_light_source(objects_);
}

void World::DeleteObject(const std::string& name) {    
  for (int i = 0; i < objects_.size(); i++) {
    if (objects_[i]->GetName() == name) {
      objects_.erase(objects_.begin() + i);
    }
  }

  hasLightSource_ = check_for_light_source(objects_);
}

bool World::ContainsLightSource() const {
  return hasLightSource_;
}

bool World::ContainsCamera() const {
  for (auto& object : objects_) {
    if (utils::instance_of<Camera>(object))
      return true;
  }
  return false;
}

bool World::ContainsObject(Object* other) const {
  for (auto& object : objects_) {
    if ((*object) == (*other)) {
      return true;
    }
  }
  return false;
}