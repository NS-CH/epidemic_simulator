// ADD ALL THE HEADER FILES

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>

// USE NAMESPACE STD
using namespace std;

// CREATE DIFFERENT STATES FOR PERSONS
enum State { Susceptible=0, Infected=1, Recovered=2, Deceased=3 };

// CREATE THE PERSON CLASS
class Person {
    public:
        // Define characteristics such as state and days since infected
        State state;
        int daysInfected;

        // Initialise initial characterisitcs
        Person() : state(Susceptible), daysInfected(0) {}
};

// CREATE THE EPIDEMIC SIMULATOR CLASS
class EpidemicSimulator {
    // Initialise simulation characteristics
    private:
        vector<Person> population;
        int startingInfectedPopulation;
        double infectionRate;
        double recoveryRate;
        double deathRate;
        int duration;
        int personInteractionAmount;
        int populationSize;

    public:
        // Epidemic Simulator Constructor
        /* 
        This is the constructor where the simulation properties are initialised. This is where the simulation
        independent variables are defined. User will be asked to input, which will edit these properties.
        populationSize (Amount of Persons in the simulation.)
        infRate (Rate at random that when a person comes in contact with an infected person that they themselves
        will become infected.)
        recRate (Chance rolled at every iteration of simulation on whether an infected person will recover or not.)
        deathChance (Chance rolled at every iteration of simulation on whether an infected person will die or not.)
        simDuration (Amount of iterations the simulation will run for. This duration will be cut short if
        simulation is terminated)
        startingInfPop (amount of people on first iteration who are already infected.)
        personIntAmount (amount of people a person will interact with.)
        */
        EpidemicSimulator(int populationSize, double infRate, double recRate, double deathChance, int simDuration, int startingInfPop, int personIntAmount)
        : infectionRate(infRate), recoveryRate(recRate), deathRate(deathChance), duration(simDuration), startingInfectedPopulation(startingInfPop), personInteractionAmount(personIntAmount), populationSize(populationSize)
        {
            // Loops for the population size. Will create a person in the vector for the size of population.
            for (int i = 0; i < populationSize; i++)
            {
                // Pushes a Person Object to the vector for population size.
                population.push_back(Person());
            }

            // Randomly selects a group of people to be infected by default.
            for (int i = 0; i < startingInfPop; i++)
            {
                while (true)
                {
                    int randomSelectedPerson = rand() % populationSize;
                    if (population[randomSelectedPerson].state != Infected)
                    {
                        population[randomSelectedPerson].state = Infected;
                        break;
                    }
                }
            }
        }

        // Simulation Function
        void simulate()
        {
            // Loop for days (simulation iterations) of the simulation duration.
            for (int day = 0; day < duration; day++)
            {
                // Update Infected Individuals
                // Loops through every person in population
                for (auto& person : population)
                {
                    // Checks if person is infected
                    if (person.state == Infected)
                    {
                        // Adds to the amount of days they have been infected
                        person.daysInfected++;
                        // Rolls random chance to decide if they will recover or not
                        if ((double)rand() / RAND_MAX < recoveryRate)
                        {
                            // Sets state to recovered
                           person.state = Recovered; 
                        }
                        // Rolls random chance to decide if they will die or not
                        else if ((double)rand() / RAND_MAX < deathRate)
                        {
                            // Sets state to Deceased
                            person.state = Deceased;
                        }
                    }
                }

                // Update for Susceptible Individuals
                // Loops through every person in population
                for (auto& person : population)
                {
                    // Checks if they are susceptible
                    if (person.state == Susceptible)
                    {
                        // Loops for the amount of interactions a person has
                        for (int i = 0; i < personInteractionAmount; i++)
                        {
                            // Checks if the person they have interacted with are infected
                            if (population[rand() % populationSize].state == Infected)
                            {
                                // Rolls random chance to see if they will be infected.
                                if ((double)rand() / RAND_MAX <= infectionRate)
                                {
                                    // Sets state to Infected
                                    person.state = Infected;
                                }
                            }
                        } 
                    }
                }
                // Reports for this iteration of the simulation
                report(day);
            }
        }

        // Iteration Report Function - Reports the changes and statistics for this iteration of the simulation
        void report(int day)
        {
            int susceptibleCount = 0;
            int infectedCount = 0;
            int recoveredCount = 0;
            int deceasedCount = 0;

            // Loops through every person in the population
            for (const auto& person : population)
            {
                // Checks if they are susceptible
                if (person.state == Susceptible)
                {
                    // Adds one to susceptible count
                    susceptibleCount++;
                }
                // Checks if they are infected
                else if (person.state == Infected)
                {
                    // Adds one to infected count
                    infectedCount++;
                }
                // Checks if they are recovered
                else if (person.state == Recovered)
                {
                    // Adds one to recovered count
                    recoveredCount++;
                }
                // Checks if they are deceased
                else if (person.state == Deceased)
                {
                    // Adds one to deceased count
                    deceasedCount++;
                }
            }

            cout << "Day " << day << " Report: " << '\n';
            cout << "Susceptible Count: " << susceptibleCount << '\n';
            cout << "Infected Count: " << infectedCount << '\n';
            cout << "Recovered Count: " << recoveredCount << '\n';
            cout << "Deceased Count: " << deceasedCount << '\n';
            cout << " " << endl;
        }
};

int main()
{
    srand(time(0));

    double userSelectedInfectionRate;
    double userSelectedRecoveryRate;
    double userSelectedDeathRate;
    int userSelectedPersonInteractionAmount;
    int userSelectedPopulationSize;
    int userSelectedStartingInfectionAmount;
    int userSelectedSimDuration;

    cout << "What would you like the infection rate to be? (Enter percentage in decimal format.): ";
    cin >> userSelectedInfectionRate;

    cout << "What would you like the recovery rate to be? (Enter percentage in decimal format.): ";
    cin >> userSelectedRecoveryRate;

    cout << "What would you like the death rate to be? (Enter percentage in decimal format.): ";
    cin >> userSelectedDeathRate;

    cout << "What would you like the person interaction amount to be (the amount of people a person interacts with each iteration.): ";
    cin >> userSelectedPersonInteractionAmount;

    cout << "What would you like the population size to be?: ";
    cin >> userSelectedPopulationSize;

    cout << "What would you like the starting infected amount to be? (the amount of people who are already infected on the first iteration): ";
    cin >> userSelectedStartingInfectionAmount;

    cout << "What would you like the sim duration to be? (the amount of iterations the simulation will go through): ";
    cin >> userSelectedSimDuration;

    EpidemicSimulator simulator(userSelectedPopulationSize, userSelectedInfectionRate, userSelectedRecoveryRate, userSelectedDeathRate, userSelectedSimDuration, userSelectedStartingInfectionAmount, userSelectedPersonInteractionAmount);
    simulator.simulate();

    cout << "************************" << '\n';
    cout << "Press any Key to exit.";
    cin.ignore();
    cin.get();
    return 0;
}