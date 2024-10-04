#include "setting_info.h"

using namespace s21;

SettingInfo::SettingInfo() {
  std::ifstream f(SAVE_SETTINHGS);

  if (f.is_open()) {
    std::string line;

    std::getline(f, line);
    projection_type = std::stoi(line);

    std::getline(f, line);
    edges_type = std::stoi(line);

    std::getline(f, line);
    edge_color = std::make_unique<std::string>(line);

    std::getline(f, line);
    edge_thickness = std::stoi(line);

    std::getline(f, line);
    background_color = std::make_unique<std::string>(line);

    std::getline(f, line);
    vertex_type = std::stoi(line);

    std::getline(f, line);
    vertex_color = std::make_unique<std::string>(line);

    std::getline(f, line);
    vertex_size = std::stoi(line);

    f.close();

  } else {
    projection_type = 1;
    edges_type = 0;
    edge_color = std::make_unique<std::string>("#ffffff");
    edge_thickness = 1;
    background_color = NULL;
    vertex_type = 0;
    vertex_color = std::make_unique<std::string>("#ffffff");
    vertex_size = 5;
  }
}

void SettingInfo::save_settings() {
  std::ofstream f(SAVE_SETTINHGS);

  if (f.is_open()) {
    f << projection_type << "\n"
      << edges_type << "\n"
      << (edge_color ? *edge_color : "") << "\n"
      << edge_thickness << "\n"
      << (background_color ? *background_color : "") << "\n"
      << vertex_type << "\n"
      << (vertex_color ? *vertex_color : "") << "\n"
      << vertex_size;
    f.close();
  }
}
