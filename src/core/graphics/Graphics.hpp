#pragma once

#include <memory>
#include <queue>
#include <initializer_list>

#include "ShadersProgram.hpp"

namespace meov::core {

class Texture;
class Mesh;

class Graphics final {
public:
    class Graphics::Impl {
        static constexpr glm::u8vec4 DefaultColor{ 0xFF, 0xFF, 0xFF, 0xFF };
        static constexpr glm::mat4 DefaultTransform{ 1 };

    public:
        Impl();

        virtual void PushColor(const glm::u8vec4 &color);
        virtual void PopColor();

        virtual void PushTransform(const glm::mat4 &transform);
        virtual void PopTransform();

        virtual void PushProgram(const shaders::Program &program);
        virtual void PopProgram();

        virtual void DrawDot(const glm::vec3 &position, const float radius = 1) = 0;
        virtual void DrawLine(std::initializer_list<glm::vec3> &&vertices) = 0;

        virtual void DrawTriangle(const std::array<glm::vec3, 3> &positions) = 0;

        virtual void DrawRectangle(const std::array<glm::vec3, 4> &positions) = 0;

        virtual void DrawTexture(const std::array<glm::vec3, 4> &positions, const std::shared_ptr<Texture> &tex) = 0;

        virtual void DrawMesh(const Mesh &mesh) = 0;

    protected:
        std::queue<glm::u8vec4> mColorQueue;
        std::queue<glm::mat4> mTransformQueue;
        std::queue<shaders::Program> mProgramQueue;
    };

    Graphics::Graphics();

    void PushColor(const glm::u8vec4 &color);
    void PopColor();

    void PushTransform(const glm::mat4 &transform);
    void PopTransform();

    void PushProgram(const shaders::Program &program);
    void PopProgram();

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