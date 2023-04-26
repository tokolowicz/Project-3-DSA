#include "Movie.h"
Movie::Movie(){
    this->name = "Movie";
    this->ID = 0;
    this->avgRating = 0;
    this->totalRatings = 0;
    this->genres = {};
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