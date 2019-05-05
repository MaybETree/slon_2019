#!/usr/bin/python3

vertSpacing = 30
horizSpacing = 20
padLeft = 10
padRight = 10
padTop = 10
padBottom = 10
image = """<svg
    version="1.1"
    baseProfile="full"
    width="{0}"
    height="{1}"
    xmlns="http://www.w3.org/2000/svg">
        {2}
    </svg>"""
line = """<line x1="{0}" y1="{1}" x2="{2}" y2="{3}" stroke="black" />\n"""
circle = """<circle cx="{0}" cy="{1}" r="5" fill="none" stroke="black" />\n"""

drawing = ''
levels = [0,0]
maxWidth = 0
maxHeight = 0
tree = eval(input())

def scan(tree, depth = 0):
    global levels, drawing, maxWidth, maxHeight
    if len(levels) == depth+1:
        levels += [0]

    if depth > maxHeight:
        maxHeight = depth

    if levels[depth] > maxWidth:
        maxWidth = levels[depth]

    drawing += circle.format(
        levels[depth] * horizSpacing + padLeft,
        depth * vertSpacing + padTop,
        
    )
        
    for branch in tree:
        drawing += line.format(
            levels[depth] * horizSpacing + padLeft,
            depth * vertSpacing + padTop,
            levels[depth+1] * horizSpacing + padLeft,
            (depth+1) * vertSpacing + padTop,
        )
        scan(branch, depth+1)
        
        levels[depth+1] += 1

scan(tree)

image = image.format(
    maxWidth * horizSpacing + padLeft + padRight,
    maxHeight * vertSpacing + padTop + padBottom,
    drawing
)

print(image)