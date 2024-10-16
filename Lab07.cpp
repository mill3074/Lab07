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
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle Roof;
	Roof.setSize(Vector2f(800, 20));
	Roof.setCenter(Vector2f(400, 0));
	Roof.setStatic(true);
	world.AddPhysicsBody(Roof);

	PhysicsRectangle Wallr;
	Wallr.setSize(Vector2f(30, 600));
	Wallr.setCenter(Vector2f(800, 300));
	Wallr.setStatic(true);
	world.AddPhysicsBody(Wallr);

	PhysicsRectangle WallL;
	WallL.setSize(Vector2f(30, 600));
	WallL.setCenter(Vector2f(0, 300));
	WallL.setStatic(true);
	world.AddPhysicsBody(WallL);

	PhysicsRectangle Target;
	Target.setSize(Vector2f(50, 50));
	Target.setCenter(Vector2f(400, 300));
	Target.setFillColor(Color(255, 0, 0));
	Target.setRotation(10);
	Target.setStatic(true);
	world.AddPhysicsBody(Target);
	Target.

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;

		//int bangCount(0);
			//floor.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
			//cout << "thud " << bangCount << endl;
			//bangCount++;

		//if (bangCount == 3) {
			//cout << "okay" << endl;
		//}
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
		world.VisualizeAllBounds(window);
		window.display();

	}
}
