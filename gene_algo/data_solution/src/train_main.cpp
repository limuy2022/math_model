#include <rename.h>
#include <unistd.h>

#include <Eigen/Core>
#include <bitset>
#include <cassert>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "Eigen/src/Core/Matrix.h"

template <typename Chromosome>
struct Creature {
    friend std::ifstream &operator>>(std::ifstream &file,
                                     std::vector<Chromosome> &chromosomes);
    friend std::ofstream &operator<<(
        std::ofstream &file, std::vector<Chromosome> const &chromosomes);
    static std::filesystem::path rootPath;
    static constexpr usize mid1{20}, mid2{20};
    static constexpr usize chromosomesSize{mid1 * 5 + mid1 * mid2 + mid2 +
                                           mid1 + mid2 + 1};
    static std::default_random_engine engine;
    std::vector<Chromosome> chromosomes;
    f64 fitness{};

    Creature() = default;

    void initCreature() {
        static std::uniform_real_distribution<f64> normalGenerator1(
            -std::exp(std::log(6. / 5.) * 0.5),
            std::exp(std::log(6. / 5.) * 0.5));
        static std::uniform_real_distribution<f64> normalGenerator2(
            -std::exp(std::log(6. / mid1) * 0.5),
            std::exp(std::log(6. / mid1) * 0.5));
        static std::uniform_real_distribution<f64> normalGenerator3(
            -std::exp(std::log(6. / mid2) * 0.5),
            std::exp(std::log(6. / mid2) * 0.5));
        static std::normal_distribution<f64> normalGeneratorB(1, 0.01);
        static std::ifstream trainIn(rootPath / "../data/train.txt");
        if (trainIn.is_open()) {
            // std::cout << "He" << std::endl;
            trainIn >> chromosomes;
            if (trainIn.eof()) {
                trainIn.close();
            }
        } else {
            chromosomes.resize(chromosomesSize);
        START:
            i32 nowId{};
            for (i32 _i{0}; _i < mid1; ++_i) {
                for (i32 _j{0}; _j < 5; ++_j) {
                    chromosomes[nowId].value = normalGenerator1(engine);
                    ++nowId;
                }
            }
            for (i32 _i{0}; _i < mid1; ++_i) {
                chromosomes[nowId].value = normalGeneratorB(engine);
                ++nowId;
            }
            for (i32 _i{0}; _i < mid2; ++_i) {
                for (i32 _j{0}; _j < mid1; ++_j) {
                    chromosomes[nowId].value = normalGenerator2(engine);
                    ++nowId;
                }
            }
            for (i32 _i{0}; _i < mid2; ++_i) {
                chromosomes[nowId].value = normalGeneratorB(engine);
                ++nowId;
            }
            for (i32 _i{0}; _i < 1; ++_i) {
                for (i32 _j{0}; _j < mid2; ++_j) {
                    chromosomes[nowId].value = normalGenerator3(engine);
                    ++nowId;
                }
            }
            for (i32 _i{0}; _i < 1; ++_i) {
                chromosomes[nowId].value = normalGeneratorB(engine);
                ++nowId;
            }
            calFitness();
            // std::cout << "**:" << std::fabs(1. / fitness - 0.104) << '\n';
            // if (std::fabs(fitness - 9.604) < 0.01) {
            //     // std::puts("Hi");
            //     goto START;
            // }
        }
    }

    void variateCreature() {
        static std::uniform_real_distribution<f64> normalGenerator1(
            -std::exp(std::log(6. / 5.) * 0.5),
            std::exp(std::log(6. / 5.) * 0.5));
        static std::uniform_real_distribution<f64> normalGenerator2(
            -std::exp(std::log(6. / mid1) * 0.5),
            std::exp(std::log(6. / mid1) * 0.5));
        static std::uniform_real_distribution<f64> normalGenerator3(
            -std::exp(std::log(6. / mid2) * 0.5),
            std::exp(std::log(6. / mid2) * 0.5));
        static std::uniform_real_distribution<f64> randomValueGenerator(-1, 1);
        static std::uniform_real_distribution<f64> randomGenerator(0.0, 1.0);
        // std::puts("Hello");
        i32 nowId{};
        static constexpr f64 mutationRate{1};
        for (i32 _i{0}; _i < mid1; ++_i) {
            for (i32 _j{0}; _j < 5; ++_j) {
                if (randomGenerator(engine) < mutationRate) {
                    chromosomes[nowId].value += normalGenerator1(engine);
                    ++nowId;
                }
            }
        }
        for (i32 _i{0}; _i < mid1; ++_i) {
            if (randomGenerator(engine) < mutationRate) {
                chromosomes[nowId].value += randomValueGenerator(engine);
                ++nowId;
            }
        }
        for (i32 _i{0}; _i < mid2; ++_i) {
            for (i32 _j{0}; _j < mid1; ++_j) {
                if (randomGenerator(engine) < mutationRate) {
                    chromosomes[nowId].value += normalGenerator2(engine);
                    ++nowId;
                }
            }
        }
        for (i32 _i{0}; _i < mid2; ++_i) {
            if (randomGenerator(engine) < mutationRate) {
                chromosomes[nowId].value += randomValueGenerator(engine);
                ++nowId;
            }
        }
        for (i32 _i{0}; _i < 1; ++_i) {
            for (i32 _j{0}; _j < mid2; ++_j) {
                if (randomGenerator(engine) < mutationRate) {
                    chromosomes[nowId].value += normalGenerator3(engine);
                    ++nowId;
                }
            }
        }
        for (i32 _i{0}; _i < 1; ++_i) {
            if (randomGenerator(engine) < mutationRate) {
                chromosomes[nowId].value += randomValueGenerator(engine);
                ++nowId;
            }
        }
    }

    // static std::vector<f32> changeNum(
    //     std::vector<std::pair<Chromosome, Chromosome>> const &chromosome) {
    //     std::vector<f32> result;
    //     u32 nowCnt{}, nowSum{};
    //     for (auto &anyHomolousChromosomes : chromosome) {
    //         ++nowCnt;
    //         nowSum =
    //         static_cast<u32>(anyHomolousChromosomes.first.getValue()) |
    //                  (nowSum << 1);
    //         if (nowCnt == 32) {
    //             nowCnt = 0;
    //             result.push_back(reinterpret_cast<f32 *>(&nowSum)[0] *);
    //         }
    //     }
    //     auto resultIt = result.begin();
    //     for (auto &anyHomolousChromosomes : chromosome) {
    //         ++nowCnt;
    //         nowSum =
    //             static_cast<u32>(anyHomolousChromosomes.second.getValue()) |
    //             (nowSum << 1);
    //         if (nowCnt == 32) {
    //             nowCnt = 0;
    //             *resultIt = (*resultIt + reinterpret_cast<f32
    //             *>(&nowSum)[0]);
    //         }
    //     }
    //     return result;
    // }
    f32 getMidVal(i32 id) const { return chromosomes.at(id - 1).getValue(); }

    template <i32 N, i32 M>
    static Eigen::Matrix<f64, N, M> Sigmoid(
        Eigen::Matrix<f64, N, M> const &matrix) {
        Eigen::Matrix<f64, N, M> ret;
        for (i32 _i{0}; _i < N; ++_i) {
            for (i32 _j{0}; _j < M; ++_j) {
                ret(_i, _j) = 1.0 / (1.0 + std::exp(-matrix(_i, _j)));
            }
        }
        return ret;
    }

    template <i32 N, i32 M>
    static Eigen::Matrix<f64, N, M> ReLu(
        Eigen::Matrix<f64, N, M> const &matrix) {
        Eigen::Matrix<f64, N, M> ret;
        for (i32 _i{0}; _i < N; ++_i) {
            for (i32 _j{0}; _j < M; ++_j) {
                ret(_i, _j) = std::max(0.0, matrix(_i, _j));
            }
        }
        return ret;
    }

    void calFitness() {
        f64 ret{};
        std::ifstream tgIn(rootPath / "../data/mTG");
        std::ifstream ppIn(rootPath / "../data/mPP");
        std::ifstream rrIn(rootPath / "../data/mRR");
        std::ifstream ccIn(rootPath / "../data/mCC");
        std::ifstream huIn(rootPath / "../data/mHU");
        std::ifstream fgIn(rootPath / "../data/mFG");
        Eigen::Matrix<f64, mid1, 5> w1;
        i32 nowId = 1;
        for (i32 _i{1}; _i <= mid1; ++_i) {
            for (i32 _j{1}; _j <= 5; ++_j) {
                w1(_i - 1, _j - 1) = getMidVal(nowId);
                ++nowId;
            }
        }
        Eigen::Matrix<f64, mid1, 1> b1;
        for (i32 _i{1}; _i <= mid1; ++_i) {
            b1(_i - 1, 0) = getMidVal(nowId);
            ++nowId;
        }
        Eigen::Matrix<f64, mid2, mid1> w2;
        for (i32 _i{1}; _i <= mid2; ++_i) {
            for (i32 _j{1}; _j <= mid1; ++_j) {
                w2(_i - 1, _j - 1) = getMidVal(nowId);
                ++nowId;
            }
        }
        Eigen::Matrix<f64, mid2, 1> b2;
        for (i32 _i{1}; _i <= mid2; ++_i) {
            b2(_i - 1, 0) = getMidVal(nowId);
            ++nowId;
        }
        Eigen::Matrix<f64, 1, mid2> w3;
        for (i32 _i{1}; _i <= 1; ++_i) {
            for (i32 _j{1}; _j <= mid2; ++_j) {
                w3(_i - 1, _j - 1) = getMidVal(nowId);
                ++nowId;
            }
        }
        Eigen::Matrix<f64, 1, 1> b3;
        for (i32 _i{1}; _i <= 1; ++_i) {
            b3(_i - 1, 0) = getMidVal(nowId);
            ++nowId;
        }
        for (i32 _i{1}; _i <= 1400; ++_i) {
            f64 tg, pp, rr, cc, hu, fg;
            tgIn >> tg;
            ppIn >> pp;
            rrIn >> rr;
            ccIn >> cc;
            huIn >> hu;
            fgIn >> fg;
            Eigen::Matrix<f64, 5, 1> x;
            x(0) = tg;
            x(1) = pp;
            x(2) = fg;
            x(3) = cc;
            x(4) = hu;
            // f64 calcRR = (w3 * Sigmoid<mid2, 1>(
            //                        w2 * Sigmoid<mid1, 1>(w1 * x + b1) + b2) +
            //               b3)(0);
            // f64 calcRR =
            //     (w3 * Sigmoid<mid2, 1>(w2 * Sigmoid<mid1, 1>(w1 * x +
            //     b1)))(0);
            f64 calcRR = ReLu<1, 1>(
                w3 * ReLu<mid2, 1>(w2 * ReLu<mid1, 1>(w1 * x + b1) + b2) + b3)(
                0, 0);
            // f64 calcRR = (w1 * x)(0);
            // std::cout << calcRR << '\n';
            ret += (calcRR - rr) / 1400. * (calcRR - rr);
        }
        tgIn.close();
        ppIn.close();
        rrIn.close();
        ccIn.close();
        huIn.close();
        fgIn.close();
        fitness = 1. / ret;
    }
    void printCalFitness(bool ifOut = true) {
        f64 ret{};
        std::ifstream tgIn(rootPath / "../data/tTG");
        std::ifstream ppIn(rootPath / "../data/tPP");
        std::ifstream rrIn(rootPath / "../data/tRR");
        std::ifstream ccIn(rootPath / "../data/tCC");
        std::ifstream huIn(rootPath / "../data/tHU");
        std::ifstream fgIn(rootPath / "../data/tFG");
        Eigen::Matrix<f64, mid1, 5> w1;
        i32 nowId = 1;
        for (i32 _i{1}; _i <= mid1; ++_i) {
            for (i32 _j{1}; _j <= 5; ++_j) {
                w1(_i - 1, _j - 1) = getMidVal(nowId);
                // std::cout << w1(_i - 1, _j - 1) << ' ';
                ++nowId;
            }
            // std::cout << '\n';
        }
        Eigen::Matrix<f64, mid1, 1> b1;
        for (i32 _i{1}; _i <= mid1; ++_i) {
            b1(_i - 1, 0) = getMidVal(nowId);
            ++nowId;
        }
        Eigen::Matrix<f64, mid2, mid1> w2;
        for (i32 _i{1}; _i <= mid2; ++_i) {
            for (i32 _j{1}; _j <= mid1; ++_j) {
                w2(_i - 1, _j - 1) = getMidVal(nowId);
                ++nowId;
            }
        }
        Eigen::Matrix<f64, mid2, 1> b2;
        for (i32 _i{1}; _i <= mid2; ++_i) {
            b2(_i - 1, 0) = getMidVal(nowId);
            ++nowId;
        }
        Eigen::Matrix<f64, 1, mid2> w3;
        for (i32 _i{1}; _i <= 1; ++_i) {
            for (i32 _j{1}; _j <= mid2; ++_j) {
                w3(_i - 1, _j - 1) = getMidVal(nowId);
                // std::cout << w3(_i - 1, _j - 1) << ' ';
                ++nowId;
            }
            // std::cout << '\n';
        }
        Eigen::Matrix<f64, 1, 1> b3;
        for (i32 _i{1}; _i <= 1; ++_i) {
            b3(_i - 1, 0) = getMidVal(nowId);
            ++nowId;
        }
        // std::cout << "NowId:" << nowId << '\n';
        // std::cout << w3 << "\n\n";
        for (i32 _i{1}; _i <= 252; ++_i) {
            f64 tg, pp, rr, cc, hu, fg;
            tgIn >> tg;
            ppIn >> pp;
            rrIn >> rr;
            ccIn >> cc;
            huIn >> hu;
            fgIn >> fg;
            Eigen::Matrix<f64, 5, 1> x;
            x(0) = tg;
            x(1) = pp;
            x(2) = fg;
            x(3) = cc;
            x(4) = hu;
            // f64 calcRR = (w3 * Sigmoid<mid2, 1>(
            //                        w2 * Sigmoid<mid1, 1>(w1 * x + b1) + b2) +
            //               b3)(0);
            // f64 calcRR =
            //     (w3 * Sigmoid<mid2, 1>(w2 * Sigmoid<mid1, 1>(w1 * x +
            //     b1)))(0);
            // f64 calcRR = LePu<1, 1>(
            //     w3 * LePu<mid2, 1>(w2 * LePu<mid1, 1>(w1 * x + b1) + b2))(0);
            // f64 calcRR = (w1 * x)(0);
            // std::cout << calcRR << '\n';
            // ret += (calcRR - rr) / 600. * (calcRR - rr);
            // f64 calcRR =
            f64 calcRR = ReLu<1, 1>(
                w3 * ReLu<mid2, 1>(w2 * ReLu<mid1, 1>(w1 * x + b1) + b2) + b3)(
                0, 0);
            // f64 calcRR = ReLu<1, 1>(
            //     w3 * ReLu<mid2, 1>(w2 * ReLu<mid1, 1>(w1 * x + b1) + b2) +
            //     b3)(0);
            // std::cout << tmp;
            // std::cout << '\n' << '\n';
            // std::cout << w3;
            // std::cout << '\n' << '\n';
            // std::cout << LePu<1, 1>(w3 * tmp) << ' ';
            if (ifOut) std::cout << calcRR << ' ' << rr << '\n';
            if (rr - 0.1 <= calcRR && calcRR <= rr + 0.1) {
                ++ret;
            }
        }
        tgIn.close();
        ppIn.close();
        rrIn.close();
        ccIn.close();
        huIn.close();
        fgIn.close();
        fitness = ret;
    }

    void printChromosomes(std::ofstream &out) const { out << chromosomes; }

    std::vector<std::pair<Chromosome, Chromosome>> const &getChromosomes()
        const {
        return chromosomes;
    }

    std::vector<std::pair<Chromosome, Chromosome>> &setChromosome() {
        return chromosomes;
    }
};

template <typename Chromosome>
std::filesystem::path Creature<Chromosome>::rootPath{"../../../../"};

template <typename Chromosome>
std::ifstream &operator>>(std::ifstream &file,
                          std::vector<Chromosome> &chromosomes) {
    chromosomes.resize(Creature<Chromosome>::chromosomesSize);
    for (auto &anyHomolousChromosomes : chromosomes) {
        file >> anyHomolousChromosomes;
    }
    return file;
}

template <typename Chromosome>
std::ofstream &operator<<(std::ofstream &file,
                          std::vector<Chromosome> const &chromosomes) {
    for (auto const &anyHomolousChromosomes : chromosomes) {
        file << anyHomolousChromosomes << '\n';
    }
    return file;
}

template <typename Chromosome>
std::default_random_engine Creature<Chromosome>::engine{
    static_cast<usize>(time(nullptr))};

struct Chromosome {
    friend std::ofstream &operator<<(std::ofstream &file,
                                     Chromosome const &chromosome);

    friend std::ifstream &operator>>(std::ifstream &file,
                                     Chromosome &chromosome);
    static std::default_random_engine engine;

    f32 value{};
    Chromosome() = default;
    explicit Chromosome(f32 value) : value{value} {}

    // explicit Chromosome(bool random) {
    //     if (random) {
    // variateChromosome();
    //     }
    // }

    // void variateChromosome() {
    //     static std::uniform_real_distribution<f32> randomValueGenerator{
    //         1. / 1.5, 1.5};
    //     static std::uniform_real_distribution<f32> randomPMGenerator{0., 1.};
    //     static std::uniform_real_distribution<f32>
    //     randomDominanceGenerator{0.,
    //                                                                         1.};
    //     value = value * randomValueGenerator(Chromosome::engine);
    //     if (randomPMGenerator(Chromosome::engine) < 0.5) {
    //         value = -value;
    //     }
    // }

    f32 getValue() const { return value; }
};

std::default_random_engine Chromosome::engine{
    static_cast<usize>(time(nullptr))};
std::ofstream &operator<<(std::ofstream &file, Chromosome const &chromosome) {
    file << std::fixed << std::setprecision(30) << chromosome.value << " ";
    // file << ' ' << chromosome.value;
    return file;
}

std::ifstream &operator>>(std::ifstream &file, Chromosome &chromosome) {
    file >> chromosome.value;
    return file;
}

class BasicData {
 public:
    static f32 eliminatedRate;
    static f32 increasedCreatureRate;
    static f32 variationRate;
};
f32 BasicData::increasedCreatureRate{1};

f32 BasicData::eliminatedRate{0.5};

f32 BasicData::variationRate{0.5};

struct GeneticAlgorithm {
    GeneticAlgorithm() = default;

    explicit GeneticAlgorithm(usize initialCreatureNum) {
        creatures.resize(initialCreatureNum);
        creaturesP.resize(initialCreatureNum);
    }

    void initCreature() {
        for (auto &anyCreature : creatures) {
            anyCreature.initCreature();
        }
        calAllFitness();
        std::ranges::sort(creatures, [](auto const &a, auto const &b) -> bool {
            return a.fitness > b.fitness;
        });
    }

    void calAllFitness() {
        for (auto &anyHomolousChromosomes : creatures) {
            anyHomolousChromosomes.calFitness();
        }
    }

    void calAllP() {
        calAllFitness();
        f64 fitnessSum{};
        for (auto &anyHomolousChromosomes : creatures) {
            fitnessSum += anyHomolousChromosomes.fitness;
        }
        // std::cout << "FS:" << fitnessSum << std::endl;
        auto creaturesPIt = creaturesP.begin();
        for (auto &anyHomolousChromosomes : creatures) {
            *creaturesPIt = anyHomolousChromosomes.fitness / fitnessSum;
            ++creaturesPIt;
        }
    }

    std::vector<Creature<Chromosome>> selectSon() const {
        static std::default_random_engine randomEngine{
            static_cast<usize>(std::time(nullptr))};
        i32 nowID{0};
        std::vector<Creature<Chromosome>> ret;
        std::uniform_real_distribution<f64> randomGenerator{0., 1.};
        std::uniform_int_distribution<usize> randomSelect{
            0, creatures[0].chromosomes.size() - 1};
        // for (auto &anyP : creaturesP) {
        // std::cout << "anyP: " << anyP << '\n';
        // }
        // for (i32 _i{1}; _i <= creatures.size(); ++_i) {
        // std::cout << creatures[_i - 1].fitness << '\n';
        // }
        // exit(0);
        for (i32 _i{1}; _i <= creatures.size() * 2; ++_i) {
            i32 parent1{}, parent2{};
        SELECT:
            do {
                ++nowID;
                if (nowID == creatures.size()) {
                    nowID = 0;
                }
                // std::cout << creaturesP[nowID] << '\n';
            } while (randomGenerator(randomEngine) > creaturesP[nowID]);
            parent1 = nowID;
            do {
                ++nowID;
                if (nowID == creatures.size()) {
                    nowID = 0;
                }
            } while (randomGenerator(randomEngine) > creaturesP[nowID]);
            parent2 = nowID;
            if (parent1 == parent2) {
                goto SELECT;
            }
            // std::cout << parent1 << ' ' << parent2 << '\n';
            Creature<Chromosome> son;
            son.initCreature();
            auto cutPos{randomSelect(randomEngine)};
            for (i32 _j{1}; _j <= cutPos; ++_j) {
                // if (randomGenerator(randomEngine) <
                //     creatures[parent1].fitness / (creatures[parent1].fitness
                //     +
                //                                   creatures[parent2].fitness))
                //                                   {
                son.chromosomes[_j - 1].value =
                    creatures[parent1].chromosomes[_j - 1].value;
                //     // std::puts("1");
                // } else {
                //     son.chromosomes[_j - 1].value =
                //         creatures[parent2].chromosomes[_j - 1].value;
                //     // std::puts("2");
                // }
            }
            for (i32 _j{static_cast<i32>(cutPos + 1)};
                 _j <= son.chromosomes.size(); ++_j) {
                son.chromosomes[_j - 1].value =
                    creatures[parent2].chromosomes[_j - 1].value;
            }
            if (randomGenerator(randomEngine) < BasicData::variationRate) {
                son.variateCreature();
            }
            ret.push_back(son);
        }
        for (auto &anySon : ret) {
            anySon.calFitness();
        }
        std::ranges::sort(ret, [](auto const &a, auto const &b) -> bool {
            return a.fitness > b.fitness;
        });
        return ret;
    }

    void mergeSon(std::vector<Creature<Chromosome>> const &son) {
        std::vector<Creature<Chromosome>> newCreatures;
        newCreatures.resize(creatures.size());
        creatures.erase(creatures.end() - creatures.size() * 0.9,
                        creatures.end());
        // creatures.clear();
        auto newCreaturesIt = newCreatures.begin();
        auto creaturesIt = creatures.begin();
        auto sonIt = son.begin();
        while (creaturesIt != creatures.end() && sonIt != son.end() &&
               newCreaturesIt != newCreatures.end()) {
            if (creaturesIt->fitness > sonIt->fitness) {
                *newCreaturesIt = *creaturesIt;
                ++newCreaturesIt;
                ++creaturesIt;
            } else {
                *newCreaturesIt = *sonIt;
                ++newCreaturesIt;
                ++sonIt;
            }
        }
        while (creaturesIt != creatures.end() &&
               newCreaturesIt != newCreatures.end()) {
            *newCreaturesIt = *creaturesIt;
            ++newCreaturesIt;
            ++creaturesIt;
        }
        while (sonIt != son.end() && newCreaturesIt != newCreatures.end()) {
            *newCreaturesIt = *sonIt;
            ++newCreaturesIt;
            ++sonIt;
        }
        creatures = std::move(newCreatures);
    }

    void printCreatures(std::ofstream &out) const {
        for (auto const &anyHomolousChromosomes : creatures) {
            anyHomolousChromosomes.printChromosomes(out);
        }
        // creatures[9].printChromosomes(out);
        // out << '\n';
        // creatures[10].printChromosomes(out);
    }

    std::vector<Creature<Chromosome>> creatures;
    std::vector<f64> creaturesP;
};

i32 main(i32, char *[]) {
    std::filesystem::path rootPath{"../../../../"};
    GeneticAlgorithm geneticAlgorithm{100};
    geneticAlgorithm.initCreature();
    geneticAlgorithm.calAllP();
    i32 loopCnt{1};
    while (loopCnt--) {
        std::cout << loopCnt << std::endl;
        // for (auto &anyCreature : geneticAlgorithm.creatures) {
        //     std::cout << anyCreature.fitness << std::endl;
        // }
        std::vector<Creature<Chromosome>> son = geneticAlgorithm.selectSon();
        geneticAlgorithm.mergeSon(son);

        std::ofstream trainOut(rootPath / "../data/train.txt");
        geneticAlgorithm.printCreatures(trainOut);
        trainOut.close();
        geneticAlgorithm.calAllP();
        std::cout << 1. / geneticAlgorithm.creatures[0].fitness << std::endl;
    }
    std::ofstream resOut(rootPath / "../data/res.txt");
    // std::ofstream trainOut(rootPath / "../data/train.txt");
    // geneticAlgorithm.printCreatures(trainOut);
    // trainOut.close();
    for (auto const &anyCreature : geneticAlgorithm.creatures) {
        resOut << std::fixed << std::setprecision(40)
               << 1. / anyCreature.fitness << std::endl;
    }
    // geneticAlgorithm.printCreatures(trainOut);
    geneticAlgorithm.creatures[0].printCalFitness();
    std::cout << geneticAlgorithm.creatures[0].fitness << std::endl;
}
