#include "include/AbstractParser.hpp"
#include "include/tinyxml/tinyxml.h"
#include <iostream>

AbstractParser::AbstractParser() = default;
AbstractParser::~AbstractParser() = default;

TiXmlElement* AbstractParser::getRoot() { return fRoot; }

void AbstractParser::loadFile(std::string filename) {
    fDoc.LoadFile(filename.c_str());
    if (fDoc.Error()) {
        fRoot = nullptr;
        throw std::runtime_error("Error opening level inputfile");
    } else {
        fRoot = fDoc.FirstChildElement();
    }
}
