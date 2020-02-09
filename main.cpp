#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

bool isValidUnsignedNum(const std::string &str);
bool isInteger(const double &num);
void promptUser(unsigned int x);
unsigned int& findNextOdd(unsigned int &x);
unsigned int find_d(const unsigned int &phi, const unsigned int &e);
unsigned int gcd(const unsigned int &phi, const unsigned int &e);
unsigned int mod(const unsigned int &x, const unsigned int &y, const unsigned int &z);
std::vector<unsigned int>& getIntsFromLine(std::vector<unsigned int> &vect, std::string line);
std::vector<unsigned int>& encrypt(vector<unsigned int> &vect, const char table[],
                                   const std::string &line, const unsigned int &e, const unsigned int &n);


/*
 * This program implements RSA. The user will first be prompted for a public key
 * (e, n). The user can either choose to select Encryption 'e' or Decryption for
 * 'd'. A data file named 'input.txt' is expected and will contain either a message
 * which will be encrypted or decrypted. After the program runs an 'output.txt'
 * file will be generated along side the 'input.txt' file, containing either a
 * decrypted or encrypted message. The integers corresponding with the alphabetical
 * letter is hard coded in the program.
 */
int main(int argc, char*argv[]) //<fileName> e n 'e'/'d' <outputFileName>
{
    unsigned int e, n, d, p, q, c, m;
    std::string inputFileName = argv[4];
    std::ifstream inputFile(inputFileName);
    bool isValid_e = false, isValid_n = false, isValid_encrypORdecrypt = false;
    std::string str_e = argv[1], str_n = argv[2], str_encrypORdecrypt = argv[3], line;
    char table[50] = {' ', ' ', 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ','.','?','!'};


/* Get user public key and make sure it's positive integer */
/*
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
*/

/* Get user 'e' or 'd' and make sure it's valid */
/*    while (!isValid_encrypORdecrypt){   //if 'e' or 'd' given
        promptUser(3);
        std::getline (std::cin, str_encrypORdecrypt);

        if ( !(str_encrypORdecrypt == "d") && !(str_encrypORdecrypt == "e") )
            promptUser(5);
        else
            break;
    }
*/


/* Convert string to unsigned int */
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
                if ( gcd(phi, e) == 1 ) {       //make sure e, phi are relatively prime
                    d = find_d(phi, e);         //d = e^-1 mod( (p-1)*(q-1) )
                    break;                      //d found
                }
            }
            p--;
        }   //we don't test if n = 2


/* d found now convert integer to character*/
        std::ofstream outputFile("decrypted.txt");
        std::vector<unsigned int> intVector;

        while (std::getline(inputFile, line)) {
            intVector = getIntsFromLine(intVector, line);
            for (unsigned int i = 0; i < intVector.size(); i++) {   //for each integer in file
                m = mod(intVector.at(i), d, n);   //decrypt m = c^d mod n
                outputFile << table[m];
            }
            intVector.clear();
        }
        inputFile.close();
        outputFile.close();

    } else {


/* encryption 'e' was selected */

        //read in line and get each character
        std::ofstream outputFile("incrypted.txt");
        std::vector<unsigned int> encryptedLineVector;

        while (std::getline(inputFile, line)) {
            encryptedLineVector = encrypt(encryptedLineVector, table, line, e, n);  //c = m^e mod n

            for (unsigned int i = 0; i < encryptedLineVector.size(); i++) {
                outputFile << to_string( encryptedLineVector.at(i) );   //append unsigned int to string to file
                if (i != encryptedLineVector.size()-1)  //if last letter no space
                    outputFile << " ";
            }
            encryptedLineVector.clear();
        }
        inputFile.close();
        outputFile.close();

    }

    return 0;
}

bool isValidUnsignedNum(const std::string &str) {
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
    if ( (x % 2) == 0 )     //x is even
        x--;
    else
        x = x-2;
    return x;
}

unsigned int find_d(const unsigned int &phi, const unsigned int &e) {
    //d*e = k*phi + 1  ->   d = (k*phi + 1) / e;
    unsigned int k = 1;
    double num;

    while (true) {
        num = k*phi + 1;
        num = num / e;
        if (isInteger(num))
            break;
        k++;
    }

    return (unsigned int)num;
}

bool isInteger(const double &num) {
    unsigned int intNum = (unsigned int)num;
    double doubleNum = (double)intNum;
    if (doubleNum == num)
        return true;
    else
        return false;
}

unsigned int gcd(const unsigned int &phi, const unsigned int &e) {
    if (e == 0)   //recursive algorithm to find gcd
        return phi;
    return gcd(e, phi%e);
}

unsigned int mod(const unsigned int &x, const unsigned int &y, const unsigned int &z) {
    //x^y mod z
    unsigned int i = x, j = y;
    while (j > 1) {
        i = (i*x) % z;
        j--;
    }
    return i;
}

std::vector<unsigned int>& getIntsFromLine(std::vector<unsigned int> &vect,
                                           std::string line) {
    size_t pos;
    std::string intStr;
    unsigned int num;

    while ( (pos = line.find(" ")) != std::string::npos ) {
        intStr = line.substr(0, pos);
        std::stringstream iss(intStr);
        iss >> num;
        vect.push_back(num);
        line.erase(0, intStr.length() + 1);
    }
    std::stringstream iss(line);
    iss >> num;
    vect.push_back(num);

    return vect;
}

std::vector<unsigned int>& encrypt(vector<unsigned int> &vect, const char table[],
                                   const std::string &line, const unsigned int &e,
                                   const unsigned int &n) {

    unsigned int c;
    char letter;

    for (unsigned int i = 0; i < line.length(); i++) {  //for every character in line
        for (unsigned int j = 2; j < 35; j++) { //check for matching letter in table array
            letter = line.at(i);
            if (letter == table[j]) {
                c = mod(j, e, n); //c = m^e mod n
                vect.push_back(c);
            }
        }
    }

    return vect;
}
