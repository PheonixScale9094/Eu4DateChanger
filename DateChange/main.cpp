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
const fs::path myPath = "E:/Converters/DateChange/DateChange/DateChange/files";
//const fs::path myPath = "C:/Users/9094c/OneDrive/Documents/Paradox Interactive/Europa Universalis IV/mod/1265/history/countries";
//Funtion Prototype
void wait();

//Main Funtion
int main()
{
	int endDate = 0;
	fs::path myPath = "E:/Converters/DateChange/DateChange/DateChange/files";

	int yearsToAdd = 0;
	int filesProcessed = 0;
	int datesChanged = 0;
	ifstream fin;
	ofstream fout;
	ifstream tin;
	ofstream tout;
	string currentLine;
	const string birthdateToken = "birth_date = ";
	const string deathdateToken = "death_date = ";

	//User Prompts
	cout << "Enter the full filepath (using /): " << endl;
	cin >> myPath;
	cout << "Enter the year of conversion: " << endl;
	cin >> endDate;	

	//Calculate years to add
	yearsToAdd = 1444 - endDate;

	cout << "This will add " << yearsToAdd << "years to all birthdays" << endl;
	wait();

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

				size_t bday = currentLine.find(birthdateToken); //Looks for Birthday
				size_t dday = currentLine.find(deathdateToken); //Looks for Deathday
				size_t currentdate = currentLine.find(to_string(END_DATE)); //Looks for endDate
				if (bday != std::string::npos || dday != std::string::npos || currentdate != std::string::npos) {
					cout << currentLine << endl; // Original String


					size_t yearLoc = currentLine.find('.') - 4; //Looks for year dot

					string yearString = currentLine.substr(yearLoc, 4); //Makes string of the Year
					stringstream yearStream(yearString); //Makes StringStream of the Year
					int year = 0;
					yearStream >> year;

					year += yearsToAdd;

					currentLine.replace(yearLoc, 4, to_string(year));

					datesChanged += 1;
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
			filesProcessed += 1;
			cout << "closed " << dirEntry.path().filename() << endl;
		}
	}

	//output how many dates and files were processed
	cout << endl << "Files processed: " << filesProcessed << endl;
	cout << endl << "Dates changed: " << datesChanged << endl;

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