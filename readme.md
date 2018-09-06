# OpenGL Practise

This is a practise of OpenGL. It is written several years ago as a course project. Hope it would be helpful to someone.
<br />

### Results Display

The design of car model is shown as: 

![design car](./imgs/design.gif)


The model with texture is shown as: <br />
![texture car](./imgs/car.gif)

### Usage

If you are using Ubuntu, the installation of OpenGL would be super easy:

- sudo apt-get install libgl1-mesa-dev
- sudo apt install libglu1-mesa-dev
- sudo apt install freeglut3-dev

Then you can use the following order to compile program:

- g++ -o design car_design.cpp -lGL -lGLU -lglut
- g++ -o carTex texture_car.cpp -lGL -lGLU -lglut

### Key Description

You can use keyboard to control the movement of model. 
- 'f' : move the wheel
- 's', 'w' : rotate the model
- 'z', 'Z', 'x', 'X' : zoom in/out the model
- 'l' : open/close left door
- 'r' : open/close right door
- 'y', 'Y' : change the view at vertical plane
