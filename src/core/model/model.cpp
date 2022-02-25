#include "Common.hpp"

#include "model.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
// #include "renderer.h"
// #include "render_context.h"

namespace meov::core {

Model::Model(const MeshPtr &mesh, const ShaderPtr &shader, const TexturePtr &texture)
    : mMesh{ mesh }, mShader{ shader }, mTexture{ texture } {
    if(nullptr == mShader) {
        return;
    }
    if(nullptr == mTexture || !mTexture->valid()) {
        return;
    }
    mShader->get("useTexture").set(true);
    mShader->get("defTexture").set(0);
}

Model& Model::Mesh(const MeshPtr &Mesh) {
    mMesh = Mesh;
    return *this;
}

Model& Model::shader(const ShaderPtr &shader) {
    mShader = shader;
    return *this;
}

Model& Model::texture(const TexturePtr &texture) {
    mTexture = texture;
    return *this;
}

const MeshPtr Model::Mesh() const {
    return mMesh;
}

const ShaderPtr Model::shader() const {
    return mShader;
}

const TexturePtr Model::texture() const {
    return mTexture;
}

void Model::draw() {
    bind();
    if(!mMesh->hasIndices()) {
        glDrawArrays(GL_TRIANGLES, 0, mMesh->vertices());
    } else {
        glDrawElements(GL_TRIANGLES, mMesh->indices(), GL_UNSIGNED_INT, nullptr);
    }
}

void Model::bind() const {
    if(mShader) mShader->use();
    if(mMesh) mMesh->bind();
    if(mTexture) mTexture->bind();
}

} // namespace meov::core