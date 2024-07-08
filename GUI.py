import os

from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QGridLayout, \
    QTabWidget, QPushButton, QSizePolicy, QLabel, QProgressBar, QHBoxLayout, QButtonGroup
import qdarktheme
import sys
from argparse import ArgumentParser, Namespace
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtCore import Qt, QSize
from QLed import QLed

from constants import MOVES, GUI_COLORS, CUBE_STRING, FACELET_POSITION


class SolvingTimer(QWidget):
    def __init__(self):
        super(SolvingTimer, self).__init__()
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)

        self.solved_label = QLabel("Solved in :")
        self.solved_label.setAlignment(Qt.AlignCenter)
        self.solved_label.setFont(QFont('Arial', 20))
        self.layout.addWidget(self.solved_label)

        self.solved_timer = QLabel("0.00")
        self.solved_timer.setAlignment(Qt.AlignCenter)
        self.solved_timer.setFont(QFont('Arial', 20))
        self.solved_timer.setFixedWidth(150)
        self.layout.addWidget(self.solved_timer)

        self.solved_seconds = QLabel("s")
        self.solved_seconds.setAlignment(Qt.AlignCenter)
        self.solved_seconds.setFont(QFont('Arial', 20))
        self.layout.addWidget(self.solved_seconds)

        self.current_time_ms = 0

    @property
    def current_time_ms(self):
        return self._current_time_ms

    @current_time_ms.setter
    def current_time_ms(self, val: int):
        self._current_time_ms = val
        self.solved_timer.setText(str(self._current_time_ms / 1000))


class CubeFace(QLabel):
    def __init__(self, val: str, x: int, y: int, size: int = 30):
        super(CubeFace, self).__init__()
        self.setContentsMargins(0, 0, 0, 0)
        self.setAlignment(Qt.AlignCenter)

        self.size_face = size
        self.x_pos = x
        self.y_pos = y
        self.val = val

    @property
    def x_pos(self):
        return self._x_pos

    @x_pos.setter
    def x_pos(self, val: int):
        self._x_pos = val

    @property
    def y_pos(self):
        return self._y_pos

    @y_pos.setter
    def y_pos(self, val: int):
        self._y_pos = val

    @property
    def size_face(self):
        return self._size_face

    @size_face.setter
    def size_face(self, val: int):
        self._size_face = val
        self.setFixedWidth(self._size_face)
        self.setFixedHeight(self._size_face)

    @property
    def val(self):
        return self._val

    @val.setter
    def val(self, value: str):
        self._val = value
        self.setStyleSheet(f"background-color: {GUI_COLORS[value]}; border: 1px solid black; ")


class MoveButton(QPushButton):
    def __init__(self, name: str, row: int, col: int, icon_size: int = 90):
        super(MoveButton, self).__init__()

        self.icon_size = icon_size
        self.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)

        self.name = name
        self.row = row
        self.col = col

    @property
    def row(self):
        return self._row

    @row.setter
    def row(self, val: int):
        self._row = val

    @property
    def col(self):
        return self._col

    @col.setter
    def col(self, val: int):
        self._col = val

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, val: str):
        self._name = val
        self.icon = QIcon(os.path.join(os.path.abspath(os.getcwd())) + f"/assets/{self.name}.png")
        self.setIcon(self.icon)

    @property
    def icon_size(self):
        return self._icon_size

    @icon_size.setter
    def icon_size(self, val: int):
        self._icon_size = val
        self.setIconSize(QSize(self._icon_size, self._icon_size))


class MainWindow(QMainWindow):
    def __init__(self, arg_parse: Namespace):
        super().__init__()
        self.setWindowTitle("Cube Solver")
        self.setGeometry(0, 0, 800, 480)

        # Full Screen mode
        if arg_parse.full_screen:
            self.showFullScreen()

        ###############
        # Main Layout #
        ###############

        # Central Widget
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        # Main Layout
        self.main_layout = QGridLayout(self.central_widget)

        # Tabs
        self.tabs = QTabWidget(self.central_widget)

        self.moves_tab = QWidget(self.tabs)
        self.moves_tab.layout = QGridLayout()
        self.moves_tab.setLayout(self.moves_tab.layout)

        self.solver_tab = QWidget(self.tabs)
        self.solver_tab.layout = QGridLayout()
        self.solver_tab.setLayout(self.solver_tab.layout)

        self.tabs.addTab(self.moves_tab, "Moves")
        self.tabs.addTab(self.solver_tab, "Auto Solver")

        # Quit button
        self.quit_button = QPushButton("Quit")
        self.quit_button.setMinimumWidth(150)

        # Populating main layout
        self.main_layout.addWidget(self.tabs, 0, 0, 1, 6)
        self.main_layout.addWidget(self.quit_button, 1, 5, Qt.AlignRight | Qt.AlignBottom)

        ###################
        # Manual Move Tab #
        ###################

        # Move Buttons
        self.possible_moves = MOVES
        self.simple_move_group = QButtonGroup()
        self.simple_move_group.setExclusive(True)
        for i, col in enumerate(self.possible_moves):
            for j, move in enumerate(col):
                button = MoveButton(name=move, row=j, col=i)
                self.moves_tab.layout.addWidget(button,
                                                button.row,
                                                button.col
                                                )
                self.simple_move_group.addButton(button)

        # Scramble Button
        self.scramble = QPushButton("Random Scramble")
        self.moves_tab.layout.addWidget(self.scramble, 3, 0, 1, 2, Qt.AlignCenter)

        # Scramble Progress
        self.scramble_progress = QProgressBar()
        self.scramble_progress.setMinimum(0)
        self.scramble_progress.setMaximum(1)
        self.scramble_progress.setValue(0)
        self.scramble_progress.setStyleSheet("QProgressBar::chunk {margin: 5px;}")
        self.scramble_progress.setFixedHeight(35)
        self.scramble_progress.setFixedWidth(400)
        self.scramble_progress.setContentsMargins(0, 10, 0, 10)
        self.moves_tab.layout.addWidget(self.scramble_progress, 3, 2, 1, 4, alignment=Qt.AlignHCenter)
        self.scramble_progress.setHidden(True)


        ##################
        # Auto Solve Tab #
        ##################
        self.facelets = []
        for index, val in enumerate(CUBE_STRING):
            self.facelets.append(CubeFace(val, FACELET_POSITION[index][0], FACELET_POSITION[index][1]))

        # Setting the grid such that it is squared, to display the cube without distortion
        self.solver_tab.layout.setContentsMargins(0, 0, 0, 0)
        self.solver_tab.layout.setSpacing(0)
        self.solver_tab.layout.setRowStretch(0, 1)
        self.solver_tab.layout.setRowStretch(10, 1)
        self.solver_tab.layout.setColumnStretch(0, 1)
        self.solver_tab.layout.setColumnStretch(13, 1)
        self.solver_tab.layout.setColumnStretch(17, 1)
        self.solver_tab.layout.setRowMinimumHeight(11, 50)

        # Populating the grid with the cube
        for a_facelet in self.facelets:
            self.solver_tab.layout.addWidget(a_facelet, a_facelet.x_pos, a_facelet.y_pos)

        # Color recognition Button
        self.color_reco_button = QPushButton("Color Recognition")
        self.color_reco_button.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        self.solver_tab.layout.addWidget(self.color_reco_button, 2, 14, 2, 2)

        # Color recognition Status
        self.recognition_led = QLed(self, onColour=QLed.Green, shape=QLed.Circle)
        self.recognition_led.setFixedSize(25, 25)
        self.solver_tab.layout.addWidget(self.recognition_led, 5, 14)

        # Color recognition Text
        self.recognition_text = QLabel(" Recognition Successful ")
        self.recognition_text.setAlignment(Qt.AlignCenter)
        self.recognition_text.setFixedWidth(180)
        self.solver_tab.layout.addWidget(self.recognition_text, 4, 15, 3, 1)

        # Solving Button
        self.solve_button = QPushButton("Solve")
        self.solve_button.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        self.solve_button.setEnabled(False)
        self.solver_tab.layout.addWidget(self.solve_button, 7, 14, 2, 2)

        # Recognition Progress
        self.recognition_progress = QProgressBar()
        self.recognition_progress.setMinimum(0)
        self.recognition_progress.setMaximum(48)  # 48 facelets to discover
        self.recognition_progress.setValue(47)
        self.recognition_progress.setStyleSheet("QProgressBar::chunk {margin: 5px;}")
        self.recognition_progress.setFixedHeight(35)
        self.recognition_progress.setFixedWidth(600)
        self.recognition_progress.setContentsMargins(0, 10, 0, 10)

        # Solving Timer
        self.solver_timer = SolvingTimer()
        self.solver_timer.setFixedWidth(300)
        self.solver_tab.layout.addWidget(self.solver_timer, 11, 0, 1, 18, alignment=Qt.AlignHCenter)
        self.solver_tab.layout.addWidget(self.recognition_progress, 11, 0, 1, 18, alignment=Qt.AlignHCenter)

        # Hide timers so far
        self.hide_timers()

    def _init_facelets(self):
        for index, val in enumerate(CUBE_STRING):
            self.facelets[index].val = val

    def show_reco_timer(self):
        self.solver_timer.setHidden(True)
        self.recognition_progress.setHidden(False)

    def show_solve_timer(self):
        self.solver_timer.setHidden(False)
        self.recognition_progress.setHidden(True)

    def hide_timers(self):
        self.solver_timer.setHidden(True)
        self.recognition_progress.setHidden(True)


if __name__ == "__main__":
    parser = ArgumentParser(
        prog='Cube Solver',
        description="Move, Analyze and Solve the Rubik's Cube!",
        epilog='Thanks for using me!')
    parser.add_argument('-f', '--full-screen', action='store_true')

    App = QApplication(sys.argv)
    qdarktheme.setup_theme()
    window = MainWindow(parser.parse_args())
    window.show()
    sys.exit(App.exec())
