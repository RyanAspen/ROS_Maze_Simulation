#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include <string>


const string TEMP_PATH1 = "gazebo/template1.txt";
const string TEMP_PATH2 = "gazebo/template2.txt";
const string BOX_PATH1 = "gazebo/box1.txt";
const string BOX_PATH2 = "gazebo/box2.txt";
const string COMPLETE_GAZEBO_PATH = "gazebo/maze.sdf";
const string GRID_PATH = "gazebo/grid.txt";

int box_num = 1;
const int MIN_X = 1;
const int MIN_Y = 1;
int rows = 0;
int columns = 0;
bool grid[1000] = {};

string read_file(string path)
{
  ifstream file(path);
  if (!file.is_open())
  {
    cerr << "Failed to open " << path << endl;
    exit(1);
  }
  string fileContent((istreambuf_iterator<char>(file)), 
                       istreambuf_iterator<char>());
  file.close();
  return fileContent;
}

void create_grid()
{
  string contents = read_file(GRID_PATH);
  stringstream ss(contents);
  string line;
  int j = 0;
  rows = 0;
  while (!ss.eof())
  {
    getline(ss, line, '\n');
    rows++;
    if (columns < line.length())
    {
      columns = line.length();
    }
    cout << "Columns = " << columns << endl;
    for (int i = 0; i < columns; i++)
    {
      cout << line[i];
      if (line[i] != '0')
      {
	cout << " True" << endl;
	grid[j] = true;
      }
      cout << endl;
      j++;
    }
    cout << j << endl;
  }
}

string create_box(int x, int y)
{
  float posX = x + 0.5;
  float posY = y + 0.5;
  string box_string = "\t<model name=\"box" + to_string(box_num) + "\">\n\t  <pose> " + to_string(posX) +  " " + to_string(posY) + " " + read_file(BOX_PATH2);
  box_num++;
  return box_string;
}

int main()
{
  string gazebo_text = read_file(TEMP_PATH1);
  create_grid();
  cout << "End of grid creation, rows = " << rows << ", columns = " << columns << endl;
  for (int y = 0; y < rows; y++)
  {
    for (int x = 0; x < columns; x++)
    {
      int j = y*columns + x;
      cout << grid[j];
      if (grid[j])
      {
	cout << " True";
	gazebo_text.append("\n" + create_box(x + MIN_X, y + MIN_Y));
      }
      cout << endl;
    }
  }
  gazebo_text.append("\n" + read_file(TEMP_PATH2));
  ofstream gazebo_file;
  gazebo_file.open(COMPLETE_GAZEBO_PATH);
  gazebo_file << gazebo_text;
  gazebo_file.close();
  cout << "Finished generating Gazebo file" << endl;
  return 0;
}
