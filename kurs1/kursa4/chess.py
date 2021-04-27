import pygame
import os
import numpy as np
from pprint import pprint
import time

pygame.init()
FOLDER_ABS_PATH = os.path.dirname(os.path.abspath(__file__))
CELL_WIDTH = 90
FIGURE_SCALE = [CELL_WIDTH, CELL_WIDTH]
SCREEN_WIDTH = 8 * CELL_WIDTH
SCREEN_HEIGHT = 8 * CELL_WIDTH
FONT_SIZE = CELL_WIDTH // 5
FIGURE_SHIFT = np.array([(CELL_WIDTH - FIGURE_SCALE[0]) // 2, (CELL_WIDTH - FIGURE_SCALE[1]) // 2])
COORDS_FONT = pygame.font.SysFont('Comic Sans MS', CELL_WIDTH // 5)
COORDS_TEXT = 'abcdefgh'
DARK = (116, 150, 84)
LIGHT = (236, 238, 212)
SHIFTS_SQUARE = np.array([[0, 0], [1, 0], [1, 1], [0, 1], [0, 0]]) 
PATH_DELTAS = np.array([[1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1], [0, 1]])
PATHS = {
    'queen' : [[path_delta * j for j in range(1, 10)] for path_delta in PATH_DELTAS],
    'bishop' : [[path_delta * j for j in range(1, 10)] for j, path_delta in enumerate(PATH_DELTAS) if [1, 0, 1, 0, 1, 0, 1, 0][j]],
    'rook' : [[path_delta * j for j in range(1, 10)] for j, path_delta in enumerate(PATH_DELTAS) if [0, 1, 0, 1, 0, 1, 0, 1][j]], 
    'king' : [[path_delta] for path_delta in PATH_DELTAS],
    'knight' : np.array([[[1, 2]], [[2, 1]], [[2, -1]], [[-1, 2]], [[-1, -2]], [[-2, -1]], [[-2, 1]], [[1, -2]]]),
    'pawn' : np.array([[1, 0], [1, -1], [1, 1], [2, 0], [-1, 0], [-1, -1], [-1, 1], [-2, 0]]),
}

def def_start_figure_by_coord(x, y) :
    if x in [1, 6] :
        #return [None] * 3
        return ['pawn', x == 1, False]#turned at least once
    else :
        if x in [0, 7] :
            color = x == 0
            if y in [0, 7] : return ['rook', color, False]#turned at least once
            elif y in [1, 6] : return ['knight', color, False]
            elif y in [2, 5] : return ['bishop', color, False]
            elif y == 3 : return ['queen', color, False]
            elif y == 4 : return ['king', color, False]#turned at least once
    return [None, None, None]

def is_inside_field(cell) :
    return 0 <= cell[0] <= 7 and 0 <= cell[1] <= 7

def get_all_possible_places_to_turn(active_figure) :
    highlighted = np.zeros((8, 8))
    figure = field[active_figure[1]][active_figure[0]] 
    
    if figure[0] != 'pawn' :
        for path in PATHS[figure[0]] :
            for shift in path : 
                tempcell = active_figure + shift
                if is_inside_field(tempcell) :
                    tempfigure = field[tempcell[1]][tempcell[0]]
                    if tempfigure[1] != figure[1] : highlighted[tempcell[1]][tempcell[0]] = 1
                    if tempfigure[0] != None : break
    else :
        possible = []
        x_shift = 1 if figure[1] else -1
        fig = [[None, None, None]] * 4
        if is_inside_field([active_figure[0] + x_shift, active_figure[1] - 1]) : fig[0] = field[active_figure[1] - 1][active_figure[0] + x_shift]
        if is_inside_field([active_figure[0] + x_shift, active_figure[1]]) : fig[1] = field[active_figure[1]][active_figure[0] + x_shift]
        if is_inside_field([active_figure[0] + x_shift, active_figure[1] + 1]) : fig[2] = field[active_figure[1] + 1][active_figure[0] + x_shift]
        if is_inside_field([active_figure[0] + x_shift * 2, active_figure[1]]) : fig[3] = field[active_figure[1]][active_figure[0] + x_shift * 2]
        if fig[0][0] and fig[0][1] != figure[1] : possible.append(1)
        if not any(fig[1]) : 
            possible.append(0)
            if not figure[2] and not any(fig[3]) : possible.append(3) 
        if fig[2][0] and fig[2][1] != figure[1] : possible.append(2)
        index_shift = 0 if figure[1] else 4
        for index in possible :
            tempcell = PATHS['pawn'][index + index_shift] + active_figure
            if is_inside_field(tempcell) : highlighted[tempcell[1]][tempcell[0]] = 1
    return highlighted

def draw_square(cell, color, border = 5) :
    for sindex in range(1, 5) :
        pygame.draw.line(surface, color, (cell + SHIFTS_SQUARE[sindex - 1]) * CELL_WIDTH, (cell + SHIFTS_SQUARE[sindex]) * CELL_WIDTH, border)

def draw_field() :
    #field
    surface.blit(fon, (0, 0))
    #active cell
    if cell_is_active : 
        surface.blit(active, (active_cell * CELL_WIDTH).astype(int))
    
    #highlighted
    for y in range(8) :
        for x in range(8) :
            if highlighted[y][x] :
                if field[y][x][0] != None :
                    draw_square((x, y), (180, 20, 20), 4)
                else :
                    surface.blit(miniblack, (x * CELL_WIDTH + CELL_WIDTH // 3, y * CELL_WIDTH + CELL_WIDTH // 3))
    
    #figures
    for y in range(8) :
        for x in range(8) :
            figure = field[y][x]
            if figure[0] != None :
                surface.blit(white_figures[figure[0]] if figure[1] else black_figures[figure[0]], (x * CELL_WIDTH + FIGURE_SHIFT[0], y * CELL_WIDTH + FIGURE_SHIFT[1]))

    #draw_square(kings[True], (180, 20, 20), 4)
    #draw_square(kings[False], (180, 20, 20), 4)

def is_check() : 
    res = np.zeros(3)
    res[1] = 1
    for y in range(8) :
        for x in range(8) :
            figure = field[y][x]
            if figure[0] != None : 
                temp = get_all_possible_places_to_turn(np.array([x, y]))
                if temp[kings[not figure[1]][1]][kings[not figure[1]][0]] :
                    res[2 if figure[1] else 0] = 1
                    res[1] = 0
    return res

def turn(back) :
    global TURN, field, kincgs, coord, highlighted, active_cell, cell_is_active, cellS
    AF = field[active_cell[1]][active_cell[0]]
    kingmode = AF[0] == 'king'
    if back :
        field[active_cell[1]][active_cell[0]][2] = True
        field[coord[1]][coord[0]] = field[active_cell[1]][active_cell[0]]
        field[active_cell[1]][active_cell[0]] = [None] * 3
        if kingmode : kings[TURN] = coord
        check = is_check()
        field[coord[1]][coord[0]] = cell
        field[active_cell[1]][active_cell[0]] = AF
        if kingmode : kings[TURN] = active_cell
        return not check[0 if TURN else 2]
    else :
        field[active_cell[1]][active_cell[0]][2] = True
        field[coord[1]][coord[0]] = field[active_cell[1]][active_cell[0]]
        field[active_cell[1]][active_cell[0]] = [None] * 3
        if kingmode : kings[TURN] = coord
        if is_check()[0 if TURN else 2] :
            field[coord[1]][coord[0]] = cell
            field[active_cell[1]][active_cell[0]] = AF
            if kingmode : kings[TURN] = active_cell
            return False
        cell_is_active = False
        TURN = not TURN
        highlighted = np.zeros((8, 8))
        return True

def mate() :
    global TURN, field, kincgs, coord, highlighted, active_cell, cell_is_active, cell
    for y in range(8) :
        for x in range(8) :
            figure = field[y][x]
            if figure[1] == TURN :
                h = get_all_possible_places_to_turn(np.array([x, y]))
                if np.any(h) : 
                    for yyy in range(8) :
                        for xxx in range(8) :
                            if h[yyy][xxx] and yyy != y and xxx != x : 
                                coord = np.array([xxx, yyy])
                                active_cell = np.array([x, y])
                                cell = field[coord[1]][coord[0]]
                                if turn(True) :
                                    return 0
    return 1 if TURN else -1

#init window
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
surface = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('CHESS')

#load images
white_figures = {
    'pawn' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\pawn_white.png'), FIGURE_SCALE),
    'rook' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\rook_white.png'), FIGURE_SCALE),
    'knight' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\knight_white.png'), FIGURE_SCALE),
    'bishop' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\bishop_white.png'), FIGURE_SCALE),
    'king' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\king_white.png'), FIGURE_SCALE),
    'queen' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\queen_white.png'), FIGURE_SCALE),
}
black_figures = {
    'pawn' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\pawn_black.png'), FIGURE_SCALE),
    'rook' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\rook_black.png'), FIGURE_SCALE),
    'knight' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\knight_black.png'), FIGURE_SCALE),
    'bishop' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\bishop_black.png'), FIGURE_SCALE),
    'king' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\king_black.png'), FIGURE_SCALE),
    'queen' : pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\queen_black.png'), FIGURE_SCALE),
}

fon = pygame.transform.scale(pygame.image.load(FOLDER_ABS_PATH + '\\images\\field.png'), (CELL_WIDTH * 8, CELL_WIDTH * 8))

active = pygame.image.load(FOLDER_ABS_PATH + '\\images\\active_figure.jpg')
active = pygame.transform.scale(active, (CELL_WIDTH, CELL_WIDTH))
active.set_alpha(180)

black = pygame.image.load(FOLDER_ABS_PATH + '\\images\\ultrablack_pixel.jpg')
black = pygame.transform.scale(black, (CELL_WIDTH, CELL_WIDTH))
miniblack = pygame.transform.scale(black, (CELL_WIDTH // 3, CELL_WIDTH // 3))
miniblack.set_alpha(120)

#init field
field = []
for y in range(8) :
    field.append([])
    for x in range(8) :
        field[y].append(def_start_figure_by_coord(x, y))            
kings = {True : np.array([0, 4]), False : np.array([7, 4])}

#game cycle
highlighted = np.zeros((8, 8))
TURN = True
cell_is_active = False
winner = 0
while 1 : 
    mouse = np.array(pygame.mouse.get_pos())
    coord = mouse // CELL_WIDTH
    for e in pygame.event.get() : 
        if e.type == pygame.QUIT : exit()
        if e.type == pygame.MOUSEBUTTONDOWN :
            if e.button == 1 and winner == 0 : 
                cell_is_active = False
                if is_inside_field(coord) :
                    cell = field[coord[1]][coord[0]]
                    if TURN == cell[1] :
                        active_cell = coord
                        cell_is_active = True
                        highlighted = get_all_possible_places_to_turn(active_cell)
                    elif TURN != cell[1] and highlighted[coord[1]][coord[0]] :
                        temp = turn(False)
                        if temp and is_check()[0 if TURN else 2] :
                            winner = mate()
                    else : 
                        highlighted = np.zeros((8, 8))
    draw_field()
    screen.blit(surface, (0, 0))
    pygame.display.update()
