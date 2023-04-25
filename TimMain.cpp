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

    void merge(vector<int>& sort, int start, int mid, int end){
        vector<int> leftV(sort.begin() + start, sort.begin() + mid + 1); //makes a vector that houses the left side of the vector
        vector<int> rightV(sort.begin() + mid + 1, sort.begin() + end + 1); //makes a vector that houses the right side of the vector

        int leftI = 0; //values for holding the position for sorting of the vector
        int rightI = 0; 
        int resultI = start;

        while(leftI < leftV.size() && rightI < rightV.size()){ //while neither positions are at the end of their vectors
            if(IDtoMovInfo[leftV[leftI]].getAvgRating() <= IDtoMovInfo[rightV[rightI]].getAvgRating()){ //if left's index's movie rating is less than right's index's movie rating
                sort[resultI] = leftV[leftI]; //put it as far to the left as possible
                leftI++;
            }
            else{
                sort[resultI] = rightV[rightI];
                rightI++;
            }
            resultI++; //goes to the next slot for insertion
        }

        while(leftI < leftV.size()){ //put the rest of the left vector into place
            sort[resultI] = leftV[leftI];
            leftI++;
            resultI++;
        }

        while(rightI < rightV.size()){ //put the rest of the right vector into place
            sort[resultI] = rightV[rightI];
            rightI++;
            resultI++;
        }
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
                            movByGen.emplace(v.at(i),vector<int>());        //emplace 
                        }
    
                        movByGen.at(v.at(i)).push_back(movie.getID());        //insert movie id into genre
                    }

                }
                catch (...) {
                    cout << "oopsies" << endl;
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
                    cout << "oopsies" << endl;
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

    /*void outMov() {
        cout << "Input Title: ";

        string title;
        cin >> title;

        auto FI = movToID.find(title);

        if (FI != movToID.end()) {
            int id = FI->second;

            auto FM = IDtoMovInfo.find(id);

            cout << "We found your movie!";

            cout << FM->second.name << endl;
            cout << "The genres its associated with:" << endl;
            for (int i = 0; i < FM->second.genres.size(); i++) {
                cout << FM->second.genres.at(i) << " ";
            }
            cout << endl;
            cout << "The rating is: " << FM->second.rating << endl;
        }
        else {
            cout << "movie not in list." << endl;
        }



    }
*/
    vector<int> getMovies(vector<string> genres){
        //first we need to get all of the possible movies with the selected genres into the v vector
        vector<int> gms = movByGen[genres[0]]; //holds all of the movies with a specific genre
        vector<int> sort; //holds all of the data for the possible movies
        if(genres.size() > 1){ //if there is more than one genre type selected
            for(int i = 0; i < gms.size(); i++){ //go through all of the first genre's values to see if each movie has all of the required genres
                bool gs = true; //holds a boolean to determine if all of the genres are met
                for(int j = 1; j < genres.size(); j++){ //check each movie for each genre, starting with the second one (presumably the first is the gms genre)
                    vector<string> v = IDtoMovInfo[gms[i]].getGenres(); 
                    if(find(v.begin(), v.end(), genres[j]) == v.end()){ //if it doesn't find the genre within that movie
                        gs = false; 
                        break;
                    }
                }
                if(gs){ //if it found all of the genres within that one movie, then add it
                    sort.push_back(gms[i]);
                }
            }
        }
        else{
            sort = gms;
        }
        return sort;
    }
    void mergeSort(vector<int>& sort, int start, int end){
        if(start < end){ //if the position in the vector is less than one space
            int mid = (start + end) / 2;
            mergeSort(sort, start, mid); //calls the left half again
            mergeSort(sort, mid + 1, end); //calls the right half again
            merge(sort, start, mid, end); //calls the sorting part of the merge
        }
    }
    void displayMerge(vector<int>& sort, double low, double high){ //loops through the sorted vector and prints out the names and average ratings of those movies within certain ranges
        for(int i = 0; i < sort.size(); i++){
            double avg = IDtoMovInfo[sort[i]].getAvgRating();
            if(avg >= low && avg <= high){
                cout << IDtoMovInfo[sort[i]].getName() << " " << fixed << setprecision(2) << avg << "\n";
            }
            else if(avg > high){ //it's larger than the greatest value required, cuts it short to save time
                break;
            }
        }
    }
    void displayTest(){
        for(auto iter : IDtoMovInfo){
            cout << iter.first << " " << iter.second.getName() << " " << iter.second.getAvgRating() << "\n";
        }
    }

};


int main()
{
    MovRateSys help;
    help.readFile();

    while(true){
        
        int option = 0;
        string line;
        getline(cin, line);
        option = stoi(line);
        if(option == 1){ //search specific movie
            //Output:
                //Avg Rating
                //Genres of the Movie
                //Open a link to IMDB for the movie (option yes or no)
        }
        else if(option == 2){ //search by genre
            //Type in which genre/ genres are desired "Action Comedy"
            cout << "Type in your desired genre(s):\n";
            string line;
            getline(cin, line);
            istringstream iss(line);
            string genre;
            vector<string> gs;

            while(iss >> genre){
                gs.push_back(genre);
            }

            vector<int> sort = help.getMovies(gs); //gives an unsorted vector of possible movie IDs
            help.mergeSort(sort, 0, sort.size()-1); //do the mergesort (gets low -> high)

            //Tony put in the other sort here if you want (make a separate vector<int> variable for yours though)

            double low, high = -1.0;

            while(true){ //takes in lowest rating
                cout << "Input lowest rating desired (0-5): \n";
                getline(cin, line);
                low = stoi(line);
                if(low <= 5 && low >= 0)
                    break;
            }

            while(true){ //takes in highest rating
                cout << "Input highest rating desired (0-5): \n";
                getline(cin, line);
                high = stoi(line);
                if(high <= 5 && high >= 0 && high >= low)
                    break;
            }
            
            help.displayMerge(sort, low, high);
        }
        else if(option == 3){ //exits program
            help.displayTest();
            break;
        }
        else{
            cout << "Oops, invalid command. Try again.\n";
        }

        //ShellExecuteW(0, 0, L"http://www.google.com", 0, 0 , SW_SHOW );
        //ShellExecuteW(0, 0, L"https://www.imdb.com/title/tt0042451/", 0,0,SW_SHOW);

        std::cout << "Hello World!\n";
    }
}