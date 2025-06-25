//
// Created by erez on 25/06/2025.
//

#pragma once


class Icosahedron : public Model{
private:

    GLuint VBO{0};
    GLuint EBO{0};
    bool initVBO();


public:
    Icosahedron(const Scene&, Material* material);
    ~Icosahedron() override;
    bool init() override;
    void updateState() override;
    void render() const override;

};
