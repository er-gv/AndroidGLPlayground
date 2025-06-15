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


class Model {
    friend class Scene;
public:
    virtual ~Model() {if (material) delete material;};
    explicit Model() : material{nullptr} {}
    explicit Model(Material *material) : material{material} {}
    virtual bool init() = 0;
    virtual void render() const = 0;
    virtual void updateState() = 0;

protected:
    Transform transform;
    glm::vec3 pivot{0};
    Material* material;

    inline void setPivot(glm::vec3 &p){pivot = p;}

};


