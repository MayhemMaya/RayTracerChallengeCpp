#include "world.h"

bool check_for_light_source(const std::vector<Object*>& world_objects) {
  for (int i = 0; i < world_objects.size(); i++) {
    if (utils::instance_of<LightSource>(world_objects[i]))
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
  }
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
    if (utils::instance_of<LightSource>(objects_[i]))
      lights.push_back((LightSource*)(objects_[i]));
  }
  return lights;
}

std::vector<Shape*> World::GetShapes() const {
  std::vector<Shape*> shapes;
  for (int i = 0; i < objects_.size(); i++) {
    if (utils::instance_of<Shape>(objects_[i]))
      shapes.push_back((Shape*)(objects_[i]));
  }
  return shapes;
}

std::vector<Camera*> World::GetCameras() const {
  std::vector<Camera*> cameras;
  for (int i = 0; i < objects_.size(); i++) {
    if (utils::instance_of<Camera>(objects_[i]))
      cameras.push_back((Camera*)(objects_[i]));
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

void World::ListObjects(const ObjectType& type) const {
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
    }
  }
  objects_.push_back(object);
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
  for (int i = 0; i < objects_.size(); i++) {
    if (utils::instance_of<Camera>(objects_[i]))
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