/*
TODO: (16.3.22)
1. Material class. +
2. Texture ctor.
3. Node class.
4. Properties.
*/


#define SDL_MAIN_HANDLED

#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"
#include "TimeUtils.hpp"

#include "windows/Git.hpp"
#include "windows/Log.hpp"

#include "OGLFrameBuffer.hpp"
#include "ShadersProgram.hpp"
#include "mesh.h"
#include "vertex.h"
#include "texture.h"
#include "Graphics.hpp"

#include "Core.hpp"

#include <assimp/Importer.hpp>   // C++ importer interface.
#include <assimp/scene.h>        // Output data structure.
#include <assimp/postprocess.h>  // Post processing flags.

std::shared_ptr<meov::core::Mesh> DoTheImportThing(const std::string& pFile) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile(pFile, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    // If the import failed, report it
    if(!scene) {
        LOGE << importer.GetErrorString();
        return nullptr;
    }

    // Now we can access the file's contents.
    // scene->GetEmbeddedTexture("Box0.bin");
    if(!scene->mNumMeshes) {
        return nullptr;
    }

    auto& mesh{ scene->mMeshes[0] };

    std::vector<meov::core::Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    glm::u8vec4 white{ 0xff, 0xff, 0xff, 0xff };
    for(int i{}; i < mesh->mNumVertices; ++i) {
        glm::vec3 position{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        glm::u8vec4 color;
        if(mesh->mColors[0] == nullptr) {
            color = white;
        } else {
            color = { mesh->mColors[0]->r * 255, mesh->mColors[0]->g * 255, mesh->mColors[0]->b * 255, mesh->mColors[0]->a * 255 };
        }
        // glm::vec2 texturePosition{ mesh->mTextureCoords[i]->x, mesh->mTextureCoords[i]->y };
        glm::vec2 texturePosition{ 0, 0 };

        vertices.emplace_back(std::move(position), std::move(color), std::move(texturePosition));
    }

    std::vector<unsigned> indices;
    indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
    for(int i{}; i < mesh->mNumFaces; ++i) {
        indices.insert(
            indices.end(),
            mesh->mFaces[i].mIndices,
            mesh->mFaces[i].mIndices + mesh->mFaces[i].mNumIndices);
    }

    // std::vector<std::shared_ptr<meov::core::Texture>> textures;
    return std::make_shared<meov::core::Mesh>(std::move(vertices), std::move(indices), std::vector<std::shared_ptr<meov::core::Texture>>{});
}

int main() {
    stbi_set_flip_vertically_on_load(true);
    meov::utils::LogUtils::Instance()->Initialize();

    LOGI << "Current directory: " << fs::current_path().string();
    meov::core::Core core{ std::vector<std::string>{} };

    std::shared_ptr graphics{ std::make_shared<meov::core::Graphics>() };

    // Our state.
    const ImVec4 clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };

    // Dear ImGui windows.
    meov::Window::Git gitW;
    meov::Window::Log::Reference logW1{ new meov::Window::Log{ "First", { 1280, 850 } } };  // FIXME: ambiguous '::Ref' from Subscriber.

    auto logStorage{ meov::utils::LogUtils::Instance()->GetLogStorage() };
    if(logStorage != nullptr) {
        logStorage->Subscribe(logW1);
    }

    // clang-format off

    auto vertShader{ std::make_shared<meov::core::shaders::Shader>() };
    vertShader->Initialize(meov::core::shaders::ShaderType::Vertex);

    auto fragShader{ std::make_shared<meov::core::shaders::Shader>() };
    fragShader->Initialize(meov::core::shaders::ShaderType::Fragment);

    meov::core::shaders::Program program;
    program.Initialize("Default shaders program");
    program.Attach(vertShader);
    program.Attach(fragShader);

    graphics->PushProgram(program);

    const glm::u8vec4 white{ 0xFF, 0xFF, 0xFF, 0xFF };
    const glm::u8vec4 black{ 0x00, 0x00, 0x00, 0xFF };
    const glm::u8vec4 red{ 0xFF, 0x00, 0x00, 0xFF };
    const glm::u8vec4 green{ 0x00, 0xFF, 0x00, 0xFF };
    const glm::u8vec4 blue{ 0x00, 0x00, 0xFF, 0xFF };

    auto mesh = DoTheImportThing("models/box/Box.gltf");

    // clang-format on
    meov::core::gl::FrameBuffer buffer;
    buffer.Initialize();

    meov::core::gl::FrameBuffer testBuffer;
    testBuffer.Initialize();
    glm::mat4 projection{ 1 };
    glm::mat4 view{ 1.f };
    glm::mat4 model{ 1.f };

    constexpr float step{ 0.05f };
    view = glm::translate(view, glm::vec3{ 0.0f, 0.0f, -2.0f });

    // Main loop.
    LOGI << "Start main loop";
    bool done = false;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

    auto bestOfTheBestTex{ meov::core::Texture::Make("textures/best-of-the-best.png", meov::core::Texture::Type::Diffuse) };
    auto wallTex{ meov::core::Texture::Make("textures/wall.jpg", meov::core::Texture::Type::Diffuse) };

    meov::utilities::time::Clock clock;
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!done) {
        clock.Update();
        model = glm::rotate<float>(model, clock.Delta(), glm::vec3{ 1.0f, 1.0f, 0.0f });
        program.Use();
        program.Get("projection")->Set(projection);
        program.Get("view")->Set(view);
        program.Get("model")->Set(model);
        program.UnUse();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(core.mWindow);
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        buffer.Bind();
        graphics->DrawMesh(*mesh);
        buffer.UnBind();

        testBuffer.Bind();
        graphics->PushColor(glm::u8vec4{ 0xFF, 0x00, 0x00, 0xFF });
        graphics->DrawTexture(bestOfTheBestTex, { -0.5f, -0.5f, 0.5f }, 1.0f, 1.0f);
        graphics->DrawTexture(wallTex, { -0.5f, -0.5f, -0.5f }, 1.0f, 1.0f);
        graphics->PopColor();
        testBuffer.UnBind();

        ImGui::Begin("Scene");
        const auto [width, height]{ ImGui::GetContentRegionAvail() };
        projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
        // Add rendered texture to ImGUI scene window.
        uint32_t textureID = buffer.GetFrameTexture();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ width, height }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();

        ImGui::Begin("Test Scene");
        const auto [twidth, theight]{ ImGui::GetContentRegionAvail() };
        // Add rendered texture to ImGUI scene window.
        textureID = testBuffer.GetFrameTexture();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ twidth, theight }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();


        // Show singleton log window.
        logW1->Draw();
        // Show Git info window.
        gitW.Draw();

        // Rendering.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(core.mWindow);

        // Poll and handle events (inputs, window resize, etc.).
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch(event.type) {
                case SDL_KEYDOWN: {
                    auto& keysym = event.key.keysym;
                    LOGD << "Key pressed: " << SDL_GetKeyName(keysym.sym);
                    glm::vec3 velocity{};
                    switch(keysym.sym) {
                        case SDLK_s: velocity.z -= step; break;
                        case SDLK_w: velocity.z += step; break;
                        case SDLK_a: velocity.x += step; break;
                        case SDLK_d: velocity.x -= step; break;
                    }
                    if(velocity != glm::vec3{}) {
                        view = glm::translate(view, velocity);
                    }
                } break;
                case SDL_WINDOWEVENT:
                    if(event.window.windowID != SDL_GetWindowID(core.mWindow)) {
                        break;
                    }
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        glViewport(0, 0, event.window.data1, event.window.data2);
                        break;
                    } else if(event.window.event != SDL_WINDOWEVENT_CLOSE) {
                        break;
                    }
                case SDL_QUIT:
                    done = true;
                default:
                    break;
            }
        }
    }

    buffer.Destroy();
    vertShader->Destroy();
    fragShader->Destroy();
    program.Destroy();

    return 0;
}
