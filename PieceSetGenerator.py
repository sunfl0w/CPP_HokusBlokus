from PIL import Image
import os
import time


pieceSetTileCount = 21


def main():
    print("Starting to generate piece sets")
    startTime = time.time_ns()

    basePieceSets = []
    edgePieceSets = []
    cornerPieceSets = []

    print("Starting to generate base piece sets")

    # Populate base piece sets
    basePieceSets.append(PieceSet("BlokusPieceSet_N", Image.open("resources/BlokusPieceSet_N.pbm")))
    basePieceSets.append(PieceSet("BlokusPieceSet_E", generateRotatetPieceSetImage(basePieceSets[0].pieceSetImage, 5, 270)))
    basePieceSets.append(PieceSet("BlokusPieceSet_S", generateRotatetPieceSetImage(basePieceSets[0].pieceSetImage, 5, 180)))
    basePieceSets.append(PieceSet("BlokusPieceSet_W", generateRotatetPieceSetImage(basePieceSets[0].pieceSetImage, 5, 90)))

    basePieceSets.append(PieceSet("BlokusPieceSet_NF", generateFlippedPieceSetImage(basePieceSets[0].pieceSetImage, 5)))
    basePieceSets.append(PieceSet("BlokusPieceSet_EF", generateFlippedPieceSetImage(basePieceSets[1].pieceSetImage, 5)))
    basePieceSets.append(PieceSet("BlokusPieceSet_SF", generateFlippedPieceSetImage(basePieceSets[2].pieceSetImage, 5)))
    basePieceSets.append(PieceSet("BlokusPieceSet_WF", generateFlippedPieceSetImage(basePieceSets[3].pieceSetImage, 5)))

    print("Starting to generate edge piece sets")

    # Populate edge piece sets
    for baseSet in basePieceSets:
        pieceSetIdentifier = baseSet.name.split('_')[1]
        name = "BlokusPieceSet_" + pieceSetIdentifier + "E"
        edgePieceSets.append(PieceSet(name, generateEdgePieceSetImage(baseSet.pieceSetImage, 5)))

    print("Starting to generate corner piece sets")

    # Populate corner piece sets
    for baseSet in basePieceSets:
        pieceSetIdentifier = baseSet.name.split('_')[1]
        name = "BlokusPieceSet_" + pieceSetIdentifier + "C"
        cornerPieceSets.append(PieceSet(name, generateCornerPieceSetImage(baseSet.pieceSetImage, 5)))

    # Create directory for saving if none was found
    cwd = os.getcwd()
    generatedResourcePath = os.path.join(cwd, "generatedResources")

    if not os.path.exists(generatedResourcePath):
        os.mkdir(generatedResourcePath)

    print("Saving generated piece sets")
    # Save base sets
    for baseSet in basePieceSets:
        baseSet.pieceSetImage.save(os.path.join(generatedResourcePath, baseSet.name + ".pbm"))

    # Save edge sets
    for edgeSet in edgePieceSets:
        edgeSet.pieceSetImage.save(os.path.join(generatedResourcePath, edgeSet.name + ".pbm"))

    # Save corner sets
    for cornerSet in cornerPieceSets:
        cornerSet.pieceSetImage.save(os.path.join(generatedResourcePath, cornerSet.name + ".pbm"))

    print("Piece sets generated successfully in {} ms.".format((time.time_ns() - startTime) / 1000000))


def generateRotatetPieceSetImage(pieceSetImage, tileSize, rotationDegrees):
    rotatedPieceSet = Image.new('1', pieceSetImage.size)

    minX = 0
    minY = 0
    maxX = tileSize
    maxY = tileSize
    for i in range(pieceSetTileCount):
        pieceShape = pieceSetImage.crop((minX, minY, maxX, maxY))
        pieceShape = pieceShape.rotate(rotationDegrees)

        pieceShape = cropImageToContent(pieceShape)

        rotatedPieceSet.paste(pieceShape, (minX, minY))

        minX = maxX % pieceSetImage.width
        maxX = minX + tileSize
        if (minX == 0):
            minY = maxY
            maxY += tileSize

    return rotatedPieceSet


def generateFlippedPieceSetImage(pieceSetImage, tileSize):
    flippedPieceSet = Image.new('1', pieceSetImage.size)

    minX = 0
    minY = 0
    maxX = tileSize
    maxY = tileSize
    for i in range(pieceSetTileCount):
        pieceShape = pieceSetImage.crop((minX, minY, maxX, maxY))
        pieceShape = pieceShape.transpose(Image.FLIP_TOP_BOTTOM)

        pieceShape = cropImageToContent(pieceShape)

        flippedPieceSet.paste(pieceShape, (minX, minY))

        minX = maxX % pieceSetImage.width
        maxX = minX + tileSize
        if (minX == 0):
            minY = maxY
            maxY += tileSize

    return flippedPieceSet


def cropImageToContent(image):
    contentMinX = image.width
    contentMinY = image.height
    contentMaxX = 0
    contentMaxY = 0

    for x in range(image.width):
        for y in range(image.height):
            if image.getpixel((x, y)):
                contentMinX = min(contentMinX, x)
                contentMinY = min(contentMinY, y)
                contentMaxX = max(contentMaxX, x + 1)
                contentMaxY = max(contentMaxY, y + 1)

    return image.crop((contentMinX, contentMinY, contentMaxX, contentMaxY))


def generateEdgePieceSetImage(pieceSetImage, tileSize):
    edgePieceSet = Image.new('1', (int((tileSize + 2) * pieceSetImage.width / tileSize), int((tileSize + 2) * pieceSetImage.width / tileSize)))

    minX = 0
    minY = 0
    maxX = tileSize
    maxY = tileSize
    for i in range(pieceSetTileCount):
        pieceShape = pieceSetImage.crop((minX, minY, maxX, maxY))
        pieceShapeExtended = Image.new('1', (tileSize + 2, tileSize + 2))
        pieceShapeExtended.paste(pieceShape, (1, 1))

        pieceEdgeShape = Image.new('1', (tileSize + 2, tileSize + 2))

        for x in range(pieceShapeExtended.width):
            for y in range(pieceShapeExtended.height):
                if isPixelEdge(pieceShapeExtended, x, y):
                    pieceEdgeShape.putpixel((x, y), True)

        pieceEdgeShape = cropImageToContent(pieceEdgeShape)

        edgePieceSet.paste(pieceEdgeShape, (int(minX / tileSize * 7), int(minY / tileSize * 7)))

        minX = maxX % pieceSetImage.width
        maxX = minX + tileSize
        if (minX == 0):
            minY = maxY
            maxY += tileSize

    return edgePieceSet


def generateCornerPieceSetImage(pieceSetImage, tileSize):
    cornerPieceSet = Image.new('1', (int((tileSize + 2) * pieceSetImage.width / tileSize), int((tileSize + 2) * pieceSetImage.width / tileSize)))

    minX = 0
    minY = 0
    maxX = tileSize
    maxY = tileSize
    for i in range(pieceSetTileCount):
        pieceShape = pieceSetImage.crop((minX, minY, maxX, maxY))
        pieceShapeExtended = Image.new('1', (tileSize + 2, tileSize + 2))
        pieceShapeExtended.paste(pieceShape, (1, 1))

        pieceCornerShape = Image.new('1', (tileSize + 2, tileSize + 2))

        for x in range(pieceShapeExtended.width):
            for y in range(pieceShapeExtended.height):
                if isPixelCorner(pieceShapeExtended, x, y):
                    pieceCornerShape.putpixel((x, y), True)

        pieceCornerShape = cropImageToContent(pieceCornerShape)

        cornerPieceSet.paste(pieceCornerShape, (int(minX / tileSize * 7), int(minY / tileSize * 7)))

        minX = maxX % pieceSetImage.width
        maxX = minX + tileSize
        if (minX == 0):
            minY = maxY
            maxY += tileSize

    return cornerPieceSet


def isPixelEdge(image, x, y):
    if not image.getpixel((x, y)):
        for edgeCoord in getEdgeCoordinatesOnImage(image, x, y):
            if image.getpixel(edgeCoord):
                return True
    return False


def getEdgeCoordinatesOnImage(image, x, y):
    edgeCoords = [(x, y + 1), (x + 1, y), (x, y - 1), (x - 1, y)]
    inImageEdgeCoords = []

    for edgeCoord in edgeCoords:
        if not(edgeCoord[0] < 0 or edgeCoord[0] >= image.width or edgeCoord[1] < 0 or edgeCoord[1] >= image.height):
            inImageEdgeCoords.append(edgeCoord)
    return inImageEdgeCoords


def isPixelCorner(image, x, y):
    if not image.getpixel((x, y)) and not isPixelEdge(image, x, y):
        for cornerCoord in getCornerCoordinatesOnImage(image, x, y):
            if image.getpixel(cornerCoord):
                return True
    return False


def getCornerCoordinatesOnImage(image, x, y):
    cornerCoords = [(x + 1, y + 1), (x + 1, y - 1), (x - 1, y - 1), (x - 1, y + 1)]
    inImageCornerCoords = []

    for cornerCoord in cornerCoords:
        if not(cornerCoord[0] < 0 or cornerCoord[0] >= image.width or cornerCoord[1] < 0 or cornerCoord[1] >= image.height):
            inImageCornerCoords.append(cornerCoord)
    return inImageCornerCoords


def drawImageInConsole(image):
    print("-----------")
    for y in range(image.height):
        line = ""
        for x in range(image.width):
            if(image.getpixel((x, y))):
                line += "1"
            else:
                line += "0"
        print(line)
    print("-----------")


class PieceSet:
    name = "Unnamed"
    pieceSetImage = None

    def __init__(self, name, pieceSetImage):
        self.name = name
        self.pieceSetImage = pieceSetImage


if __name__ == "__main__":
    main()