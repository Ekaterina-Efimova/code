#include "parse.h"

std::vector<size_t> s21::parse_file(const std::string& filename) {
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig config;
  config.triangulate = false;
  if (!reader.ParseFromFile(filename, config)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  auto& attrib = reader.GetAttrib();
  auto& shapes = reader.GetShapes();

  s21::Figure* fig = s21::get_figure();
  fig->points_file = attrib.vertices;
  fig->find_min_max_vertices();
  fig->convert_shapes_to_edges(shapes);
  fig->points = std::vector<float>(fig->points_file);
  fig->edges = std::vector<unsigned int>(fig->edges_file);

  return {fig->points.size() / 3, fig->edges.size() / 2};
}