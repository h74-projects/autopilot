
#include "pugixml.hpp"

void fill_map(std::string const& a_filename, concurrency::BlockingMap<std::string, std::tuple<std::string, std::string, Var>>& a_variables)
{
    pugi::xml_document doc;
    if (!doc.load_file(a_filename.c_str())) {
        throw std::runtime_error("failed to load");
    }

    for (pugi::xml_node chunk_node : doc.select_nodes("/root/chunk")) {
        std::string name = chunk_node.child_value("name");
        std::string type = chunk_node.child_value("type");
        std::string format = chunk_node.child_value("format");
        std::string node = chunk_node.child_value("node");

        if (!name.empty() && !type.empty() && !format.empty() && !node.empty()) {
            variables[name] = std::make_tuple(node, type, Var(format));
        }
    }
}