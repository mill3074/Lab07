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
	ball.setCenter(Vector2f(400, 200));
	ball.setRadius(20);
	ball.setVelocity(Vector2f(0.5,0.5));
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle Roof;
	Roof.setSize(Vector2f(800, 20));
	Roof.setCenter(Vector2f(400, 10));
	Roof.setStatic(true);
	world.AddPhysicsBody(Roof);

	PhysicsRectangle Wallr;
	Wallr.setSize(Vector2f(30, 550));
	Wallr.setCenter(Vector2f(800, 300));
	Wallr.setStatic(true);
	world.AddPhysicsBody(Wallr);

	PhysicsRectangle WallL;
	WallL.setSize(Vector2f(30, 550));
	WallL.setCenter(Vector2f(0, 300));
	WallL.setStatic(true);
	world.AddPhysicsBody(WallL);

	PhysicsRectangle Target;
	Target.setSize(Vector2f(75, 50));
	Target.setCenter(Vector2f(400, 300));
	Target.setFillColor(Color(255, 0, 0));
	Target.setStatic(true);
	world.AddPhysicsBody(Target);

	int thudCount(1);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	Wallr.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	int bangCount(0);
	Target.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		bangCount++;
		cout << "bang " << bangCount << endl;
		

		if (bangCount == 3) {
			cout << "!!!!" << endl;
			exit(0);
		}
	};




	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MilliS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(Wallr);
		window.draw(WallL);
		window.draw(Roof);
		window.draw(Target);
		window.display();

	}
}
