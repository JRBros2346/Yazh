# C0
BEL= '\7' # Bell/Alert
ESC='\33' # Escape

# Fe
CSI=ESC+'[' # Control Sequence Introducer

def SGR(n=''):
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
FONT=[SGR(n) for n in range(11,20)]
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
FG3={
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
def FG8(n=''):
    # Foreground 8-bit
    return SGR("38;5;{n}")
def FG24(n=''):
    # Foreground 24-bit
    return SGR("38;2;{r};{g};{b}")
DEFAULT_FOREGROUND = SGR(39)
BG3={
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
def BG8(n=''):
    # Background 8-bit
    return SGR("48;5;{n}")
def BG24(n=None):
    # Background 24-bit
    return SGR("48;2;{r};{g};{b}")
DEFAULT_BACKGROUND = SGR(49)
DISABLE_PROPORTIONAL_SPACING = SGR(50)
FG4={
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
BG4={
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

if __name__=='__main__':
    print(BEL, 'bell')
    print(BOLD, 'bold',
          ITALIC, 'italic',
          FAINT, 'faint',
          UNDERLINE, 'line below',
          SLOW_BLINK, 'blink slow',
          RAPID_BLINK, 'blink fast',
          INVERT, 'INVERTED',
          CONCEAL, 'hide', RESET+'<-hidden',
          STRIKE, 'line through', RESET)
    for font in FONT:
        print(font,f'font{FONT.index(font)}')
    print(FRAKTUR, 'fraktur',
          BOLD, 'bold', NOT_BOLD, 'notbold',
          BOLD, 'bold', FAINT, 'faint', NORMAL_INTENSITY, 'not bold or faint',
          ITALIC, 'italic', 'notitalic',
          UNDERLINE, 'line below', NOT_UNDERLINED, 'noline below',
          SLOW_BLINK, 'blink slow', RAPID_BLINK, 'blink fast', NOT_BLINKING, 'blink not',
          PROPORTIONAL_SPACING, 'spaced...', RESET,
          INVERT, 'reversed', NOT_REVERSED, 'no reverse',
          CONCEAL, 'hidden', REVEAL, 'nohidden',
          STRIKE, 'striken', NOT_CROSSED_OUT, 'no strike')
    for color in FOREGROUND_3:
        print(FOREGROUND_3[color], color)
    print(DEFAULT_FOREGROUND, 'default')
    for color in BACKGROUND_3:
        print(BACKGROUND_3[color], color)
    print(DEFAULT_BACKGROUND, 'default')
    print(PROPORTIONAL_SPACING, 'spaced...', DISABLE_PROPORTIONAL_SPACING, 'Not Spaced!')
    for color in FOREGROUND_4:
        print(FOREGROUND_4[color], color)
    print(DEFAULT_FOREGROUND, 'default')
    for color in BACKGROUND_4:
        print(BACKGROUND_4[color], color)
    print(DEFAULT_BACKGROUND, 'default')
    input()
    print(RESET)
