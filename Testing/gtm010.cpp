/*=========================================================================
 *
 *  Copyright OSEHRA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "GTM.h"

#include <cstdlib>
#include <iostream>

//
//   Compute the Fibonacci Series
//

int main( int argc, char * argv [] )
{
  GTM gtm;

  try
    {

    gtm.Set( "^FibonacciA", "1" );
    gtm.Set( "^FibonacciB", "1" );

    std::string getValue = "Initially empty";

    for( unsigned int i = 0; i < 10; i++ )
      {
      gtm.Execute("set ^FibonacciValue=^FibonacciA+^FibonacciB");
      gtm.Execute("set ^FibonacciB=^FibonacciA");
      gtm.Execute("set ^FibonacciA=^FibonacciValue");
      gtm.Get( "^FibonacciValue", getValue );

      std::cout << "Fibonacci value = " << getValue << std::endl;
      }

    gtm.Kill( "^FibonacciA" );
    gtm.Kill( "^FibonacciB" );
    gtm.Kill( "^FibonacciValue" );

    }
  catch( std::runtime_error & excp )
    {
    std::cerr << excp.what() << std::endl;
    }

  return EXIT_SUCCESS;
}
