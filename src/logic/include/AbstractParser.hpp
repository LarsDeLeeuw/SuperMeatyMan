#ifndef LOGIC_ABSTRACTPARSER_H
#define LOGIC_ABSTRACTPARSER_H

#include "tinyxml/tinyxml.h"
#include <string>

class AbstractParser {
public:
    AbstractParser();
    virtual ~AbstractParser();

    TiXmlElement* getRoot();

    void loadFile(std::string filename);

private:
    TiXmlElement* fRoot;
    TiXmlDocument fDoc;
};

#endif
