#include <iostream>
#include <memory>

using namespace std;

class ITextHandler
{
public:
    virtual string prepareMessage(const string &text) const = 0;
    virtual ~ITextHandler() = default;
};

class ITextSharer
{
public:
    explicit ITextSharer(const ITextHandler &handler) : m_textHandler(handler){}
    bool shareText(const string& text)
    {
        const string preparedText = m_textHandler.prepareMessage(text);
        return sharePreparedText(preparedText);
    }

    virtual ~ITextSharer() = default;
protected:
    virtual bool sharePreparedText(const string& text) = 0;

private:
    const ITextHandler& m_textHandler;
};

class PlainTextHandler : public ITextHandler
{
public:
    string prepareMessage(const string& text) const override
    {
        cout << "PlainTextHandler::prepareMessage() returning original text..." << endl;
        return text;
    }
};


class EmailShare : public ITextSharer
{
public:
    explicit EmailShare(const PlainTextHandler& handler) : ITextSharer(handler) {}

    bool sharePreparedText(const string& text) override
    {
        cout << "EmailShare::shareText sharing text: " << text << endl;
        return true;
    }
};

class EncryptedTextHandler : public ITextHandler
{
public:
    string prepareMessage(const string& text) const override
    {
        cout << "EncryptedTextHandler::prepareMessage() ecrypting text..." << endl;
        string encrypted = xorEncrypt(text);
        return encrypted;
    }

private:
    string xorEncrypt(const string& input) const
    {
        char key = 64;
        string output = input; 

        for(int i = 0; i < input.size(); ++i)
            output[i] = input[i] ^ key;

        return output;
    }

};


class EmailShareEncrypted : public ITextSharer
{
public:
    explicit EmailShareEncrypted(const EncryptedTextHandler& handler) : ITextSharer(handler) {}

protected:
    bool sharePreparedText(const string& text) override
    {
        cout << "EmailShareEncrypted::shareText() sharing text: " << text << endl;
        return true;
    }
};


int main(int argc, char* argv[])
{
    PlainTextHandler handler = PlainTextHandler();
    EncryptedTextHandler encryptedHandler = EncryptedTextHandler();

    const unique_ptr<ITextSharer> sharingServices[]
    {
        make_unique<EmailShare>(handler),
        make_unique<EmailShareEncrypted>(encryptedHandler)
    };

    const string content = "Beam me up, Scotty!";
    for(const auto& service : sharingServices)
    {
        service->shareText(content);
        cout << endl;
    }

    return 0;
}
