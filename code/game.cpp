#include <stdio.h>
#include <windows.h>
#include <glad/glad.h>


#include "game.h"
#include "math.h"
#include <math.h>

void GenerateTerrain(Terrain* terrain, int numCols, int numRows, int cellSpacing)
{
    // first we need to store space to generate the terrain
    // get the size of the data structures we need
    int numbVertex    = numCols * numRows;
    int numCellRows   = numRows - 1;
    int numCellCols   = numCols - 1;
    int numTriangles  = 2 * (numCellRows * numCellCols);
    terrain->numIndex = numTriangles * 3;
    // get a pointer to that memory
    terrain->vertexBuffer = (VertexBuffer*)malloc(numbVertex * sizeof(VertexBuffer));
    terrain->indexBuffer  = (int*) malloc(terrain->numIndex * sizeof(int));

    for(int y = 0; y < numRows; y++)
    {
        for(int x = 0; x < numCols; x++)
        {
            Vec3 vertexPos = {0.0f, 0.0f, 0.0f};
            if( x <= numCols / 2)
            {
                vertexPos = {(float)(x * cellSpacing),
                             0.0f,
                             (float)(y * cellSpacing)};
            }
            else
            {
                vertexPos = {(float)(x * cellSpacing),
                             3.0f,
                             (float)(y * cellSpacing)};
        
            }
            Vec3 normalPos = {0.0f, 1.0f, 0.0f}; 
            Vec2 texturePos = {(float)x, (float)y};

            int index = (y * numCols) + x;
            terrain->vertexBuffer[index].vertice      = vertexPos;
            terrain->vertexBuffer[index].normal       = normalPos;
            terrain->vertexBuffer[index].textureCoord = texturePos;
        }
    }

    int index = 0;
    for(int y = 0; y < numCellRows; y++)
    {
        for(int x = 0; x < numCellCols; x++)
        {
            terrain->indexBuffer[index + 0] = ((y + 1) * numCols) + x;  
            terrain->indexBuffer[index + 1] = (y * numCols) + (x + 1);
            terrain->indexBuffer[index + 2] = (y * numCols) + x;

            terrain->indexBuffer[index + 3] = ((y + 1) * numCols) + (x + 1);
            terrain->indexBuffer[index + 4] = (y * numCols) + (x + 1);
            terrain->indexBuffer[index + 5] = ((y + 1) * numCols) + x;
            index += 6;
        }
    }
    
    glGenVertexArrays(1, &terrain->vao);
    glBindVertexArray(terrain->vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numbVertex * sizeof(VertexBuffer), terrain->vertexBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrain->numIndex * sizeof(int), terrain->indexBuffer, GL_STATIC_DRAW);
    
    free(terrain->vertexBuffer);
    free(terrain->indexBuffer); 
}

void GameInit(MainGame* game)
{
    float triangle_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.5f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.5f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f
    };

    InitializeCamera(&game->camera);
    
    LoadShader(&game->main_shader,
            "./code/vertexShader.vert",
            "./code/fragmentShader.frag");
    LoadShader(&game->mesh_shader,
            "./code/sphereVertexShader.vert",
            "./code/sphereFragmentShader.frag"); 

    glGenVertexArrays(1, &game->triangle_vao);
    glBindVertexArray(game->triangle_vao);

    unsigned int VBO;  // vertex buffer obj...
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(triangle_vertices),
            triangle_vertices,
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Matrix proj = get_projection_perspective_matrix(to_radiant(45), WNDWIDTH/WNDHEIGHT, 0.1f, 100.0f); 

    UseShader(&game->main_shader);
    int projMatLoc = glGetUniformLocation(game->main_shader.id, "Proj");
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, proj.m[0]);

    UseShader(&game->mesh_shader);
    int SphProjMatLoc = glGetUniformLocation(game->mesh_shader.id, "Proj");
    glUniformMatrix4fv(SphProjMatLoc, 1, GL_FALSE, proj.m[0]);

    LoadOBJFileIndex(&game->sphere, "./data/tree.obj", "./data/tree.bmp");
    LoadOBJFileIndex(&game->SuperPene, "./data/SuperPene.obj", "./data/terrain.bmp");

    GenerateTerrain(&game->terrain, 7, 7, 5);
}

void GameUnpdateAndRender(MainGame* game, float deltaTime)
{
    UpdateCamera(&game->camera, &game->input, deltaTime);

    UseShader(&game->mesh_shader);
    int SphViewMatLoc = glGetUniformLocation(game->mesh_shader.id, "View");
    glUniformMatrix4fv(SphViewMatLoc, 1, GL_FALSE, game->camera.viewMat.m[0]);

    UseShader(&game->main_shader);
    int viewMatLoc = glGetUniformLocation(game->main_shader.id, "View");
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, game->camera.viewMat.m[0]);
    

    UseShader(&game->main_shader);
    glBindVertexArray(game->triangle_vao);
    Matrix model = get_identity_matrix();
    int worldMatLoc = glGetUniformLocation(game->main_shader.id, "World"); 
    static float time = 0.0f;
    float t = absf(sinf(time));
    Vec3 startPos  = {2.0f,  0.0f, 0.0f};
    Vec3 endPos    = {-2.0f, 0.0f, 0.0f};
    Vec3 actualPos = Lerp(startPos, endPos, t);

    if(GetMouseButtonPress(&game->input, LEFTBUTTON))  // see if the left arroy is DOWN...
        time += 1 * deltaTime;

    // Draw the start position
    model = get_translation_matrix(startPos);
    glUniformMatrix4fv(worldMatLoc, 1, GL_FALSE, model.m[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // Draw the end position
    model = get_translation_matrix(endPos);
    glUniformMatrix4fv(worldMatLoc, 1, GL_FALSE, model.m[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw SUPER::PENE...
    UseShader(&game->main_shader);
    glBindVertexArray(game->SuperPene.vao);
    model = get_translation_matrix({0.0f, 0.0f, 4.0f});
    glUniformMatrix4fv(worldMatLoc, 1, GL_FALSE, model.m[0]);
    glDrawElements(GL_TRIANGLES, game->SuperPene.numIndex * 3, GL_UNSIGNED_INT, 0);

    UseShader(&game->mesh_shader);
    int SphWorldMatLoc = glGetUniformLocation(game->mesh_shader.id, "World");
    glBindTexture(GL_TEXTURE_2D, game->SuperPene.texId);
    glBindVertexArray(game->terrain.vao);
    model = get_identity_matrix();
    glUniformMatrix4fv(SphWorldMatLoc, 1, GL_FALSE, model.m[0]);
    glDrawElements(GL_TRIANGLES, game->terrain.numIndex * 3, GL_UNSIGNED_INT, 0); 
    glBindTexture(GL_TEXTURE_2D, game->sphere.texId);
    glBindVertexArray(game->sphere.vao);
    model = get_translation_matrix(actualPos);
    glUniformMatrix4fv(SphWorldMatLoc, 1, GL_FALSE, model.m[0]);
    glDrawElements(GL_TRIANGLES, game->sphere.numIndex * 3, GL_UNSIGNED_INT, 0);
}
