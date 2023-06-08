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
#include <omp.h>

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

// Define a custom comparison function that compares the first element of the tuples for the maxHeap
struct CompareFirstElement {
    bool operator()(const std::tuple<double, Candidate>& a, const std::tuple<double, Candidate>& b) const {
        return std::get<0>(a) < std::get<0>(b);
    }
};


int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Get the start time

    // initialize solution space
    ParamDist soln_space;

    // pass in number of models as argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number of models>" << std::endl;
        return 1;
    }
    const int nModels = std::stoi(argv[1]);

    // bottom rung
    std::vector<Candidate> candidates(nModels);

    // size of thread pool
    const int thread_count = omp_get_max_threads();

    // discretize solution space
    for (int i = 0; i < nModels; i++) {
        Candidate new_model = soln_space.generate_candidate();  
        candidates[i] = new_model;
    }

    // intitialize ladder (heap pyramid)
    const int height = log2(nModels) + 1;

    // height decreases from left to right 
    std::vector<std::priority_queue<std::tuple<double, Candidate>, std::vector<std::tuple<double, Candidate>>, CompareFirstElement>> ladder(height);

    std::cout << "ASH: " << thread_count << " threads, " << nModels << " models\n" << std::endl; 

    // parallel region runs as long as the top rung is empty, with thread pool size {num_threads}
    #pragma omp parallel shared(ladder, candidates) num_threads(thread_count)
    {
        // while the top rung is empty
        while (ladder[1].size() < 2) {
        
        // searches through ladder for highest available job
            std::tuple<double, Candidate> prev;
            int rung = height;
            Candidate model;
            bool model_accessed = false;
            // critical section: ladder is shared memory
            #pragma omp critical
            {
                for (int i = 1; i <= height; i++) {
                    // bottom rung: pop from candidates instead of ladder
                    if (i == height) {
                        if (candidates.size() == 0) {
                            break;
                        }
                        model = candidates.back();
                        candidates.pop_back();
                        model_accessed = true;
                        break;
                    }
                    // any rung that is not the bottom: only pop top half performer
                    if (ladder[i].size() > std::pow(2, i - 1)) { // this is equivalent to half of 2^i
                        if ((i == 1 ) & (ladder[1].size() >= 2)) {
                            break;
                        }
                        prev = ladder[i].top();
                        ladder[i].pop();
                        model = std::get<1>(prev);
                        rung = i;
                        model_accessed = true;
                        break;
                    }
                }
            }
            if (model_accessed) {
                // train model
                int nEpochs = std::pow(2, height - rung);
                auto start_time_model = std::chrono::high_resolution_clock::now();  // Get the start time
                double score = helper(model.alpha, nEpochs);
                auto end_time_model = std::chrono::high_resolution_clock::now();  // Get the end time
                auto duration_model = std::chrono::duration_cast<std::chrono::microseconds>(end_time_model - start_time_model);  // Calculate the duration in microseconds
                std::cout << "Epochs: " << nEpochs << " || Local Duration: " << duration_model.count() << " microseconds \n" << std::endl;  // Print the duration
        
                std::tuple<double, Candidate> cur = std::make_tuple(score, model);

                // critical section: push result to next rung
                #pragma omp critical
                {
                    ladder[rung - 1].push(cur);
                }
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();  // Get the end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);  // Calculate the duration in microseconds
    std::cout << "\nOverall Duration: " << duration.count() << " microseconds" << std::endl;  // Print the duration
    return 0;
}
