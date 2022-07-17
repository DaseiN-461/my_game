#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define pixel_size 5

#define x_size 16
#define y_size 16

#define x_grid_size 32
#define y_grid_size 32

uint32_t grid[x_grid_size][y_grid_size];
uint32_t background[x_grid_size][y_grid_size];




typedef struct{
    bool mask_grid[x_grid_size][y_grid_size];
    uint32_t mask_color[x_size][y_size];
    uint8_t pos[2];
}object2D;


void generate_grid(){
    for(uint8_t y=0; y<x_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            if(x>14){
                grid[x][y] = 0X7ED321;
                background[x][y] = 0X7ED321;
            }else{
                grid[x][y] = 0X090155;
                background[x][y] = 0X090155;
            }
            
            
        }    
    }
}




/*
void generate_object(object2D *ptr_object ,uint8_t pos[2], bool mask_grid[x_grid_size][y_grid_size], uint32_t mask_color[x_size][y_size]){
    
    ptr_object -> pos[0] = pos[0];
    ptr_object -> pos[1] = pos[1];
    
    for(uint8_t y=0; y<y_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            ptr_object -> mask_grid[x][y] = mask_grid[x][y];
        }
    }
    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            ptr_object -> mask_color[x][y] = mask_color[x][y];
        }
    }
}
*/


object2D update_object(uint8_t x0, uint8_t y0, uint32_t new_mask_color[x_size][y_size]){
    object2D new_object = {
        .mask_grid = {},
        .mask_color = {},
        .pos = {}
    };

    new_object.pos[0] = x0;
    new_object.pos[1] = y0;

    for(uint8_t y=0; y<y_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            new_object.mask_grid[x][y] = 0;
        }
    }
    
    for(uint8_t y=0; y<y_size; y++){
        for(uint8_t x=0; x<x_size; x++){
            new_object.mask_color[x][y] = new_mask_color[x][y];
            if(new_object.mask_color[x][y] != 0x0000){
                new_object.mask_grid[x0+x][y0+y] = 1;
            }
        }
    }
    return new_object;
}



void update_object_in_grid(object2D *ptr_object0,object2D *ptr_object1){

    bool mask_0[x_grid_size][y_grid_size]; 
    bool mask_1[x_grid_size][y_grid_size];

    bool mask_intersection[x_grid_size][y_grid_size];
    
    uint32_t mask_color0[x_size][y_size];
    uint32_t mask_color1[x_size][y_size];
    
    uint8_t x0 = ptr_object0 -> pos[0];
    uint8_t y0 = ptr_object0 -> pos[1];
    
    uint8_t x1 = ptr_object1 -> pos[0];
    uint8_t y1 = ptr_object1 -> pos[1];
    
    bool flag = 0;
    
    for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                mask_0[x][y] = ptr_object0 -> mask_grid[x][y];
                mask_1[x][y] = ptr_object1 -> mask_grid[x][y];
            }    
    }
    
    for(uint8_t y=0; y<y_size; y++){
            for(uint8_t x=0; x<x_size; x++){
                mask_color0[x][y] = ptr_object0 -> mask_color[x][y];
                mask_color1[x][y] = ptr_object1 -> mask_color[x][y];
            }    
    }
    
    for(uint8_t y=0; y<y_grid_size; y++){
        for(uint8_t x=0; x<x_grid_size; x++){
            if(mask_0[x][y] && mask_1[x][y]){
                if(flag == 0){
                    flag = 1;
                }
                mask_intersection[x][y] = 1;
            }else{
                mask_intersection[x][y] = 0;
            }
        }
    }

    if(flag == 1){
        for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                if(mask_0[x][y] != mask_intersection[x][y]){
                    grid[x][y] = background[x][y];
                }
                if(mask_1[x][y] != mask_intersection[x][y]){
                    grid[x][y] = mask_color1[x-x1][y-y1];
                }
                if(mask_intersection[x][y]){
                    if(grid[x][y] != mask_color1[x-x1][y-y1]){
                        grid[x][y] = mask_color1[x-x1][y-y1];
                    }
                }
            }    
        }
        
        
    }else if (flag == 0){
        for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                if(mask_0[x][y] == 1){
                    grid[x][y] = background[x][y];
                }
                if (mask_1[x][y] == 1){
                    grid[x][y] = mask_color1[x-x1][y-y1];
                }
                
            }
        }
    }
}



void update_background_in_grid(){
    for(uint8_t y=0; y<y_grid_size; y++){
            for(uint8_t x=0; x<x_grid_size; x++){
                
            }
    }
}