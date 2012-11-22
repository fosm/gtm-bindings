#include <node.h>
#include <node_version.h>

#include <cstdlib>
#include <iostream>

int main( int argc, char * argv [] )
{

  std::cout << "Node.js Version = " << NODE_VERSION_STRING << std::endl;

  return EXIT_SUCCESS;
}
