#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

bool isValidUnsignedNum(std::string &str);
void promptUser(unsigned int x);
unsigned int& findNextOdd(unsigned int &x);
unsigned int find_d(const unsigned int &e, const unsigned int &phi);
unsigned int gcd(const unsigned int &e, const unsigned int &phi);

/*
 * This program implements RSA. The user will first be prompted for a public key
 * (e, n). The user can either choose to select Encryption 'e' or Decryption for
 * 'd'. A data file named 'input.txt' is expected and will contain either a message
 * which will be encrypted or decrypted. After the program runs an 'output.txt'
 * file will be generated along side the 'input.txt' file, containing either a
 * decrypted or encrypted message. The integers corresponding with the alphabetical
 * letter is hard coded in the program.
 */
int main()
{
    unsigned int e, n, d, p, q;
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


    /* Decryption 'd' was seleted */
    if (str_encrypORdecrypt == "d") {
        p = sqrt(n);            //start p with first odd number thats below the square root of n
        p = findNextOdd(p);     //p is now odd
        while (p != 1) {        //go through every odd number
            if (n % p == 0) {   //p successfully divided n, q is found
                q = n/p;

                unsigned int phi = (p-1)*(q-1); //totient of n
                if ( gcd(e, phi) == 1 ) {
                    d = find_d(e, phi);         //d = e^-1 mod( (p-1)*(q-1) )
                    break;                      //d found
                }
            }
            p--;
        }

        //d found now convert text
        //test 2

    } else

    /* encryption 'e' was selected */









    return 0;
}

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
    if (x == 1) {           //prompt 1
        std::cout << "\n                  RSA CODE ENCRYPTION & DECRYPTION\n" << std::endl;
        std::cout << "Please enter the public key (e, n):\n";
        std::cout << "e: ";
    } else if (x == 2) {    //prompt 2
        std::cout << "n: ";
    }
    else if (x == 3) {      //prompt 3
        std::cout << "'e' for encryption and 'd' for decryption\n";
    } else if (x == 4) {    //prompt 4
        std::cout << "Your input was not a valid public key\n"<< std::endl;
    } else if (x == 5) {    //prompt 5
        std::cout << "Your input was not 'e' or 'd'"<< std::endl;
    }
}

unsigned int& findNextOdd(unsigned int &x) {
    x = (x % 2) ? x : x-1;      //if x is even subtract it by 1
    return x;
}

unsigned int find_d(const unsigned int &e, const unsigned int &phi) {
    //d*e = 1 mod( (p-1)*(q-1) )
    unsigned int d = (unsigned int)pow(e, phi-2) % phi;
    return d;
}

unsigned int gcd(const unsigned int &e, const unsigned int &phi) {
    if (e == phi)   //recursive algorithm to find gcd
        return e;
    if (e < phi)
        return gcd(phi-e, e);
    return gcd(e-phi, phi);
}
