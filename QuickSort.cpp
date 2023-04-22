#include "movie.h"
/*takes in a vector of movie IDs, a start and stop index, and an unordered map of ID keys and movie name values
sorts greatest to least based on average movie rating*/
void quickSort(vector<int>& IDs, int low, int high, unordered_map<int, Movie>& _movies);
int partition(vector<int>& IDs, int low, int high, unordered_map<int, Movie>& _movies);

void quickSort(vector<int>& IDs, int low, int high, unordered_map<int, Movie>& _movies) {
    //if there is more than one movie ID
    if (low < high) {
        //get pivot index
        int pivot = partition(IDs, low, high, _movies);
        //recursively sort left subarray
        quickSort(IDs, low, pivot - 1, _movies);
        //recursively sort right subarray
        quickSort(IDs, pivot + 1, high, _movies);
    }
}
int partition(vector<int>& IDs, int low, int high, unordered_map<int, Movie>& _movies) {
    //set pivot to first element, init pointers
    int pivot = IDs[low];
    int up=low, down=high;

    while(up < down) {
        //sorts greatest to least
        for (int j = up; j < high; j++) {
            //find first element greater than pivot
            if(_movies[IDs[up]].getAvgRating() < _movies[pivot].getAvgRating())
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            //find first element less than pivot
            if(_movies[IDs[down]].getAvgRating() > _movies[pivot].getAvgRating())
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