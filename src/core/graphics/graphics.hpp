#pragma once

#include <deque>
#include <initializer_list>
#include <utils/types.hpp>

#include <common>
#include "core/shaders/shaders_program/shaders_program.hpp"

namespace meov::core {

namespace resources {
class Texture;
} // namespace resources
class Mesh;
class Model;

class Graphics final {
public:
    class Impl {
        static constexpr glm::vec4 DefaultColor{ 1.0f, 1.0f, 1.0f, 1.0f };
        static constexpr glm::mat4 DefaultTransform{ 1 };

    public:
        Impl();

        virtual void SetViewMatrix(const glm::mat4 &view);
        virtual void SetProjection(const glm::mat4 &projection);

        virtual const glm::mat4 &GetViewMatrix() const;
        virtual const glm::mat4 &GetProjection() const;

        virtual void PushColor(const glm::vec4 &color);
        virtual void PopColor();
        virtual glm::vec4 CurrentColor() const;

        virtual void PushTransform(const glm::mat4 &transform);
        virtual void PopTransform();
        virtual glm::mat4 CurrentTransform() const;
        virtual glm::mat4 ResultingTransform() const;

        virtual void PushProgram(const shaders::Program &program);
        virtual void PopProgram();
        virtual shaders::Program CurrentProgram() const;

        virtual void DrawDot(const glm::vec3 &position, const f32 radius = 1) = 0;
        virtual void DrawLine(std::initializer_list<glm::vec3> &&vertices) = 0;

        virtual void DrawTriangle(const std::array<glm::vec3, 3> &positions) = 0;

        virtual void DrawRectangle(const std::array<glm::vec3, 4> &positions) = 0;

        virtual void DrawTexture(const std::array<glm::vec3, 4> &positions, const sptr<resources::Texture> &tex) = 0;

        virtual void DrawMesh(const Mesh &mesh) = 0;
        virtual void DrawModel(const Model &model) = 0;

    protected:
        std::deque<glm::vec4> mColorQueue;
        std::deque<glm::mat4> mTransformQueue;
        std::deque<shaders::Program> mProgramQueue;
        glm::mat4 mView{ 1.f };
        glm::mat4 mProjection{ 1.f };
        glm::mat4 mResultTransform{ 1.f };
    };

    Graphics();

    void SetViewMatrix(const glm::mat4 &view);
    void SetProjection(const glm::mat4 &projection);

    const glm::mat4 &GetViewMatrix() const;
    const glm::mat4 &GetProjection() const;

    void PushColor(const glm::vec4 &color);
    void PopColor();
    glm::vec4 CurrentColor() const;

    void PushTransform(const glm::mat4 &transform);
    void PopTransform();
    glm::mat4 CurrentTransform() const;
    glm::mat4 ResultingTransform() const;  // All pushed transforms

    void PushProgram(const shaders::Program &program);
    void PopProgram();
    shaders::Program CurrentProgram() const;

    void DrawDot(const glm::vec3 &position, const f32 radius = 1);
    void DrawLine(std::initializer_list<glm::vec3> &&vertices);

    void DrawTriangle(const std::array<glm::vec3, 3> &positions);

    void DrawRectangle(const std::array<glm::vec3, 4> &positions);
    void DrawRectangle(const glm::vec3 &position, const f32 width, const f32 height);

    void DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<resources::Texture> &tex);
    void DrawTexture(const std::shared_ptr<resources::Texture> &tex, const glm::vec3 position, const f32 width, const f32 height);

    void DrawMesh(const Mesh &mesh);
    void DrawModel(const Model &model);

private:
    sptr<Impl> mImpl;
};

}  // namespace meov::core
