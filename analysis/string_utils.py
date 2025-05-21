import re


def add_decimal_point(string):
    if string[0] != "0":
        return string
    last_zero = string.rfind("0")
    return f"{string[:last_zero+1]}.{string[last_zero+1:]}"


def extract_percentage_and_element(s):
    match = re.search(r"(\d+)([a-zA-Z]+)$", s)

    if match:
        num = match.group(1)
        suf = match.group(2)
        return add_decimal_point(num), suf.capitalize()
    else:
        raise "was unable to get percentage and element from the filename"
