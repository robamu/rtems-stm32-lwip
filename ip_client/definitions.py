import enum


class AnsiColors:
    RED = "\x1b[31m"
    GREEN = "\x1b[32m"
    YELLOW = "\x1b[33m"
    BLUE = "\x1b[34m"
    MAGNETA = "\x1b[35m"
    CYAN = "\x1b[36m"
    RESET = "\x1b[0m"


class Protocols(enum.Enum):
    TCPIP_PROT_0_TCP = 0
    TCPIP_PROT_1_UDP = 1


