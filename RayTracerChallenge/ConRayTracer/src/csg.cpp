#include "csg.h"
#include "utils.h"
#include "group.h"
#include "ray.h"

bool includes(Shape* a, Object* b) {
  if (a->GetObjectType() == ObjectType::kGroup) {
    Group* a_as_group = (Group*)a;
    for (const auto& child : a_as_group->GetChildren()) {
      if (includes(child, b)) {
        return true;
      }
    }
  }

  if (a->GetObjectType() == ObjectType::kCSG) {
    CSG* a_as_csg = (CSG*)a;
    if (includes(a_as_csg->GetLeft(), b) || includes(a_as_csg->GetRight(), b)) {
      return true;
    }
  }
  return (*a == *b);
}

Shape* validate_shape(Shape* shape) {
  if (shape == nullptr) {
    throw std::invalid_argument("CSV shape cannot be nullptr.");
  }

  return shape;
}

CSG::CSG(const Operation& operation, Shape* left, Shape* right)
  : Shape("csv", ObjectType::kCSG), operation_(operation), left_(validate_shape(left)), right_(validate_shape(right)) {
  left_->SetParent(this);
  right_->SetParent(this);
}

CSG::CSG(const std::string& name, const Operation& operation, Shape* left, Shape* right)
  : Shape(name, ObjectType::kCSG), operation_(operation), left_(left), right_(right) {
  left_->SetParent(this);
  right_->SetParent(this);
}

CSG::CSG(const std::string& name, const Operation& operation, Shape* left, Shape* right, const Matrix4& transform)
  : Shape(name, ObjectType::kCSG, transform), operation_(operation), left_(left), right_(right) {
  left_->SetParent(this);
  right_->SetParent(this);
}

CSG::~CSG() {
  left_->RemoveParent();
  right_->RemoveParent();
  left_ = nullptr;
  right_ = nullptr;
  delete left_;
  delete right_;
}

bool CSG::operator==(const Object& object) const {
  CSG* other = (CSG*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    parent_ == other->GetParent() &&
    id_ == other->GetID() &&
    material_ == other->GetMaterial() &&
    left_ == other->GetLeft() &&
    right_ == other->GetRight());
}

CSG& CSG::operator=(const Object& object) {
  CSG* other = (CSG*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();

  return *this;
}

Operation CSG::GetOperation() const {
  return operation_;
}

Shape* CSG::GetLeft() const {
  return left_;
}

Shape* CSG::GetRight() const {
  return right_;
}

void CSG::SetLeft(Shape* left) {
  left_ = validate_shape(left);
}

void CSG::SetRight(Shape* right) {
  right_ = validate_shape(right);
}

std::vector<Intersection> CSG::filter_intersections(const std::vector<Intersection>& xs) const {
  // begin outside of both children
  bool inl = false;
  bool inr = false;

  // prepare a list to receive the filtered intersections
  std::vector<Intersection> allowed_xs;

  for (const auto& i : xs) {
    // if i.object is part of the "left" child, then lhit is true
    bool lhit = includes(this->left_, i.GetObject());

    if (CSG::intersection_allowed(this->operation_, lhit, inl, inr)) {
      allowed_xs.push_back(i);
    }

    // depending on which object was hit, toggle either inl or inr
    if (lhit) {
      inl = !inl;
    }
    else {
      inr = !inr;
    }
  }
  return allowed_xs;
}

std::vector<Intersection> CSG::local_intersect(const utils::RayStruct& local_ray) {
  Ray ray = Ray(local_ray.origin, local_ray.direction);
  std::vector<Intersection> left_xs = ray.intersect(this->left_);
  std::vector<Intersection> right_xs = ray.intersect(this->right_);

  std::vector<Intersection> xs;
  xs.insert(xs.end(), left_xs.begin(), left_xs.end());
  xs.insert(xs.end(), right_xs.begin(), right_xs.end());

  xs = Intersection::intersections(xs);
  return this->filter_intersections(xs);
}

Vector CSG::local_normal_at(const Point& local_point, const Intersection& hit) const {
  throw std::exception("Cannot call local_normal_at() on CSG objects!");
}

BoundingBox CSG::bounds() const {
  return BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
}

bool CSG::intersection_allowed(Operation op, bool lhit, bool inl, bool inr) {
  if (op == Operation::UNION) {
    return (lhit && !inr) || (!lhit && !inl);
  }

  if (op == Operation::INTERSECTION) {
    return (lhit && inr) || (!lhit && inl);
  }

  if (op == Operation::DIFFERENCE) {
    return (lhit && !inr) || (!lhit && inl);
  }
  return false;
}