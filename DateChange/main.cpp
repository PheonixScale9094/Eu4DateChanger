//Preprocessing Statements
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>

//Namespaces
using namespace std;
namespace fs = std::filesystem;

//Constants
const int END_DATE = 1229;
const fs::path myPath = "E:\Converters\DateChange\DateChange\DateChange\files";

//Funtion Prototype
void wait();

//Main Funtion
int main()
{
	ifstream fin;
	ofstream fout;
	ifstream tin;
	ofstream tout;
	string currentLine;
	const string birthdateToken = "birth_date = ";
	const string deathdateToken = "death_date = ";

	int yearsToAdd;
	//Calculate years to add
	yearsToAdd = 1444 - END_DATE;

	cout << "Time being added = " << yearsToAdd << endl;
	
	const string extension{ ".txt" };
	int number{ 0 };
	// iterate through all the files in the directory
	for (const auto& dirEntry : fs::directory_iterator(myPath))
	{
		// if the file is to be changed
		if (fs::is_regular_file(dirEntry) && dirEntry.path().extension() == extension)
		{
			fin.open(dirEntry);
			cout << "opened " << dirEntry.path().filename() << endl;
			tout.open("temp.txt");

			while (!fin.eof())      //if not at end of file, continue reading
			{
				getline(fin, currentLine);

				size_t found = currentLine.find(birthdateToken); //Looks for Birthday
				if (found == std::string::npos) {
					size_t found = currentLine.find(deathdateToken);
				}
				if (found != std::string::npos) {
					cout << currentLine << endl; // Original String


					size_t yearLoc = currentLine.find('.') - 4; //Looks for year dot

					string yearString = currentLine.substr(yearLoc, 4); //Makes string of the Year
					stringstream yearStream(yearString); //Makes StringStream of the Year
					int year = 0;
					yearStream >> year;

					year += yearsToAdd;

					currentLine.replace(yearLoc, 4, to_string(year));
					
					cout <<	"		converted to" << endl << currentLine << endl << endl; // new String
				}

				tout << currentLine << endl;
				
			}
			tout.close();
			fin.close();
			fout.open(dirEntry);
			tin.open("temp.txt");

			while (!tin.eof()) {
				getline(tin, currentLine);
				fout << currentLine << endl;
			}

			fout.close();
			tin.close();
			cout << "closed " << dirEntry.path().filename() << endl;
		}
	}

	//Closing Statements
	tin.close();
	tout.close();
	fin.close();
	fout.close();
	remove("temp.txt");
	wait();
	return 0;
}

void wait()
{
	//The following if-statement checks to see how many characters are in cin's buffer
	//If the buffer has characters in it, the clear and ignore methods get rid of them.
	if (cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clear the input buffer 
	}
	char ch;
	cout << "Press the Enter key to continue ... ";
	cin.get(ch);
}