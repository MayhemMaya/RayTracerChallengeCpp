#pragma once


#include <string>
#include <fstream>
#include <vector>
#include <array>
#include "group.h"
#include "utils.h"
#include "point.h"
#include "triangle.h"
#include "smooth-triangle.h"

struct FaceSegmentData {
  std::string position_id;
  std::string texture_coord;
  std::string normal_id;
};

struct PolygonComponent {
  Point vertex;
  Vector normal;
};

enum class ShadingType {
  FLAT,
  SMOOTH
};

class ObjParser {
public:
  ObjParser(const std::string& file, const ShadingType& shading_type = ShadingType::FLAT, bool suppress_errors = false);
  ~ObjParser();
  std::vector<Point> GetVertices() const;
  std::vector<Vector> GetNormals() const;
  Group* GetDefaultGroup() const;
  Group* GetGroupByName(const std::string& name) const;
  int GetLinesIgnored() const;
  void ConvertToSceneGroup(Group* scene_group) const;
  int GetTriangleCount() const;
  int GetGroupCount() const;
  int GetFaceCount() const;
  std::vector<Group*> GetGroups() const;
private:
  int lines_ignored_;
  int current_line_;
  int triangle_count_;
  int face_count_;
  bool suppress_errors_;
  std::vector<Point> vertices_;
  std::vector<Vector> normals_;
  std::vector<Group*> groups_;
  int selected_group_index_;
  std::string file_name_;
  ShadingType shading_type_;
  void process_line(const std::string& line);
  void process_vertex(const std::string& line);
  void process_vertex_normal(const std::string& line);
  void process_group(const std::string& line);
  void process_face(const std::string& line);
  void fan_triangulation(const std::vector<PolygonComponent>& components, bool has_normals);
  std::vector<FaceSegmentData> process_face_segments(const std::vector<std::string>& segments);
  void process_polygon(const std::vector<FaceSegmentData>& face_segments);
  void process_single_triangle(const std::vector<FaceSegmentData>& face_segments);
};