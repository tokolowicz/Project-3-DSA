#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

class Movie{
    //private variables of the class
    private:
        string name;
        int ID;
        vector<double> ratings;
        vector<string> genres;
    public:
        Movie(string name, int ID, vector<string> genres){ //constructor
            this->name = name;
            this->ID = ID;
            this->genres = genres;
            this->ratings; // I think this may initialize the vector so we can insert stuff without initialization?
        }
        //getter methods for all of the variables
        string getName(){
            return this->name;
        }
        int getID(){
            return this->ID;
        }
        vector<string> getGenres(){
            return this->genres;
        }
        vector<double> getRatings(){
            return this->ratings;
        }
        //setter methods for all of the variables needed
        void setRatings(double rating){
            this->ratings.push_back(rating);
        }
};