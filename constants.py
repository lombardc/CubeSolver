# Array of the possible manual moves
# Sorted in a grid, as they will be displayed
MOVES = [["U", "U'", "U2"],
         ["D", "D'", "D2"],
         ["R", "R'", "R2"],
         ["L", "L'", "L2"],
         ["F", "F'", "F2"],
         ["B", "B'", "B2"],
         ]

# Dictionary defining the GUI color for each facelet
GUI_COLORS = {"x": "gray",
              "U": "cornflowerblue",
              "D": "lightgreen",
              "F": "white",
              "B": "yellow",
              "R": "tomato",
              "L": "darkorange",
              }


# Cube string as usually used (URFDLB)
CUBE_STRING = ["x", "x", "x", "x", "U", "x", "x", "x", "x",  # 0  -> Up Face (Blue)
               "x", "x", "x", "x", "R", "x", "x", "x", "x",  # 9  -> Right Face (Red)
               "x", "x", "x", "x", "F", "x", "x", "x", "x",  # 18 -> Front Face (White)
               "x", "x", "x", "x", "D", "x", "x", "x", "x",  # 27 -> Down Face (Green)
               "x", "x", "x", "x", "L", "x", "x", "x", "x",  # 36 -> Left Face (Orange)
               "x", "x", "x", "x", "B", "x", "x", "x", "x",  # 45 -> Back Face (Yellow)
               ]

# Array giving the position of each facelet in a 14x11 grid.
# This is used to display a flat version of the cube
FACELET_POSITION = [[1, 4], [1, 5], [1, 6], [2, 4], [2, 5], [2, 6], [3, 4], [3, 5], [3, 6],  # U
                    [4, 7], [4, 8], [4, 9], [5, 7], [5, 8], [5, 9], [6, 7], [6, 8], [6, 9],  # R
                    [4, 4], [4, 5], [4, 6], [5, 4], [5, 5], [5, 6], [6, 4], [6, 5], [6, 6],  # F
                    [7, 4], [7, 5], [7, 6], [8, 4], [8, 5], [8, 6], [9, 4], [9, 5], [9, 6],  # D
                    [4, 1], [4, 2], [4, 3], [5, 1], [5, 2], [5, 3], [6, 1], [6, 2], [6, 3],  # L
                    [4, 10], [4, 11], [4, 12], [5, 10], [5, 11], [5, 12], [6, 10], [6, 11], [6, 12],  # B
                    ]

# Everytime the camera is used to recognize the facelets colors, 9 values are returned
# The values correspond to the colors of the 9 facelets composing the corner facing the
# camera. The array recognition_steps indicate, the position of this corner in the cube
# string, this according to the move performed in the array RECOGNITION_MOVES.
RECOGNITION_STEPS = [
    [[0, 39], [1, 42], [2, 43], [3, 50], [4, 53], [5, 52], [6, 34], [7, 33], [8, 30]],
    [[1, 44], [2, 41], [4, 27], [7, 24], [8, 21]],
    [[1, 38], [2, 37], [4, 18], [7, 6], [8, 3]],
    [[1, 36], [4, 0], [7, 47]],
    [[1, 51], [4, 17], [5, 16], [6, 32], [7, 35]],
    [[1, 15], [4, 26], [5, 25], [6, 28], [7, 29]],
    [[0, 1], [3, 46]],
    [[0, 14], [1, 11], [3, 48], [4, 45], [7, 2]],
    [[0, 10], [1, 9], [3, 5], [4, 8], [7, 20]],
    [[0, 19], [3, 7]],
    [[2, 12], [8, 23]]
]

RECOGNITION_MOVES = [
    "L",
    "L",
    "L",
    "L-D",
    "D",
    "D2-B",
    "B",
    "B2-U2-L2-L",
    "L-U2-U-L2-L",
    "L-U2-U-R-B2-B2-R2-D2",
    "D2-R"
]

# The camera always looks at the 9 facelets composing the corner facing it.
# Each facelet is observed through a squared ROI.
# ROI_POSITIONS contains the list of the 9 ROIs positions, referenced by the positions
# of the top left corner, in pixels.
ROI_POSITIONS = [[690, 200],
                 [690, 330],
                 [815, 410],

                 [580, 230],
                 [580, 330],
                 [460, 410],

                 [515, 515],
                 [640, 460],
                 [770, 515],
                 ]

# define range of red color in HSV Color Space
LOWER_RED = [0, 130, 130]
UPPER_RED = [10, 255, 196]

# define range of green color in HSV Color Space
LOWER_GREEN = [50, 210, 130]
UPPER_GREEN = [80, 255, 195]

# define range of blue color in HSV Color Space
LOWER_BLUE = [94, 190, 100]
UPPER_BLUE = [110, 255, 175]

# define range of white color in HLS Color Space
LOWER_WHITE = [70, 70, 30]
UPPER_WHITE = [105, 150, 100]

# define range of orange color in HLS Color Space
LOWER_ORANGE = [10, 0, 0]
UPPER_ORANGE = [30, 125, 255]

# define range of yellow color in HSL Color Space
LOWER_YELLOW = [25, 70, 110]
UPPER_YELLOW = [50, 255, 255]

# define the ROI size, in pixels
ROI_SIZE = 20
