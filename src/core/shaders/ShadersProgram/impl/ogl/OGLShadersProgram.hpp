#pragma once

#include <memory>
#include <string>

#include "ShadersProgram.hpp"

namespace meov::core::shaders::gl {


// ============================= OGLProgramImpl ==============================//

class OGLProgramImpl : public Program::Impl {
public:
    explicit OGLProgramImpl(const std::string &name);
    ~OGLProgramImpl();

    bool Attach(const std::shared_ptr<Shader> &shader);
    bool Detach(const std::shared_ptr<Shader> &shader);
    void Clear();

    void Use();
    void UnUse();

    bool IsValid() const;
    uint32_t GetID() const;

    std::shared_ptr<Setter> Get(const std::string_view &name);

private:
    bool mValid{ true };

    bool Link();
};

// ================================ OGLSetter ================================//

class OGLSetter final : public Setter {
public:
    explicit OGLSetter(Program &parent, const std::string_view &name = "");

    Setter *Get(const std::string_view &name) override;

    Setter *Set(float value) override;
    Setter *Set(float v1, float v2) override;
    Setter *Set(float v1, float v2, float v3) override;
    Setter *Set(float v1, float v2, float v3, float v4) override;

    Setter *Set(int value) override;
    Setter *Set(int v1, int v2) override;
    Setter *Set(int v1, int v2, int v3) override;
    Setter *Set(int v1, int v2, int v3, int v4) override;

    Setter *Set(unsigned value) override;
    Setter *Set(unsigned v1, unsigned v2) override;
    Setter *Set(unsigned v1, unsigned v2, unsigned v3) override;
    Setter *Set(unsigned v1, unsigned v2, unsigned v3, unsigned v4) override;

    Setter *Set(bool value) override;
    Setter *Set(bool v1, bool v2) override;
    Setter *Set(bool v1, bool v2, bool v3) override;
    Setter *Set(bool v1, bool v2, bool v3, bool v4) override;

    Setter *Set(const glm::mat4 &matrix) override;

private:
    int mId{ -1 };
};

} // namespace meov::core::shaders::gl
