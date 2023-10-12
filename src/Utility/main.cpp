#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION

#include "Graphics/DLPipeline.h"




int main() {
    DLPipeline app;

    // UPGRADEME add update, render, physics functions
    // actually, this should be wrapped again. Loop should be separate from pipeline, which is separate from main
    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}