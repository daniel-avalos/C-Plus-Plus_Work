// Daniel Avalos, 2018
// Lab 4 - Classes, Completed
// Given population, number of births, and number of deaths,
//  calculates and displays the birthrate and deathrate


#include <iostream> // std::cout, std::cin, std::string, std::right
using namespace std;

// Stores a given populaces population, and # of births and Deaths
class Population {

    private:
        //  Store value, Minimum value
        int population,  popMin   = 2,
            numOfBirths, birthMin = 0,
            numOfDeaths, deathMin = 0;

    public:
        // # Constructors #
        // Default. Requires manually calling setters
        Population() {
            population  = popMin;
            numOfBirths = birthMin;
            numOfDeaths = deathMin;
        }

        // Overload. Allows single line assignments
        Population(int x, int y, int z) {
            setPopulation(x);
            setNumOfBirths(y);
            setNumOfDeaths(z);
        }

        // # Setters #
        // Each checks against respective minimums
        void setPopulation(int val){
            population = val < popMin ? popMin : val;
        }
        void setNumOfBirths(int val){
            numOfBirths = val < birthMin ? birthMin : val;
        }
        void setNumOfDeaths(int val){
            numOfDeaths = val < deathMin ? deathMin : val;
        }

        // # Getters #
        // Floats used for consistency
        const float getPopulation() {
            return population;
        }
        const float getNumberOfBirths(){
            return numOfBirths;
        }
        const float getNumberOfDeaths(){
            return numOfDeaths;
        }
        const float getBirthrate(){
            return float(numOfBirths) / float(population);
        }
        const float getDeathrate(){
            return float(numOfDeaths) / float(population);
        }
};

// # Prototypes #
int passer(string&&);                 // cin -> return
void tabler(string&&, float&& val );  // standard output

// Used to display request for desired value
// Returns said value
int passer(string&& prompt = "") {
    int toPass;
    cout << prompt << ": ";
    cin >> toPass;
    return toPass;
};

// To match formatting, width(8) and right were used
// This is just to standardize and reduce typing
void tabler(string&& rowName, float&& val ){
    cout << "\t\t" << rowName << ": ";
    cout.width(8); cout << right << val << "\n";
}


int main() {

    // Population poppo(500000, 7500, 8000);
    Population poppo;
    poppo.setPopulation(passer("Enter total population"));
    poppo.setNumOfBirths(passer("Enter annual number of births"));
    poppo.setNumOfDeaths(passer("Enter annual number of deaths"));

    cout << "\nPopulation Statistics\n\n";

    tabler("Population", poppo.getPopulation());
    tabler("Birth Rate", poppo.getBirthrate());
    tabler("Death Rate", poppo.getDeathrate());
    cout << endl;

    return 0;
}