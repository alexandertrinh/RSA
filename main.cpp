#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

bool isValidUnsignedNum(std::string &str) {
    std::string::const_iterator iterator;
    iterator = str.begin();

    while( (iterator != str.end()) ) {
        if ( !std::isdigit(*iterator) )
            return false;
        iterator++;
    }

    return true;
}

void promptUser(unsigned int x) {
    if (x == 1) {   //prompt 1
        std::cout << "\n                  RSA CODE ENCRYPTION & DECRYPTION\n" << std::endl;
        std::cout << "Please enter the public key (e, n):\n";
        std::cout << "e: ";
    } else if (x == 2) {    //prompt 2
        std::cout << "n: ";
    }
    else if (x == 3) {    //prompt 3
        std::cout << "'e' for encryption and 'd' for decryption\n";
    } else if (x == 4) {    //prompt 4
        std::cout << "Your input was not a valid public key\n"<< std::endl;
    } else if (x == 5) {    //prompt 5
        std::cout << "Your input was not 'e' or 'd'"<< std::endl;
    }
}

int main()
{
    unsigned int e, n, d;
    bool isValid_e = false, isValid_n = false, isValid_encrypORdecrypt = false;
    std::string str_e, str_n, str_encrypORdecrypt;

    /* Get user public key and make sure it's positive integer */
    while (!isValid_e || !isValid_n) {  //if e and n are valid
        promptUser(1);
        std::getline (std::cin, str_e);
        isValid_e = isValidUnsignedNum(str_e);

        promptUser(2);
        std::getline (std::cin, str_n);
        isValid_n = isValidUnsignedNum(str_n);
        std::cout << "\n";

        if (!isValid_e || !isValid_n)
            promptUser(4);
    }

    /* Get user 'e' or 'd' and make sure it's valid */
    while (!isValid_encrypORdecrypt){   //if 'e' or 'd' given
        promptUser(3);
        std::getline (std::cin, str_encrypORdecrypt);

        if ( !(str_encrypORdecrypt == "d") && !(str_encrypORdecrypt == "e") )
            promptUser(5);
        else
            break;
    }

    /* Convert string to unsigned int */
    std::cout << "\n";  //newline
    std::stringstream iss_e(str_e);
    iss_e >> e;
    std::stringstream iss_n(str_n);
    iss_n >> n;











    return 0;
}
