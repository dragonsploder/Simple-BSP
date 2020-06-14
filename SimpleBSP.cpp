#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include <cstring>

using namespace std;

void printMap(vector<vector<int> > &mapMatrix){
    int hight = mapMatrix.size();
    int width = mapMatrix[0].size();
    for (int h = 0; h < hight; h++){
        for (int w = 0; w < width; w++){
            if (mapMatrix[h][w] == 1){
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}


void binarySpacePartitioning(vector<vector<int> > &mapMatrix, int iterations, bool fullWalls, int minWallDist){
    int hight = mapMatrix.size() - 1;
    int width = mapMatrix[0].size() - 1;
    vector<vector<int> > roomCoordinates;
    vector<vector<int> > newRoomCoordinates;
    //Format = X1,Y1,X2,Y2
    roomCoordinates.push_back({0, 0, width, hight});
    for (int i = 0; i < iterations; i++){
        for (int room = 0; room < roomCoordinates.size(); room++){
            int roomWidth = (roomCoordinates[room][2] - roomCoordinates[room][0]);
            int roomHight = (roomCoordinates[room][3] - roomCoordinates[room][1]);
            int r = rand() % (roomHight + roomWidth);

            if (r <= roomHight){ 
                if ((minWallDist + 1) * 2 < roomHight && roomHight >= 4){
                    int lineY = (rand() % (roomHight - (2 * minWallDist))) + minWallDist;
        
                    newRoomCoordinates.push_back({roomCoordinates[room][0], roomCoordinates[room][1], roomWidth + roomCoordinates[room][0], lineY + roomCoordinates[room][1]});
                    newRoomCoordinates.push_back({roomCoordinates[room][0], lineY + roomCoordinates[room][1], roomWidth + roomCoordinates[room][0], roomHight + roomCoordinates[room][1]});
                }
            } else {
                if ((minWallDist + 1) * 2 < roomWidth && roomWidth >= 4){
                    int lineX = (rand() % (roomWidth - (2 * minWallDist))) + minWallDist;

                    newRoomCoordinates.push_back({roomCoordinates[room][0], roomCoordinates[room][1], lineX + roomCoordinates[room][0], roomHight + roomCoordinates[room][1]});
                    newRoomCoordinates.push_back({lineX + roomCoordinates[room][0], roomCoordinates[room][1], roomWidth + roomCoordinates[room][0], roomHight + roomCoordinates[room][1]});
                }
            }
        }
        roomCoordinates.clear();
        for (int i = 0; i < newRoomCoordinates.size(); i++){
            roomCoordinates.push_back(newRoomCoordinates[i]);
        }
        newRoomCoordinates.clear();
    }
    if (fullWalls){
        roomCoordinates.push_back({0, 0, width, hight});
    }

    
    for (int room = 0; room < roomCoordinates.size(); room++){
        int x1 = roomCoordinates[room][0];
        int y1 = roomCoordinates[room][1];
        int x2 = roomCoordinates[room][2];
        int y2 = roomCoordinates[room][3];

        for (int i = x1; i <= x2; i++){
            mapMatrix[y1][i] = 1;
        }
        for (int i = y1; i <= y2; i++){
            mapMatrix[i][x1] = 1;
        }
        for (int i = x1; i <= x2; i++){
            mapMatrix[y2][i] = 1;
        }
        for (int i = y1; i <= y2; i++){
            mapMatrix[i][x2] = 1;
        }
    }

}

int main(int argc, char *argv[]){
    int hight;
    int width;
    int iterations = 2;
    bool fullWalls = false;
    int minimumRoomSize = 1;
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "--help") == 0 || argc == 1){
            printf("Binary Space Partitioning:\nRequired:\n\t-w [width]\n\t-h [hight]\nOptional:\n\t-i [iterations]\n\t-f (full Walls)\n\t-m [minimum room size]\n");
            exit(0);
        }
        if (strcmp(argv[i], "-w") == 0){
            width = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-h") == 0){
            hight = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-i") == 0){
            iterations = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-m") == 0){
            minimumRoomSize = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-f") == 0){
            fullWalls = true;
        }
    }
    if (hight == 0 || width == 0){
        printf("Need to specify width and hight\n");
        exit(0);
    }
    if (minimumRoomSize < 1){
        printf("Need larger room size\n");
        exit(0);
    }
    srand (time(NULL));
    vector<vector<int> > mapMatrix(hight, vector<int>(width,0));
    binarySpacePartitioning(mapMatrix, iterations, fullWalls, minimumRoomSize);
    printMap(mapMatrix);
}