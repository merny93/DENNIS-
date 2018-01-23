/*
  Calibration:
    The two potential colors are defined as being either 1 or 2.
    Calibration will happen by placing a ball of the first color in the left dispenser and a ball of the second color in the second.

  Picking the correct subtower when sorting by color:
    Since the left bucket color (number) will always be equal to the tower (number),
    we can simplify picking the correct side by comparing the two numbers.

  Main loop:
    The robot will begin by running initialize. After each task (including initialize),
    the robot will wait for some sort of input the user to know to begin the next task.
    Each task will be contained in its own function.

  Conventions:
    Left tower/dispenser will be labeled as '1' and right tower/dispenser will be '2'.
*/

/*
TODO:
1. Implement motor controls
2. Implement sensor controls
3. Finalize logic for tasks
*/

void initialize();
int getLeft();
int getRight();
int getColor();
void goToTower(int tower);
int pickSubTower(int tower, int color);
void goToSubTower(int subTower);
void releaseBall(int dispenser);

void task1();
void task2();
void task3();
void task4();
void task5();

// Defines which task the robot is currently working on, where 0 represents the initialize state
int currTask = 0;

// Margin of error for the infrared sensors
int epsilon;

int main()
{
  while(!complete)
  {
    switch(currTask)
    {
      case 1 :
        task1();
        break;
      case 2 :
        task2();
        break;
      case 3 :
        task3();
        break;
      case 4 :
        task4();
        break;
      case 5 :
        task5();
        break;
      default :
        initialize();
    }
    currTask++;
    pause_till_next;
  }

  return 0;
}

// Sets the inital calibration of the 2 colors.
void initialize()
{
  color1 = getLeft();
  color2 = getRight();
  return;
}

// Get the infrared reading of the sensor in the left dispenser
int getLeft()
{
  return leftSensorOut();
}

// Get the infrared reading of the sensor in the right dispenser
int getRight()
{
  return rightSensorOut();
}

// Get's the reading from each sensor and checks it against the saved value for the color +- some epsilon
bool getColor(int side)
{
  if (side == 1)
      if (abs(getLeft() - color1) < epsilon)
        return color1;
      else if (abs(getLeft() - color2) < epsilon)
        return color2;
      else
        return 0;
  else if (side == 2)
      if (abs(getLeft() - color1) < epsilon)
        return color1;
      else if (abs(getLeft() - color2) < epsilon)
        return color2;
      else
        return 0;
}

// Allow a single ball to leave the specified dispenser
void releaseBall(dispenser)
{

  return;
}

// Controls the central teeter-totter motor to control which tower the ball will go into.
void goToTower(tower)
{
  if (tower == 1)
    rotateMotor(counterclockwise);
  else if (tower == 2)
    rotateMotor(clockwise);
}

// Decides which tower the ball should go to based on its color.
int pickSubTower(tower, color)
{
  if (tower == color)
  {
    subTower = left;
  }
  else
  {
    subTower = right;
  }

  return subTower;
}

// Controls motor to direct balls into the correct bucket (subtower)
void goToSubTower(subTower)
{
  if (subTower == "left")
    rotateTeeterMotor(counterclockwise);
  else if (subTower == "right")
    rotateTeeterMotor(clockwise);

}

// Main logic for task 1
void task1()
{
  releaseBall(1);
  goToTower(1);

  return;
}

// Main logic for task 2
void task2()
{
  releaseBall(1);
  goToTower(1);

  return;
}

// Main logic for task 3
void task3()
{
  for (i = 0; i < 10; i++)
  {
    if (getColor(1) != 0)
      releaseBall(1);
    else if (getColor(2) != 0)
      releaseBall(2);
  }
  return;
}

// Main logic for task 4
void task4()
{
  return;
}

// Main logic for task 5
void task5()
{


  complete = true;
  return;
}
