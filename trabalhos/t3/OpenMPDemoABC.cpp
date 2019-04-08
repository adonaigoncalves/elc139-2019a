#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <omp.h>

class SharedArray{
  private:
    char *array;
    int index;
    int size;

  public:
    SharedArray(int n) : size(n), index(0){
        array = new char[size];
        std::fill(array, array + size, '-');
    }

    ~SharedArray(){
        delete[] array;
    }

    void addChar(char c){
        #pragma omp critical
        {
            array[index] = c;
            spendSomeTime();
            index++;
        }
    }

    void addCharNoCritical(char c){
        array[index] = c;
        spendSomeTime();
        index++;
    }

    int countOccurrences(char c){
        return std::count(array, array+size, c);
    }

    std::string toString(){
        return std::string(array, size);
    }

  private:
    void spendSomeTime(){
        for (int i = 0; i < 10000; i++){
            for (int j = 0; j < 1000; j++){
                // These loops shouldn't be removed by the compiler
            }
        }
    }
};

class ArrayFiller{
  private:
    int chunk = 0;
    int nThreads = 0;
    int nTimes = 0;
    SharedArray *array;

  public:
    ArrayFiller(int nThreads, int nTimes, int chunk){
        this->nThreads = nThreads;
        this->nTimes = nTimes;
        this->chunk = chunk;
        array = new SharedArray(nThreads * nTimes);
    }

    void fillArrayConcurrently(int schedule){
        int i;
        switch (schedule){
        case 1: // Static schedule with chunk
            #pragma omp parallel for schedule(static, chunk) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 2: // Static schedule without chunk
            #pragma omp parallel for schedule(static) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 3: // Dynamic schedule with chunk
            #pragma omp parallel for schedule(dynamic, chunk) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 4: // Dynamic schedule without chunk
            #pragma omp parallel for schedule(dynamic) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 5: // Guided schedule with chunk
            #pragma omp parallel for schedule(guided, chunk) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 6: // Guided schedule without chunk
            #pragma omp parallel for schedule(guided) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 7: // Runtime schedule
            #pragma omp parallel for schedule(runtime) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;

        case 8: // Auto schedule
            #pragma omp parallel for schedule(auto) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addChar('A' + omp_get_thread_num());
            break;
            
        case 9: // Auto schedule without critical section 
            #pragma omp parallel for schedule(auto) num_threads(nThreads) private(i)
            for (i = 0; i < nTimes * nThreads; i++)
                array->addCharNoCritical('A' + omp_get_thread_num());
            break;
        }
    }

    void printStats(){
        std::cout << array->toString() << std::endl;
        for (int i = 0; i < nThreads; ++i)
            std::cout << (char)('A' + i) << "="
                      << array->countOccurrences('A' + i) << " ";
        std::cout << std::endl;
    }

    ~ArrayFiller(){
        delete array;
    }
};

int main(int argc, char **argv){
    if (argc != 4){
        printf("Use: %s <nThreads> <nTimes> <chunk>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int nThreads = atoi(argv[1]);
    int nTimes = atoi(argv[2]);
    int chunk = atoi(argv[3]);

    std::cout << "Each thread should add its char to the array n times, where n = " << nTimes << std::endl;
    std::cout << "Correct results should total exactly nThreads*nTimes chars, which is " << nTimes * nThreads << std::endl;

    std::cout << "\nCase 1: Static schedule with chunk" << std::endl;
    ArrayFiller case1(nThreads, nTimes, chunk);
    case1.fillArrayConcurrently(1);
    case1.printStats();

    std::cout << "\nCase 2: Static schedule without chunk" << std::endl;
    ArrayFiller case2(nThreads, nTimes, chunk);
    case2.fillArrayConcurrently(2);
    case2.printStats();

    std::cout << "\nCase 3: Dynamic schedule with chunk" << std::endl;
    ArrayFiller case3(nThreads, nTimes, chunk);
    case3.fillArrayConcurrently(3);
    case3.printStats();

    std::cout << "\nCase 4: Dynamic schedule without chunk" << std::endl;
    ArrayFiller case4(nThreads, nTimes, chunk);
    case4.fillArrayConcurrently(4);
    case4.printStats();

    std::cout << "\nCase 5: Guided schedule with chunk" << std::endl;
    ArrayFiller case5(nThreads, nTimes, chunk);
    case5.fillArrayConcurrently(5);
    case5.printStats();

    std::cout << "\nCase 6: Guided schedule without chunk" << std::endl;
    ArrayFiller case6(nThreads, nTimes, chunk);
    case6.fillArrayConcurrently(6);
    case6.printStats();
    
    std::cout << "\nCase 7: Runtime schedule" << std::endl;
    ArrayFiller case7(nThreads, nTimes, chunk);
    case7.fillArrayConcurrently(7);
    case7.printStats();

    std::cout << "\nCase 8: Auto schedule" << std::endl;
    ArrayFiller case8(nThreads, nTimes, chunk);
    case8.fillArrayConcurrently(8);
    case8.printStats();

    std::cout << "\nCase 9: Auto schedule without critical section" << std::endl;
    ArrayFiller case9(nThreads, nTimes, chunk);
    case9.fillArrayConcurrently(9);
    case9.printStats();
}