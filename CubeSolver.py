import random
import sys
import time
from argparse import ArgumentParser, Namespace
from functools import partial

import cv2
import kociemba
import numpy as np
import qdarktheme
import serial
from PyQt5 import QtCore
from PyQt5.QtCore import QThreadPool, pyqtSignal, QTimer, Qt
from PyQt5.QtGui import QPixmap, QCursor
from PyQt5.QtWidgets import QApplication, QSplashScreen, QProgressBar
from QLed import QLed

from CubeThread import Worker
from GUI import MainWindow, MoveButton
from constants import RECOGNITION_MOVES, RECOGNITION_STEPS, \
    ROI_POSITIONS, LOWER_RED, UPPER_RED, LOWER_BLUE, UPPER_BLUE, LOWER_GREEN, UPPER_GREEN, LOWER_WHITE, \
    UPPER_WHITE, LOWER_ORANGE, UPPER_ORANGE, LOWER_YELLOW, UPPER_YELLOW, ROI_SIZE


class ScrambleGenerator:
    def __init__(self, min_length: int = 20, max_length: int = 30):
        self.min_length = min_length
        self.max_length = max_length
        self.moves = ["U", "D", "F", "B", "R", "L"]
        self.directions = ["", "'", "2"]

    @property
    def min_length(self):
        return self._min_length

    @min_length.setter
    def min_length(self, val: int):
        self._min_length = val

    @property
    def max_length(self):
        return self._max_length

    @max_length.setter
    def max_length(self, val: int):
        self._max_length = val

    def _valid(self, scramble: list):
        # Check if Move behind or 2 behind is the same as the random move
        # this gets rid of 'R R2' or 'R L R2' or similar for all moves
        for x in range(1, len(scramble)):
            while scramble[x][0] == scramble[x - 1][0]:
                scramble[x][0] = random.choice(self.moves)
        for x in range(2, len(scramble)):
            while scramble[x][0] == scramble[x - 2][0] or scramble[x][0] == scramble[x - 1][0]:
                scramble[x][0] = random.choice(self.moves)
        return scramble

    def get_scramble(self):
        slen = random.randint(self._min_length, self._max_length)
        code = self._valid([[random.choice(self.moves), random.choice(self.directions)] for x in range(slen)])
        scramble = []
        for f in code:
            scramble.append(''.join([fi for fi in f]))

        return scramble, slen


class ArduinoCom:
    def __init__(self, serial_port: str):
        self.serial = serial.Serial(serial_port, 115200, timeout=1)
        self.scramble_generator = ScrambleGenerator(min_length=20, max_length=30)

        self.solve_over = True
        self.start_solve = 0
        self.solve_time = 0

    def _write(self, OPCODE, sleep=0.01, *args, **kwargs):
        text = OPCODE + "\n"
        self.serial.write(text.encode())
        while self.serial.readline() != b'OK\r\n':
            time.sleep(sleep)
        return

    def single_move(self, move: str, *args, **kwargs):
        self._write(move)
        return

    def sequence_move(self, sequence: str, *args, **kwargs):
        self._write(f"MOVE {sequence}")
        return

    def led_power(self, power: int, *args, **kwargs):
        self._write(f"LEDP {power}")
        return

    def led_pattern(self, pattern: str, *args, **kwargs):
        self._write(f"LEDS {pattern}")
        return

    def cube_mirror(self, cube_string: str, *args, **kwargs):
        self._write(f"MIRR {cube_string}")
        return

    def solve(self, OPCODE, *args, **kwargs):
        self.solve_over = False
        self.start_solve = time.time()
        self._write(f"SOLV {OPCODE}", sleep=0.001)
        self.solve_time = time.time() - self.start_solve
        self.solve_over = True
        return True


class CubeVisualizer:
    def __init__(self, com_serial: ArduinoCom, cam_port: int):
        self._serial = com_serial
        self._cam = cv2.VideoCapture(cam_port)

        # Setting up camera
        ret_val, cap_for_exposure = self._cam.read()
        self._cam.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
        self._cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
        self._cam.set(cv2.CAP_PROP_AUTO_WB, 0.0)
        self._cam.set(cv2.CAP_PROP_WB_TEMPERATURE, 10000)
        self._cam.set(cv2.CAP_PROP_AUTO_EXPOSURE, 0.75)
        self._cam.set(cv2.CAP_PROP_EXPOSURE, 60)

        # Moves list and position list
        self._reco_moves = RECOGNITION_MOVES
        self._reco_positions = RECOGNITION_STEPS
        self._roi_positions = ROI_POSITIONS
        self._roi_size = ROI_SIZE

    def color_finder(self, frame: list[list]):
        colors = [[] for val in self._roi_positions]
        output = ["" for val in self._roi_positions]
        rois = [[[], [], [], [], [], [], [], [], []] for val in self._roi_positions]

        for index, areas in enumerate(self._roi_positions):
            rois[index][0] = frame[areas[1]: areas[1] + self._roi_size, areas[0]: areas[0] + self._roi_size]
            rois[index][1] = cv2.cvtColor(rois[index][0], cv2.COLOR_BGR2HSV)
            rois[index][2] = cv2.cvtColor(rois[index][0], cv2.COLOR_BGR2HLS)

            rois[index][3] = cv2.inRange(rois[index][1], np.array(LOWER_RED), np.array(UPPER_RED))
            rois[index][4] = cv2.inRange(rois[index][1], np.array(LOWER_GREEN), np.array(UPPER_GREEN))
            rois[index][5] = cv2.inRange(rois[index][1], np.array(LOWER_BLUE), np.array(UPPER_BLUE))
            rois[index][6] = cv2.inRange(rois[index][2], np.array(LOWER_WHITE), np.array(UPPER_WHITE))
            rois[index][7] = cv2.inRange(rois[index][2], np.array(LOWER_ORANGE), np.array(UPPER_ORANGE))
            rois[index][8] = cv2.inRange(rois[index][2], np.array(LOWER_YELLOW), np.array(UPPER_YELLOW))

            colors[index] = [np.mean(rois[index][x + 3]) for x in range(6)]
            max_index = colors[index].index(max(colors[index]))
            if max_index == 0:
                output[index] = "R"
            elif max_index == 1:
                output[index] = "D"
            elif max_index == 2:
                output[index] = "U"
            elif max_index == 3:
                output[index] = "F"
            elif max_index == 4:
                output[index] = "L"
            elif max_index == 5:
                output[index] = "B"
        return output, frame

    def get_all_colors(self, progress_callback: pyqtSignal):
        over = False
        step = 0
        f_count = 0
        while not over:
            ret, frame = self._cam.read()
            if not ret:
                # Cam not ready... Waiting...
                time.sleep(0.1)
            elif f_count < 4:
                # Skipping frames to ensure the cube is not moving anymore
                f_count += 1
            else:
                f_count = 0
                cols, img = self.color_finder(frame)
                update = []
                for val in self._reco_positions[step]:
                    update.append([val[1], cols[val[0]]])
                self._serial.sequence_move(self._reco_moves[step])
                progress_callback.emit(update)
                step += 1
                if step == len(self._reco_moves):
                    # Give time for the last emit...
                    time.sleep(0.1)
                    over = True
        return


class CubeSolver(MainWindow):
    def __init__(self, arg_parse: Namespace):
        super(CubeSolver, self).__init__(arg_parse)
        self.Arduino = ArduinoCom(serial_port=arg_parse.serial_port)
        self.CubeVisualizer = CubeVisualizer(self.Arduino, cam_port=int(arg_parse.cam_port))

        # Threadpool for asynchronous actions
        self.threadpool = QThreadPool()
        self.threadpool.setMaxThreadCount(1)  # Limit to one extra thread

        # Connecting Move Buttons
        self.simple_move_group.buttonClicked.connect(self.simple_move)
        self.scramble.clicked.connect(self._init_auto_scrambling)
        self.color_reco_button.clicked.connect(self._init_color_recognition)
        self.solve_button.clicked.connect(self._init_solve_cube)
        self.quit_button.clicked.connect(self._pre_quit)

        # Scramble Generator
        self.scramble_generator = ScrambleGenerator(min_length=20, max_length=30)

        # Cube string after recognition and cube solution
        self.visualized_cube_string = ""
        self.cube_solution = ""

        # Time for solving time measurement
        self.solving_timer = QTimer(self)

        # Init LEDS
        self.init_led()

    def _pre_quit(self):
        worker = Worker(self.Arduino.led_power, 0)
        worker.signals.finished.connect(self.close)
        self.threadpool.start(worker)

    def _init_solve_cube(self):
        self.recognition_led.value = False
        self.solve_button.setEnabled(False)
        self.solver_timer.current_time_ms = 0
        self.show_solve_timer()
        self._lock_all(True)
        self._init_facelets()

        worker = Worker(self.Arduino.solve, self.cube_solution)
        worker.signals.finished.connect(self.solve_over)

        self.solving_timer.singleShot(25, self.update_solver_timer)
        self.threadpool.start(worker)

    def update_solver_timer(self):
        if not self.Arduino.solve_over:
            self.solver_timer.current_time_ms += 25
            self.solving_timer.singleShot(25, self.update_solver_timer)

    def solve_over(self):
        self.solver_timer.current_time_ms = round(self.Arduino.solve_time, 3) * 1000
        self._lock_all(False)

    def _init_color_recognition(self):
        self._lock_all(True)
        self.recognition_progress.setValue(0)
        self.show_reco_timer()

        self._reinit_cube_solution()

        recognizer = Worker(self._auto_recognition)
        recognizer.signals.progress.connect(self._update_recognition_progress)
        recognizer.signals.finished.connect(partial(self._lock_all, False))
        self.threadpool.start(recognizer)

    def _reinit_cube_solution(self):
        # Re-init cube colors and cube params
        self._init_facelets()
        self.visualized_cube_string = ""
        self.cube_solution = ""

        # Lock the solve button
        self.solve_button.setDisabled(True)

        # Turn off the OK led
        self.recognition_led.value = False

    def _update_recognition_progress(self, vals: list[list]):
        for val in vals:
            self.facelets[val[0]].val = val[1]
        self.recognition_progress.setValue(self.recognition_progress.value() + len(vals))

    def _auto_recognition(self, progress_callback: pyqtSignal):
        self._init_led()
        self.CubeVisualizer.get_all_colors(progress_callback)
        try:
            self.visualized_cube_string = ''.join([f.val for f in self.facelets])
            self.cube_solution = kociemba.solve(self.visualized_cube_string).replace(" ", "-")
            self.recognition_led.setOnColour(QLed.Green)
            self.recognition_led.value = True
            self.Arduino.cube_mirror(self.visualized_cube_string)
            self.solve_button.setEnabled(True)
        except ValueError:  # Kociemba failed to solve -> Bad string
            self.recognition_led.setOnColour(QLed.Red)
            self.recognition_led.value = True
        finally:
            self.hide_timers()

    def _init_auto_scrambling(self):
        scramble, s_len = self.scramble_generator.get_scramble()
        self.hide_timers()
        self.scramble_progress.setMinimum(0)
        self.scramble_progress.setMaximum(s_len)
        self.scramble_progress.setValue(0)
        self.scramble_progress.setHidden(False)
        self._lock_all(True)
        scrambler = Worker(self._auto_scrambling, scramble=scramble)
        scrambler.signals.progress.connect(self._update_scrambling_progress)
        scrambler.signals.finished.connect(self._scrambling_over)
        self.threadpool.start(scrambler)

    def _auto_scrambling(self, scramble: list, progress_callback: pyqtSignal, *args, **kwargs):
        self._reinit_cube_solution()
        nb_move = 0
        self.Arduino.led_power(50)
        self.Arduino.led_pattern("CALI")
        for move in scramble:
            self.Arduino.single_move(move)
            nb_move += 1
            progress_callback.emit(nb_move)
        self.Arduino.led_pattern("RECO")

    def _update_scrambling_progress(self, status: int):
        self.scramble_progress.setValue(status)

    def _scrambling_over(self):
        self._lock_all(False)
        self.scramble_progress.setHidden(True)

    def _lock_all(self, status: bool):
        [x.setDisabled(status) for x in self.simple_move_group.buttons()]
        self.scramble.setDisabled(status)
        self.color_reco_button.setDisabled(status)

    def init_led(self):
        self._lock_all(True)
        worker = Worker(self._init_led)
        worker.signals.finished.connect(partial(self._lock_all, False))
        self.threadpool.start(worker)

    def _init_led(self, *args, **kwargs):
        self.Arduino.led_power(50)
        self.Arduino.led_pattern("RECO")

    def simple_move(self, btn: MoveButton):
        self.hide_timers()
        if self.visualized_cube_string != "":
            # The cube is recognized, we need to reset the leds, and the cube string
            self._reinit_cube_solution()
            worker = Worker(self._init_led)
            worker.signals.finished.connect(partial(self.simple_move, btn))
            self.threadpool.start(worker)
        else:
            self._lock_all(True)
            code = "MOVE " + btn.name
            worker = Worker(self.Arduino.single_move, code)
            worker.signals.finished.connect(partial(self._lock_all, False))
            self.threadpool.start(worker)


if __name__ == "__main__":
    App = QApplication(sys.argv)
    qdarktheme.setup_theme()

    cursor = QCursor(Qt.BlankCursor)
    QApplication.setOverrideCursor(cursor)
    QApplication.changeOverrideCursor(cursor)

    # Create and display the splash screen
    splash_pix = QPixmap('assets/cube_solver.png')
    splash = QSplashScreen(splash_pix, QtCore.Qt.WindowStaysOnTopHint)
    splash.setWindowFlags(QtCore.Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint)
    splash.setEnabled(True)
    progressBar = QProgressBar(splash)
    progressBar.setMaximum(30)
    progressBar.setGeometry(0, splash_pix.height() - 50, splash_pix.width(), 20)
    splash.show()

    for i in range(1, 31):
       progressBar.setValue(i)
       t = time.time()
       while time.time() < t + 0.1:
           App.processEvents()

    parser = ArgumentParser(
        prog='Cube Solver',
        description="Move, Analyze and Solve the Rubik's Cube!",
        epilog='Thanks for using me!')
    parser.add_argument('serial_port')
    parser.add_argument('cam_port')
    parser.add_argument('-f', '--full-screen', action='store_true')

    window = CubeSolver(parser.parse_args())
    window.show()
    splash.finish(window)
    sys.exit(App.exec())