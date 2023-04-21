#include "Movie.h"

unordered_map<string, vector<int>> genres;
unordered_map<int, Movie> movies;
void mergeSort(vector<int>& sort, int start, int end, unordered_map<int, Movie>& movies); 
//this is the mergesort function, it takes in a single genre of movie numbers (first one entered by user I assume) and a start/end of the point in the vector
void merge(vector<int>& sort, int start, int mid, int end, unordered_map<int, Movie>& movies); //this is the recursive call of the function that actually sorts it
vector<int> getMovies(vector<int> gms, unordered_map<int, Movie>& movies, vector<string> genres);
//this is the function that gets the correct movies for the sorting part, if it has more than one genre

//just using this for testing of sorts
int main(){

    vector<string> gs; //holds the genres for testing purposes for insertion in the 
    genres["Adventure"] = {1, 2, 8, 10};
    genres["Animation"] = {1};
    genres["Children"] = {1, 2, 8};
    genres["Comedy"] = {1, 3, 4, 5, 7};
    genres["Fantasy"] = {1, 2};
    genres["Romance"] = {3, 4, 7};
    genres["Drama"] = {4};
    genres["Action"] = {6, 9, 10};
    genres["Thriller"] = {6, 10};
    genres["Crime"] = {6};
    gs = {"Adventure", "Animation", "Children", "Comedy", "Fantasy"};
    //creating a movie
    Movie m = Movie("Toy Story", 1, gs);
    //just grabbing a few ratings for each one, I got these from the ratings csv but that took a while, so just bs it
    m.setRatings(4.0);
    m.setRatings(2.5);
    m.setRatings(4);
    m.setRatings(2.5);
    m.setRatings(4);
    //rating average should be 3.4
    movies[1] = m;
    gs.clear();
    gs = {"Adventure", "Children", "Fantasy"};
    Movie m2 = Movie("Jumanji", 2, gs);
    m2.setRatings(4.0);
    m2.setRatings(5);
    m2.setRatings(1);
    m2.setRatings(1);
    m2.setRatings(3);
    //rating average should be 2.8
    movies[2] = m2;
    gs.clear();
    gs = {"Comedy", "Romance"};
    Movie m3 = Movie("Grumpier", 3, gs);
    m3.setRatings(1);
    m3.setRatings(1);
    m3.setRatings(2);
    //rating average should be 1.3
    movies[3] = m3;
    gs.clear();
    gs = {"Comedy", "Drama", "Romance"};
    Movie m4 = Movie("Waiting to Exhale (1995)", 4, gs);
    m4.setRatings(3);
    m4.setRatings(2);
    m4.setRatings(1);
    movies[4] = m4;
    //rating average should be 2.0
    gs.clear();
    gs = {"Comedy"};
    Movie m5 = Movie("Father of the Bride Part II (1995)", 5, gs);
    m5.setRatings(5);
    m5.setRatings(4);
    m5.setRatings(5);
    //rating average should be 4.67
    movies[5] = m5;
    gs.clear();
    gs = {"Action", "Crime", "Thriller"};
    Movie m6 = Movie("Heat (1995)", 6, gs);
    m6.setRatings(4);
    m6.setRatings(4);
    m6.setRatings(3);
    //average should be 3.67
    movies[6] = m6;
    gs.clear();
    gs = {"Comedy", "Romance"};
    Movie m7 = Movie("Sabrina (1995)", 7, gs);
    m7.setRatings(3);
    m7.setRatings(1);
    m7.setRatings(1);
    //average should be 1.67
    movies[7] = m7;
    gs.clear();
    gs = {"Adventure", "Children"};
    Movie m8 = Movie("Tom and Huck (1995)", 8, gs);
    m8.setRatings(3);
    m8.setRatings(1);
    m8.setRatings(2.5);
    //average should be 2.17
    movies[8] = m8;
    gs.clear();
    gs = {"Action"};
    Movie m9 = Movie("Sudden Death (1995)", 9, gs);
    m9.setRatings(5);
    m9.setRatings(5);
    m9.setRatings(5);
    //average is 5
    movies[9] = m9;
    gs.clear();
    gs = {"Action", "Adventure", "Thriller"};
    Movie m10 = Movie("GoldenEye (1995)", 10, gs);
    m10.setRatings(3);
    m10.setRatings(3);
    m10.setRatings(3);
    //average is 3
    movies[10] = m10;

    vector<int> sort = genres["Comedy"];
    mergeSort(sort, 0, sort.size() - 1, movies);
    for(int i = 0; i < sort.size(); i++){
        cout << sort[i] << " " << movies[sort[i]].getAvgRating() << "\n";
    }

    //sorting should go as follows
    // 9 (5), 5(4.67), 6(3.67), 1(3.4), 10(3), 2(2.8), 8(2.17), 4(2), 7(1.67), 3(1.3) 
    return 0;
}
vector<int> getMovies(vector<int> gms, unordered_map<int, Movie>& movies, vector<string> genres){
    //first we need to get all of the possible movies with the selected genres into the v vector
    vector<int> sort; //holds all of the data for the possible movies
    if(genres.size() > 1){ //if there is more than one genre type selected
        for(int i = 0; i < gms.size(); i++){ //go through all of the first genre's values to see if each movie has all of the required genres
            bool gs = true; //holds a boolean to determine if all of the genres are met
            for(int j = 1; j < genres.size(); j++){ //check each movie for each genre, starting with the second one (presumably the first is the gms genre)
                vector<string> v = movies[gms[i]].getGenres(); 
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
void mergeSort(vector<int>& sort, int start, int end, unordered_map<int, Movie>& movies){
    if(start < end){ //if the position in the vector is more than one space
        int mid = (start + end) / 2;
        mergeSort(sort, start, mid, movies); //calls the left half again
        mergeSort(sort, mid + 1, end, movies); //calls the right half again
        merge(sort, start, mid, end, movies); //calls the sorting part of the merge
    }
}
void merge(vector<int>& sort, int start, int mid, int end, unordered_map<int, Movie>& movies){
    vector<int> leftV(sort.begin() + start, sort.begin() + mid + 1); //makes a vector that houses the left side of the vector
    vector<int> rightV(sort.begin() + mid + 1, sort.begin() + end + 1); //makes a vector that houses the right side of the vector

    int leftI = 0; //values for holding the position for sorting of the vector
    int rightI = 0; 
    int resultI = start;

    while(leftI < leftV.size() && rightI < rightV.size()){ //while neither positions are at the end of their vectors
        if(movies[leftV[leftI]].getAvgRating() <= movies[rightV[rightI]].getAvgRating()){ //if left's index's movie rating is less than right's index's movie rating
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
