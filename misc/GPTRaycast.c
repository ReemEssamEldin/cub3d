// untextured_raycaster.c
#include "./includes/mlx/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_vars {
    void *mlx;
    void *win;
} t_vars;

typedef struct s_player {
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
} t_player;

long get_time_in_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void draw_vertical_line(t_vars *vars, int x, int y1, int y2, int r, int g, int b) {
    int color = (r << 16) + (g << 8) + b;
    for (int y = y1; y <= y2; y++)
        mlx_pixel_put(vars->mlx, vars->win, x, y, color);
}

int render(t_vars *vars, t_player *p) {
    for (int x = 0; x < screenWidth; x++) {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = p->dirX + p->planeX * cameraX;
        double rayDirY = p->dirY + p->planeY * cameraX;

        int mapX = (int)p->posX;
        int mapY = (int)p->posY;

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        int stepX, stepY, hit = 0, side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (p->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - p->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (p->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - p->posY) * deltaDistY;
        }

        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;

        int lineHeight = (int)(screenHeight / perpWallDist);
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        int r = 255, g = 255, b = 255;
        switch (worldMap[mapX][mapY]) {
            case 1: r = 255; g = 0; b = 0; break;
            case 2: r = 0; g = 255; b = 0; break;
            case 3: r = 0; g = 0; b = 255; break;
            case 4: r = 255; g = 255; b = 255; break;
            default: r = 255; g = 255; b = 0; break;
        }
        if (side == 1) { r /= 2; g /= 2; b /= 2; }
        draw_vertical_line(vars, x, drawStart, drawEnd, r, g, b);
    }
    return (0);
}

int main() {
    t_vars vars;
    t_player player = {22, 12, -1, 0, 0, 0.66};

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Untextured Raycaster");

    while (1) {
        render(&vars, &player);
        usleep(16000); // ~60 FPS
    }
    return (0);
}