#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

#define SIZE 9

class Cell
{
public:
	int value;
	vector<int> unused;
	vector<int> used;
	Cell()
	{
		reset();
	}
	void reset()
	{
		value = 0;
		unused.clear();
		used.clear();
		for (int i = 1; i <= SIZE; i++)
			unused.push_back(i);
	}
};

class Sudoku
{
	Cell grid[SIZE][SIZE];
	int row, column, position;
public:
	void create()
	{
		row = column = position = 0;
		setValue();
		if (position == SIZE * SIZE)
		{
			for (int r = 0; r < SIZE; r++)
			{
				for (int c = 0; c < SIZE; c++)
				{
					grid[r][c].unused.clear();
					grid[r][c].used.clear();
				}
			}
			int count = SIZE * SIZE;
			int size = sqrt(SIZE);
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					for (int k = 0; k < size * 2 - 1; k++)
					{
						while (true)
						{
							int x = rand() % size;
							int y = rand() % size;
							if (grid[i * size + x][j * size + y].value != 0)
							{
								grid[i * size + x][j * size + y].value = 0;
								count--;
								break;
							}
						}
					}
				}
			}
			while (count > 35)
			{
				while (true)
				{
					position = rand() % (SIZE * SIZE);
					row = position / SIZE;
					column = position % SIZE;
					if (grid[row][column].value != 0)
					{
						grid[row][column].value = 0;
						break;
					}
				}
				count--;
			}
			display();
		}
	}
	void setValue()
	{
		if (0 <= position && position < SIZE * SIZE)
		{
			if (grid[row][column].unused.empty())
			{
				grid[row][column].reset();
				position--;
			}
			else
			{
				vector<int> temp;
				int index;
				while (!grid[row][column].unused.empty())
				{
					index = rand() % grid[row][column].unused.size();
					if (inRow(row, column, index) && inColumn(row, column, index) && inBox(row, column, index))
						break;
					temp.push_back(grid[row][column].unused[index]);
					grid[row][column].unused.erase(grid[row][column].unused.begin() + index);
				}
				if (grid[row][column].unused.empty())
				{
					grid[row][column].reset();
					position--;
				}
				else
				{
					while (!temp.empty())
					{
						grid[row][column].unused.push_back(temp.back());
						temp.pop_back();
					}
					grid[row][column].value = grid[row][column].unused[index];
					grid[row][column].used.push_back(grid[row][column].unused[index]);
					grid[row][column].unused.erase(grid[row][column].unused.begin() + index);
					position++;
				}
			}
			if (0 <= position && position < SIZE * SIZE)
			{
				row = position / SIZE;
				column = position % SIZE;
				setValue();
			}
		}
	}
	bool inRow(int r, int c, int index)
	{
		for (int i = 0; i < SIZE; i++)
			if (grid[r][i].value == grid[r][c].unused[index])
				return false;
		return true;
	}
	bool inColumn(int r, int c, int index)
	{
		for (int i = 0; i < SIZE; i++)
			if (grid[i][c].value == grid[r][c].unused[index])
				return false;
		return true;
	}
	bool inBox(int r, int c, int index)
	{
		int size = sqrt(SIZE);
		int i = (r / size) * size;
		int j = (c / size) * size;
		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++)
				if (grid[i + x][j + y].value == grid[r][c].unused[index])
					return false;
		return true;
	}

	void display()
	{
		cout << "  ";
		for (int c = 0; c < SIZE; c++)
			cout << "  " << c + 1 << " ";
		cout << " \n  ";
		for (int c = 0; c < SIZE; c++)
			cout << "+---";
		cout << "+\n";
		for (int r = 0; r < SIZE; r++)
		{
			cout << r + 1 << " ";
			for (int c = 0; c < SIZE; c++)
			{
				if (grid[r][c].value != 0)
					cout << "| " << grid[r][c].value << " ";
				else cout << "|   ";
			}
			cout << "|\n  ";
			for (int c = 0; c < SIZE; c++)
				cout << "+---";
			cout << "+\n";
		}
	}
};

int main()
{
	srand(time(0));
	Sudoku game;
	game.create();
	return 0;
}