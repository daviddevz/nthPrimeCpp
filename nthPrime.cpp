//code to produce nth prime number given an input
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

bool isPrime(int num);
int nthPrimeNum(int num);
int estPrimeUpperBound(int nth);
std::vector<int> createIntList(int loweBound, int upperBound);
std::vector<int> primeList(int nth);

int main(){
    int num;
    char tryAgain;

    std::cout<<"Enter an nth number ";
    std::cin>> num;
    
    if (num == 1){
        std::cout<<"The "<<num<<"st prime number is "<<nthPrimeNum(num)<<std::endl;
    }
    else if (num == 2){
        std::cout<<"The "<<num<<"nd prime number is "<<nthPrimeNum(num)<<std::endl;
    }
    else if (num == 3){
        std::cout<<"The "<<num<<"rd prime number is "<<nthPrimeNum(num)<<std::endl;
    }
    else{
        std::cout<<"The "<<num<<"th prime number is "<<nthPrimeNum(num)<<std::endl;
    }
    

    /* std::vector<int> listInt = primeList(estPrimeUpperBound(num));
    std::cout << "Prime List: ";
    for (int prime : listInt) {
        std::cout << prime << " ";
    }
    std::cout << std::endl; */

    std::cout<<"\nDo you want to try again?(Y/N) ";
    std::cin>>tryAgain;

    //recursive to attempt another nth number
    if(tryAgain == 'Y' || tryAgain == 'y'){
        main();
    }
    else{
        return 0;
    }
}

//Estimate prime range/upperbound
int estPrimeUpperBound(int nth){
    double upperBound;

    if(nth == 1){
        upperBound = 2; //lowest prime number is 2
    }
    else if (nth == 2){
        upperBound = 3; //pn > n * ln(n * ln(n)) for p2: pn is the nth prime
    }
    else{
        //round up and add 1 to ensure rounding go to the next int
        upperBound = round((nth * std::log(nth * std::log(nth))) + 1); 
        //std::cout<<"upperbound: "<<upperBound<<std::endl;
    }
    //std::cout<<"upperbound "<<upperBound;
    return upperBound;
}//debug: works as expected except for lower nth like 1 & 2. Improvements added

//Create integer list
std::vector<int> createIntegerList(int lowerBound, int upperBound) {
    std::vector<int> intList = {};

    //std::cout<<"intList: ";
    for(int i = lowerBound; i <= upperBound; i++){
        intList.push_back(i);
        //std::cout<<i<<" ";
    }
    return intList;
}//debug: works as expected

//Sieve of Eratosthenes Algorithm
//can only return a single value in C++
std::vector<int> primeList(int upperBound){
    int minPrimeNum = 2, composite = minPrimeNum;
    std::vector<int> intListCopy = createIntegerList(minPrimeNum, upperBound);

    for (int prime:intListCopy){
        if(!intListCopy.empty()){
            composite = prime;
        }

        while(composite <= intListCopy.back()){
            composite += prime;

            /*A lambda function that returns an iterator pointing to found ele or 
            an iterator pointing beyound the last ele i.e intListCopy.end()*/
            auto it = std::find(intListCopy.begin(), intListCopy.end(), composite);

            if (it != intListCopy.end()){//value was found equal to composite
                intListCopy.erase(it); //remove element in intListCopy vector
            }
        }
    }
    return intListCopy;
}

//IsPrime function
bool isPrime(int num){
    if (num <= 1){
        return false; // 1 or less are not prime
    }
    else if (num % 2 == 0 && num > 2){
        return false; // Even numbers greater 2 are not prime
    }
    else{
        for (int x = 3; x <= static_cast<int>(sqrt(num)+1); x += 2){ 
            if (num % x == 0 && num > 1){// increase by to find odd divisor
                return false;
                break; // Exit loop if a divisor is found
            }
        }
    }
    return true;
}

//nthPrimeNum function
int nthPrimeNum(int nth){
    int countPrimeNum = 0, numList = 2, nthPrimeNum;

    if(nth <= 10){//for smaller nth use trial division
        //loop to check for the nth prime number
        while (countPrimeNum != nth){
            if (isPrime(numList)){
                nthPrimeNum = numList;
                countPrimeNum++;
                numList++;
            }
            else{
                numList++;
            }
        }
    }
    else{
        //Lambda function that calls estPrimeUpperBound to determine
        //the uppebound of the nth  prime number, then sends that an argument to 
        //primeList which returns a list of prime number up to the upperbound
        nthPrimeNum = primeList(estPrimeUpperBound(nth))[nth-1]; //nth-1 because index start from 0
    }
    
    return nthPrimeNum;
}