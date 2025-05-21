//
// Created by erez on 15/05/2025.
//

#include "Material.h"
#include "../shadersBuilder.h"
#include "../../logger.h"
#include <stdexcept>


Material::~Material(){
    attribLocations.clear();
    uniformLocations.clear();
}


void Material::addUniform(const std::string& uniformName){
    uniformLocations.insert(std::make_pair(uniformName, glGetUniformLocation(glProgram, uniformName.c_str())));
}

void Material::addAttribute(const std::string& attributeName){
    attribLocations.insert(std::make_pair(attributeName, glGetAttribLocation(glProgram, attributeName.c_str())));
}


Material Material::materialBuilder(const char const* vertexShaderSrc, const char const* fragmentShaderSrc){
    auto program = ShadersBuilder::buildGLProgram(vertexShaderSrc, fragmentShaderSrc);
    if (!program) {
        log_error("Material", "Could not create program.");
        throw std::runtime_error();
    }
    Material mat{glProgram};

}
