#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <random>
#include <cmath>
#include <tuple>
#include <chrono>
#include <cmath>
#include "m5_neural_network.h"

// 1 variable hyperparameter (non-architecture related to ensure fixed NN architecture)
class Candidate {
  public:
    double alpha;
};

class ParamDist {
  public:
    // candidate generation
    Candidate generate_candidate() {
        Candidate candidate;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0.001, 0.1);

        double random_number = dist(gen);

        candidate.alpha = random_number;

        return candidate;
    }
};


int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Get the start time
    ParamDist soln_space;

    // SH IMPLEMENTATION
    // 1) initialize array of length log_2(total number of candidate models) where each element stores an empty vector
    // 2) add all newly generated candidate models to the vector at the array's index 0 (the first rung of the ladder)
    // 3) run loops to iterate over rungs and within the rungs to train models, score them, and advance the top half of the models to the next rung
    // check if the number of models is provided as a command-line argument
    
    // pass in number of models as argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number of models>" << std::endl;
        return 1;
    }
    const int nModels = std::stoi(argv[1]);
    std::cout << "SH: " << nModels << " models" << std::endl;
    
    std::vector<std::vector<Candidate>> ladder(int(log2(nModels))+1);

    for (int i = 0; i < nModels; i++) {
        Candidate new_model = soln_space.generate_candidate();
        ladder[0].push_back(new_model);
    }

    // Define a custom comparison function that compares the first element of the tuples for the maxHeap
    struct CompareFirstElement {
        bool operator()(const std::tuple<double, Candidate>& a, const std::tuple<double, Candidate>& b) const {
            return std::get<0>(a) < std::get<0>(b);
        }
    };

    for (int i = 0; i < ladder.size() - 1; i++) {
        std::priority_queue<std::tuple<double, Candidate>, std::vector<std::tuple<double, Candidate>>, CompareFirstElement> maxHeap;

        for (unsigned int j = 0; j < ladder[i].size(); j++) {
            Candidate model = ladder[i][j];
            int nEpochs = std::pow(2, i);
            auto start_time_model = std::chrono::high_resolution_clock::now();  // Get the start time
            double score = helper(model.alpha, nEpochs);
            auto end_time_model = std::chrono::high_resolution_clock::now();  // Get the end time
            auto duration_model = std::chrono::duration_cast<std::chrono::microseconds>(end_time_model - start_time_model);  // Calculate the duration in microseconds

            std::cout << "Epochs: " << nEpochs << " || Local Duration: " << duration_model.count() << " microseconds \n" << std::endl;  // Print the duration

            maxHeap.push(std::make_tuple(score, model));
            if (maxHeap.size() > ladder[i].size()/2) {
                std::tuple<double, Candidate> best = maxHeap.top();
                maxHeap.pop();
                ladder[i+1].push_back(std::get<1>(best));
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();  // Get the end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);  // Calculate the duration in microseconds
    std::cout << "Overall Duration: " << duration.count() << " microseconds" << std::endl;  // Print the duration

    return 0;
}

