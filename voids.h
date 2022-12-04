#pragma once
#include<list>
#include"player.h"

class Boids
{
private:

	int width = 100;
	int height = 100;

	int numBoids = 100;//ボイドの数
	int visualRange = 70;//視野

	XMINT2 pos;



	std::list<Boids> boids;

	void initBoids();

	void distance(Boids a,Boids b);

	void nClosestBoids(Boids n);

	void sizeCanvas();

	void keepWithBounds(Boids);

	void avoidOthers(Boids);

	void mathVelocity(Boids);

	void drawBoids(Boids boid);

	void animationLoop();

};