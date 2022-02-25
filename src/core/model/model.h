#pragma once

namespace meov::core {

class Mesh;
class Shader;
class Texture;

namespace {
using MeshPtr = std::shared_ptr<Mesh>;
using ShaderPtr = std::shared_ptr<Shader>;
using TexturePtr = std::shared_ptr<Texture>;
}  // namespace

class Model {
public:
    Model() = default;
    Model(const MeshPtr &Mesh,
          const ShaderPtr &shader,
          const TexturePtr &texture);

    Model &Mesh(const MeshPtr &Mesh);
    Model &shader(const ShaderPtr &shader);
    Model &texture(const TexturePtr &texture);

    const MeshPtr Mesh() const;
    const ShaderPtr shader() const;
    const TexturePtr texture() const;

    void draw();
    // void draw(Renderer &renderer, const RenderContext &rContext) const;

protected:
    void bind() const;

private:
    MeshPtr mMesh;
    ShaderPtr mShader;
    TexturePtr mTexture;
};

}  // namespace meov::core
