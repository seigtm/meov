#pragma once

#include <memory>
#include <deque>
#include <initializer_list>

#include "common.hpp"
#include "shaders_program.hpp"

namespace meov::core {

class Texture;
class Mesh;

class Graphics final {
public:
    class Impl {
        static constexpr glm::u8vec4 DefaultColor{ 0xFF, 0xFF, 0xFF, 0xFF };
        static constexpr glm::mat4 DefaultTransform{ 1 };

    public:
        Impl();

        virtual void PushColor(const glm::u8vec4 &color);
        virtual void PopColor();
        virtual glm::u8vec4 CurrentColor() const;

        virtual void PushTransform(const glm::mat4 &transform);
        virtual void PopTransform();
        virtual glm::mat4 CurrentTransform() const;
        virtual glm::mat4 ResultingTransform() const;

        virtual void PushProgram(const shaders::Program &program);
        virtual void PopProgram();
        virtual shaders::Program CurrentProgram() const;

        virtual void DrawDot(const glm::vec3 &position, const float radius = 1) = 0;
        virtual void DrawLine(std::initializer_list<glm::vec3> &&vertices) = 0;

        virtual void DrawTriangle(const std::array<glm::vec3, 3> &positions) = 0;

        virtual void DrawRectangle(const std::array<glm::vec3, 4> &positions) = 0;

        virtual void DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex) = 0;

        virtual void DrawMesh(const Mesh &mesh) = 0;

    protected:
        std::deque<glm::u8vec4> mColorQueue;
        std::deque<glm::mat4> mTransformQueue;
        std::deque<shaders::Program> mProgramQueue;
        glm::mat4 mResultTransform{ 1.f };
    };

    Graphics();

    void PushColor(const glm::u8vec4 &color);
    void PopColor();
    glm::u8vec4 CurrentColor() const;

    void PushTransform(const glm::mat4 &transform);
    void PopTransform();
    glm::mat4 CurrentTransform() const;
    glm::mat4 ResultingTransform() const;  // All pushed transforms

    void PushProgram(const shaders::Program &program);
    void PopProgram();
    shaders::Program CurrentProgram() const;

    void DrawDot(const glm::vec3 &position, const float radius = 1);
    void DrawLine(std::initializer_list<glm::vec3> &&vertices);

    void DrawTriangle(const std::array<glm::vec3, 3> &positions);

    void DrawRectangle(const std::array<glm::vec3, 4> &positions);
    void DrawRectangle(const glm::vec3 &position, const float width, const float height);

    void DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex);
    void DrawTexture(const std::shared_ptr<Texture> &tex, const glm::vec3 position, const float width, const float height);

    void DrawMesh(const Mesh &mesh);

private:
    std::shared_ptr<Impl> mImpl;
};

}  // namespace meov::core
