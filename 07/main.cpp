#include <assert.h>
#include "format.hpp"
using std::cout;
using std::endl;


int main(int argc, char const *argv[])
{

    try{
        auto text = format("{1}+{1} = {0}", 2, "one");
        assert(text == "one+one = 2");
    }
    catch(const std::runtime_error& error){
        cout << "Catched runtime_error: " << error.what() << endl; 
    }
   
    return 0;
}