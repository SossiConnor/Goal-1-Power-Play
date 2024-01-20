/*Connor Sossi
*19 Jan 2024
*CPSC 2376
*/

#include <iostream>
#include <vector>
#include <random>
#include <string>
using namespace std;

int main()
{
	random_device rdev;
	default_random_engine e(rdev());
	uniform_int_distribution<int> randomNumberOfMonsters(1, 3); // Gives a random number from 1-3.
	normal_distribution<double> randomHealth(30, 5); // Gives a random health mean 30, standard deviation 5.
	normal_distribution<double> randomStrength(5, 1); 
	bernoulli_distribution randomHit(.75); // Uses a Bernoulli distribution to give monsters a 75% chance to hit.

	int numberOfMonsters = randomNumberOfMonsters(e); //Runs to grab a random number of monsters
	int deadMonsters = 0; //Identifies how many monsters are dead in a run.

	struct Object
	{
		string name;
		int strength{ 0 };
		int health{ 0 };
	};

	Object Player; //Creates the Player object
	Player.name = "Fun Guy Name"; //Names it.
	do { //Loops atleast once, verifying that the health and strength are greater than 0.
		Player.strength = randomStrength(e); //Uses the random generators to make a strength.
		Player.health = randomHealth(e); //Same for health.
	} while (Player.strength <= 0 || Player.health <= 0);


	vector<Object> Monsters(numberOfMonsters); //Creates a vector of monsters with size of random monsters.

	for (int x = 0; x < numberOfMonsters; x++) // Same as Player, but loops for each monster in the vector.
	{
		Monsters.at(x).name = "Monster" + to_string(x + 1);
		do
		{
			Monsters.at(x).strength = randomStrength(e);
			Monsters.at(x).health = randomHealth(e);
		} while (Monsters.at(x).strength <= 0 || Monsters.at(x).health <= 0);
	}

	do {
		deadMonsters = 0; //sets deadMonsters to 0 at start of each interation to check for wincon.
		cout << Player.name + "'s current health is " + to_string(Player.health) + "\n"; //Displays Player's current Health.
		for (int x = 0; x < numberOfMonsters; x++) // Checks and displays current health of each monster
		{
			if (Monsters.at(x).health <= 0)
			{
				cout << Monsters.at(x).name + " is <DEAD>\n";
				deadMonsters++; // Adds +1 to dead monsters if one is dead.
			}
			else
			{
				cout << Monsters.at(x).name + "'s current health is " + to_string(Monsters.at(x).health) + "\n";
			}
		}
		if (deadMonsters != numberOfMonsters) // Checks if all the monsters are dead.
		{
			cout << "\nWould you like to attack or heal?\n";
			string answer;
			cin >> answer;
			if (answer == "heal") //Heals if user enters heal.
			{
				Player.health += Player.strength * 2; // Heals the player for double their strength.
			}
			else if (answer == "attack")
			{
				cout << "Choose a Monster's number to attack!\n"; //Allows user to attack a target
				int attackMonster;
				cin >> attackMonster;
				while (attackMonster > numberOfMonsters || Monsters.at(attackMonster - 1).health <= 0) //Checks if target is legitimate.
				{
					cout << "Please choose a monster available and alive!\n";
					cin >> attackMonster;
				}
				Monsters.at(attackMonster - 1).health = Monsters.at(attackMonster - 1).health - Player.strength; //Removes health from said target equal to Player's str.
			}
			for (int x = 0; x < numberOfMonsters; x++)
			{
				if (Monsters.at(x).health > 0)
				{
					if (randomHit(e) == true) //Uses the random generator to check if each monster hits the Player.
					{
						Player.health -= Monsters.at(x).strength; // If it does it will remove the Health of the Player equal to the Monsters str.
						cout << Monsters.at(x).name + " hit you for " + to_string(Monsters.at(x).strength) + "!\n";
					}
				}
			}
		}
	} while (Player.health > 0 && deadMonsters != numberOfMonsters); // If the player dies, or all monsters are defeated, the loop ends.
	if (deadMonsters == numberOfMonsters) // If the Player kills all monsters they win.
	{
		cout << "Congratulations! You win!";
	}
	else // if not they die.
	{
		cout << "You have died!";
	}
}