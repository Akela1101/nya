# NYA Library
*It is C++ header only library containing some useful aliases.*
```c++
#define umap std::unordered_map
#define uset std::unordered_set

#define u_p std::unique_ptr
#define s_p std::shared_ptr

#define all_(x) (x).begin(), (x).end()

typedef unsigned int uint;
typedef long long llong;

// and some more ...
```
See [nya.hpp](src/nya.hpp) for details.

The library is free to use — either fork or just copy the file.

## Additional C++ fun
*switch for string (and other types)*
```c++
#include "nya/switch.hpp"
#include <string>
#include <unordered_map>

caseS( "one" )
{
	std::cout << "!\n";
}
case_( "two" )
{
	std::cout << "!!\n";
}
case_( "three" )
{
	std::cout << "!!!\n";
}
switchD( s ) // default
{
	std::cout << "Non-non\n";
}
// or
switch_( s ) // without default
```
