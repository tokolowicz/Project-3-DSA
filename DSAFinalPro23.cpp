#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
//#include <string>
#include <sstream>
using namespace std;

class MovRateSys {
    struct Movie {
        string name;
        int id = 0;
        float rating = 0;
        vector<float> ratings;
        vector<string> genres;

    };

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
                    movie.id = stoi(data);                      //stored in movie.id
                    getline(str, data, ',');
                    movie.name = data;                          //next is name

                    getline(str, data, ',');                    //third is a list of genres
                    istringstream gen(data);                    //usable data
                    string genre;                               //temp storage of data

                    while (getline(gen, genre, '|')) {          //going through list of gen, storing each genre in the list
                        movie.genres.push_back(genre);
                    }
                  
                    movToID.emplace(movie.name, movie.id);      //storing what we have so far
                    IDtoMovInfo.emplace(movie.id, movie);

                    for (unsigned int i = 0; i < movie.genres.size(); i++) {         //all about the genre portion
                        if (movByGen.find(movie.genres.at(i)) == movByGen.end()) {      //if genre doesnt exist
                            movByGen.emplace(movie.genres.at(i),vector<int>());        //emplace 
                        }
    
                        movByGen.at(movie.genres.at(i)).push_back(movie.id);        //insert movie id into genre
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
                    IDtoMovInfo.at(movID).ratings.push_back(rating); //push back rating of the movie
                    
                }
                catch (...) {
                    cout << "oopsies" << endl;
                }

            }
            

        }

        for (auto& i : IDtoMovInfo) {
            float ratSum = 0;
            for (auto j : i.second.ratings) {
                ratSum = ratSum + j;
            }
           
            ratSum = ratSum / i.second.ratings.size();
            i.second.rating = ratSum;
        }


    }

    void outByGenre() {
        cout << "Input Genre: ";

        string genre;
        cin >> genre;

        /*more code here*/
    }

    void outMov() {
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

};


int main()
{
    MovRateSys help;
    help.readFile();

    int option = 0;
    cin >> option;

    if (option == 1) {
        help.outMov();
    }

    std::cout << "Hello World!\n";
}
