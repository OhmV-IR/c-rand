#include <iostream>
#include <csignal>
#include <random>
#include <cmath>

#define SIGINT 2
#define PRINT_PROBABILITIES_MAX 5752192

bool running = true;
int32_t numHeads = 0;
int32_t numTails = 0;
int32_t totalFlips = 0;

void sighandler(int nSig)
{
    printf("Received exit signal: %d\n", nSig);
    std::cout << "Final readout:\n";
    std::cout << "Heads: " << numHeads << "\n";
    std::cout << "Tails: " << numTails << "\n";
    std::cout << "TotalFlips: " << totalFlips << "\n";
    std::cout << "%Heads: " << (numHeads / totalFlips) * 100 << "\n";
    std::cout << "%Tails: " << (numTails / totalFlips) * 100 << "\n";
    running = false;
}

int main()
{
    std::cout << "Starting program...";
    std::mt19937 randomNumberGen = std::mt19937();
    std::uniform_int_distribution<uint32_t> randomNumberRange = std::uniform_int_distribution<uint32_t>(0, 1);
    std::uniform_int_distribution<uint32_t> printProbabilitiesRange = std::uniform_int_distribution<uint32_t>(0, PRINT_PROBABILITIES_MAX);
    signal(SIGINT, sighandler); // catch ctrl+c exit command
    while (running)
    {
        totalFlips++;
        if (randomNumberRange(randomNumberGen) == 0)
        {
            numHeads++;
        }
        else
        {
            numTails++;
        }
        if (printProbabilitiesRange(randomNumberGen) == 1)
        {
            std::cout << "Heads: " << numHeads << "\n";
            std::cout << "Tails: " << numTails << "\n";
            std::cout << "TotalFlips: " << totalFlips << "\n";
            std::cout << "%Heads: " << (numHeads / totalFlips) * 100 << "\n";
            std::cout << "%Tails: " << (numTails / totalFlips) * 100 << "\n";
        }
    }
    return 0;
}