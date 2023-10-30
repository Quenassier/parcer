#include <iostream>
#include <fstream>
#include <sstream>  // Добавлен заголовок для std::istringstream
#include <string>

const int maxVertices = 1000;
const int maxTexCoords = 1000;
const int maxNormals = 1000;
const int maxFaces = 1000;

class Vertex {
public:
    float x, y, z;
};

class TextureCoord {
public:
    float u, v;
};

class Normal {
public:
    float nx, ny, nz;
};

class Face {
public:
    int vertexIndices[4];
    int textureIndices[4];
    int normalIndices[4];
    int faceIndices[4];
};

Vertex vertices[maxVertices];
TextureCoord texCoords[maxTexCoords];
Normal normals[maxNormals];
Face faces[maxFaces];

int vertexCount = 0;
int texCoordCount = 0;
int normalCount = 0;
int faceCount = 0;

int main() {
    std::ifstream objFile("your_file.obj");
    if (!objFile) {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }

    std::string line;

    while (std::getline(objFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream lineStream(line);
        std::string prefix;
        lineStream >> prefix;

        if (prefix == "v" && vertexCount < maxVertices) {
            lineStream >> vertices[vertexCount].x >> vertices[vertexCount].y >> vertices[vertexCount].z;
            vertexCount++;

        } else if (prefix == "vt" && texCoordCount < maxTexCoords) {
            lineStream >> texCoords[texCoordCount].u >> texCoords[texCoordCount].v;
            texCoordCount++;

        } else if (prefix == "vn" && normalCount < maxNormals) {
            lineStream >> normals[normalCount].nx >> normals[normalCount].ny >> normals[normalCount].nz;
            normalCount++;

        } else if (prefix == "f" && faceCount < maxFaces) {
            Face& face = faces[faceCount];
            for (int i = 0; i < 4; i++) {
                lineStream >> face.vertexIndices[i] >> face.textureIndices[i] >> face.normalIndices[i] >> face.faceIndices[i];
            }
            
            faceCount++;
        }
    }

    return 0;
}