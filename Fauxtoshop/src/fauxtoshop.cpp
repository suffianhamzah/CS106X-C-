// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: rewrite this comment

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"
#include "random.h"
#include "math.h"

using namespace std;

static const int    WHITE = 0xFFFFFF;
static const int    BLACK = 0x000000;
static const int    GREEN = 0x00FF00;

static bool     openImageFromFilename(GBufferedImage &img, string filename);
static bool 	saveImageToFilename(const GBufferedImage &img, string filename);
static void     getMouseClickLocation(int &row, int &col);
void            imgScatter(GBufferedImage &img,const Grid<int> &original, int radius);
void            edgeDetect(GBufferedImage &img, const Grid<int> &original, int threshold);
void            edgeCheck(GBufferedImage &img, const Grid<int> &ori, int row1, int row2, int col1, int col2, bool &isEdge, int threshold);
int             pixelDiff(GBufferedImage &img, int pixel, int pixel2);
void            greenScreen(GBufferedImage &img2, const Grid<int> &original, const Grid<int> &sticker, int threshold, int row3, int col3);
void            getImgFile(GBufferedImage &img, string prompt, bool firstPrompt , bool& isEmpty);
int             getVal(string prompt, int mode);
/* Depending on how you approach your problem decomposition, you
 * may want to rewrite some of these lines, move them inside loops,
 * or move them inside helper functions, etc.
 *
 * TODO: rewrite this comment.
 */
int main() {

    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setVisible(true);
    while(true)
    {
        GBufferedImage img;
        bool isEmpty = false;
        cout << "Welcome to Fauxtoshop!" << endl;
        getImgFile(img, "Enter name of the image file to open (or blank to quit): ", true ,isEmpty);
        if (isEmpty) {
            break;
        }
        gw.setSize(img.getWidth(), img.getHeight());
        gw.add(&img,0,0);
        cout << "Which image filter would you like to apply?" << endl << "   1 - Scatter" << endl << "   2 - Edge Detection" << endl;
        cout << "   3 - \"Green Screen\" with another image" << endl << "   4 - Compare image with another image" << endl;
        Grid<int> original = img.toGrid();
        bool choiceExist = false;
        while(!choiceExist)
        {
            int choiceNo = getInteger("Your choice: ", "Number not in choice");
            switch (choiceNo)
            {
            case 1:
            {
                int radius = getVal("Enter degree of scatter [1-100]: ", 100);
                imgScatter(img, original, radius);
                choiceExist = true;
                break;
            }
            case 2:
            {
                int threshold = getVal("Enter Threshold for Edge Detection: ", 10000);
                edgeDetect(img, original, threshold);
                choiceExist = true;
                break;
            }
            case 3:
            {
                GBufferedImage img2;
                cout << "Now choose another file to add to your background image." << endl;
                getImgFile(img2, "Enter name of imagefile to open: ", false, isEmpty);
                Grid<int> sticker = img2.toGrid();
                int val = getVal("Now choose a tolerance threshold: ", 10000);
                int row3 = -1;
                int col3 = -1;
                while (row3 < 0 && col3 < 0)
                {
                    string xy = getLine("Enter location to place image as \"(row,col)\" (or blank to use mouse): ");
                    if (xy != "") {
                        stringstream ss(xy);
                        char a,b;
                        ss >> a >> row3 >> b >> col3;
                    } else {
                        getMouseClickLocation(row3, col3);
                        cout << "Chosen location: (" << row3 << "," << col3 << ")" << endl;
                    }
                }
                greenScreen(img,original, sticker, val, row3, col3);
                choiceExist = true;
                break;
            }
            case 4:
            {
                GBufferedImage compimg;
                cout << "Now choose another Image file to compare to." << endl;
                getImgFile(compimg, "Enter name of image file to open: ", false, isEmpty);
                int difference = img.countDiffPixels(compimg);
                if (difference == 0) {
                    cout << "These images are the same!" << endl;
                } else {
                    cout << "These images differ in " << difference << " pixel locations!" << endl;
                }
                choiceExist = true;
                break;
            }
            default:
            {
                cout << "Option does not exist" << endl;
            }
            }
        }
        gw.add(&img, 0, 0);
        string savename = getLine("Enter Filename to save image (or blank to skip saving): ");
        if (savename == "")
        {
            isEmpty = true;
        }
        while (!isEmpty && !saveImageToFilename(img,savename))
        {
            savename = getLine("Enter Filename to save image (or blank to skip saving): ");
            if (savename == "")
            {
                isEmpty = true;
            }
        }
        //int row, col;
        //
        gw.clear();
    }
    return 0;
}


/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to open the image file 'filename'.
 *
 * This function returns true when the image file was successfully
 * opened and the 'img' object now contains that image, otherwise it
 * returns false.
 */
static bool openImageFromFilename(GBufferedImage &img, string filename) {
    try { img.load(filename); }
    catch (...) { return false; }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Attempts to save the image file to 'filename'.
 *
 * This function returns true when the image was successfully saved
 * to the file specified, otherwise it returns false.
 */
static bool saveImageToFilename(const GBufferedImage &img, string filename) {
    try {
        img.save(filename);
    } catch (...) {
        return false;
    }
    return true;
}

/* STARTER CODE HELPER FUNCTION - DO NOT EDIT
 *
 * Waits for a mouse click in the GWindow and reports click location.
 *
 * When this function returns, row and col are set to the row and
 * column where a mouse click was detected.
 */
static void getMouseClickLocation(int &row, int &col) {
    GMouseEvent me;
    do {
        me = getNextEvent(MOUSE_EVENT);
    } while (me.getEventType() != MOUSE_CLICKED);
    row = me.getY();
    col = me.getX();
}

void imgScatter(GBufferedImage &img, const Grid<int> &original, int radius) {
    Grid<int> ori2 = original;
    for (int row = 0 ; row < original.numRows(); row++)
    {
        for (int col = 0; col < original.numCols(); col++)
        {
            int newRow = -1;
            int newCol = -1;
            while (!original.inBounds(newRow, newCol))
            {
                newRow = randomInteger(max(row - radius, 0), min(row + radius,original.numRows()));
                newCol = randomInteger(max(col - radius, 0), min(col + radius,original.numRows()));
            }
            ori2[row][col] = original[newRow][newCol];
        }
    }
    img.fromGrid(ori2);
}

void edgeDetect(GBufferedImage &img, const Grid<int> &original, int threshold)
{
    Grid<int> ori2 = original;

    for (int row = 0 ; row < original.numRows(); row++)
    {
        for (int col = 0; col < original.numCols(); col++)
        {
            //check all adjacent squares
            //top left
            bool isEdge = false;
            edgeCheck(img, original, row, row-1, col, col-1, isEdge, threshold);
            edgeCheck(img, original, row, row-1, col, col, isEdge, threshold);
            edgeCheck(img, original, row, row-1, col, col+1, isEdge, threshold);
            edgeCheck(img, original, row, row, col, col-1, isEdge, threshold);
            edgeCheck(img, original, row, row-1, col, col+1, isEdge, threshold);
            edgeCheck(img, original, row, row+1, col, col-1, isEdge, threshold);
            edgeCheck(img, original, row, row+1, col, col, isEdge, threshold);
            edgeCheck(img, original, row, row+1, col, col+1, isEdge, threshold);
            if (isEdge)
            {
                ori2[row][col] = BLACK;
            }
            else
            {
                ori2[row][col] = WHITE;
            }
        }
    }
    img.fromGrid(ori2);
}

void edgeCheck(GBufferedImage &img, const Grid<int>& ori, int row1, int row2, int col1, int col2, bool& isEdge, int threshold)
{
    if (isEdge)
    {
        return;
    }

    if (!ori.inBounds(row2,col2))
    {
        return;
    }

    if (pixelDiff(img, ori[row1][col1],ori[row2][col2]) > threshold)
    {
        isEdge = true;
    }
}

int pixelDiff(GBufferedImage &img, int pixel, int pixel2)
{
    int red1, blue1, green1,red2, blue2, green2;
    img.getRedGreenBlue(pixel, red1, green1, blue1);
    img.getRedGreenBlue(pixel2, red2, green2, blue2);
    return max(max(abs(red1-red2), abs(blue1-blue2)),abs(green1-green2));
}

void greenScreen(GBufferedImage &img, const Grid<int> &original,const Grid<int> &sticker, int threshold, int row3, int col3)
{
    Grid<int> ori2 = original;
    int maxrow = min(original.numRows() - row3, sticker.numRows());
    int maxcol = min(original.numCols() - col3, sticker.numCols());
    for (int row = 0 ; row < maxrow; row++)
    {
        int coltemp = col3;
        for (int col = 0 ; col < maxcol; col++)
        {
            if (pixelDiff(img, GREEN , sticker[row][col]) > threshold )
            {
                ori2[row3][coltemp] = sticker[row][col];
            }
            coltemp++;
        }
        row3++;
    }
    img.fromGrid(ori2);;
}

void getImgFile(GBufferedImage &img, string prompt, bool firstPrompt, bool &isEmpty)
{
    string filename= getLine(prompt);
    if (firstPrompt && filename == "")
    {
        isEmpty = true;
        return;
    }
    cout << "Opening image file, may take a minute..." << endl;
    while (!openImageFromFilename(img,filename))
    {
        filename = getLine(prompt);
        if (filename == "")
        {
            isEmpty = true;
            return;
        }
        cout << "Opening image file, may take a minute..." << endl;
    }
}

int getVal(string prompt, int mode)
{
    int val = 0;
    while (val < 1 || val > mode)
    {
        val = getInteger(prompt);
    }

    return val;
}
