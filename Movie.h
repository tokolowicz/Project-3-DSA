#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

class Movie{
    //private variables of the class
    private:
        string name;
        int ID;
        vector<double> ratings;
        double totalRatings; //holds the total sum of the ratings vector
        double avgRating; //holds the average of the ratings vector
        vector<string> genres;
        int IMDB; //holds IMDB id
    public:
        Movie(); 
        Movie(string name, int ID, vector<string> genres);
        string getName();
        int getID();
        vector<string> getGenres();
        vector<double> getRatings();
        double getAvgRating();
        void setRatings(double rating);
        void setID(int ID);
        void setName(string name);
        void setGenre(string genre);
        void setIMDB(int ID);
        int getIMDB();

        
};
Movie::Movie(){
    this->name = "Fake Movie";
    this->ID = 9999999;
    this->avgRating = 0;
    this->totalRatings = 0;
    this->genres = {"Swag", "Bimbo", "Suckotash"};
    this->ratings;
}
Movie::Movie(string name, int ID, vector<string> genres){ //constructor
    this->name = name;
    this->ID = ID;
    this->genres = genres;
    this->ratings; // I think this may initialize the vector so we can insert stuff without initialization?
    this->avgRating = 0;
    this->totalRatings = 0;
}
//getter methods for all of the variables
string Movie::getName(){
    return this->name;
}
int Movie::getID(){
    return this->ID;
}
vector<string> Movie::getGenres(){
    return this->genres;
}
vector<double> Movie::getRatings(){
    return this->ratings;
}
double Movie::getAvgRating(){
    return this->avgRating;
}
//setter methods for all of the variables needed
void Movie::setRatings(double rating){
    this->ratings.push_back(rating);
    this->totalRatings += rating;
    this->avgRating = totalRatings / this->ratings.size();
}
void Movie::setID(int ID){
    this->ID = ID;
}
void Movie::setName(string name){
    this->name = name;
}
void Movie::setGenre(string genre){
    this->genres.push_back(genre);
}
void Movie::setIMDB(int ID){
    this->IMDB = ID;
}
int Movie::getIMDB(){
    return this->IMDB;
}