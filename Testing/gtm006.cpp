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
//  Test the Query method
//

int main( int argc, char * argv [] )
{
  GTM gtm;

  std::string globalName;
  std::string setValue;
  std::string getValue;
  std::string expectedValue;

  try
    {

    //
    //   Exercise the std::string API
    //

    globalName = "^Capital(\"US\")";
    setValue = "Washington";

    gtm.Set( globalName, setValue );

    globalName = "^Capital(\"UK\")";
    setValue = "London";

    gtm.Set( globalName, setValue );

    gtm.Query( globalName, getValue );

    std::cout << "Query of " << globalName << " = " << getValue << std::endl;

    expectedValue = "^Capital(\"US\")";

    gtm.Kill( "^Capital" );

    if( getValue != expectedValue )
      {
      std::cerr << "Test FAILED !" << std::endl;
      std::cerr << "Expected value = " << expectedValue << std::endl;
      std::cerr << "Received value = " << getValue << std::endl;
      return EXIT_FAILURE;
      }

    //
    //   Exercise the same pattern with direct strings
    //

    gtm.Set( "^Capital(\"US\")", "Washington" );
    gtm.Set( "^Capital(\"UK\")", "London" );

    globalName = "^Capital(\"UK\")";

    gtm.Query( globalName, getValue );

    std::cout << "Query of " << globalName << " = " << getValue << std::endl;

    expectedValue = "^Capital(\"US\")";

    gtm.Kill( "^Capital" );

    if( getValue != expectedValue )
      {
      std::cerr << "Test FAILED !" << std::endl;
      std::cerr << "Expected value = " << expectedValue << std::endl;
      std::cerr << "Received value = " << getValue << std::endl;
      return EXIT_FAILURE;
      }

    }
  catch( std::runtime_error & excp )
    {
    std::cerr << excp.what() << std::endl;
    }

  return EXIT_SUCCESS;
}
