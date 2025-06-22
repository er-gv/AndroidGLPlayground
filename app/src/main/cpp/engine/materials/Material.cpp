//
// Created by erez on 15/05/2025.
//

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "Material.h"
#include "../shadersBuilder.h"
#include "../../logger.h"
#include <stdexcept>

#define LOG_TAG "MATTERIAL"



Material::~Material(){
    attribLocations.clear();
    uniformLocations.clear();
    textures.clear();
}

bool Material::addUniforms(const std::vector<const std::string>& uniforms){
    for(auto& uniform: uniforms){
        if (!addUniform(uniform))
            return false;
    }
    return true;
}

bool Material::addUniform(const std::string& uniformName){
    GLint loc = glGetUniformLocation(glProgram, uniformName.c_str());
    auto gotErrors = checkGlError("glGetUniformLocation", LOG_TAG);
    if((-1 == loc) || gotErrors){
        log_error("cant find uniform %s in shader.", uniformName.c_str());
        return false;
    }
    uniformLocations[uniformName] =loc;
    return true;
}


bool Material::addAttributes(const std::vector<std::tuple<const std::string&, GLsizei, GLsizei>>& attribs){
    return all_of(attribs.begin(), attribs.end(),
                  [this](auto& attrib){
                        return addAttribute(attrib);
    });
}

bool Material::addAttribute(const std::tuple<const std::string&, GLsizei, GLsizei>& attrib){
    auto name = std::get<0>(attrib);
    GLuint loc = glGetAttribLocation(glProgram, name.c_str());
    auto gotErrors = checkGlError("glGetAttribLocation", LOG_TAG);
    if(gotErrors){
        log_error("cant find attribute %s in shader.", name.c_str());
        return false;
    }
    VertexAttribute va{loc, std::get<1>(attrib), std::get<2>(attrib)};
    attribLocations[name] = va;
    return true;
}


void Material::generateTextures(const std::vector<const char*>& vec){

    for(const auto& texture_name: vec){
        auto textureID = loadTextureFromAsset(texture_name);
        addTexture(textureID);
    }
}

void Material::addTexture(GLuint textureUnit){
    textures.push_back(textureUnit);
}

GLuint Material::getTexture(GLuint idx) const{
    if (idx < textures.size())
        return textures[idx];
    else{
        log_error(LOG_TAG, "No texture at index %d", idx);
        throw std::runtime_error("Invalid index error  at Material::getTexturemsg");
    }
}



GLint Material::getUniformLocation(const std::string& uniformName) const{
    auto it = uniformLocations.find(uniformName);
    if(it == uniformLocations.end()){
        std::string msg {"No uniform "};
        msg.append(uniformName);
        throw std::runtime_error(msg);
    }
    return it->second;
}


bool Material::setProperty(const std::string& property, float value) const{
    auto result = true;
    auto handler{getUniformLocation(property)};
    if(handler >= 0)
        glUniform1f(handler, value);
    else result=false;

    return result;
}

bool Material::setProperty(const std::string& property, const glm::vec2& value) const{
    auto result = true;
    auto handler{getUniformLocation(property)};
    if(handler >= 0)
        glUniform2f(handler, value.x, value.y);
    else result=false;
    return result;
}

bool Material::setProperty(const std::string& property, const glm::vec3& value) const{
    auto result = true;
    auto handler{getUniformLocation(property)};
    if(handler >= 0)
        glUniform3f(handler, value.x, value.y, value.z);
    else result=false;
    return result;
}

void Material::populateAttribBuffers() const{
    auto stride{getVertexStride()};

    for(auto& attrib :attribLocations){
        //attrib.first is attrib name, second is pair <location, number of elements>
        auto attribLocation = attrib.second.position;
        auto attribSize = attrib.second.size;
        auto offset = attrib.second.offset;
        glVertexAttribPointer(attribLocation, attribSize, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof (float)));
        checkGlError("glVertexAttribPointer", LOG_TAG);
        glEnableVertexAttribArray(attribLocation);
        checkGlError("glEnableVertexAttribArray", LOG_TAG);

    }
}

GLuint Material::getAttribLocation(const std::string& attribName) const{
    auto it = attribLocations.find(attribName);
    if(it == attribLocations.end()){
        std::string msg {"No attribute "};
        msg.append(attribName);
        throw std::runtime_error(msg);
    }
    auto attribLocation = it->second.position;
    return attribLocation;
}

GLsizei Material::getAttribSize(const std::string& attribName) const{
    auto it = attribLocations.find(attribName);
    if(it == attribLocations.end()){
        std::string msg {"No attribute "};
        msg.append(attribName);
        throw std::runtime_error(msg);
    }
    auto attribSize = it->second.size;
    return attribSize;
}

GLsizei Material::getVertexStride() const{
    int offset = 0;
    for(const auto& attrib : attribLocations)
        offset += attrib.second.size;
    return offset*sizeof(float);
}


Material* Material::materialBuilder(const char* vertexShaderSrc, const char* fragmentShaderSrc){
    auto glProgram = ShadersBuilder::buildGLProgram(vertexShaderSrc, fragmentShaderSrc);
    if (!glProgram) {
        log_error("Material", "Could not create program.");
        throw std::runtime_error("Division by zero error");
    }
    return new Material(glProgram);
}

void Material::enable() const {
    glUseProgram(this->glProgram);
    checkGlError("glUseProgram", LOG_TAG);
}

void Material::disable() const{


    for(auto& attrib :attribLocations){
        //attrib.first is attrib name, second is pair <location, number of elements>
        glDisableVertexAttribArray(attrib.second.position);
    }

    for(auto& texture : textures){
        glActiveTexture(texture);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glUseProgram(0);
}

void Material::logUniforms() const{
    GLint n_uniforms;
    GLsizei bufSize = 16;
    GLsizei length;
    GLenum type;
    GLchar name[16];
    GLint size;
    glGetProgramiv(glProgram, GL_ACTIVE_UNIFORMS, &n_uniforms);
    log_info("MATERIAL", "Active uniforms: %d", n_uniforms);
    for (auto i = 0; i < n_uniforms; i++)
    {
        glGetActiveUniform(glProgram, (GLuint)i, bufSize, &length, &size, &type, name);
        char* buffer = new char[length+1];
        strncpy(buffer, name, length);
        buffer[length] = '\0';
        log_info("MATERIAL", "Uniform #%d Type: %u Name: %s\n", i, (unsigned)type, buffer);
        delete[] buffer;
    }
}

