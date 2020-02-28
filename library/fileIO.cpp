#include "../includes_usr/fileIO.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>

#include "../includes_usr/constants.h"
#include "../includes_usr/datastructures.h"

using namespace std;
const char CHAR_TO_SEARCH_FOR = ',';
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{

	books.clear();
	ifstream inputfile;
	inputfile.open(filename);

	if (!inputfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	string token;

	stringstream ss;
	while (!inputfile.eof()) {
		getline(inputfile, line);
		ss.str(line);
		book bookData;

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		if (token.empty()) {
			break;
		}
		bookData.book_id = atoi(token.c_str());

		getline(ss, bookData.title, CHAR_TO_SEARCH_FOR);

		getline(ss, bookData.author, CHAR_TO_SEARCH_FOR);

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		int tempToken = atoi(token.c_str());
		bookData.state = static_cast<book_checkout_state>(tempToken);

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		bookData.loaned_to_patron_id = atoi(token.c_str());

		books.push_back(bookData);

		ss.clear();
	}
	if (books.empty()) {
		return NO_BOOKS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream inputfile;
	inputfile.open(filename);
	if (!inputfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	string bookData;
	for (book b: books) {
		bookData = to_string(b.book_id) + "," + b.title + "," + b.author + "," +
				to_string(b.state) + "," + to_string(b.loaned_to_patron_id);
		inputfile<<bookData<<endl;
	}

	if (inputfile.is_open()) {
		inputfile.close();
	}
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	patrons.clear();
	ifstream inputfile;
	inputfile.open(filename);

	if (!inputfile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	string token;

	stringstream ss;
	while (!inputfile.eof()) {
		getline(inputfile, line);
		ss.str(line);
		patron patronData;

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		if (token.empty()) {
			break;
		}
		patronData.patron_id = atoi(token.c_str());

		getline(ss, patronData.name, CHAR_TO_SEARCH_FOR);

		getline(ss, token, CHAR_TO_SEARCH_FOR);
		patronData.number_books_checked_out = atoi(token.c_str());

		patrons.push_back(patronData);
		ss.clear();
	}
	if (patrons.empty()) {
		return NO_PATRONS_IN_LIBRARY;
	}
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	ofstream inputfile;
	inputfile.open(filename);
	if (!inputfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	string patronData;
	for (patron p : patrons) {
		patronData = to_string(p.patron_id) + "," + p.name + "," + to_string(p.number_books_checked_out);
		inputfile<<patronData<<endl;
	}
	if (inputfile.is_open()) {
		inputfile.close();
	}
	return SUCCESS;
}
