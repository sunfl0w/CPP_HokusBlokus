from PIL import Image
import os


def main():
    pieceShapeImageN = Image.open("resources/BlokusPieceShapesN.pbm")
    pieceShapeImageE = generateRotatetTiledImage(pieceShapeImageN, 5, 270)
    pieceShapeImageS = generateRotatetTiledImage(pieceShapeImageN, 5, 180)
    pieceShapeImageW = generateRotatetTiledImage(pieceShapeImageN, 5, 90)

    pieceShapeImageNF = generateFlippedTiledImage(pieceShapeImageN, 5)
    pieceShapeImageEF = generateFlippedTiledImage(pieceShapeImageE, 5)
    pieceShapeImageSF = generateFlippedTiledImage(pieceShapeImageS, 5)
    pieceShapeImageWF = generateFlippedTiledImage(pieceShapeImageW, 5)

    cwd = os.getcwd()
    generatedResourcePath = os.path.join(cwd, "generatedResources")

    if not os.path.exists(generatedResourcePath):
        os.mkdir(generatedResourcePath)

    pieceShapeImageN.save(os.path.join(generatedResourcePath, "BlokusPieceShapesN.pbm"))
    pieceShapeImageE.save(os.path.join(generatedResourcePath, "BlokusPieceShapesE.pbm"))
    pieceShapeImageS.save(os.path.join(generatedResourcePath, "BlokusPieceShapesS.pbm"))
    pieceShapeImageW.save(os.path.join(generatedResourcePath, "BlokusPieceShapesW.pbm"))

    pieceShapeImageNF.save(os.path.join(generatedResourcePath, "BlokusPieceShapesNF.pbm"))
    pieceShapeImageEF.save(os.path.join(generatedResourcePath, "BlokusPieceShapesEF.pbm"))
    pieceShapeImageSF.save(os.path.join(generatedResourcePath, "BlokusPieceShapesSF.pbm"))
    pieceShapeImageWF.save(os.path.join(generatedResourcePath, "BlokusPieceShapesWF.pbm"))


def loadPieceShapeDimensionData():
    dimensionDataFile = open("resources/BlokusPieceShapeDimensions.txt", "r")
    dimensionDataString = dimensionDataFile.read()
    dimensionDataList = []

    for i in range(21):
        dimensionDataList.append((dimensionDataString[i * 2], dimensionDataString[i * 2 + 1]))

    dimensionDataFile.close()
    return dimensionDataList


def generateRotatetTiledImage(image, tileSize, rotationDegrees):
    tiledRotatedImage = Image.new('1', image.size)

    minX = 0
    minY = 0
    maxX = tileSize
    maxY = tileSize
    for i in range(21):
        pieceShape = image.crop((minX, minY, maxX, maxY))
        pieceShape = pieceShape.rotate(rotationDegrees)

        pieceShape = cropImageToContent(pieceShape)

        tiledRotatedImage.paste(pieceShape, (minX, minY))

        minX = maxX % image.width
        maxX = minX + tileSize
        if (minX == 0):
            minY = maxY
            maxY += tileSize

    return tiledRotatedImage


def generateFlippedTiledImage(image, tileSize):
    tiledFlippedImage = Image.new('1', image.size)

    minX = 0
    minY = 0
    maxX = tileSize
    maxY = tileSize
    for i in range(21):
        pieceShape = image.crop((minX, minY, maxX, maxY))
        pieceShape = pieceShape.transpose(Image.FLIP_TOP_BOTTOM)

        pieceShape = cropImageToContent(pieceShape)

        tiledFlippedImage.paste(pieceShape, (minX, minY))

        minX = maxX % image.width
        maxX = minX + tileSize
        if (minX == 0):
            minY = maxY
            maxY += tileSize

    return tiledFlippedImage


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


if __name__ == "__main__":
    main()
