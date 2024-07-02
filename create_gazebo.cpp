#include <iostream>
#include <fstream>

using namespace std;

#include <string>


const string TEMP_PATH1 = "gazebo/template1.txt";
const string TEMP_PATH2 = "gazebo/template2.txt";
const string BOX_PATH1 = "gazebo/box1.txt";
const string BOX_PATH2 = "gazebo/box2.txt";
const string COMPLETE_GAZEBO_PATH = "gazebo/maze.sdf";

int box_num = 1;
const int MIN_X = 1;
const int MIN_Y = 1;
const int LENGTH_X = 4;
const int LENGTH_Y = 4;
const bool grid[][LENGTH_X] = {
  {true, false, false, true},
  {true, false, false, true},
  {true, false, true, true},
  {true, true, true, true}
};

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
  for (int y = 0; y < LENGTH_Y; y++)
  {
    for (int x = 0; x < LENGTH_X; x++)
    {
      if (grid[y][x])
      {
	gazebo_text.append("\n" + create_box(x + MIN_X, y + MIN_Y));
      }
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
