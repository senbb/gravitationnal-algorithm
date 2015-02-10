#include "gravitationalalgorithm.h"

using namespace std;

MyAlgorithm::MyAlgorithm(const Problem &pbm, const SetUpParams &setup):
    _solutions(), _fitness_values(), _setup(setup), _upper_cost(), _lower_cost()
{
    _solutions.push_back(new Solution(pbm));
    initialize();
}

const SetUpParams& MyAlgorithm::setup() const
{
    return _setup;
}

unsigned int MyAlgorithm::upper_cost() const
{
    return _upper_cost;
}

unsigned int MyAlgorithm::lower_cost() const
{
    return _lower_cost;
}

const vector<Solution *>& MyAlgorithm::solutions() const
{
    return _solutions;
}

void MyAlgorithm::initialize()
{
    struct particle p;

    for(int i=0; i<30; ++i)
    {
        Solution solution;
        p.fitness =solution.fitness();
        p.index = i;
        solutions.push_back(&solution);
        _fitness_values.push_back(p);
    }
}

vector<struct particle>& MyAlgorithm::fitness_values() const
{
    return _fitness_values;
}

double MyAlgorithm::fitness(const unsigned int index) const
{
    for(struct particle p: _fitness_values)
        if(p.index==index)
            return p.fitness;
}

double MyAlgorithm::best_cost() const
{
    double fit = 0.0;

    for(struct particle fitness : _fitness_values)
    {
        if(fit<fitness.fitness)
            fit=fitness;
    }

    return fit;
}

double MyAlgorithm::worst_solution() const
{
    double fit = 0.0;

    for(struct particle fitness : _fitness_values)
    {
        if(fit>fitness.fitness)
            fit=fitness;
    }

    return fit;
}

Solution& MyAlgorithm::best_solution() const
{
    Solution bestSolution;

    for(Solution sol: _solutions)
    {
        if(sol<bestSolution)
            bestSolution=sol;
    }

    return sol;
}

Solution& MyAlgorithm::worst_solution() const
{
    Solution worstSolution;

    for(Solution sol: _solutions)
    {
        if(sol>worstSolution)
            bestSolution=sol;
    }

    return sol;
}


ostream& operator << (ostream& os, const MyAlgorithm& myAlgo)
{
    os<<myAlgo._setup;
    os<<"\n"<<myAlgo._upper_cost<<","<<myAlgo._lower_cost;
    for(int i=0; i<myAlgo._solutions.size(); ++i)
    {
        os<<myAlgo._solutions.at(i)<<","<<myAlgo._fitness_values.at(i);
    }

    return os;
}


istream& operator >> (istream& is, const MyAlgorithm& myAlgo)
{
    while(is)
    {
        getline(is, line);
        iterator it = line.begin;
    }
}