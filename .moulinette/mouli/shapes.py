"""Generateurs des sorties attendues (rush 1, star, count_island...)."""

RUSH_CHARS = {
    # coin haut-gauche, haut-droit, bas-gauche, bas-droit, horizontal, vertical
    1: ("o", "o", "o", "o", "-", "|"),
    2: ("/", "\\", "\\", "/", "*", "*"),
    3: ("A", "A", "C", "C", "B", "B"),
    4: ("A", "C", "A", "C", "B", "B"),
    5: ("A", "C", "C", "A", "B", "B"),
}


def rush1(number, x, y):
    """Sortie attendue de rush(x, y) pour l'assignement `number`, ou None
    si la taille est invalide."""
    if x <= 0 or y <= 0:
        return None
    tl, tr, bl, br, hor, ver = RUSH_CHARS[number]
    if number != 1 and (x == 1 or y == 1):
        return "".join(hor * x + "\n" for _ in range(y))
    lines = []
    for i in range(y):
        row = ""
        for j in range(x):
            top, bottom = i == 0, i == y - 1
            left, right = j == 0, j == x - 1
            if (top or bottom) and (left or right):
                row += (tl if left else tr) if top else (bl if left else br)
            elif top or bottom:
                row += hor
            elif left or right:
                row += ver
            else:
                row += " "
        lines.append(row + "\n")
    return "".join(lines)


def star(size):
    if size == 0:
        return ""
    gap = 1 if size == 1 else 2 * size - 3
    width = 2 * (2 * size + 1) + gap
    center = width // 2
    rows = []

    def line(cols):
        chars = [" "] * (max(cols) + 1)
        for col in cols:
            chars[col] = "*"
        return "".join(chars)
    top = [line([center - i, center + i]) for i in range(size)]
    bar = "*" * (2 * size + 1) + " " * gap + "*" * (2 * size + 1)
    middle = [line([j, width - 1 - j])
              for j in list(range(1, size + 1)) + list(range(size - 1, 0, -1))]
    rows = top + [bar] + middle + [bar] + top[::-1]
    return "".join(row + "\n" for row in rows)


def count_island(world):
    """Renvoie (nombre d'iles, carte numerotee)."""
    grid = [list(row) for row in world]
    count = 0
    for y, row in enumerate(grid):
        for x, cell in enumerate(row):
            if cell != "X":
                continue
            stack = [(y, x)]
            digit = str(count)
            while stack:
                cy, cx = stack.pop()
                if 0 <= cy < len(grid) and 0 <= cx < len(grid[cy]) and grid[cy][cx] == "X":
                    grid[cy][cx] = digit
                    stack += [(cy + 1, cx), (cy - 1, cx), (cy, cx + 1), (cy, cx - 1)]
            count += 1
    return count, ["".join(row) for row in grid]


def rush3_answer(text):
    """Reponse attendue du Final Stumper pour une entree donnee."""
    lines = text.split("\n")
    if text.endswith("\n"):
        lines = lines[:-1]
    if not lines or not lines[0]:
        return "none"
    x, y = len(lines[0]), len(lines)
    found = ["[rush1-%d] %d %d" % (n, x, y) for n in range(1, 6)
             if rush1(n, x, y) == text]
    return " || ".join(found) if found else "none"
