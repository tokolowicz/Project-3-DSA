#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
#pragma once

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
