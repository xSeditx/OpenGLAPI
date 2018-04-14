#pragma once
#include<string>
#include<fstream>
#include<vector>

class  FileUtils{
	public:
        static std::string read_file(const char* filepath){
		          FILE *file = fopen(filepath,"rt");

		          fseek(file,0,SEEK_END);

		          unsigned long length = ftell(file);

		          char *data = new char[length + 1];
		          memset(data, 0, length +1);

		          fseek(file,0,SEEK_SET);
		          fread(data,1,length,file);

		          fclose(file);
                  
		          std::string result(data);
		          delete[] data;
                  return result;
		}
};



//bool loadOBJ( const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals)
 //   );



//    // ====================================================== Using the Data ==============================================================
//    
//    // Read our .obj file
//    std::vector< Vec3 > vertices;
//    std::vector< Vec2 > uvs;
//    std::vector< Vec3 > normals; // Won't be used at the moment.
//    bool res = LoadModel("cube.obj", vertices, uvs, normals);
//     
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);
//    
//    


// NOT FUNCTIONING YET
bool LoadModel(const char* path){
    
    Print("WARNING LOAD MODEL FUNCTION NOT COMPLETE!!!!!");

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< Vec3 > temp_vertices;
    std::vector< Vec2 > temp_uvs;
    std::vector< Vec3 > temp_normals;
    

    char lineHeader[128]; // Header of OBJ files
    
    
    FILE * file = fopen(path, "r");

    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }
    
    
    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF) break; // EOF = End Of File. Quit the loop.
    }



    if ( strcmp( lineHeader, "v" ) == 0)
    {
        Vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        temp_vertices.push_back(vertex);
    }



    else if ( strcmp( lineHeader, "vt" ) == 0 )
    {
        Vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        temp_uvs.push_back(uv);
    }
    else if ( strcmp( lineHeader, "vn" ) == 0 )
    {
        Vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        temp_normals.push_back(normal);
    }
    else if ( strcmp( lineHeader, "f" ) == 0 )
    {
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
        if (matches != 9){
            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            return false;
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        uvIndices    .push_back(uvIndex[0]);
        uvIndices    .push_back(uvIndex[1]);
        uvIndices    .push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
    }
    
    
// ================================================ Process the incoming Data ==================================================
     
        std::vector < Vec3 > out_vertices;
        std::vector < Vec2 > out_uvs;
        std::vector < Vec3 > out_normals;
        
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
    
        Vec3 vertex = temp_vertices[ vertexIndex-1 ];
    
        out_vertices.push_back(vertex);
    
}
}