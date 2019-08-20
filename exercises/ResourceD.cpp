#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

class Resource
{ 
public:
    void use(const char* N)
    {
        cout << "Using resource. Passed " << *N << endl;
        if (*N == 'd')
        {
            throw logic_error("Passed d. d is prohibited.");
        }
    };

};

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }
    const char* N = argv[1];
    // 1)
    //Resource* rsc = nullptr;
    // 3)
    std::unique_ptr<Resource> rsc;
    try
    {
        // 2)
        //std::unique_ptr<Resource> rsc = make_unique<Resource>();
        // 3)
        rsc.reset(new Resource());

        rsc->use(N);
    }
    catch (logic_error & e)
    {
        cout << e.what() << endl;
        // 1)
        //delete rsc;
    }

    return 0;
}

