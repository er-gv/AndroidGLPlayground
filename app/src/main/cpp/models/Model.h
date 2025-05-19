//
// Created by erez on 22/04/2025.
//

#ifndef QUANTIZED_SHAPES_MODEL_H
#define QUANTIZED_SHAPES_MODEL_H


class Model {
public:
    virtual ~Model() = default;
    Model()=default;
    virtual bool init() = 0;
    virtual void render() const = 0;
    virtual void updateState() = 0;
};


#endif //QUANTIZED_SHAPES_MODEL_H
