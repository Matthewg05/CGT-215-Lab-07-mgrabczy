//including the libraries to add the physics and draw the shapes
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(100, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0.75, -0.5));
	//creating the square in the center
	PhysicsRectangle square;
	square.setSize(Vector2f(100, 100));
	square.setCenter(Vector2f(400, 300));
	square.setStatic(true);
	world.AddPhysicsBody(square);
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	// Create an OnCollision callback for the floor and the ball coliding
	int thudCount(1);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	//Create an OnCollision callback for the square and the ball coliding
	int bangCount(1);
	square.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		};
	//creating the walls and ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	PhysicsRectangle left;
	left.setSize(Vector2f(20, 580));
	left.setCenter(Vector2f(10, 300));
	left.setStatic(true);
	world.AddPhysicsBody(left);
	PhysicsRectangle right;
	right.setSize(Vector2f(20, 580));
	right.setCenter(Vector2f(790, 300));
	right.setStatic(true);
	world.AddPhysicsBody(right);
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		//sets the background color for the window
		window.clear(Color(0, 0, 0));
		//draws the boxes and the ball on the window
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(left);
		window.draw(right);
		window.draw(square);
		window.display();
		//closes the window after the ball hits the center object 3 times
		if (bangCount == 4) {
			window.close();
			break;
		}
	}
}
