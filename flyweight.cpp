#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

class Texture
{
public:
    explicit Texture(const string& fileName) : m_FileName(fileName), m_Id(arc4random_uniform(INT_MAX)) {}

    const string description() const
    {
        return "<" + m_FileName + " id" + to_string(m_Id) + ">";
    }

private:
    const string m_FileName;
    const int m_Id;
};

class Sprite
{
public:
    Sprite(Texture* texture) : m_Texture(texture) 
    {
        cout << "Creating sprite with texture file " << texture->description() << endl;
    }

    void setPositionSize(int x, int y, int width, int height)
    {
        m_X = x;
        m_Y = y;
        m_Width = width;
        m_Height = height;
    }

    void render()
    {
        cout << "Rendering sprite with texture: " << m_Texture->description() << endl;
    }

private:
    int m_Width, m_Height, m_X, m_Y;
    Texture* m_Texture;
};

class SpriteFactory
{
public:
    Sprite* makeSprite(const string& fileName)
    {
        auto it = m_SpritePool.find(fileName);

        if(it != m_SpritePool.end())
        {
            return it->second;
        }
        else 
        {
            const auto texture = getTexture(fileName);
            auto [newIt, _] = m_SpritePool.emplace(fileName, new Sprite(texture));
            return newIt->second;
        }
    }

    ~SpriteFactory()
    {
        for(auto &[fileName, sprite] : m_SpritePool)
            delete sprite;

        for(auto &[fileName, texture] : m_TexturePool)
            delete texture;
    }

private:
    std::unordered_map<string, Sprite*> m_SpritePool;
    std::unordered_map<string, Texture*> m_TexturePool;

    Texture* getTexture(const string& fileName)
    {

        auto it = m_TexturePool.find(fileName);

        if(it != m_TexturePool.end())
        {
            return it->second;
        }
        else 
        {
            auto [newIt, _] = m_TexturePool.emplace(fileName, new Texture(fileName));
            return newIt->second;
        }
    }
};

int main(int argc, char* argv[])
{
    vector<Sprite*> sprites;
    const int numSprites = 10;
    const string textureFile = "spaceship.png";

    SpriteFactory factory;

    for(int i = 0; i < numSprites; ++i)
    {
        auto sprite = factory.makeSprite(textureFile);
        sprite->setPositionSize(10,10,10*i,10*i);
        sprites.push_back(sprite);
    }

    for(auto &sprite : sprites)
    {
        sprite->render();
    }

    return 0;
}
