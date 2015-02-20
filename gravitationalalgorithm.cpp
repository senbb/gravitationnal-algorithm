#include "gravitationalalgorithm.h"
#include <cmath>
#include <iterator>
#include <string>

using namespace std;

Problem::Problem():_dimension(30),LowerLimit(0),UpperLimit(0)
{
}

Problem::~Problem()
{
}

Problem& Problem::operator = (const Problem& pbm)
{
    if(this != &pbm)
    {
        _dimension = pbm._dimension;
        LowerLimit = pbm.LowerLimit;
        UpperLimit = pbm.UpperLimit;
    }

    return *this;
}

bool Problem::operator ==(const Problem& pbm) const
{
    return (_dimension==pbm._dimension)&&(UpperLimit==pbm.UpperLimit)&&(LowerLimit==pbm.LowerLimit);
}

bool Problem::operator !=(const Problem& pbm) const
{
    return !((_dimension==pbm._dimension)&&(UpperLimit==pbm.UpperLimit)&&(LowerLimit==pbm.LowerLimit));
}

int Problem::dimension() const
{
    return _dimension;
}

ostream& operator << (ostream& os, const Problem& pbm)
{
    return os << pbm._dimension << "," << pbm.LowerLimit << "," << pbm.UpperLimit;
}

istream& operator >> (istream& is, Problem& pbm)
{

    istream_iterator<string> it(is),end;
    pbm._dimension = string2Value<int>(*it);
    it++;
    it++;
    pbm.LowerLimit = string2Value<double>(*it);
    it++;
    it++;
    pbm.UpperLimit = string2Value<double>(*it);

    return is;
}


void MyAlgorithm::evaluate()
{
    _fitness_values.erase(_fitness_values.begin(), _fitness_values.end());
    int i = 0;

    for(Solution* solution : _solutions)
    {
        struct particle tmp;
        tmp.fitness = solution->get_fitness();
        tmp.index = i;
        i++;
    }
}

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

    for(int i=0; i<29; ++i)
    {
        Solution solution(_pbm);
        solution.initialize();
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
            fit=fitness.fitness;
    }

    return fit;
}

Solution& MyAlgorithm::worst_solution() const
{
    double bestSolutionFitness = 0.0;
    Solution *bestSolution;

    for(Solution sol: _solutions)
    {
        if(sol.fitness()>bestSolution.fitness())
            bestSolution=sol;
    }

    return sol;
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
            worstSolution=sol;
    }

    return sol;
}

void MyAlgorithm::evolution(int iter)
{

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

Solution::Solution (const Problem& pbm):_pbm(pbm)
{
}

Solution::Solution (const Solution& sol)
{
    for(int i = 0; i < sol._solution.size(); i++)
    {
        _solution.push_back(sol._solution[i]);
    }

    _current_fitness=sol._current_fitness ;
}

Solution::~Solution()
{
    _solution.clear();
}

ostream&  Solution::operator<< (ostream& os, const Solution& sol)
{
    for(vector<double>::iterator i = sol._solution.begin(); i != sol._solution.end();++i)
        os << i << ',';
    return os ;
}


istream&  Solution::operator>> (istream& is, Solution& sol)
{
    for(vector<double>::iterator i = sol._solution.begin(); i != sol._solution.end();++i)
        is >> i >> ',';
    return is ;
}

const Problem& Solution::pbm() const
{
    return _pbm;
}

Solution& Solution::operator=  (const Solution& sol)
{

    if(&sol != this) {

        for(size_t i = 0; i < sol._solution.size(); ++i)
        {
            _solution[i] = sol._solution[i];
        }

        _current_fitness=sol._current_fitness ;
        _pbm=sol._pbm;

        cout <<endl<< "-> =";
    }
    return *this;

}

bool Solution::operator== (const Solution& sol) const
{

    return this->solution()== sol.solution() && this->get_fitness() == sol.get_fitness()&& this->pbm()==sol.pbm() ;

}

bool Solution::operator!= (const Solution& sol) const
{

    return !(*this == sol);

}

void Solution::initialize()
{



}

double Solution::fitness()
{
    _current_fitness = _pbm.evaluate(_solution);
    return _current_fitness;
}

double Solution::get_fitness()
{

    return _current_fitness ;

}

unsigned int Solution::size() const
{

    return _solution.size();

}

vector<double>& Solution::solution()
{

    return _solution ;

}

double& Solution::position(const int index)
{

    return _solution.at(index);

}

void  Solution::position(const int index, const double value)
{

    _solution.assign(index, value);

}



//Constructeur et Destructeur
//Voir page 46 du cours
SetUpParams::SetUpParams() :_independent_runs(30), _nb_evolution_steps(0), _population_size(30), _solution_size(0){} // A finir
SetUpParams::~SetUpParams()  {}

//Getteurs
const unsigned int  SetUpParams::independent_runs() const{
    return _independent_runs;
}

const unsigned int  SetUpParams::nb_evolution_steps() const{
    return _nb_evolution_steps;
}

const unsigned int  SetUpParams::population_size() const{
    return _population_size;
}

const unsigned int  SetUpParams::solution_size() const{
    return _solution_size;
}


//Setteurs
void SetUpParams::independent_runs(const unsigned int val){
    _independent_runs = val;
}

void SetUpParams::nb_evolution_steps(const unsigned int val){
    _nb_evolution_steps = val;
}

void SetUpParams::population_size(const unsigned int val){
    _population_size = val;
}

void SetUpParams::solution_size(const unsigned int val){
    _solution_size = val;
}


//Opérateurs
ostream& operator<< (ostream& os, const SetUpParams& setup){
    return os << setup._independent_runs << "," << setup._nb_evolution_steps << "," << setup._population_size << "," << setup._solution_size;
}


istream& operator>> (istream& is, SetUpParams& setup){ // A finir
    string line;
    getline(is,line);
    //iterator it = line.begin();
    //string2value((*it));
    //it++;
    //it++;
}
