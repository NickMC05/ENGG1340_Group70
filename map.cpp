#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
using namespace std;

class MAP {
    private: 
        tuple straight = [
            (0.0f, 10.0f),
            (0.0f, 50.0f), 
            (0.0f, 100.0f),
            (0.0f, 200.0f)
            ];
        tuple left = [
            (0.25f, 200.0f),
            (0.5f, 200.0f),
            (0.5f, 400.0f),
            (1.0f, 200.0f),
            (1.0f, 400.0f),
            ];
        tuple right = [
            (0.25f, 200.0f),
            (0.5f, 200.0f),
            (0.5f, 400.0f),
            (1.0f, 200.0f),
            (1.0f, 400.0f),
            ];
        array roadArray = [straight, left, right];
        int courseLength = 5000.0f;


    
    public:
        vector makeMap(){
            vector<pair<float, float>> track;
            track.push_back(make_pair(*roadArray[0][0]));
            int distance = 0;
            for (int currdistance = 10; currdistance <= courseLength; currdistance += distance){
                int directionIndex = rand() % 4;      
                int sectionIndex = rand() % (sizeof(roadArray[directionIndex]) + 1);
                tuple section = roadArray[directionIndex][sectionIndex]
                track.push_back(make_pair(*section));
                distance += section[1];
            }
            }
};
int main(){
    vector<pair<float, float>> vecTrack;
    vecTrack.push_back(make_pair(2.0f, 10.0f));  
    cout << vecTrack[0].first;
}