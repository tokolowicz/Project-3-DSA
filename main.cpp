#include <fstream>
//#include <string>
#include <sstream>
#include <windows.h>
#include <shellapi.h>
#include <chrono>
#include "Movie.h"
using namespace std;

//Citations:
    //https://stackoverflow.com/questions/17347950/how-do-i-open-a-url-from-c //used for displaying output of the URLs for the specific movies

class MovRateSys {
    /*struct Movie {
        string name;
        int id = 0;
        float rating = 0;
        vector<float> ratings;
        vector<string> genres;

    };*/

    unordered_map<string, int> movToID;  // <movieName, ID>
    unordered_map<int, Movie> IDtoMovInfo;   // <ID, movie object>
    unordered_map<string, vector<int>> movByGen;  // <Genre, vector<ID> in genre>

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
                    float rating = stof(data);
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
};


int main()
{
    MovRateSys help;
    help.readFile();

    while(true){

        
        int option = 0;
        
        cin >> option;
        if(option == 1){ //search specific movie
            //Output:
                //Avg Rating
                //Genres of the Movie
                //Open a link to IMDB for the movie (option yes or no)
        }
        else if(option == 2){ //search by genre
            //Type in which genre/ genres are desired "Action Comedy"
            //Input lowest rating desired (0-5)
            //Input highest rating desired (0-5)
                //Output: (only mergesort prints out to the user)
                        //Movie Name Avg Rating (2 decimal) 
        }

        //ShellExecuteW(0, 0, L"http://www.google.com", 0, 0 , SW_SHOW );
        //ShellExecuteW(0, 0, L"https://www.imdb.com/title/tt0042451/", 0,0,SW_SHOW);

        std::cout << "Hello World!\n";
    }
}