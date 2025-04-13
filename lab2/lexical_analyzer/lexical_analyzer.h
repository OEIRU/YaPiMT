#pragma once


#include "../tcontroller/tcontroller.h"
#include "conveyer.h"

using namespace std;

class LEXICAL_ANALYZER {
public:
    LEXICAL_ANALYZER(
        STATIC_TCONTROLLER& tstatic,
        DYNAMIC_TCONTROLLER& tvariables,
        DYNAMIC_TCONTROLLER& tconstants
    ) : tstatic(tstatic), tvariables(tvariables), tconstants(tconstants){};

    string build_from_source(const string& source) {
        CONVEYER conveyer(source, tstatic, tvariables, tconstants);
        return conveyer.build();
    }

    string build_from_file(const string& filename) {
        std::ifstream file(filename, std::ios::binary);

        std::ostringstream buffer;
        buffer << file.rdbuf();

        return build_from_source(buffer.str());
    }
private:
    STATIC_TCONTROLLER& tstatic;
    DYNAMIC_TCONTROLLER& tvariables;
    DYNAMIC_TCONTROLLER& tconstants;
};