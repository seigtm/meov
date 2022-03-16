#include "settings.hpp"

namespace meov::utilities {

Settings& Settings::Instance() {
    static Settings settings;
    return settings;
}

void Settings::WriteDefaults() {
    // Opening output file stream.
    std::ofstream ofs{ mFilePath };
    // If somehow file can't be opened.
    if(!ofs.is_open()) {
        LOGE << "Can't open settings file to save default configuration (" << mFilePath.c_str() << ")!";
        return;
    }
    // Writing default configuration of settings file.
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    writer.StartObject();
    {
        writer.String("Window");
        writer.StartObject();
        {
            writer.String("Width");
            writer.Int(1920);
            writer.String("Height");
            writer.Int(1080);
            writer.String("Transparency");
            writer.Int(100);
        }
        writer.EndObject();

        writer.String("Presets");
        writer.StartObject();
        {
            writer.String("First");
            writer.Int(1);
            writer.String("Second");
            writer.Int(2);
            writer.String("Third");
            writer.Int(3);
        }
        writer.EndObject();
    }
    writer.EndObject();
}

// TODO: Change in later to something more relatable.
bool Settings::AreCorrect() {
    bool hasAllMembers{
        mDocument["Window"].HasMember("Width") &&
        mDocument["Window"].HasMember("Height") &&
        mDocument["Window"].HasMember("Transparency") &&
        mDocument["Presets"].HasMember("First") &&
        mDocument["Presets"].HasMember("Second") &&
        mDocument["Presets"].HasMember("Third")
    };

    bool hasCorrectTypes{ false };
    if(hasAllMembers) {
        hasCorrectTypes = {
            mDocument["Window"]["Width"].IsInt() &&
            mDocument["Window"]["Height"].IsInt() &&
            mDocument["Window"]["Transparency"].IsInt() &&
            mDocument["Presets"]["First"].IsInt() &&
            mDocument["Presets"]["Second"].IsInt() &&
            mDocument["Presets"]["Third"].IsInt()
        };
    }

    return hasAllMembers && hasCorrectTypes;
}

Settings::Settings()
    : mFilePath{ fs::current_path() / "settings" / "settings.json" } {
    // If settings file not exists.
    if(!fs::exists(mFilePath)) {
        // If even the settings directory doesn't exist.
        if(!fs::exists(mFilePath.parent_path())) {
            LOGI << "Note! Couldn't find settings directory, so creating it.";
            fs::create_directory("settings");
        }
        LOGI << "Note! Settings file doesn't exist, so creating a new one with default config.";
        // Create it and write default settings.
        WriteDefaults();
    }
    // Opening input file stream.
    std::ifstream ifs{ mFilePath };
    // If somehow file can't be opened.
    if(!ifs.is_open()) {
        LOGE << "Can't open settings file to load configuration (" << mFilePath.c_str() << ")!";
        return;
    }

    rapidjson::IStreamWrapper isw{ ifs };
    // Parse JSON settings to mDocument object.
    mDocument.ParseStream(isw);
    // If there were any parse errors.
    if(mDocument.HasParseError()) {
        LOGE << "Failed to parse JSON. Error: " << GetParseError_En(mDocument.GetParseError());
        // If somehow document is empty.
        if(mDocument.GetParseError() == rapidjson::kParseErrorDocumentEmpty) {
            LOGI << "Recreating JSON settings file with default configuration (" << mFilePath.c_str() << ")";
            WriteDefaults();
        }
        return;
    }
    // If settings have invalid members or types in it.
    if(!AreCorrect()) {
        LOGE << "Invalid JSON structure of settings file (" << mFilePath.c_str() << ")";
        LOGI << "Recreating JSON settings file with default configuration (" << mFilePath.c_str() << ")";
        WriteDefaults();
    }
}

void Settings::Save() {
    // Opening output file stream.
    std::ofstream ofs{ mFilePath };
    // If somehow file can't be opened.
    if(!ofs.is_open()) {
        LOGE << "Can't open settings file to save configuration (" << mFilePath.c_str() << ")!";
        return;
    }
    // Writing default configuration of settings file.
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    mDocument.Accept(writer);

    LOGI << "Saved settings configuration to JSON file (" << mFilePath.c_str() << ")";
}

rapidjson::Value& Settings::operator[](std::string const& key) {
    return mDocument[key.c_str()];
}

}  // namespace meov::utilities
