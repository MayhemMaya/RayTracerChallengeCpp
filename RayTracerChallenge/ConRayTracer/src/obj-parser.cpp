#include "obj-parser.h"

ObjParser::ObjParser(const std::string& file_name, const ShadingType& shading_type, bool suppress_errors) : lines_ignored_(0), face_count_(0), current_line_(1), groups_({ new Group("__DefaultGroup__") }),
  selected_group_index_(0), triangle_count_(0), file_name_(file_name), suppress_errors_(suppress_errors), shading_type_(shading_type) {
  utils::FileNameCheck check = utils::check_file_name(file_name, utils::FileExtensions::OBJ);
  if (check.err.occured) {
    std::cerr << check.err.msg << "\n";
    return;
  }

  std::ifstream file(check.file_name);

  if (!file.is_open()) {
    if (!suppress_errors_) std::cerr << "File '" << check.file_name << "' does not exist." << "\n";
    return;
  }

  std::cout << "Processing file: '" << check.file_name << "'." << "\n";

  std::string line;
  // Use a while loop together with the getline() function to read the file line by line
  while (std::getline(file, line)) {
    std::string stripped_line = utils::remove_leading_and_trailing_whitespace(line);
    std::string equal_line = utils::create_equal_whitespace(stripped_line);
    process_line(equal_line);
    current_line_++;
  }

  std::cout << "File '" << check.file_name << "' opened and parsed successfully." << "\n\n";

  // Close the file
  file.close();
}

ObjParser::~ObjParser() {
  for (int i = 0; i < groups_.size(); i++) {
    groups_[i] = nullptr;
    delete groups_[i];
  }
}

std::vector<Point> ObjParser::GetVertices() const {
  return vertices_;
}

std::vector<Vector> ObjParser::GetNormals() const {
  return normals_;
}

Group* ObjParser::GetDefaultGroup() const {
  return groups_[0];
}

Group* ObjParser::GetGroupByName(const std::string& name) const {
  for (auto& group : groups_) {
    if (group->GetName() == name) {
      return group;
    }
  }
  return groups_[0];
}

int ObjParser::GetLinesIgnored() const {
  return lines_ignored_;
}

void ObjParser::ConvertToSceneGroup(Group* scene_group) const {
  for (auto& group : groups_) {
    if (group->GetChildrenCount() > 0) {
      scene_group->AddChild(group);
    }
  }
}

int ObjParser::GetTriangleCount() const {
  return triangle_count_;
}

int ObjParser::GetGroupCount() const {
  return groups_.size();
}

int ObjParser::GetFaceCount() const {
  return face_count_;
}

std::vector<Group*> ObjParser::GetGroups() const {
  return groups_;
}

void ObjParser::process_line(const std::string& line) {

  if (0 > line.size() || 1 > line.size()) {
    return;
  }

  if (line.at(0) == 'v' && line.at(1) == ' ') {
    process_vertex(line);
    return;
  }

  if (line.at(0) == 'v' && line.at(1) == 'n' && line.at(2) == ' ') {
    process_vertex_normal(line);
    return;
  }

  if (line.at(0) == 'g' && line.at(1) == ' ') {
    process_group(line);
    return;
  }

  if (line.at(0) == 'f' && line.at(1) == ' ') {
    process_face(line);
    face_count_++;
    return;
  }

  lines_ignored_++;
}

void ObjParser::process_vertex(const std::string& line) {
  utils::SplitStringResult split_result = utils::split_string(line, ' ');
  if (split_result.failed) {
    if (!suppress_errors_) std::cerr << "Could not process vertex on line: " << current_line_ << " due to failed string split.\n";
  }
  split_result.segments.erase(std::remove(split_result.segments.begin(), split_result.segments.end(), "v"), split_result.segments.end());
  utils::Number x = utils::string_to_number(split_result.segments[0], suppress_errors_);
  utils::Number y = utils::string_to_number(split_result.segments[1], suppress_errors_);
  utils::Number z = utils::string_to_number(split_result.segments[2], suppress_errors_);

  if (x.type == utils::NumberType::UNKNOWN ||
    y.type == utils::NumberType::UNKNOWN ||
    z.type == utils::NumberType::UNKNOWN) {
    if (!suppress_errors_) std::cerr << "Could not process vertex on line: " << current_line_ << " due to NumberType::UNKNOWN.\n";
  }

  if (x.type == utils::NumberType::FLOAT ||
    y.type == utils::NumberType::FLOAT ||
    z.type == utils::NumberType::FLOAT) {
    vertices_.push_back(Point(x.float_value, y.float_value, z.float_value));
    return;
  }

  vertices_.push_back(Point(x.int_value, y.int_value, z.int_value));
}

void ObjParser::process_vertex_normal(const std::string& line) {
  utils::SplitStringResult split_result = utils::split_string(line, ' ');
  if (split_result.failed) {
    if (!suppress_errors_) std::cerr << "Could not process vertex normal on line: " << current_line_ << " due to failed string split.\n";
  }
  split_result.segments.erase(std::remove(split_result.segments.begin(), split_result.segments.end(), "vn"), split_result.segments.end());
  utils::Number x = utils::string_to_number(split_result.segments[0], suppress_errors_);
  utils::Number y = utils::string_to_number(split_result.segments[1], suppress_errors_);
  utils::Number z = utils::string_to_number(split_result.segments[2], suppress_errors_);

  if (x.type == utils::NumberType::UNKNOWN ||
    y.type == utils::NumberType::UNKNOWN ||
    z.type == utils::NumberType::UNKNOWN) {
    if (!suppress_errors_) std::cerr << "Could not process vertex normal on line: " << current_line_ << " due to NumberType::UNKNOWN.\n";
  }

  if (x.type == utils::NumberType::FLOAT ||
    y.type == utils::NumberType::FLOAT ||
    z.type == utils::NumberType::FLOAT) {
    normals_.push_back(Vector(x.float_value, y.float_value, z.float_value));
    return;
  }

  normals_.push_back(Vector(x.int_value, y.int_value, z.int_value));
}

void ObjParser::process_group(const std::string& line) {
  utils::SplitStringResult split_result = utils::split_string(line, ' ');
  if (split_result.failed) {
    if (!suppress_errors_) std::cerr << "Could not process group on line: " << current_line_ << " due to failed string split.\n";
  }
  split_result.segments.erase(std::remove(split_result.segments.begin(), split_result.segments.end(), "g"), split_result.segments.end());
  std::string group_name = split_result.segments[0];
  groups_.push_back(new Group(group_name));
  // set the selected group index to the index of the latest element
  selected_group_index_ = (groups_.size() - 1);
}

void ObjParser::process_face(const std::string& line) {
  utils::SplitStringResult split_result = utils::split_string(line, ' ');
  if (split_result.failed) {
    if (!suppress_errors_) std::cerr << "Could not process face on line: " << current_line_ << " due to failed string split.\n";
  }
  split_result.segments.erase(std::remove(split_result.segments.begin(), split_result.segments.end(), "f"), split_result.segments.end());

  std::vector<FaceSegmentData> face_segments = process_face_segments(split_result.segments);

  if (face_segments.size() > 3) {
    process_polygon(face_segments);
    return;
  }

  process_single_triangle(face_segments);
}

void ObjParser::fan_triangulation(const std::vector<PolygonComponent>& components, bool has_normals) {
  if (has_normals && shading_type_ == ShadingType::SMOOTH) {
    for (int i = 1; i < components.size() - 1; i++) {
      groups_[selected_group_index_]->AddChild(new SmoothTriangle(components[0].vertex, components[i].vertex, components[i + 1].vertex, components[0].normal, components[i].normal, components[i + 1].normal));
      triangle_count_++;
    }
    return;
  }
  for (int i = 1; i < components.size() -1; i++) {
    groups_[selected_group_index_]->AddChild(new Triangle(components[0].vertex, components[i].vertex, components[i + 1].vertex));
    triangle_count_++;
  }
}

std::vector<FaceSegmentData> ObjParser::process_face_segments(const std::vector<std::string>& segments) {
  std::vector<FaceSegmentData> face_segments;
  for (int i = 0; i < segments.size(); i++) {
    FaceSegmentData data;
    utils::SplitStringResult split_result = utils::split_string(segments[i], '/');
    if (split_result.failed) {
      data.position_id = segments[i];
      data.texture_coord = "";
      data.normal_id = "";
    }
    else {
      data.position_id = split_result.segments[0];
      data.texture_coord = split_result.segments[1];
      data.normal_id = split_result.segments[2];
    }
    face_segments.push_back(data);
  }
  return face_segments;
}

void ObjParser::process_polygon(const std::vector<FaceSegmentData>& face_segments) {
  std::vector<PolygonComponent> polygon_components;
  bool has_normals = false;
  for (auto& face_segment : face_segments) {
    PolygonComponent polygon;
    utils::Number vertex_pos_id = utils::string_to_number(face_segment.position_id, suppress_errors_);

    if (vertex_pos_id.type == utils::NumberType::UNKNOWN) {
      if (!suppress_errors_) std::cerr << "Could not process face on line: " << current_line_ << " due to NumberType::UNKNOWN.\n";
    }

    // We need to subtract 1 here since our vertices array is 0 based and the indexes of the vertices from the file are 1 based.
    polygon.vertex = vertices_[vertex_pos_id.int_value - 1];

    if (face_segment.normal_id != "" && shading_type_ == ShadingType::SMOOTH) {
      has_normals = true;
      utils::Number vertex_normal_id = utils::string_to_number(face_segment.normal_id, suppress_errors_);

      if (vertex_normal_id.type == utils::NumberType::UNKNOWN) {
        if (!suppress_errors_) std::cerr << "Could not process face on line: " << current_line_ << " due to NumberType::UNKNOWN.\n";
      }

      // We need to subtract 1 here since our vertices array is 0 based and the indexes of the normals from the file are 1 based.
      polygon.normal = normals_[vertex_normal_id.int_value - 1];
    }

    polygon_components.push_back(polygon);
  }

  fan_triangulation(polygon_components, has_normals);
}

void ObjParser::process_single_triangle(const std::vector<FaceSegmentData>& face_segments) {
  utils::Number vertex_1_pos_id = utils::string_to_number(face_segments[0].position_id, suppress_errors_);
  utils::Number vertex_2_pos_id = utils::string_to_number(face_segments[1].position_id, suppress_errors_);
  utils::Number vertex_3_pos_id = utils::string_to_number(face_segments[2].position_id, suppress_errors_);

  if (vertex_1_pos_id.type == utils::NumberType::UNKNOWN ||
      vertex_2_pos_id.type == utils::NumberType::UNKNOWN ||
      vertex_3_pos_id.type == utils::NumberType::UNKNOWN) {
    if (!suppress_errors_) std::cerr << "Could not process face on line: " << current_line_ << " due to NumberType::UNKNOWN.\n";
  }

  // We need to subtract 1 here since our vertices array is 0 based and the indexes of the vertices from the file are 1 based.
  Point p1 = vertices_[vertex_1_pos_id.int_value - 1];
  Point p2 = vertices_[vertex_2_pos_id.int_value - 1];
  Point p3 = vertices_[vertex_3_pos_id.int_value - 1];

  if (face_segments[0].normal_id != "" && face_segments[1].normal_id != "" && face_segments[2].normal_id != "" && shading_type_ == ShadingType::SMOOTH) {
    utils::Number vertex_1_normal_id = utils::string_to_number(face_segments[0].normal_id, suppress_errors_);
    utils::Number vertex_2_normal_id = utils::string_to_number(face_segments[1].normal_id, suppress_errors_);
    utils::Number vertex_3_normal_id = utils::string_to_number(face_segments[2].normal_id, suppress_errors_);

    if (vertex_1_normal_id.type == utils::NumberType::UNKNOWN ||
        vertex_2_normal_id.type == utils::NumberType::UNKNOWN ||
        vertex_3_normal_id.type == utils::NumberType::UNKNOWN) {
      if (!suppress_errors_) std::cerr << "Could not process face on line: " << current_line_ << " due to NumberType::UNKNOWN.\n";
    }

    // We need to subtract 1 here since our vertices array is 0 based and the indexes of the normals from the file are 1 based.
    Vector n1 = normals_[vertex_1_normal_id.int_value - 1];
    Vector n2 = normals_[vertex_2_normal_id.int_value - 1];
    Vector n3 = normals_[vertex_3_normal_id.int_value - 1];

    groups_[selected_group_index_]->AddChild(new SmoothTriangle(p1, p2, p3, n1, n2, n3));
    triangle_count_++;
    return;
  }

  groups_[selected_group_index_]->AddChild(new Triangle(p1, p2, p3));
  triangle_count_++;
}
