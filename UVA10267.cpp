#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define MAX_SIZE 250
#define MAX_NAME_LEN 10000
#define NUM_DIRECTION 4
#define DEFAULT_COLOR 'O'
#define EXIT_CMD 'X'
#define CLEAR_CMD 'C'
#define INIT_CMD 'I'
#define FILL_CMD 'F'
#define SETV_CMD 'V'
#define SETH_CMD 'H'
#define SETSUB_CMD 'K'
#define SETSINGLE_CMD 'L'
#define WRITE_CMD 'S'

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

void setColor(char colorGrid[][MAX_SIZE + 1], int topLeftRow, int topLeftCol, int bottomRightRow, int bottomRightCol, char color);
void fillRegion(char colorGrid[][MAX_SIZE + 1], int numRow, int numCol, int startRow, int startCol, char color);
bool isValidCell(int row, int col, int numRow, int numCol);
void writePicture(char gridColor[][MAX_SIZE + 1], int numRow, int numCol, char name[]);

int main(void)
{
	int numRow, numCol, fromRow, toRow, fromCol, toCol, temp;
	char name[MAX_NAME_LEN + 1], cmd[MAX_NAME_LEN + 1], trash[MAX_NAME_LEN + 1],
	     colorGrid[MAX_SIZE][MAX_SIZE + 1], color[MAX_NAME_LEN + 1]; 

	while(1)
	{
		scanf("%s", cmd);
		if(cmd[0] == EXIT_CMD)
			break;

		switch(cmd[0])
		{
			case INIT_CMD:
			{
				scanf("%d %d", &numCol, &numRow);
				setColor(colorGrid, 0, 0, numRow - 1, numCol - 1, DEFAULT_COLOR);
				break;
			}
			case CLEAR_CMD:
			{
				setColor(colorGrid, 0, 0, numRow - 1, numCol - 1, DEFAULT_COLOR);
				break;
			}
			case SETSINGLE_CMD:
			{
				scanf("%d %d %s", &fromCol, &fromRow, color);
				fromRow--;
				fromCol--;
				setColor(colorGrid, fromRow, fromCol, fromRow, fromCol, color[0]);
				break;
			}
			case SETV_CMD:
			{
				scanf("%d %d %d %s", &fromCol, &fromRow, &toRow, color);
				fromCol--;
				fromRow--;
				toRow--;
				if(fromRow > toRow)
				{
					temp = fromRow;
					fromRow = toRow;
					toRow = temp;
				}
				setColor(colorGrid, fromRow, fromCol, toRow, fromCol, color[0]);
				break;
			}
			case SETH_CMD:
			{
				scanf("%d %d %d %s", &fromCol, &toCol, &fromRow, color);
				fromCol--;
				toCol--;
				fromRow--;
				if(fromCol > toCol)
				{
					temp = fromCol;
					fromCol = toCol;
					toCol = temp;
				}
				setColor(colorGrid, fromRow, fromCol, fromRow, toCol, color[0]);
				break;
			}
			case SETSUB_CMD:
			{
				scanf("%d %d %d %d %s", &fromCol, &fromRow, &toCol, &toRow, color);
				fromCol--;
				toCol--;
				fromRow--;
				toRow--;
				setColor(colorGrid, fromRow, fromCol, toRow, toCol, color[0]);
				break;
			}
			case FILL_CMD:
			{
				scanf("%d %d %s", &fromCol, &fromRow, color);
				fromRow--;
				fromCol--;
				fillRegion(colorGrid, numRow, numCol, fromRow, fromCol, color[0]);
				break;
			}
			case WRITE_CMD:
			{
				scanf("%s", name);
				writePicture(colorGrid, numRow, numCol, name);
				break;
			}
			default:
				// Invalid command. Ignore the whole line
				gets(trash);
		}
	}
	return 0;
}

void setColor(char colorGrid[][MAX_SIZE + 1], int topLeftRow, int topLeftCol, int bottomRightRow, int bottomRightCol, char color)
{
	int row, col;

	for(row = topLeftRow; row <= bottomRightRow; row++)
		for(col = topLeftCol; col <= bottomRightCol; col++)
			colorGrid[row][col] = color;
}

void fillRegion(char colorGrid[][MAX_SIZE + 1], int numRow, int numCol, int startRow, int startCol, char color)
{
	char originalColor = colorGrid[startRow][startCol];
	if(originalColor == color)
		return;

	queue<pair<int, int> > cellQueue;
	cellQueue.push(pair<int, int> (startRow, startCol) );
	colorGrid[startRow][startCol] = color;

	int nextRow, nextCol, curRow, curCol;

	while(!cellQueue.empty())
	{
		pair<int, int> & curCell = cellQueue.front();
		cellQueue.pop();
		curRow = curCell.first;
		curCol = curCell.second;

		for(int direction = 0; direction < NUM_DIRECTION; direction++)
		{
			nextRow = curRow + rowOffset[direction];
			nextCol = curCol + colOffset[direction];
			if(isValidCell(nextRow, nextCol, numRow, numCol) && colorGrid[nextRow][nextCol] == originalColor)
			{
				colorGrid[nextRow][nextCol] = color;
				cellQueue.push(pair<int, int> (nextRow, nextCol) );
			}
		}
	}
}

bool isValidCell(int row, int col, int numRow, int numCol)
{
	if(row < 0 || col < 0 || row >= numRow || col >= numCol)
		return false;
	return true;
}

void writePicture(char gridColor[][MAX_SIZE + 1], int numRow, int numCol, char name[])
{
	int row;

	for(row = 0; row < numRow; row++)
		gridColor[row][numCol] = '\0';

	printf("%s\n", name);
	for(row = 0; row < numRow; row++)
		printf("%s\n", gridColor[row]);
}
