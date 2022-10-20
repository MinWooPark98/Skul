#include "ResourceMgr.h"

string ResourceMgr::FilePath = "Resources.csv";

ResourceMgr::ResourceMgr()
{
    LoadAll();
}

ResourceMgr::~ResourceMgr()
{
    ReleaseAll();
}

void ResourceMgr::ReleaseAll()
{
    for (auto& it : texMap)
    {
        delete it.second;
    }
    texMap.clear();
    for (auto& it : fontMap)
    {
        delete it.second;
    }
    fontMap.clear();
    for (auto& it : soundMap)
    {
        delete it.second;
    }
    soundMap.clear();
}

bool ResourceMgr::LoadAll()
{
    ReleaseAll();

    rapidcsv::Document doc(FilePath, rapidcsv::LabelParams(0, -1));

    auto ids = doc.GetColumn<string>(0);
    auto types = doc.GetColumn<int>(1);

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        if (!Load((ResourceTypes)types[i], ids[i]))
            return false;
    }
    return true;
}

bool ResourceMgr::Load(ResourceTypes type, string id)
{
    switch (type)
    {
    case ResourceTypes::Texture:
        return LoadTexture(id);
    case ResourceTypes::Font:
        return LoadFont(id);
    case ResourceTypes::SoundBuffer:
        return LoadSoundBuffer(id);
    default:
        return false;
    }
}

bool ResourceMgr::LoadTexture(string id)
{
    if (texMap.find(id) != texMap.end())
    {
        return false;
    }

    auto texture = new Texture();
    if (!texture->loadFromFile(id))
    {
        delete texture;
        return false;
    }
    texMap.insert({ id, texture });
    return true;
}

bool ResourceMgr::LoadFont(string id)
{
    if (fontMap.find(id) != fontMap.end())
    {
        return false;
    }

    auto font = new Font();
    if (!font->loadFromFile(id))
    {
        delete font;
        return false;
    }
    fontMap.insert({ id, font });
    return true;
}

bool ResourceMgr::LoadSoundBuffer(string id)
{
    if (soundMap.find(id) != soundMap.end())
    {
        return false;
    }

    auto buffer = new SoundBuffer();
    if (!buffer->loadFromFile(id))
    {
        delete buffer;
        return false;
    }
    soundMap.insert({ id, buffer });
    return true;
}

Texture* ResourceMgr::GetTexture(string id) const
{
    auto it = texMap.find(id);
    if (it == texMap.end())
        return nullptr;
    return it->second;
}

Font* ResourceMgr::GetFont(string id) const
{
    auto it = fontMap.find(id);
    if (it == fontMap.end())
        return nullptr;
    return it->second;
}

SoundBuffer* ResourceMgr::GetSoundBuffer(string id) const
{
    auto it = soundMap.find(id);
    if (it == soundMap.end())
        return nullptr;
    return it->second;
}
