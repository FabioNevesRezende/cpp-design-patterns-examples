#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class ConfigFile
{
public:
    virtual vector<string> getSettings() = 0;
    virtual ~ConfigFile() = default;
};

class RealConfigFile : ConfigFile
{
public:
    explicit RealConfigFile(const string& filename)
    {
        cout << "RealConfigFile created." << endl;

        ifstream file(filename);
        string line;
        while(getline(file, line))
        {
            settings.push_back(line);
        }
        cout << settings.size() << " settings loaded." << endl;
    }

    vector<string> getSettings() override
    {
        return settings;
    }

private:
    vector<string> settings;

};

class ConfigFileProxy : public ConfigFile
{
public:
    ConfigFileProxy(const string& filename) : filename(filename), realConfigFile(nullptr)
    {
        cout << "ConfigFileProxy created" << endl;
    }

    // lazy loading, real config file is only created when they are necessary
    vector<string> getSettings() override
    {
        if(realConfigFile == nullptr)
        {
            realConfigFile = make_unique<RealConfigFile>(filename);
        }
        return realConfigFile->getSettings();
    }

private:
    string filename;
    unique_ptr<RealConfigFile> realConfigFile;

};

int main(int argc, char* argv[])
{
    ConfigFileProxy configFile(argv[1]); // insecure loading but just for sake of example and simplicity

    bool useSettings = true;
    if(useSettings)
    {
        vector<string> settings = configFile.getSettings();
        for(const auto& setting  : settings)
        {
            cout <<  setting << endl;
        }
    }
    else 
    {
        cout << "Configuration not used." << endl;
    }

    return 0;
}
