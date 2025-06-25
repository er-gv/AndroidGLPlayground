//
// Created by erez on 22/04/2025.
//

#pragma once

#include <thread>
#include <chrono>
#include "../engine/materials/Material.h"
#include "../engine/Transform.h"
#include "../engine/libs/glm/glm.hpp"
#include "../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../engine/libs/glm/gtc/type_ptr.hpp"
//#include "../scenes/Scene.h"

class Scene;

class Model {

public:
    virtual ~Model() { delete p_material;};
    explicit Model(const Scene& scene, Material *material) :  parentScene{scene}, p_material{material} {}
    virtual bool init() = 0;
    virtual void render() const = 0;
    virtual void updateState() = 0;
    Transform& transform() {return m_transform;}
    const Material* material() const {return p_material;}
    void setPerFrameTransform(const Transform& t){perFrameTransform = t;};

protected:
    const Scene& parentScene;
    Transform m_transform;
    Transform perFrameTransform{glm::mat4(1.0f)};
    glm::vec3 pivot{0};
    Material* p_material;


    inline void setPivot(glm::vec3 &p){pivot = p;}

};


