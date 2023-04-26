#include <fstream>
#include <sstream>
#include <windows.h>
#include <shellapi.h>
#include <chrono>
#include <iomanip>
#include "Movie.h"
using namespace std;

//Citations:
//https://stackoverflow.com/questions/17347950/how-do-i-open-a-url-from-c //used for displaying output of the URLs for the specific movies

class MovRateSys {

    unordered_map<string, int> movToID;  // <movieName, ID>
    unordered_map<int, Movie> IDtoMovInfo;   // <ID, movie object>
    unordered_map<string, vector<int>> movByGen;  // <Genre, vector<ID> in genre>

    void merge(vector<int>& sort, int start, int mid, int end) {
        vector<int> leftV(sort.begin() + start, sort.begin() + mid + 1); //makes a vector that houses the left side of the vector
        vector<int> rightV(sort.begin() + mid + 1, sort.begin() + end + 1); //makes a vector that houses the right side of the vector

        int leftI = 0; //values for holding the position for sorting of the vector
        int rightI = 0;
        int resultI = start;

        while (leftI < leftV.size() && rightI < rightV.size()) { //while neither positions are at the end of their vectors
            if (IDtoMovInfo[leftV[leftI]].getAvgRating() <= IDtoMovInfo[rightV[rightI]].getAvgRating()) { //if left's index's movie rating is less than right's index's movie rating
                sort[resultI] = leftV[leftI]; //put it as far to the left as possible
                leftI++;
            }
            else {
                sort[resultI] = rightV[rightI];
                rightI++;
            }
            resultI++; //goes to the next slot for insertion
        }

        while (leftI < leftV.size()) { //put the rest of the left vector into place
            sort[resultI] = leftV[leftI];
            leftI++;
            resultI++;
        }

        while (rightI < rightV.size()) { //put the rest of the right vector into place
            sort[resultI] = rightV[rightI];
            rightI++;
            resultI++;
        }
    }
    int partition(vector<int>& IDs, int low, int high) {
        //set pivot to first element, init pointers
        int pivot = IDs[low];
        int up=low, down=high;

        while(up < down) {
            //sorts greatest to least
            for (int j = up; j < high; j++) {
                //find first element greater than pivot
                if(IDtoMovInfo[IDs[up]].getAvgRating() < IDtoMovInfo[pivot].getAvgRating())
                    break;
                up++;
            }
            for (int j = high; j > low; j--) {
                //find first element less than pivot
                if(IDtoMovInfo[IDs[down]].getAvgRating() > IDtoMovInfo[pivot].getAvgRating())
                    break;
                down--;
            }
            //one pass of sorting
            if(up<down)
                swap(IDs[up], IDs[down]);
        }
        //move on to next element
        swap(IDs[low], IDs[down]);
        return down;
    }

public:
    void readFile() {

        ifstream inMovie("data/movies.csv");                    //opening file

        if (inMovie.is_open()) {
            string line;
            getline(inMovie, line);                             //getting header

            while (getline(inMovie, line)) {                    //line by line in file
                istringstream str(line);                        //converting to usable data
                string data;                                    //temp storage
                Movie movie;                                    //temp movie object

                try {
                    getline(str, data, ',');                    //first in, id
                    movie.setID(stoi(data));                      //stored in movie.id
                    getline(str, data, ',');
                    movie.setName(data);                          //next is name

                    getline(str, data, ',');                    //third is a list of genres
                    istringstream gen(data);                    //usable data
                    string genre;                               //temp storage of data

                    while (getline(gen, genre, '|')) {          //going through list of gen, storing each genre in the list
                        movie.setGenre(genre);
                    }

                    movToID.emplace(movie.getName(), movie.getID());      //storing what we have so far
                    IDtoMovInfo.emplace(movie.getID(), movie);

                    vector<string> v = movie.getGenres();
                    for (unsigned int i = 0; i < v.size(); i++) {         //all about the genre portion
                        if (movByGen.find(v.at(i)) == movByGen.end()) {      //if genre doesnt exist
                            movByGen.emplace(v.at(i), vector<int>());        //emplace
                        }

                        movByGen.at(v.at(i)).push_back(movie.getID());        //insert movie id into genre
                    }

                }
                catch (...) {
                    cout << "oopsies movies" << endl;
                }
            }
        }
        ifstream inRating("data/ratings.csv");                    //opening file

        if (inRating.is_open()) {
            string line;
            getline(inRating, line);                            //get header

            while (getline(inRating, line)) {
                istringstream str(line);
                string data;

                try {
                    getline(str, data, ',');            //userID, throaway
                    getline(str, data, ',');            //movieID
                    int movID = stoi(data);

                    getline(str, data, ',');            //rating
                    double rating = stod(data);
                    IDtoMovInfo.at(movID).setRatings(rating); //push back rating of the movie

                }
                catch (...) {
                    cout << "oopsies rating" << endl;
                }
            }
        }

        ifstream inLinks("data/links.csv");                    //opening file

        if (inLinks.is_open()) {
            string line;
            getline(inLinks, line);                            //get header

            while (getline(inLinks, line)) {
                istringstream str(line);
                string data;

                try {
                    getline(str, data, ',');            //movieID
                    int movID = stoi(data);

                    getline(str, data, ',');            //link
                    double link = stoi(data);
                    IDtoMovInfo.at(movID).setIMDB(link); //push back rating of the movie

                }
                catch (...) {
                    cout << "oopsies links" << endl;
                }
            }
        }

    }

    void outByGenre() {
        cout << "Input Genre: ";

        string genre;
        cin >> genre;

        /*more code here*/
    }

    vector<int> getMovies(vector<string> genres) {
        //first we need to get all of the possible movies with the selected genres into the v vector
        vector<int> gms = movByGen[genres[0]]; //holds all of the movies with a specific genre
        vector<int> sort; //holds all of the data for the possible movies
        if (genres.size() > 1) { //if there is more than one genre type selected
            for (int i = 0; i < gms.size(); i++) { //go through all of the first genre's values to see if each movie has all of the required genres
                bool gs = true; //holds a boolean to determine if all of the genres are met
                for (int j = 1; j < genres.size(); j++) { //check each movie for each genre, starting with the second one (presumably the first is the gms genre)
                    vector<string> v = IDtoMovInfo[gms[i]].getGenres();
                    if (find(v.begin(), v.end(), genres[j]) == v.end()) { //if it doesn't find the genre within that movie
                        gs = false;
                        break;
                    }
                }
                if (gs) { //if it found all of the genres within that one movie, then add it
                    sort.push_back(gms[i]);
                }
            }
        }
        else {
            sort = gms;
        }
        return sort;
    }
    void mergeSort(vector<int>& sort, int start, int end) {
        if (start < end) { //if the position in the vector is less than one space
            int mid = (start + end) / 2;
            mergeSort(sort, start, mid); //calls the left half again
            mergeSort(sort, mid + 1, end); //calls the right half again
            merge(sort, start, mid, end); //calls the sorting part of the merge
        }
    }
    void displayMerge(vector<int>& sort, double low, double high) { //loops through the sorted vector and prints out the names and average ratings of those movies within certain ranges
        for (int i = 0; i < sort.size(); i++) {
            double avg = IDtoMovInfo[sort[i]].getAvgRating();
            if (avg >= low && avg <= high) {
                cout << IDtoMovInfo[sort[i]].getName() << " " << fixed << setprecision(2) << avg << "\n";
            }
            else if (avg > high) { //it's larger than the greatest value required, cuts it short to save time
                break;
            }
        }
    }
    void quickSort(vector<int>& IDs, int low, int high) {
        //if there is more than one movie ID
        if (low < high) {
            //get pivot index
            int pivot = partition(IDs, low, high);
            //recursively sort left subarray
            quickSort(IDs, low, pivot - 1);
            //recursively sort right subarray
            quickSort(IDs, pivot + 1, high);
        }
    }
    void displayTest() {
        for (auto iter : IDtoMovInfo) {
            cout << iter.first << " " << iter.second.getName() << " " << iter.second.getAvgRating() << "\n";
        }
    }
    bool isValidGenre(string genre) {
        if (genre.compare("Compare") == 0)
            return true;
        else if (movByGen.find(genre) != movByGen.end())
            return true;
        else return false;
    }

    void findMovie(vector<string>& links) {
        while (true) {                               //loops until user decides to break
            string input;
            getline(cin, input);
            cout << "\n" << endl;

            if (input.length() == 0) {              //if the user clicks enter, go back to main
                return;
            }
            else if (input == "link") {             //if the types link, they will be given options for links to open

                while (true) {
                    if (links.size() > 1) {         //more then 1 link in list
                        cout << "Which would link would you like to open?" << endl;
                        cout << "TITLES: ";
                        for (int i = 0; i < links.size(); i++) {
                            cout << i + 1 << ", ";
                        }
                        cout << endl;

                        int title = 0;              //chosen option for link to open
                        cin >> title;
                        if (title != 0) {
                            ShellExecuteA(0, 0, links.at(title - 1).c_str(), 0, 0, SW_SHOW);        //opens link
                        }
                        else {
                            cout << "Please enter correct numerical option from above." << endl;
                            continue;
                        }

                        cout << "Would you like to open another link? (yes or no)" << endl;
                        string openAnother;
                        cin >> openAnother;
                        if (openAnother == "yes" || openAnother == "Yes") {
                            continue;
                        }
                        else {
                            cout << "Try another movie or go back by pressing enter!" << endl;
                            break;
                        }
                    }
                    else {
                        ShellExecuteA(0, 0, links.at(0).c_str(), 0, 0, SW_SHOW);            //opens link if only 1 option in vector
                        cout << "Try another movie or go back by pressing enter!" << endl;
                        break;
                    }
                }

                links.clear();                                                              //clears vector for next cycle
            }
            else {
                int counter = 0;                                                            //determines how many movies selected
                for (auto& i : movToID) {

                    if (i.first.find(input) != string::npos) {                              //if the current title contains a key word

                        Movie& movie = IDtoMovInfo[i.second];
                        counter++;
                        if (counter == 1) {
                            cout << "TITLES FOUND" << endl;
                        }

                        cout << counter << ": " << movie.getName() << endl;
                        cout << movie.getAvgRating() << endl;                               //outputs rating

                        for (int i = 0; i < movie.getGenres().size(); i++) {
                            cout << movie.getGenres().at(i) << ", ";                        //outputs genres
                        }
                        cout << endl;

                        string link = "https://www.imdb.com/title/tt0" + to_string(movie.getIMDB()) + "/";          //link needed to open + movie ID
                        links.push_back(link);                                                                      //stores links for use for option "Links"
                        cout << link << endl << endl;
                    }
                }
                if (!counter) {                                                                                     //if no title was found at all
                    cout << "Sorry! We couldn't find that title! Try another movie or go back by pressing enter" << endl;
                }
                else {
                    cout << "Try another movie or go back by pressing enter!" << endl;
                    cout << "(If you want to follow a link, type \"link\"!)" << endl;
                }
            }
        }
    }
};


int main()
{
    MovRateSys help;
    help.readFile();

    while (true) {
        cout << "What would you like to do?" << endl;
        cout << "Enter '1' to search for a movie" << endl;
        cout << "      '2' to search by genre" << endl;
        cout << "      '3' to exit this program" << endl;

        int option = 0;
        string line;
        getline(cin, line);
        option = stoi(line);
        if (option == 1) { //search specific movie
            cout << "Enter your movie or go back by pressing enter" << endl;
            vector<string> links;
            help.findMovie(links);
        }
        else if (option == 2) { //search by genre
            //Type in which genre/ genres are desired "Action Comedy"
            cout << "Type in your desired genre(s):\n";
            string line;
            getline(cin, line);
            istringstream iss(line);
            string genre;
            vector<string> gs;
            bool compare = false;
            bool validGenres = true;

            while (iss >> genre) {
                if (help.isValidGenre(genre))
                    gs.push_back(genre);
                else {
                    cout << "Invalid genre selected!\n";
                    validGenres = false;
                }
            }

            if (validGenres == true) {
                if (!gs.empty() && gs.at(gs.size() - 1).compare("Compare") == 0) { //checks to see if compare is the last value
                    gs.pop_back(); //pops off the compare value
                    compare = true; //sets a boolean so we know to compare the two sorting algorithms
                }

                vector<int> sort = help.getMovies(gs); //gives an unsorted vector of possible movie IDs
                vector<int> sort2 = sort;

                auto start = chrono::high_resolution_clock::now(); //start point before the mergesort happens

                help.mergeSort(sort, 0, sort.size() - 1); //do the mergesort (gets low -> high)

                auto stop = chrono::high_resolution_clock::now(); //end point after mergesort
                auto mergeDur = chrono::duration_cast<chrono::microseconds>(stop - start);

                //same process for quicksort
                auto start2 = chrono::high_resolution_clock::now();

                help.quickSort(sort2, 0, sort2.size() - 1);

                auto stop2 = chrono::high_resolution_clock::now();
                auto quickDur = chrono::duration_cast<chrono::microseconds>(stop - start);

                if (compare == true) { //if we are comparing, print out the times it takes to sort the two methods
                    cout << "Merge sort took " << mergeDur.count() << " microseconds and Quick sort took " << quickDur.count() << " microseconds.\n";
                }

                double low, high = -1.0;

                while (true) { //takes in lowest rating
                    cout << "Input lowest rating desired (0-5): \n";
                    getline(cin, line);
                    low = stoi(line);
                    if (low <= 5 && low >= 0)
                        break;
                }

                while (true) { //takes in highest rating
                    cout << "Input highest rating desired (0-5): \n";
                    getline(cin, line);
                    high = stoi(line);
                    if (high <= 5 && high >= 0 && high >= low)
                        break;
                }

                help.displayMerge(sort, low, high);
            }
        }
        else if (option == 3) { //exits program
            break;
        }
        else {
            cout << "Oops, invalid command. Try again.\n";
        }

        //ShellExecuteW(0, 0, L"http://www.google.com", 0, 0 , SW_SHOW );
        //ShellExecuteW(0, 0, L"https://www.imdb.com/title/tt0042451/", 0,0,SW_SHOW);
    }
}

