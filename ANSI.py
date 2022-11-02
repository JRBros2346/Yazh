# C0
BEL= '\7' # Bell/Alert
ESC='\33' # Escape

# Fe
CSI=ESC+'[' # Control Sequence Introducer

# ANSI Control Sequences
def CUU(n=None):
    # Cursor Up
    return f'{CSI}{n}A'
def CUD(n=None):
    # Cursor Down
    return f'{CSI}{n}B'
def CUF(n=None):
    # Cursor Forward
    return f'{CSI}{n}C'
def CUB(n=None):
    # Cursor Backward
    return f'{CSI}{n}D'
def CUP(n=None,m=None):
    # Cursor Position
    return f'{CSI}{n};{m}H'
def EL(n=None):
    # Erase in Line
    # -------------
    # 0: Cursor to End of Line
    # 1: Cursor to Beginning of Line
    # 2: Entire Line
    return f'{CSI}{n}K'
def HVP(n=None,m=None):
    # Horizontal Vertical Position
    return f'{CSI}{n};{m}f'
def SGR(n=None):
    return f'{CSI}{n}m'

# Some SGR's 
RESET = NORMAL = SGR()
BOLD = INCREASED_INTENSITY = SGR(1)
FAINT = DECREASED_INTENSITY = DIM = SGR(2)
ITALIC = SGR(3)
UNDERLINE = SGR(4)
SLOW_BLINK = SGR(5)
RAPID_BLINK = SGR(6)
REVERSE_VIDEO = INVERT = SGR(7)
CONCEAL = HIDE = SGR(8)
CROSSED_OUT = STRIKE = SGR(10)
ALTERNATIVE_FONT=[SGR(n) for n in range(11,20)]
FRAKTUR = GOTHIC = SGR(20)
NOT_BOLD = SGR(21)
NORMAL_INTENSITY = SGR(22)
NEITHER_ITALIC_NOR_BLOCKLETTER = SGR(23)
NOT_UNDERLINED = SGR(24)
NOT_BLINKING = SGR(25)
PROPORTIONAL_SPACING = SGR(26)
NOT_REVERSED = SGR(27)
REVEAL = SGR(28)
NOT_CROSSED_OUT = SGR(29)
FOREGROUND_3={
    # Foreground 3-bit
    "BLACK": SGR(30),
    "RED": SGR(31),
    "GREEN": SGR(32),
    "YELLOW": SGR(33),
    "BLUE": SGR(34),
    "MAGENTA": SGR(35),
    "CYAN": SGR(36),
    "WHITE": SGR(37)
}
def FOREGROUND_8(n=None):
    # Foreground 8-bit
    return SGR("38;5;{n}")
def FOREGROUND_24(n=None):
    # Foreground 24-bit
    return SGR("38;2;{r};{g};{b}")
DEFAULT_FOREGROUND = SGR(39)
BACKGROUND_3={
    # Background 3-bit
    "BLACK": SGR(40),
    "RED": SGR(41),
    "GREEN": SGR(42),
    "YELLOW": SGR(43),
    "BLUE": SGR(44),
    "MAGENTA": SGR(45),
    "CYAN": SGR(46),
    "WHITE": SGR(47)
}
def BACKGROUND_8(n=None):
    # Background 8-bit
    return SGR("48;5;{n}")
def FOREGROUND_24(n=None):
    # Background 24-bit
    return SGR("48;2;{r};{g};{b}")
DEFAULT_BACKGROUND = SGR(49)
DISABLE_PROPORTIONAL_SPACING = SGR(50)
FOREGROUND_4={
    # Foreground 4-bit (Bright)
    "BLACK": SGR(90),
    "RED": SGR(91),
    "GREEN": SGR(92),
    "YELLOW": SGR(93),
    "BLUE": SGR(94),
    "MAGENTA": SGR(95),
    "CYAN": SGR(96),
    "WHITE": SGR(97)
}
BACKGROUND_4={
    # Background 4-bit (Bright)
    "BLACK": SGR(100),
    "RED": SGR(101),
    "GREEN": SGR(102),
    "YELLOW": SGR(103),
    "BLUE": SGR(104),
    "MAGENTA": SGR(105),
    "CYAN": SGR(106),
    "WHITE": SGR(107)
}
