import time
from machine import Pin

FULL_ROTATION = int(4075.7728395061727 / 8)
LOW = 0
HIGH = 1
HALF_STEP = [
    [LOW, LOW, LOW, HIGH],
    [LOW, LOW, HIGH, HIGH],
    [LOW, LOW, HIGH, LOW],
    [LOW, HIGH, HIGH, LOW],
    [LOW, HIGH, LOW, LOW],
    [HIGH, HIGH, LOW, LOW],
    [HIGH, LOW, LOW, LOW],
    [HIGH, LOW, LOW, HIGH],
]

FULL_STEP = [
    [HIGH, LOW, HIGH, LOW],
    [LOW, HIGH, HIGH, LOW],
    [LOW, HIGH, LOW, HIGH],
    [HIGH, LOW, LOW, HIGH]
]


class Command:
    """Tell a stepper to move X many steps in direction"""

    def __init__(self, stepper, steps, direction):
        self.stepper = stepper
        self.steps = steps
        self.direction = direction


class Stepper:
    def __init__(self, mode, pin1, pin2, pin3, pin4, delay=0.001):
        self.mode = mode
        self.pin1 = Pin(pin1, Pin.OUT)
        self.pin2 = Pin(pin2, Pin.OUT)
        self.pin3 = Pin(pin3, Pin.OUT)
        self.pin4 = Pin(pin4, Pin.OUT)
        self.delay = delay  # Recommend 10+ for FULL_STEP, 1 is OK for HALF_STEP
        # Initialize all to 0
        self.reset()

    def step(self, count, direction):
        """Rotate count steps. direction = -1 means backwards"""
        for x in range(count):
            for bit in self.mode[::direction]:
                self.pin1.value(bit[0])
                self.pin2.value(bit[1])
                self.pin3.value(bit[2])
                self.pin4.value(bit[3])
                time.sleep(self.delay)
        self.reset()

    def reset(self):
        # Reset to 0, no holding, these are geared, you can't move them
        self.pin1.value(0)
        self.pin2.value(0)
        self.pin3.value(0)
        self.pin4.value(0)


class Driver:
    """Drive a set of motors, each with their own commands"""

    @staticmethod
    def run(commands):
        """Takes a list of commands and interleaves their step calls"""

        # Work out total steps to take
        max_steps = sum([c.steps for c in commands])

        count = 0
        while count != max_steps:
            for command in commands:
                # we want to interleave the commands
                if command.steps > 0:
                    command.stepper.step(1, command.direction)
                    command.steps -= 1
                    count += 1


if __name__ == '__main__':
    s1 = Stepper(HALF_STEP, 9, 8, 7, 6)

    runner = Driver()
    runner.run([Command(s1, FULL_ROTATION, 1)])
