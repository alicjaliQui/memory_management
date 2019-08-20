#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Resource
{
    Resource(char* byte) : byte_(byte) {}
    char* byte() const { return byte_; }
    virtual string name() const = 0;
    virtual ~Resource() { delete byte_; }

protected:
    char* byte_ = nullptr;
};

struct ResourceA : Resource
{
    ResourceA(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceA ").append(byte_, 1); }
};

struct ResourceB : Resource
{
    ResourceB(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceB ").append(byte_, 1); }
};

struct ResourceFactory
{ 
    unique_ptr<Resource> makeResourceA(char* byte) { return make_unique<ResourceA>(byte); }
    unique_ptr<Resource> makeResourceB(char* byte) { return make_unique<ResourceB>(byte); }
};

struct ResourceCollection
{
    void add(unique_ptr<Resource> r) { resources.push_back(move(r)); }
    void clear() {
        resources.clear();
    }
    Resource* operator[](int index) { return resources[index].get(); }
    void printAll()
    {
        for (const auto & res : resources)
        {
            cout << res->name() << endl;
        }
    }
    ~ResourceCollection()
    {
        clear();
    }

private:
    vector<unique_ptr<Resource>> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;

    collection.add(rf.makeResourceA(new char{0x63}));
    collection.add(rf.makeResourceB(new char{0x64}));
    collection.printAll();

    auto firstByte = collection[0]->byte();
    cout << *firstByte << endl;
    //collection.clear();

    return 0;
}

