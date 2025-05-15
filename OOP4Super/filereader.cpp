#include "filereader.h"
#include "qdebug.h"
#include "qlogging.h"
#include <cstring>
#include <fstream>
#include <sstream>
#define MAX_LINE_DATA 1024
#define MAX_DATA_SIZE 1024

Scene FileReader::readScene(char* path, NormalizationParameters params) {

    Scene scene;
    std::vector<std::vector<float>> data;
    std::vector<float> oneRow;
    FILE* file = fopen(path, "r");
    if (!file)
        return scene;
    else{
        char line[MAX_LINE_DATA];
        int row = 0;
        while (fgets(line, sizeof(line), file) && row < MAX_DATA_SIZE) {
            char* token = strtok(line, ",");
            int col = 0;
            while (token && col < MAX_DATA_SIZE) {
                oneRow.push_back(atof(token));
                token = strtok(NULL, ",");
                col++;
            }
            data.push_back(oneRow);
            oneRow.clear();
            row++;
        }
        fclose(file);
    }

    float min = data[0][0];
    float max = data[0][0];

    for (const auto& row : data) {
        for (float val : row) {
            min = std::min(min, val);
            max = std::max(max, val);
        }
    }

    std::vector<std::vector<Vertex>> verticesGrid;
    for (size_t i = 0; i < data.size(); ++i) {
        std::vector<Vertex> rowVertices;
        for (size_t j = 0; j < data[i].size(); ++j) {
            float norm_z = params.min + (data[i][j] - min) / (max - min) * (params.max - params.min);

            point3D pos;
            pos.x = j*params.step;
            pos.y = i*params.step;
            pos.z = norm_z;
            rowVertices.push_back(pos);
        }
        verticesGrid.push_back(rowVertices);
    }

    std::vector<Vertex> quart;

    //отдельно в фигуры запишем оси
    Vertex o1(point3D{0,0,0});
    Vertex ox(point3D{5,0,0});
    Vertex oy(point3D{0,5,0});
    Vertex oz(point3D{0,0,5});

    quart.push_back(o1);
    quart.push_back(ox);
    Figure figureX(quart);
    scene.addFigure(figureX);
    quart.clear();

    quart.push_back(o1);
    quart.push_back(oy);
    Figure figureY(quart);
    scene.addFigure(figureY);
    quart.clear();

    quart.push_back(o1);
    quart.push_back(oz);
    Figure figureZ(quart);
    scene.addFigure(figureZ);
    quart.clear();


    for (size_t i = 0; i < verticesGrid.size() - 1; ++i) {
        for (size_t j = 0; j < verticesGrid[i].size() - 1; ++j) {
            quart.push_back(verticesGrid[i][j]);
            quart.push_back(verticesGrid[i][j+1]);
            quart.push_back(verticesGrid[i+1][j+1]);
            quart.push_back(verticesGrid[i+1][j]);
            Figure figure(quart);
            scene.addFigure(figure);
            quart.clear();
        }
    }
    return scene;



}
