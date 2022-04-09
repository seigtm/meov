#pragma once

#include <unordered_map>
#include <memory>

#include "shader.hpp"

namespace meov::core::shaders {

class Setter;

class Program {
public:
    class Impl {
    public:
        explicit Impl(const std::string &name, uint32_t id = 0);
        virtual ~Impl() = default;

        uint32_t GetID() const;
        const std::string &GetName() const;

        virtual bool Attach(const std::shared_ptr<Shader> &shader) = 0;
        virtual bool Detach(const std::shared_ptr<Shader> &shader) = 0;

        virtual void Use() = 0;
        virtual void UnUse() = 0;

        virtual bool IsValid() const = 0;
        virtual std::shared_ptr<Setter> Get(Program &parent, const std::string_view &name) = 0;

    protected:
        std::string mName;
        uint32_t mId;
        std::unordered_map<ShaderType, std::shared_ptr<Shader>> mShaders;
    };

    void Initialize(const std::string &name);
    void Destroy();

    bool Attach(const std::shared_ptr<Shader> &shader);
    bool Detach(const std::shared_ptr<Shader> &shader);

    void Use();
    void UnUse();

    bool IsValid() const;
    uint32_t GetID() const;
    std::string GetName() const;
    std::shared_ptr<Setter> Get(const std::string_view &name);

private:
    std::shared_ptr<Impl> mImpl;
};

class Setter {
public:
    explicit Setter(Program &parent)
        : mParent{ parent } {}

    virtual Setter *Get(const std::string_view &name) = 0;

    virtual Setter *Set(float value) = 0;
    virtual Setter *Set(float v1, float v2) = 0;
    virtual Setter *Set(float v1, float v2, float v3) = 0;
    virtual Setter *Set(float v1, float v2, float v3, float v4) = 0;

    virtual Setter *Set(int value) = 0;
    virtual Setter *Set(int v1, int v2) = 0;
    virtual Setter *Set(int v1, int v2, int v3) = 0;
    virtual Setter *Set(int v1, int v2, int v3, int v4) = 0;

    virtual Setter *Set(unsigned value) = 0;
    virtual Setter *Set(unsigned v1, unsigned v2) = 0;
    virtual Setter *Set(unsigned v1, unsigned v2, unsigned v3) = 0;
    virtual Setter *Set(unsigned v1, unsigned v2, unsigned v3, unsigned v4) = 0;

    virtual Setter *Set(bool value) = 0;
    virtual Setter *Set(bool v1, bool v2) = 0;
    virtual Setter *Set(bool v1, bool v2, bool v3) = 0;
    virtual Setter *Set(bool v1, bool v2, bool v3, bool v4) = 0;

    virtual Setter *Set(const glm::mat4 &matrix) = 0;

protected:
    Program &mParent;
};

}  // namespace meov::core::shaders